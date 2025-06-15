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
#include <functional>
#include <chrono>
#include "GuiaUsuario.h"
#include "AdministradorCompartirCancion.h"
#include "AdministradorDatosValoracion.h"
#include "AdministradorPodcast.h"
#include "AdministradorCancion.h"
#include "Cancion.h"
#include "Podcast.h"
#include "Historial.h"
#include "EnlaceFavorito.h"
#include "DatosValoracion.h"
#include "CompartirCancion.h"
#include "Login.h"
#include "Utilidades.h"
#include "Usuario.h"
#include <iostream>
#include <memory>    
#include <conio.h>



// Funcion para validar entrada de enteros
int leerEntero(const string& mensaje) {
    int valor;
    string entrada;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        // Verificar si la entrada esta vacia
        if (entrada.empty()) {
            cout << "ERROR: Ingrese correctamente el valor\n";
            continue;
        }

        // Verificar si todos los caracteres son digitos (permitir numeros negativos)
        bool esValido = true;
        size_t inicio = 0;

        // Permitir signo negativo al inicio
        if (entrada[0] == '-' || entrada[0] == '+') {
            inicio = 1;
            if (entrada.length() == 1) {
                esValido = false;
            }
        }

        // Verificar que el resto sean digitos
        for (size_t i = inicio; i < entrada.length(); i++) {
            if (!isdigit(entrada[i])) {
                esValido = false;
                break;
            }
        }

        if (esValido) {
            try {
                valor = stoi(entrada);
                break;
            }
            catch (const exception&) {
                cout << "ERROR: Ingrese correctamente el valor\n";
            }
        }
        else {
            cout << "ERROR: Ingrese correctamente el valor\n";
        }
    }

    return valor;
}

// Funcion para leer enteros con validacion de rango
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo) {
    int valor;

    while (true) {
        valor = leerEntero(mensaje);

        if (valor >= minimo && valor <= maximo) {
            break;
        }
        else {
            cout << "ERROR: El valor debe estar entre " << minimo << " y " << maximo << "\n";
        }
    }

    return valor;
}

// Implementacion de QuickSort para canciones
class QuickSortCanciones {
public:
    // Enum para diferentes criterios de ordenamiento
    enum CriterioOrdenamiento {
        POR_TITULO,
        POR_ARTISTA,
        POR_ALBUM,
        POR_DURACION
    };

private:
    static int particion(vector<Cancion>& canciones, int bajo, int alto, CriterioOrdenamiento criterio) {
        Cancion pivote = canciones[alto];
        int i = bajo - 1;

        for (int j = bajo; j <= alto - 1; j++) {
            if (compararCanciones(canciones[j], pivote, criterio)) {
                i++;
                swap(canciones[i], canciones[j]);
            }
        }
        swap(canciones[i + 1], canciones[alto]);
        return i + 1;
    }

    static void quickSortRecursivo(vector<Cancion>& canciones, int bajo, int alto, CriterioOrdenamiento criterio) {
        if (bajo < alto) {
            int pi = particion(canciones, bajo, alto, criterio);
            quickSortRecursivo(canciones, bajo, pi - 1, criterio);
            quickSortRecursivo(canciones, pi + 1, alto, criterio);
        }
    }

    static bool compararCanciones(const Cancion& a, const Cancion& b, CriterioOrdenamiento criterio) {
        switch (criterio) {
        case POR_TITULO:
            return a.obtenerTitulo() < b.obtenerTitulo();
        case POR_ARTISTA:
            return a.obtenerArtista() < b.obtenerArtista();
        case POR_ALBUM:
            return a.obtenerAlbum() < b.obtenerAlbum();
        case POR_DURACION:
            return a.obtenerDuracion() < b.obtenerDuracion();
        default:
            return a.obtenerTitulo() < b.obtenerTitulo();
        }
    }

public:
    static void ordenar(vector<Cancion>& canciones, CriterioOrdenamiento criterio = POR_TITULO) {
        if (canciones.size() <= 1) return;
        quickSortRecursivo(canciones, 0, canciones.size() - 1, criterio);
    }

