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
#include "AdministradorCompartirCancion.h"
#include "AdministradorPodcast.h"
#include "AdministradorCancion.h"
#include "Cancion.h"
#include "Podcast.h"
#include "Historial.h"
#include "EstadisticaPista.h"
#include "EnlaceFavorito.h"
#include "DatosValoracion.h"
#include "DatosComentario.h"
#include "CompartirCancion.h"
#include "Login.h"
#include "Utilidades.h"
#include "Usuario.h"

void registrarse(vector<Usuario>& usuarios) {
    limpiarPantalla();
    dibujarCaja({ "REGISTRARSE" });
    string nombreUsuario, correoElectronico, contrasenaUsuario;
    cout << "Nombre: "; getline(cin, nombreUsuario);
    cout << "Correo: "; getline(cin, correoElectronico);
    cout << "Contrasena: "; getline(cin, contrasenaUsuario);
    usuarios.emplace_back(nombreUsuario, correoElectronico, contrasenaUsuario);
    cout << "-> Usuario registrado!\n";
    pausar();
}

void iniciarSesion(vector<Usuario> usuarios) {
    limpiarPantalla();
    dibujarCaja({ "INICIAR SESION" });
    string correoElectronico, contrasenaUsuario;
    cout << "Correo: "; getline(cin, correoElectronico);
    cout << "Contrasena: "; getline(cin, contrasenaUsuario);
    auto it = find_if(
        usuarios.begin(), usuarios.end(),
        [&](const Usuario& u) { return u.obtenerCorreo() == correoElectronico; }
    );
    if (it == usuarios.end()) {
        cout << "-> Usuario no existe!\n";
        pausar();
        return;
    }
    if (it->obtenerContrasena() != contrasenaUsuario) {
        cout << "-> Contrasena incorrecta!\n";
        pausar();
        return;
    }

    Usuario& usuarioLogueado = *it;
    DatosComentario   gestorComentarios;
    CompartirCancion  gestorCompartir;
    DatosValoracion gestorValoracion;
    EnlaceFavorito gestorEnlaces;
    EstadisticaPista estadisticas;
    map<string, int> progresoCanciones;
    mutex mtxTiempo;
    atomic<bool> enReproduccion(false);
    atomic<bool> detenerHilo(false);
    Historial historial;
    AdministradorPodcast gestorPodcasts;



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
            "7. Agregar Comentario",
            "8. Ver Comentarios",
            "9. Eliminar Comentario",
            "10. Compartir Cancion",
            "11. Ver Compartidos",
            "12. Valorar Cancion",
            "13. Ver Valoraciones",
            "14. Agregar Enlace Favorito",
            "15. Ver Enlaces",
            "16. Eliminar Enlace",
            "17. Reproducir Cancion",
            "18. Ver Estadisticas",
            "19. Historial General",
            "20. Registrar Podcast",
            "21. Ver Podcasts",
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
            historial.registrarEvento("Se creo la playlist: " + nombreP);
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
                    historial.registrarEvento("Se agrego la cancion '" + t + "' a la playlist: " + nombreP);
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
        case 0:
            sesionActiva = false;
            break;

        case 7: {  // Agregar Comentario
            limpiarPantalla();
            dibujarCaja({ "AGREGAR COMENTARIO" });
            string titulo, texto;
            cout << "Titulo (cancion/playlist): "; getline(cin, titulo);
            cout << "Comentario               : "; getline(cin, texto);
            if (gestorComentarios.agregarComentario(titulo, texto))
                cout << "-> Comentario anadido!\n";
            else
                cout << "-> Capacidad de comentarios llena!\n";
            pausar();
            break;
        }
        case 8:  // Ver Comentarios
            limpiarPantalla();
            dibujarCaja({ "LISTA DE COMENTARIOS" });
            gestorComentarios.listarComentarios();
            pausar();
            break;

        case 9: {  // Eliminar Comentario
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR COMENTARIO" });
            gestorComentarios.listarComentarios();
            cout << "Indice a eliminar (1-" << gestorComentarios.obtenerCantidad() << "): ";
            int idx; cin >> idx; cin.ignore();
            if (gestorComentarios.eliminarComentario(idx - 1))
                cout << "-> Comentario eliminado!\n";
            else
                cout << "-> Indice invalido!\n";
            pausar();
            break;
        }

        case 10: {  // Compartir Cancion
            limpiarPantalla();
            dibujarCaja({ "COMPARTIR CANCION" });
            string titulo;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            string link = gestorCompartir.compartir(titulo);
            if (!link.empty())
                cout << "-> Link generado: " << link << "\n";
            else
                cout << "-> Limite de compartidos alcanzado!\n";
            historial.registrarEvento("Se compartio la cancion: " + titulo);

            pausar();
            break;
        }
        case 11: { // Ver Compartidos
            limpiarPantalla();
            dibujarCaja({ "CANCIONES COMPARTIDAS" });
            gestorCompartir.listarCompartidos();
            pausar();
            break;
        }
        case 12: { // VALORAR CANCIÓN
            limpiarPantalla();
            dibujarCaja({ "VALORAR CANCION" });
            string titulo;
            int valor;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            cout << "Valor (1-5): "; cin >> valor; cin.ignore();

            if (gestorValoracion.agregarValoracion(titulo, valor))
                cout << "-> Valoracion guardada!\n";
            else
                cout << "-> Valor no valido o capacidad llena\n";
            historial.registrarEvento("Se valoro la cancion '" + titulo + "' con: " + to_string(valor));

            pausar();
            break;
        }
        case 13: { // VER VALORACIONES
            limpiarPantalla();
            dibujarCaja({ "VALORACIONES PROMEDIO" });
            gestorValoracion.listarPromedios();
            pausar();
            break;
        }
        case 14: {
            limpiarPantalla();
            dibujarCaja({ "AGREGAR ENLACE FAVORITO" });
            string titulo, url;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            cout << "URL externa(numero de 3 digitos):https://open.spotify.com/intl-es/track/"; getline(cin, url);
            if (gestorEnlaces.agregarEnlace(titulo, url))
                cout << "-> Enlace guardado!\n";
            else
                cout << "-> Limite alcanzado!\n";
            pausar();
            break;
        }
        case 15: {
            limpiarPantalla();
            dibujarCaja({ "TUS ENLACES FAVORITOS" });
            gestorEnlaces.listarFavoritos();
            pausar();
            break;
        }
        case 16: {
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR ENLACE FAVORITO" });
            gestorEnlaces.listarFavoritos();
            cout << "Indice a eliminar: ";
            int idx; std::cin >> idx; std::cin.ignore();
            if (gestorEnlaces.eliminarEnlace(idx - 1))
                cout << "-> Enlace eliminado!\n";
            else
                cout << "-> Indice no valido\n";
            pausar();
            break;
        }
        case 17: { // REPRODUCTOR AVANZADO MULTIHILO
            limpiarPantalla();
            dibujarCaja({ "REPRODUCTOR DE CANCIONES" });

            string titulo;
            cout << "Titulo de la cancion: ";
            getline(cin, titulo);

            const int DURACION_TOTAL = 150;
            int& segundos = progresoCanciones[titulo]; // Progreso por referencia

            enReproduccion = false;
            detenerHilo = false;

            // Hilo: simula la reproducción (1 seg por segundo)
            thread hiloCronometro([&]() {
                while (!detenerHilo) {
                    if (enReproduccion && segundos < DURACION_TOTAL) {
                        this_thread::sleep_for(chrono::seconds(1));
                        lock_guard<mutex> lock(mtxTiempo);
                        ++segundos;
                        if (segundos >= DURACION_TOTAL) {
                            enReproduccion = false;
                            cout << "\n>> Cancion finalizada.\n";
                            estadisticas.registrarReproduccion(titulo);
                        }
                    }
                    else {
                        this_thread::sleep_for(chrono::milliseconds(200));
                    }
                }
                });

            // Hilo: muestra tiempo actual cada segundo
            thread hiloVisual([&]() {
                while (!detenerHilo) {
                    this_thread::sleep_for(chrono::milliseconds(500));
                    lock_guard<mutex> lock(mtxTiempo);
                    cout << "\r[ " << (segundos / 60) << "m " << (segundos % 60) << "s / 2m 30s ] ";
                    cout.flush();
                }
                });

            // Submenú: acepta comandos sin bloquear reproducción
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
                        cout << ">> Ya termino. Reinicia manualmente.\n";
                    }
                    else {
                        enReproduccion = true;
                        cout << ">> Reproduciendo...\n";
                    }
                    break;
                case 2:
                    enReproduccion = false;
                    cout << ">> Pausado.\n";
                    break;
                case 3:
                    detenerHilo = true;
                    enReproduccion = false;
                    salir = true;
                    cout << ">> Saliendo del reproductor...\n";
                    break;
                default:
                    cout << "Opcion invalida.\n";
                }
            }
            // Esperar cierre de hilos
            if (hiloCronometro.joinable()) hiloCronometro.join();
            if (hiloVisual.joinable()) hiloVisual.join();
            historial.registrarEvento("Reproduccion iniciada de: " + titulo);
            break;
        }


        case 18: {
            limpiarPantalla();
            dibujarCaja({ "ESTADISTICAS DE REPRODUCCION" });
            estadisticas.mostrarEstadisticas();
            pausar();
            break;
        }
        case 19: {
            limpiarPantalla();
            dibujarCaja({ "HISTORIAL GENERAL DE ACTIVIDADES" });
            historial.mostrarHistorial();
            pausar();
            break;
        }

        case 20: {
            limpiarPantalla();
            dibujarCaja({ "REGISTRAR PODCAST" });
            string titulo, creador;
            int duracion;
            cout << "Titulo del podcast : "; getline(cin, titulo);
            cout << "Creador del podcast: "; getline(cin, creador);
            cout << "Duracion (segundos): "; cin >> duracion; cin.ignore();
            if (gestorPodcasts.registrarPodcast(titulo, creador, duracion))
                cout << "-> Podcast registrado!\n";
            else
                cout << "-> Limite de podcasts alcanzado!\n";
            pausar();
            break;
        }
        case 21: {
            limpiarPantalla();
            dibujarCaja({ "LISTA DE PODCASTS" });
            gestorPodcasts.listarPodcasts();
            pausar();
            break;
        }


        default:
            cout << "Opcion no valida!\n";
            pausar();
        }
    }
}

void cargarUsuarios(vector<Usuario>& usuarios) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, correo, contrasena;
        if (getline(ss, nombre, ',') &&
            getline(ss, correo, ',') &&
            getline(ss, contrasena, ','))
        {
            usuarios.emplace_back(nombre, correo, contrasena);
        }
    }
}

void guardarUsuarios(const vector<Usuario>& usuarios) {
    ofstream archivo("usuarios.txt");
    if (!archivo.is_open()) return;
    for (const auto& u : usuarios) {
        archivo << u.obtenerNombre() << ","
            << u.obtenerCorreo() << ","
            << u.obtenerContrasena() << "\n";
    }
}
