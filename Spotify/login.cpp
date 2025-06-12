    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <sstream>
    #include <algorithm>
    #include <limits>
    #include <map>
    #include <thread>
    #include <mutex>
    #include <atomic>
    #include "AdministradorCompartirCancion.h"
    #include "AdministradorEstadisticaPista.h"
    #include "AdministradorDatosValoracion.h"
    #include "AdministradorPodcast.h"
    #include "AdministradorCancion.h"
    #include "Cancion.h"
    #include "Podcast.h"
    #include "Historial.h"
    #include "EstadisticaPista.h"
    #include "EnlaceFavorito.h"
    #include "DatosValoracion.h"
    #include "CompartirCancion.h"
    #include "Login.h"
    #include "Utilidades.h"
    #include "Usuario.h"
    #include <iostream>
#include <memory>    
 
    using namespace std;


    void registrarse(vector<Usuario>& usuarios) {
        limpiarPantalla();
        dibujarCaja({ "REGISTRARSE" });
        string n, c, p;
        cout << "Nombre: ";   getline(cin, n);
        cout << "Correo: ";   getline(cin, c);
        cout << "Contrasena: "; getline(cin, p);
        usuarios.emplace_back(n, c, p);
        cout << "-> Usuario registrado!\n";
        pausar();
    }

    void iniciarSesion(vector<Usuario>& usuarios) {
        limpiarPantalla();
        dibujarCaja({ "INICIAR SESION" });
        string correo, pass;
        cout << "Correo: ";     getline(cin, correo);
        cout << "Contrasena: "; getline(cin, pass);

        auto it = find_if(usuarios.begin(), usuarios.end(),
            [&](auto& u) { return u.obtenerCorreo() == correo; });
        if (it == usuarios.end() || it->obtenerContrasena() != pass) {
            cout << "-> Credenciales inválidas!\n";
            pausar();
            return;
        }

        Usuario& usuarioLogueado = *it;

        auto gestorCompartir = make_unique<CompartirCancion>();
        auto gestorValoracion = make_unique<DatosValoracion>();
        auto gestorEnlaces = make_unique<EnlaceFavorito>();
        auto estadisticas = make_unique<EstadisticaPista>();
        auto historial = make_unique<Historial>();
        auto gestorPodcasts = make_unique<AdministradorPodcast>();

        auto progresoCanciones = make_unique<map<string, int>>();
        auto mtxTiempo = make_unique<mutex>();
        auto enReproduccion = make_unique<atomic<bool>>(false);
        auto detenerHilo = make_unique<atomic<bool>>(false);

        bool sesionActiva = true;
        int  opcion;



        while (sesionActiva) {
            limpiarPantalla();
            dibujarCaja({
                "SESION: " + usuarioLogueado.obtenerNombre(),
                "1. Crear Playlist",
                "2. Eliminar Playlist",
                "3. Listar Playlists",
                "4. Agregar Cancion",
                "5. Eliminar Cancion",
                "6. Listar Canciones",
                "7. Compartir Cancion",
                "8. Ver Compartidos",
                "9. Valorar Cancion",
                "10. Ver Valoraciones",
                "11. Agregar Enlace Favorito",
                "12. Ver Enlaces",
                "13. Eliminar Enlace",
                "14. Reproducir Cancion",
                "15. Ver Estadisticas",
                "16. Historial General",
                "17. Registrar Podcast",
                "18. Ver Podcasts",
                "0. Cerrar Sesion",
                });
            cout << "Seleccione opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
            case 1: {
                limpiarPantalla();
                dibujarCaja({ "CREAR PLAYLIST" });
                string nombreP, descP;
                cout << "Nombre Playlist: "; getline(cin, nombreP);
                cout << "Descripcion    : "; getline(cin, descP);
                usuarioLogueado.crearListaReproduccion(ListaReproduccion(nombreP, descP));
                cout << "-> Playlist creada!\n";
                historial->registrarEvento("Se creo la playlist: " + nombreP);
                pausar();
                break;
            }
            case 2: {
                limpiarPantalla();
                dibujarCaja({ "ELIMINAR PLAYLIST" });
                string nombreP;
                cout << "Nombre Playlist: "; getline(cin, nombreP);
                usuarioLogueado.eliminarListaReproduccion(nombreP);
                cout << "-> Eliminada si existia!\n";
                pausar();
                break;
            }
            case 3: {
                limpiarPantalla();
                dibujarCaja({ "TUS PLAYLISTS" });
                for (const auto& p : usuarioLogueado.obtenerListaReproduccion())
                    cout << "* " << p.obtenerNombre() << "\n";
                pausar();
                break;
            }
            case 4: {
                limpiarPantalla();
                dibujarCaja({ "AGREGAR CANCION" });

                string nombreP, t, art, alb;
                int dur;
                cout << "Playlist      : "; getline(cin, nombreP);
                cout << "Titulo Cancion: "; getline(cin, t);
                cout << "Artista       : "; getline(cin, art);
                cout << "Album         : "; getline(cin, alb);
                cout << "Duracion (s)  : "; cin >> dur; cin.ignore();

                bool encontrada = false;

                for (auto& p : usuarioLogueado.obtenerListaReproduccion()) {
                    if (p.obtenerNombre() == nombreP) {
                        p.agregarCancion(Cancion(t, art, alb, dur));
                        cout << "-> Cancion agregada!\n";
                        historial->registrarEvento("Se agrego la cancion '" + t + "' a la playlist: " + nombreP);
                        encontrada = true;
                        break;
                    }
                }

                if (!encontrada) {
                    cout << "-> ERROR: La playlist '" << nombreP << "' no existe.\n";
                }

                pausar();
                break;
            }

            case 5: {
                limpiarPantalla();
                dibujarCaja({ "ELIMINAR CANCION" });
                string nombreP, t;
                cout << "Playlist      : "; getline(cin, nombreP);
                cout << "Titulo Cancion: "; getline(cin, t);
                for (auto& p : usuarioLogueado.obtenerListaReproduccion())
                    if (p.obtenerNombre() == nombreP)
                        p.eliminarCancion(t);
                cout << "-> Eliminada si existia!\n";
                pausar();
                break;
            }
            case 6: {
                limpiarPantalla();
                dibujarCaja({ "LISTAR CANCIONES" });
                string nombreP;
                cout << "Playlist: "; getline(cin, nombreP);
                for (const auto& p : usuarioLogueado.obtenerListaReproduccion())
                    if (p.obtenerNombre() == nombreP)
                        p.listarCanciones();
                pausar();
                break;
            }
           

        

            case 7: {  // Compartir Cancion
                limpiarPantalla();
                dibujarCaja({ "COMPARTIR CANCION" });
                string titulo;
                cout << "Titulo de la cancion: "; getline(cin, titulo);
                string link = gestorCompartir->compartir(titulo);
                if (!link.empty())
                    cout << "-> Link generado: " << link << "\n";
                else
                    cout << "-> Limite de compartidos alcanzado!\n";
                historial->registrarEvento("Se compartio la cancion: " + titulo);

                pausar();
                break;
            }
            case 8: { // Ver Compartidos
                limpiarPantalla();
                dibujarCaja({ "CANCIONES COMPARTIDAS" });
                gestorCompartir->listarCompartidos();
                pausar();
                break;
            }
            case 9: { // VALORAR CANCIÓN
                limpiarPantalla();
                dibujarCaja({ "VALORAR CANCION" });
                string titulo;
                int valor;
                cout << "Titulo de la cancion: "; getline(cin, titulo);
                cout << "Valor (1-5): "; cin >> valor; cin.ignore();

                if (gestorValoracion->agregarValoracion(titulo, valor))
                    cout << "-> Valoracion guardada!\n";
                else
                    cout << "-> Valor no valido o capacidad llena\n";
                historial->registrarEvento("Se valoro la cancion '" + titulo + "' con: " + to_string(valor));

                pausar();
                break;
            }
            case 10: { // VER VALORACIONES
                limpiarPantalla();
                dibujarCaja({ "VALORACIONES PROMEDIO" });
                gestorValoracion->listarPromedios();
                pausar();
                break;
            }
            case 11: {
                limpiarPantalla();
                dibujarCaja({ "AGREGAR ENLACE FAVORITO" });
                string titulo, url;
                cout << "Titulo de la cancion: "; getline(cin, titulo);
                cout << "URL externa(numero de 3 digitos):https://open.spotify.com/intl-es/track/"; getline(cin, url);
                if (gestorEnlaces->agregarEnlace(titulo, url))
                    cout << "-> Enlace guardado!\n";
                else
                    cout << "-> Limite alcanzado!\n";
                pausar();
                break;
            }
            case 12: {
                limpiarPantalla();
                dibujarCaja({ "TUS ENLACES FAVORITOS" });
                gestorEnlaces->listarFavoritos();
                pausar();
                break;
            }
            case 13: {
                limpiarPantalla();
                dibujarCaja({ "ELIMINAR ENLACE FAVORITO" });
                gestorEnlaces->listarFavoritos();
                cout << "Indice a eliminar: ";
                int idx; std::cin >> idx; std::cin.ignore();
                if (gestorEnlaces->eliminarEnlace(idx - 1))
                    cout << "-> Enlace eliminado!\n";
                else
                    cout << "-> Indice no valido\n";
                pausar();
                break;
            }
            case 14: { // REPRODUCTOR ADAPTADO
                limpiarPantalla();
                dibujarCaja({ "REPRODUCTOR DE CANCIONES O PODCAST" });

                string titulo;
                cout << "Titulo de la cancion o podcast: ";
                getline(cin, titulo);

                // Buscar duración
                int DURACION_TOTAL = -1;

                // Buscar en canciones del usuario
                for (const auto& playlist : usuarioLogueado.obtenerListaReproduccion()) {
                    const auto& canciones = playlist.obtenerCanciones();
                    canciones.porCada([&](const Cancion& c) {
                        if (c.obtenerTitulo() == titulo) {
                            DURACION_TOTAL = c.obtenerDuracion();
                        }
                        });
                    if (DURACION_TOTAL != -1) break;
                }

                // Buscar en podcasts
                if (DURACION_TOTAL == -1) {
                    const Podcast* lista = gestorPodcasts->obtenerTodos();
                    int cantidad = gestorPodcasts->obtenerCantidad();
                    for (int i = 0; i < cantidad; ++i) {
                        if (lista[i].obtenerTitulo() == titulo) {
                            DURACION_TOTAL = lista[i].obtenerDuracion();
                            break;
                        }
                    }
                }

                // Si no se encuentra, mostrar error
                if (DURACION_TOTAL == -1) {
                    cout << ">> ERROR: Titulo no encontrado en canciones ni podcasts.\n";
                    pausar();
                    break;
                }

                int& segundos = (*progresoCanciones)[titulo]; // Progreso

                *enReproduccion = false;
                *detenerHilo = false;

                thread hiloCronometro([&]() {
                    while (!(*detenerHilo)) {
                        if (*enReproduccion && segundos < DURACION_TOTAL) {
                            this_thread::sleep_for(chrono::seconds(1));
                            {
                                lock_guard<mutex> lock(*mtxTiempo);
                                ++segundos;
                                if (segundos >= DURACION_TOTAL) {
                                    *enReproduccion = false;
                                    cout << "\n>> Reproduccion finalizada.\n";
                                    estadisticas->registrarReproduccion(titulo);
                                }
                            }
                        }
                        else {
                            this_thread::sleep_for(chrono::milliseconds(200));
                        }
                    }
                    });

                thread hiloVisual([&]() {
                    while (!(*detenerHilo)) {
                        this_thread::sleep_for(chrono::milliseconds(500));
                        lock_guard<mutex> lock(*mtxTiempo);
                        int mins = DURACION_TOTAL / 60;
                        int secs = DURACION_TOTAL % 60;
                        cout << "\r[ " << (segundos / 60) << "m " << (segundos % 60)
                            << "s / " << mins << "m " << secs << "s ] ";
                        cout.flush();
                    }
                    });

                bool salir = false;
                while (!salir) {
                    cout << "\n\nSubopciones: 1.Reproducir  2.Pausar  3.Salir\n";
                    cout << "Ingrese opcion: ";
                    int sub;
                    cin >> sub;
                    cin.ignore();

                    switch (sub) {
                    case 1:
                        if (segundos >= DURACION_TOTAL) {
                            cout << ">> Ya terminó. Reinicia manualmente (resetea el contador).\n";
                        }
                        else {
                            *enReproduccion = true;
                            cout << ">> Reproduciendo...\n";
                        }
                        break;
                    case 2:
                        *enReproduccion = false;
                        cout << ">> Pausado.\n";
                        break;
                    case 3:
                        *detenerHilo = true;
                        *enReproduccion = false;
                        salir = true;
                        break;
                    default:
                        cout << ">> Opcion invalida.\n";
                    }
                }

                if (hiloCronometro.joinable()) hiloCronometro.join();
                if (hiloVisual.joinable()) hiloVisual.join();

                historial->registrarEvento("Reproduccion iniciada de: " + titulo);
                cout << ">> Saliendo del reproductor...\n";
                pausar();
                break;
            }



            case 15: {
                limpiarPantalla();
                dibujarCaja({ "ESTADISTICAS DE REPRODUCCION" });
                estadisticas->mostrarEstadisticas();
                pausar();
                break;
            }
            case 16: {
                limpiarPantalla();
                dibujarCaja({ "HISTORIAL GENERAL DE ACTIVIDADES" });
                historial->mostrarHistorial();
                pausar();
                break;
            }

            case 17: {
                limpiarPantalla();
                dibujarCaja({ "REGISTRAR PODCAST" });
                string titulo, creador;
                int duracion;
                cout << "Titulo del podcast : "; getline(cin, titulo);
                cout << "Creador del podcast: "; getline(cin, creador);
                cout << "Duracion (segundos): "; cin >> duracion; cin.ignore();
                if (gestorPodcasts->registrarPodcast(titulo, creador, duracion))
                    cout << "-> Podcast registrado!\n";
                else
                    cout << "-> Limite de podcasts alcanzado!\n";
                pausar();
                break;
            }
            case 18: {
                limpiarPantalla();
                dibujarCaja({ "LISTA DE PODCASTS" });
                gestorPodcasts->listarPodcasts();
                pausar();
                break;
            }
            case 0:
                sesionActiva = false;
                break;

            default:
                cout << "Opcion no valida!\n";
                pausar();
            }
        }
    }

    void cargarUsuarios(vector<Usuario>& usuarios) {
        ifstream f("usuarios.txt"); if (!f) return;
        string linea;
        while (getline(f, linea)) {
            stringstream ss(linea);
            string n, c, p;
            if (getline(ss, n, ',') && getline(ss, c, ',') && getline(ss, p, ',')) {
                usuarios.emplace_back(n, c, p);
            }
        }
    }

    void guardarUsuarios(const vector<Usuario>& usuarios) {
        ofstream f("usuarios.txt"); if (!f) return;
        for (auto& u : usuarios)
            f << u.obtenerNombre() << "," << u.obtenerCorreo() << "," << u.obtenerContrasena() << "\n";
    }