    static string obtenerNombreCriterio(CriterioOrdenamiento criterio) {
        switch (criterio) {
        case POR_TITULO: return "Titulo";
        case POR_ARTISTA: return "Artista";
        case POR_ALBUM: return "Album";
        case POR_DURACION: return "Duracion";
        default: return "Titulo";
        }
    }
};

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

enum MenuOpcion { PLAYLIST, CANCIONES, VALORACIONES, ENLACES, PODCAST, AYUDA, SALIR };

vector<string> obtenerOpcionesSubmenu(MenuOpcion opcion) {
    vector<string> opciones;

    switch (opcion) {
    case PLAYLIST:
        opciones = {
            "Crear Playlist",
            "Eliminar Playlist",
            "Listar Playlists",
            "Volver"
        };
        break;
    case CANCIONES:
        opciones = {
            "Agregar Cancion",
            "Eliminar Cancion",
            "Listar Canciones",
            "Compartir Cancion",
            "Canciones Compartidos",
            "Ordenar Canciones",
            "Reproducir Cancion",
            "Volver"
        };
        break;
    case VALORACIONES:
        opciones = {
            "Valorar Formato",
            "Ver Valoraciones",
            "Volver"
        };
        break;
    case ENLACES:
        opciones = {
            "Agregar Enlace Favorito",
            "Ver Enlaces",
            "Eliminar Enlace",
            "Volver"
        };
        break;
    case PODCAST:
        opciones = {
            "Registrar Podcast",
            "Ver Podcasts",
            "Ordenar Podcasts(MergeSort)",
            "Volver"
        };
        break;
    case AYUDA:
        opciones = {
            "Guia del Usuario",
            "Historial General",
            "Volver"
        };
        break;
    }
     

    return opciones;
}

map<int, function<void()>> obtenerAccionesSubmenu(
    MenuOpcion opcion, 
    Usuario& usuarioLogueado,
    unique_ptr<Historial>& historial,
    bool& salir,
    unique_ptr<map<string, int>>& progresoCanciones,
    unique_ptr<mutex>& mtxTiempo,
    unique_ptr<atomic<bool>>& enReproduccion,
    unique_ptr<atomic<bool>>& detenerHilo,
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir
) {
    map<int, function<void()>> acciones;
    
   /* auto gestorCompartir = make_unique<CompartirCancion>();
    auto gestorValoracion = make_unique<DatosValoracion>();
    auto gestorEnlaces = make_unique<EnlaceFavorito>();
    auto estadisticas = make_unique<GuiaUsuario>();*/
    //auto gestorPodcasts = make_unique<AdministradorPodcast>();

    switch (opcion) {
        case PLAYLIST: {
            acciones[0] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "CREAR PLAYLIST" });
                string nombreP, descP;
                cout << "Nombre Playlist: "; getline(cin, nombreP);
                cout << "Descripcion    : "; getline(cin, descP);
                usuarioLogueado.crearListaReproduccion(ListaReproduccion(nombreP, descP));
                cout << "-> Playlist creada!\n";
                historial->registrarEvento("Se creo la playlist: " + nombreP);
                pausar();
                };

            acciones[1] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "ELIMINAR PLAYLIST" });
                string nombreP;
                cout << "Nombre Playlist: "; getline(cin, nombreP);
                usuarioLogueado.eliminarListaReproduccion(nombreP);
                cout << "-> Eliminada si existia!\n";
                pausar();
                };

            acciones[2] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "TUS PLAYLISTS" });
                for (const auto& p : usuarioLogueado.obtenerListaReproduccion())
                    cout << "* " << p.obtenerNombre() << "\n";
                pausar();
                };

            acciones[3] = [&]() {
                salir = true;
                };
            break;
        }
        case CANCIONES: {
            acciones[0] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "AGREGAR CANCION" });

                string nombreP, t, art, alb;
                int dur;
                cout << "Playlist      : "; getline(cin, nombreP);
                cout << "Titulo Cancion: "; getline(cin, t);
                cout << "Artista       : "; getline(cin, art);
                cout << "Album         : "; getline(cin, alb);
                dur = leerEnteroEnRango("Duracion (s)  : ", 1, 7200); // Entre 1 segundo y 2 horas

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
                };

            acciones[1] = [&]() {
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
                };

            acciones[2] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "LISTAR CANCIONES" });
                string nombreP;
                cout << "Playlist: "; getline(cin, nombreP);
                for (const auto& p : usuarioLogueado.obtenerListaReproduccion())
                    if (p.obtenerNombre() == nombreP)
                        p.listarCanciones();
                pausar();
                };

            acciones[3] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "COMPARTIR CANCION" });
                string titulo;
                cout << "Titulo de la cancion: "; getline(cin, titulo);
                string link = gestorCompartir.compartir(titulo);
                if (!link.empty())
                    cout << "-> Link generado: " << link << "\n";
                else
                    cout << "-> Limite de compartidos alcanzado!\n";
                historial->registrarEvento("Se compartio la cancion: " + titulo);

                pausar();
                };

            acciones[4] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "CANCIONES COMPARTIDAS" });
                gestorCompartir.listarCompartidos();
                pausar();
                };

            acciones[5] = [&]() {

                limpiarPantalla();
                dibujarCaja({ "ORDENAR CANCIONES CON QUICKSORT" });

                string nombreP;
                cout << "Nombre de la playlist: "; getline(cin, nombreP);

                bool playlistEncontrada = false;
                for (auto& p : usuarioLogueado.obtenerListaReproduccion()) {
                    if (p.obtenerNombre() == nombreP) {
                        playlistEncontrada = true;

                        // Obtener canciones para ordenar
                        vector<Cancion> cancionesTemp;
                        const auto& cancionesOriginales = p.obtenerCanciones();

                        // Convertir de ListaEnlazada a vector para usar QuickSort
                        cancionesOriginales.porCada([&](const Cancion& c) {
                            cancionesTemp.push_back(c);
                            });

                        if (cancionesTemp.empty()) {
                            cout << "-> La playlist esta vacia!\n";
                            pausar();
                            break;
                        }

                        // Mostrar opciones de ordenamiento
                        cout << "\nCriterios de ordenamiento:\n";
                        cout << "1. Por Titulo\n";
                        cout << "2. Por Artista\n";
                        cout << "3. Por Album\n";
                        cout << "4. Por Duracion\n";
                        cout << "Seleccione criterio: ";

                        int criterio = leerEnteroEnRango("", 1, 4);

                        QuickSortCanciones::CriterioOrdenamiento criterioSeleccionado;
                        switch (criterio) {
                        case 1: criterioSeleccionado = QuickSortCanciones::POR_TITULO; break;
                        case 2: criterioSeleccionado = QuickSortCanciones::POR_ARTISTA; break;
                        case 3: criterioSeleccionado = QuickSortCanciones::POR_ALBUM; break;
                        case 4: criterioSeleccionado = QuickSortCanciones::POR_DURACION; break;
                        default:
                            cout << "-> Criterio invalido, usando ordenamiento por titulo\n";
                            criterioSeleccionado = QuickSortCanciones::POR_TITULO;
                        }

                        // Medir tiempo de ejecucion del QuickSort
                        auto tiempoInicio = chrono::high_resolution_clock::now();

                        // Aplicar QuickSort
                        QuickSortCanciones::ordenar(cancionesTemp, criterioSeleccionado);

                        auto tiempoFin = chrono::high_resolution_clock::now();
                        auto duracionMicrosegundos = chrono::duration_cast<chrono::microseconds>(tiempoFin - tiempoInicio);

                        cout << "\n-> Ordenado en " << duracionMicrosegundos.count() << " microsegundos!\n";

                        // Mostrar canciones ordenadas
                        cout << "\n-> Canciones ordenadas por " << QuickSortCanciones::obtenerNombreCriterio(criterioSeleccionado) << ":\n";
                        cout << "==========================================\n";

                        int contador = 1;
                        for (const auto& cancion : cancionesTemp) {
                            cout << contador << ". " << cancion.obtenerTitulo()
                                << " - " << cancion.obtenerArtista()
                                << " [" << cancion.obtenerAlbum() << "] "
                                << "(" << cancion.obtenerDuracion() << "s)\n";
                            contador++;
                        }

                        historial->registrarEvento("Se ordenaron las canciones de la playlist '" + nombreP + "' por " +
                            QuickSortCanciones::obtenerNombreCriterio(criterioSeleccionado));

                        cout << "\n-> Ordenamiento completado con QuickSort!\n";
                        break;
                    }
                }

                if (!playlistEncontrada) {
                    cout << "-> ERROR: La playlist '" << nombreP << "' no existe.\n";
                }

                pausar();
                };

            acciones[6] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "REPRODUCTOR DE CANCIONES O PODCAST" });

                string titulo;
                cout << "Titulo de la cancion o podcast: ";
                getline(cin, titulo);

                // Buscar duracion
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
                    const Podcast* lista = gestorPodcasts.obtenerTodos();
                    int cantidad = gestorPodcasts.obtenerCantidad();
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
                    return;
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
                    int sub = leerEnteroEnRango("", 1, 3);

                    switch (sub) {
                    case 1:
                        if (segundos >= DURACION_TOTAL) {
                            cout << ">> Ya termino. Reinicia manualmente (resetea el contador).\n";
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
                };

            acciones[7] = [&]() {
                salir = true;
                };
            break;
        }
        case VALORACIONES: {
            acciones[0] = [&]() {
              
                limpiarPantalla();
                dibujarCaja({ "VALORAR FORMATO" });
                cout << "�Qu� quieres valorar?\n"
                    << " 1. Cancion\n"
                    << " 2. Podcast\n"
                    << "Selecciona (1-2): ";
                int tipo = leerEnteroEnRango("", 1, 2);

                string titulo;
                cout << (tipo == 1 ? "Titulo de la cancion: " : "Titulo del podcast: ");
                getline(cin, titulo);

                // 1) Verificar existencia
                bool existe = false;
                if (tipo == 1) {
                    // Buscamos en todas las playlists del usuario
                    for (const auto& lista : usuarioLogueado.obtenerListaReproduccion()) {
                        lista.obtenerCanciones().porCada([&](const Cancion& c) {
                            if (c.obtenerTitulo() == titulo)
                                existe = true;
                            });
                        if (existe) break;
                    }
                }
                else {
                    // Buscamos en el AdministradorPodcast
                    const Podcast* arr = gestorPodcasts.obtenerTodos();
                    int tot = gestorPodcasts.obtenerCantidad();
                    for (int i = 0; i < tot; ++i) {
                        if (arr[i].obtenerTitulo() == titulo) {
                            existe = true;
                            break;
                        }
                    }
                }

                if (!existe) {
                    cout << "-> ERROR: El titulo \"" << titulo
                        << "\" no existe en " << (tipo == 1 ? "canciones" : "podcasts") << ".\n";
                    pausar();
                    return;
                }

                // 2) Leer valor y registrar
                int valor = leerEnteroEnRango("Valor (1-5): ", 1, 5);
                bool ok = gestorValoracion.agregarValoracion(titulo, valor);

                if (ok)
                    cout << "-> Valoracion guardada!\n";
                else
                    cout << "-> ERROR: Valor no valido o capacidad de valoraciones llena.\n";

                historial->registrarEvento(
                    string("Se valoro ") + (tipo == 1 ? "cancion: \"" : "podcast: \"")
                    + titulo + "\" con: " + to_string(valor)
                );
                pausar();
                };

            acciones[1] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "VALORACIONES PROMEDIO" });
                gestorValoracion.listarPromedios();
                pausar();

                };
            acciones[2] = [&]() {
                salir = true;
                };
            break;
        }
        case ENLACES: {
            acciones[0] = [&]() {
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
                };

            acciones[1] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "TUS ENLACES FAVORITOS" });
                gestorEnlaces.listarFavoritos();
                pausar();
                };

            acciones[2] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "ELIMINAR ENLACE FAVORITO" });
                gestorEnlaces.listarFavoritos();
                int idx = leerEnteroEnRango("Indice a eliminar: ", 1, 100); // Rango razonable para indices
                if (gestorEnlaces.eliminarEnlace(idx - 1))
                    cout << "-> Enlace eliminado!\n";
                else
                    cout << "-> Indice no valido\n";
                pausar();
                };

            acciones[3] = [&]() {
                salir = true;
                };
            break;
        }
        case PODCAST: {
            acciones[0] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "REGISTRAR PODCAST" });
                string titulo, creador;
                cout << "Titulo del podcast : "; getline(cin, titulo);
                cout << "Creador del podcast: "; getline(cin, creador);
                int duracion = leerEnteroEnRango("Duracion (segundos): ", 1, 14400); // Entre 1 segundo y 4 horas
                if (gestorPodcasts.registrarPodcast(titulo, creador, duracion))
                    cout << "-> Podcast registrado!\n";
                else
                    cout << "-> Limite de podcasts alcanzado!\n";
                pausar();
                };
            acciones[1] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "LISTA DE PODCASTS" });
                gestorPodcasts.listarPodcasts();
                pausar();
                };
            acciones[2] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "ORDENAR PODCAST CON MERGESORT" });
                gestorPodcasts.ordenarPorTituloMerge();
                historial->registrarEvento("Se ordenaron los podcasts por Titulo usando MergeSort");
                pausar();
                };
            acciones[3] = [&]() {
                salir = true;
                };
            break;
        }
        case AYUDA: {
            acciones[0] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "GUIA DEL USUARIO" });
                estadisticas.mostrarGuia();
                pausar();
                };
            acciones[1] = [&]() {
                limpiarPantalla();
                dibujarCaja({ "HISTORIAL GENERAL DE ACTIVIDADES" });
                historial->mostrarHistorial();
                pausar();
                };
            acciones[2] = [&]() {
                salir = true;
                };
            break;
        }
    }
    
    return acciones;
}


void subMenu(
    MenuOpcion opcion, 
    Usuario& usuarioLogueado, 
    unique_ptr<Historial>& historial,
    unique_ptr<map<string, int>>& progresoCanciones,
    unique_ptr<mutex>& mtxTiempo,
    unique_ptr<atomic<bool>>& enReproduccion,
    unique_ptr<atomic<bool>>& detenerHilo,
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir
)
{
    vector<string> opciones = obtenerOpcionesSubmenu(opcion);
    int seleccion = 0;
    bool salir = false;

    auto acciones = obtenerAccionesSubmenu(opcion, usuarioLogueado, historial, salir, progresoCanciones, mtxTiempo, enReproduccion, detenerHilo, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir);
    
    while (!salir) {
        limpiarPantalla();
        dibujarCajaConSeleccion(opciones, seleccion, 50);
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
            if (tecla == 80) seleccion = (seleccion + 1) % opciones.size();
        }
        else if (tecla == 13) {
            acciones[seleccion]();
        }
    }
}



void iniciarSesion(vector<Usuario>& usuarios) {
    limpiarPantalla();
    dibujarCaja({ "INICIAR SESION" });
    string identifier, pass;
    cout << "Correo o nombre de usuario: "; getline(cin, identifier);
    cout << "Contrasena                : "; getline(cin, pass);

    auto it = find_if(usuarios.begin(), usuarios.end(),
        [&](auto& u) {
        return (u.obtenerNombre() == identifier || u.obtenerCorreo() == identifier);
        });
    if (it == usuarios.end() || it->obtenerContrasena() != pass) {
        cout << "-> Credenciales invalidas!\n";
        pausar();
        return;
    }

    Usuario& usuarioLogueado = *it;

    auto gestorCompartir = make_unique<CompartirCancion>();
    auto gestorValoracion = make_unique<DatosValoracion>();
    auto gestorEnlaces = make_unique<EnlaceFavorito>();
    auto estadisticas = make_unique<GuiaUsuario>();
    auto gestorPodcasts = make_unique<AdministradorPodcast>();
    auto historial = make_unique<Historial>();

    auto progresoCanciones = make_unique<map<string, int>>();
    auto mtxTiempo = make_unique<mutex>();
    auto enReproduccion = make_unique<atomic<bool>>(false);
    auto detenerHilo = make_unique<atomic<bool>>(false);

    bool sesionActiva = true;
    int  opcion;
    int seleccion = 0;
    bool seleccionHecha = false;

    vector<string> opciones = {
        "Playlist",                      
        "Canciones",         
        "Valoraciones",
        "Enlaces",
        "Podcast",
        "Ayuda",
        "Cerrar Sesion"                  
    };

    while (sesionActiva) {
        limpiarPantalla();
        //dibujarCaja({
        //    "SESION: " + usuarioLogueado.obtenerNombre(),
        //   /* "1. Crear Playlist",
        //    "2. Eliminar Playlist",
        //    "3. Listar Playlists",*/
        //    "Playlist",
        //    "4. Agregar Cancion",
        //    "5. Eliminar Cancion",
        //    "6. Listar Canciones",
        //    "7. Compartir Formato",
        //    "8. Ver Compartidos",
        //    "9. Valorar Formato",
        //    "10. Ver Valoraciones",
        //    "11. Agregar Enlace Favorito",
        //    "12. Ver Enlaces",
        //    "13. Eliminar Enlace",
        //    "14. Reproducir Formato",
        //    "15. Guia del Usuario",
        //    "16. Historial General",
        //    "17. Registrar Podcast",
        //    "18. Ver Podcasts",
        //    "19. Ordenar Canciones", 
        //    "0. Cerrar Sesion",
        //    });
        /*cout << "Seleccione opcion: ";
        int opcion = leerEnteroEnRango("", 0, 19);*/
        while (!seleccionHecha) {
            limpiarPantalla();
            dibujarCajaConSeleccion(opciones, seleccion, 60, "MENU PRINCIPAL");

            int tecla = _getch();
            if (tecla == 224) {
                tecla = _getch();
                if (tecla == 72) seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
                if (tecla == 80) seleccion = (seleccion + 1) % opciones.size(); 
            }
            else if (tecla == 13) {
                seleccionHecha = true;
            }
        }
        int opcion = seleccion + 1;

        switch (opcion) {
        case 1: {
            subMenu(
                PLAYLIST, 
                usuarioLogueado, 
                historial, 
                progresoCanciones, 
                mtxTiempo, 
                enReproduccion, 
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
                );
            seleccionHecha = false;
            break;
        }
        case 2: {
            subMenu(
                CANCIONES,
                usuarioLogueado,
                historial,
                progresoCanciones,
                mtxTiempo,
                enReproduccion,
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
            );
            seleccionHecha = false;
            break;
        }
        case 3: {
            subMenu(
                VALORACIONES,
                usuarioLogueado,
                historial,
                progresoCanciones,
                mtxTiempo,
                enReproduccion,
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
            );
            seleccionHecha = false;
            break;
        }
        case 4: {
            subMenu(
                ENLACES,
                usuarioLogueado,
                historial,
                progresoCanciones,
                mtxTiempo,
                enReproduccion,
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
            );
            seleccionHecha = false;
            break;
        }
        case 5: {
            subMenu(
                PODCAST, 
                usuarioLogueado,
                historial,
                progresoCanciones,
                mtxTiempo,
                enReproduccion,
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
            );
            seleccionHecha = false;
            break;
        }
        case 6: {
            subMenu(
                AYUDA, 
                usuarioLogueado,
                historial,
                progresoCanciones,
                mtxTiempo,
                enReproduccion,
                detenerHilo,
                *gestorPodcasts,
                *gestorValoracion,
                *gestorEnlaces,
                *estadisticas,
                *gestorCompartir
            );
            seleccionHecha = false;
            break;
        }
        case 7: {
            sesionActiva = false;
            seleccionHecha = false;
            break;
        }
        case 9: { // VALORAR FORMATO
            limpiarPantalla();
            dibujarCaja({ "VALORAR FORMATO" });
            cout << "Que deseas valorar?\n"
                << " 1. Cancion\n"
                << " 2. Podcast\n"
                << "Selecciona (1-2): ";
            int tipo = leerEnteroEnRango("", 1, 2);

            string titulo;
            cout << (tipo == 1 ? "Titulo de la cancion: " : "Titulo del podcast: ");
            getline(cin, titulo);

            // 1) Verificar existencia
            bool existe = false;
            if (tipo == 1) {
                // Buscamos en todas las playlists del usuario
                for (const auto& lista : usuarioLogueado.obtenerListaReproduccion()) {
                    lista.obtenerCanciones().porCada([&](const Cancion& c) {
                        if (c.obtenerTitulo() == titulo)
                            existe = true;
                        });
                    if (existe) break;
                }
            }
            else {
                // Buscamos en el AdministradorPodcast
                const Podcast* arr = gestorPodcasts->obtenerTodos();
                int tot = gestorPodcasts->obtenerCantidad();
                for (int i = 0; i < tot; ++i) {
                    if (arr[i].obtenerTitulo() == titulo) {
                        existe = true;
                        break;
                    }
                }
            }

            if (!existe) {
                cout << "-> ERROR: El titulo \"" << titulo
                    << "\" no existe en " << (tipo == 1 ? "canciones" : "podcasts") << ".\n";
                pausar();
                break;
            }

            // 2) Leer valor y registrar
            int valor = leerEnteroEnRango("Valor (1-5): ", 1, 5);
            bool ok = gestorValoracion->agregarValoracion(titulo, valor);

            if (ok)
                cout << "-> Valoracion guardada!\n";
            else
                cout << "-> ERROR: Valor no valido o capacidad de valoraciones llena.\n";

            historial->registrarEvento(
                string("Se valoro ") + (tipo == 1 ? "cancion: \"" : "podcast: \"")
                + titulo + "\" con: " + to_string(valor)
            );
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
            int idx = leerEnteroEnRango("Indice a eliminar: ", 1, 100); // Rango razonable para indices
            if (gestorEnlaces->eliminarEnlace(idx - 1))
                cout << "-> Enlace eliminado!\n";
            else
                cout << "-> Indice no valido\n";
            pausar();
            break;
        }
        case 14: { // REPRODUCTOR ADAPTADO
            
            break;
        }

        case 15: {
            limpiarPantalla();
            dibujarCaja({ "GUIA DEL USUARIO" });
            estadisticas->mostrarGuia();
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
            cout << "Titulo del podcast : "; getline(cin, titulo);
            cout << "Creador del podcast: "; getline(cin, creador);
            int duracion = leerEnteroEnRango("Duracion (segundos): ", 1, 14400); // Entre 1 segundo y 4 horas
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
        case 19: { // NUEVA OPCION: Ordenar Canciones con QuickSort
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