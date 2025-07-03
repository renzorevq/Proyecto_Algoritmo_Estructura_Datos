#include "AdministradorCancion.h"
#include "AdministradorCompartirCancion.h"
#include "AdministradorDatosValoracion.h"
#include "AdministradorPodcast.h"
#include "Cancion.h"
#include "Login.h"
#include "CompartirCancion.h"
#include "Creditos.h"
#include "DatosValoracion.h"
#include "EnlaceFavorito.h"
#include "GuiaUsuario.h"
#include "Historial.h"
#include "Login.h"
#include "Podcast.h"
#include "Usuario.h"
#include "Utilidades.h"
#include <chrono>
#include <conio.h>
#include <mutex>
#include <thread>

#include <sstream>
#include <fstream>
#include <vector> 
// #include <map> // Eliminado
// #include <vector> // Eliminado
// #include <functional> // Eliminado
// #include <atomic> // Eliminado
using namespace std;
// Reemplazo para std::vector<string> codigosGenerados;
const int MAX_CODIGOS_GENERADOS = 100;
string codigosGenerados[MAX_CODIGOS_GENERADOS];
int numCodigosGenerados = 0;

// Reemplazo para std::map<string, int> progresoCanciones;
const int MAX_CANCIONES_PROGRESO = 100;
string progresoCancionesTitulos[MAX_CANCIONES_PROGRESO];
int progresoCancionesSegundos[MAX_CANCIONES_PROGRESO];
int numProgresoCanciones = 0;

// Reemplazo para std::atomic<bool>
volatile bool g_enReproduccion = false;
volatile bool g_detenerHilo = false;


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

// Reemplazo para ordenarCodigosPorInsercion (anteriormente usaba std::vector)
void ordenarCodigosPorInsercion(string codigos[], int cantidad) {
    for (int i = 1; i < cantidad; ++i) {
        string clave = codigos[i];
        int j = i - 1;
        while (j >= 0 && codigos[j] > clave) {
            codigos[j + 1] = codigos[j];
            j--;
        }
        codigos[j + 1] = clave;
    }
}

// Reemplazo para mostrarCodigosOrdenados (anteriormente usaba std::vector)
void mostrarCodigosOrdenados(const string codigos[], int cantidad) {
    cout << "\n--- CODIGOS ORDENADOS (Timsort - 3 ultimos digitos de enlaces) ---\n";
    for (int i = 0; i < cantidad; ++i) {
        cout << "* " << codigos[i] << "\n";
    }
    cout << "--------------------------------------------------------------------\n";
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
    // Reemplazo para std::swap
    static void swapCanciones(Cancion& a, Cancion& b) {
        Cancion temp = a;
        a = b;
        b = temp;
    }

    // Reemplazo para std::vector<Cancion>
    static int particion(Cancion canciones[], int bajo, int alto, CriterioOrdenamiento criterio) {
        Cancion pivote = canciones[alto];
        int i = bajo - 1;

        for (int j = bajo; j <= alto - 1; j++) {
            if (compararCanciones(canciones[j], pivote, criterio)) {
                i++;
                swapCanciones(canciones[i], canciones[j]);
            }
        }
        swapCanciones(canciones[i + 1], canciones[alto]);
        return i + 1;
    }

    // Reemplazo para std::vector<Cancion>
    static void quickSortRecursivo(Cancion canciones[], int bajo, int alto, CriterioOrdenamiento criterio) {
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
    // Reemplazo para std::vector<Cancion>
    static void ordenar(Cancion canciones[], int cantidad, CriterioOrdenamiento criterio = POR_TITULO) {
        if (cantidad <= 1) return;
        quickSortRecursivo(canciones, 0, cantidad - 1, criterio);
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

void registrarse(Usuario usuarios[], int& numUsuarios) {
    if (numUsuarios >= MAX_USUARIOS) {
        cout << "-> Limite de usuarios alcanzado!\n";
        pausar();
        return;
    }

    limpiarPantalla();
    dibujarCaja({ "REGISTRARSE" });
    string n, c, p;
    cout << "Nombre: ";     getline(cin, n);
    cout << "Correo: ";     getline(cin, c);
    cout << "Contrasena: "; getline(cin, p);

    usuarios[numUsuarios] = Usuario(n, c, p);
    numUsuarios++;

    cout << "-> Usuario registrado!\n";
    pausar();
}

enum MenuOpcion { PLAYLIST, CANCIONES, VALORACIONES, ENLACES, PODCAST, AYUDA, SALIR };

// Reemplazo para std::vector<string>
const int MAX_OPCIONES_SUBMENU = 10; // Suficiente para todas las opciones
void obtenerOpcionesSubmenu(MenuOpcion opcion, string opciones[], int& numOpciones) {
    numOpciones = 0;
    switch (opcion) {
    case PLAYLIST:
        opciones[numOpciones++] = "Crear Playlist";
        opciones[numOpciones++] = "Eliminar Playlist";
        opciones[numOpciones++] = "Listar Playlists";
        opciones[numOpciones++] = "Volver";
        break;
    case CANCIONES:
        opciones[numOpciones++] = "Agregar Cancion";
        opciones[numOpciones++] = "Eliminar Cancion";
        opciones[numOpciones++] = "Listar Canciones";
        opciones[numOpciones++] = "Compartir Cancion";
        opciones[numOpciones++] = "Canciones Compartidos";
        opciones[numOpciones++] = "Ordenar Canciones";
        opciones[numOpciones++] = "Reproducir Cancion";
        opciones[numOpciones++] = "Ordenar Enlaces Compartidos";
        opciones[numOpciones++] = "Volver";
        break;
    case VALORACIONES:
        opciones[numOpciones++] = "Valorar Formato";
        opciones[numOpciones++] = "Ver Valoraciones";
        opciones[numOpciones++] = "Ver Valoraciones Ordenado";
        opciones[numOpciones++] = "Volver";
        break;
    case ENLACES:
        opciones[numOpciones++] = "Agregar Enlace Favorito";
        opciones[numOpciones++] = "Ver Enlaces";
        opciones[numOpciones++] = "Eliminar Enlace";
        opciones[numOpciones++] = "Volver";
        break;
    case PODCAST:
        opciones[numOpciones++] = "Registrar Podcast";
        opciones[numOpciones++] = "Ver Podcasts";
        opciones[numOpciones++] = "Ordenar Podcasts(MergeSort)";
        opciones[numOpciones++] = "Volver";
        break;
    case AYUDA:
        opciones[numOpciones++] = "Guia del Usuario";
        opciones[numOpciones++] = "Historial General";
        opciones[numOpciones++] = "Creditos";
        opciones[numOpciones++] = "Volver";
        break;
    }
}

// Reemplazo para std::map<int, std::function<void()>>
void ejecutarAccionSubmenu(
    MenuOpcion opcion,
    int seleccion,
    Usuario& usuarioLogueado,
    Historial& historial, // Puntero único a referencia
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir,
    std::mutex& mtxTiempo // Referencia al mutex
) {
    // Variables locales para el reproductor
    int* p_segundos = nullptr; // Puntero al progreso de la cancion actual
    int DURACION_TOTAL = -1;

    // Buscar el progreso de la cancion/podcast actual
    auto buscarProgreso = [&](const string& titulo) {
        for (int i = 0; i < numProgresoCanciones; ++i) {
            if (progresoCancionesTitulos[i] == titulo) {
                p_segundos = &progresoCancionesSegundos[i];
                return true;
            }
        }
        // Si no se encuentra, agregarla
        if (numProgresoCanciones < MAX_CANCIONES_PROGRESO) {
            progresoCancionesTitulos[numProgresoCanciones] = titulo;
            progresoCancionesSegundos[numProgresoCanciones] = 0;
            p_segundos = &progresoCancionesSegundos[numProgresoCanciones];
            numProgresoCanciones++;
            return true;
        }
        return false;
        };

    switch (opcion) {
    case PLAYLIST: {
        switch (seleccion) {
        case 0: { // Crear Playlist
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
        case 1: { // Eliminar Playlist
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR PLAYLIST" });
            string nombreP;
            cout << "Nombre Playlist: "; getline(cin, nombreP);
            usuarioLogueado.eliminarListaReproduccion(nombreP);
            cout << "-> Eliminada si existia!\n";
            pausar();
            break;
        }
        case 2: { // Listar Playlists
            limpiarPantalla();
            dibujarCaja({ "TUS PLAYLISTS" });
            // Reemplazo para iterar sobre std::vector<ListaReproduccion>
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data(); // Asumiendo que vector tiene data()
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                cout << "* " << listas[i].obtenerNombre() << "\n";
            }
            pausar();
            break;
        }
        }
        break;
    }
    case CANCIONES: {
        switch (seleccion) {
        case 0: { // Agregar Cancion
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
            // Reemplazo para iterar sobre std::vector<ListaReproduccion>
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP) {
                    listas[i].agregarCancion(Cancion(t, art, alb, dur));
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
        case 1: { // Eliminar Cancion
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR CANCION" });
            string nombreP, t;
            cout << "Playlist      : "; getline(cin, nombreP);
            cout << "Titulo Cancion: "; getline(cin, t);
            // Reemplazo para iterar sobre std::vector<ListaReproduccion>
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP)
                    listas[i].eliminarCancion(t);
            }
            cout << "-> Eliminada si existia!\n";
            pausar();
            break;
        }
        case 2: { // Listar Canciones
            limpiarPantalla();
            dibujarCaja({ "LISTAR CANCIONES" });
            string nombreP;
            cout << "Playlist: "; getline(cin, nombreP);
            // Reemplazo para iterar sobre std::vector<ListaReproduccion>
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP)
                    listas[i].listarCanciones();
            }
            pausar();
            break;
        }
        case 3: { // Compartir Cancion
            limpiarPantalla();
            dibujarCaja({ "COMPARTIR CANCION" });
            string titulo;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            string link = gestorCompartir.compartir(titulo);

            if (!link.empty()) {
                // Obtener ultimos 3 caracteres (los digitos aleatorios)
                string codigo = link.substr(link.size() - 3);
                if (numCodigosGenerados < MAX_CODIGOS_GENERADOS) {
                    codigosGenerados[numCodigosGenerados++] = codigo; // Guardar para ordenamiento
                }
                cout << "-> Link generado: " << link << "\n";
            }
            else {
                cout << "-> Limite de compartidos alcanzado!\n";
            }

            historial.registrarEvento("Se compartio la cancion: " + titulo);
            pausar();
            break;
        }
        case 4: { // Canciones Compartidas
            limpiarPantalla();
            dibujarCaja({ "CANCIONES COMPARTIDAS" });
            gestorCompartir.listarCompartidos();
            pausar();
            break;
        }
        case 5: { // Ordenar Canciones con QuickSort
            limpiarPantalla();
            dibujarCaja({ "ORDENAR CANCIONES CON QUICKSORT" });

            string nombreP;
            cout << "Nombre de la playlist: "; getline(cin, nombreP);

            bool playlistEncontrada = false;
            // Reemplazo para iterar sobre std::vector<ListaReproduccion>
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP) {
                    playlistEncontrada = true;

                    // Obtener canciones para ordenar
                    // Reemplazo para std::vector<Cancion> cancionesTemp;
                    Cancion cancionesTemp[MAX_CANCIONES]; // Asumiendo MAX_CANCIONES es suficiente
                    int numCancionesTemp = 0;

                    const ListaEnlazada<Cancion>& cancionesOriginales = listas[i].obtenerCanciones();

                    // Convertir de ListaEnlazada a arreglo para usar QuickSort
                    // Reemplazo para porCada con un bucle manual
                    // Esto requiere acceso interno a ListaEnlazada o una funcion que devuelva un arreglo
                    // Para simplificar, asumiremos que ListaEnlazada tiene un metodo para copiar a un arreglo
                    // O que podemos iterar manualmente si Nodo es accesible.
                    // Si no, esta parte seria mas compleja.
                    // Por ahora, simularemos la conversion:
                    // (Esto es una simplificacion, en un caso real ListaEnlazada necesitaria un metodo toArray)
                    Cancion tempArray[MAX_CANCIONES]; // Temporal para copiar
                    int tempCount = 0;
                    cancionesOriginales.porCada([&](const Cancion& c) {
                        if (tempCount < MAX_CANCIONES) {
                            tempArray[tempCount++] = c;
                        }
                        });
                    for (int k = 0; k < tempCount; ++k) {
                        cancionesTemp[numCancionesTemp++] = tempArray[k];
                    }


                    if (numCancionesTemp == 0) {
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
                    QuickSortCanciones::ordenar(cancionesTemp, numCancionesTemp, criterioSeleccionado);

                    auto tiempoFin = chrono::high_resolution_clock::now();
                    auto duracionMicrosegundos = chrono::duration_cast<chrono::microseconds>(tiempoFin - tiempoInicio);

                    cout << "\n-> Ordenado en " << duracionMicrosegundos.count() << " microsegundos!\n";

                    // Mostrar canciones ordenadas
                    cout << "\n-> Canciones ordenadas por " << QuickSortCanciones::obtenerNombreCriterio(criterioSeleccionado) << ":\n";
                    cout << "==========================================\n";

                    int contador = 1;
                    for (int k = 0; k < numCancionesTemp; ++k) {
                        cout << contador << ". " << cancionesTemp[k].obtenerTitulo()
                            << " - " << cancionesTemp[k].obtenerArtista()
                            << " [" << cancionesTemp[k].obtenerAlbum() << "] "
                            << "(" << cancionesTemp[k].obtenerDuracion() << "s)\n";
                        contador++;
                    }

                    historial.registrarEvento("Se ordenaron las canciones de la playlist '" + nombreP + "' por " +
                        QuickSortCanciones::obtenerNombreCriterio(criterioSeleccionado));

                    cout << "\n-> Ordenamiento completado con QuickSort!\n";
                    break;
                }
            }

            if (!playlistEncontrada) {
                cout << "-> ERROR: La playlist '" << nombreP << "' no existe.\n";
            }

            pausar();
            break;
        }
        case 6: { // Reproducir Cancion
            limpiarPantalla();
            dibujarCaja({ "REPRODUCTOR DE CANCIONES O PODCAST" });

            string titulo;
            cout << "Titulo de la cancion o podcast: ";
            getline(cin, titulo);

            // Buscar duracion
            DURACION_TOTAL = -1;

            // Buscar en canciones del usuario
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
            int numListas = usuarioLogueado.obtenerListaReproduccion().size();
            for (int i = 0; i < numListas; ++i) {
                const ListaEnlazada<Cancion>& canciones = listas[i].obtenerCanciones();
                // Reemplazo para porCada
                Cancion tempArray[MAX_CANCIONES]; // Temporal para copiar
                int tempCount = 0;
                canciones.porCada([&](const Cancion& c) {
                    if (tempCount < MAX_CANCIONES) {
                        tempArray[tempCount++] = c;
                    }
                    });
                for (int k = 0; k < tempCount; ++k) {
                    if (tempArray[k].obtenerTitulo() == titulo) {
                        DURACION_TOTAL = tempArray[k].obtenerDuracion();
                        break;
                    }
                }
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

            // Obtener o crear entrada en progresoCanciones
            if (!buscarProgreso(titulo)) {
                cout << ">> ERROR: No se pudo registrar el progreso de la cancion.\n";
                pausar();
                return;
            }

            g_enReproduccion = false;
            g_detenerHilo = false;

            thread hiloCronometro([&]() {
                while (!g_detenerHilo) {
                    if (g_enReproduccion && *p_segundos < DURACION_TOTAL) {
                        this_thread::sleep_for(chrono::seconds(1));
                        {
                            lock_guard<mutex> lock(mtxTiempo);
                            ++(*p_segundos);
                            if (*p_segundos >= DURACION_TOTAL) {
                                g_enReproduccion = false;
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
                while (!g_detenerHilo) {
                    this_thread::sleep_for(chrono::milliseconds(500));
                    lock_guard<mutex> lock(mtxTiempo);
                    int mins = DURACION_TOTAL / 60;
                    int secs = DURACION_TOTAL % 60;
                    cout << "\r[ " << ((*p_segundos) / 60) << "m " << ((*p_segundos) % 60)
                        << "s / " << mins << "m " << secs << "s ] ";
                    cout.flush();
                }
                });

            bool salirReproductor = false;
            while (!salirReproductor) {
                cout << "\n\nSubopciones: 1.Reproducir  2.Pausar  3.Salir\n";
                cout << "Ingrese opcion: ";
                int sub = leerEnteroEnRango("", 1, 3);

                switch (sub) {
                case 1:
                    if (*p_segundos >= DURACION_TOTAL) {
                        cout << ">> Ya termino. Reinicia manualmente (resetea el contador).\n";
                    }
                    else {
                        g_enReproduccion = true;
                        cout << ">> Reproduciendo...\n";
                    }
                    break;
                case 2:
                    g_enReproduccion = false;
                    cout << ">> Pausado.\n";
                    break;
                case 3:
                    g_detenerHilo = true;
                    g_enReproduccion = false;
                    salirReproductor = true;
                    break;
                default:
                    cout << ">> Opcion invalida.\n";
                }
            }

            if (hiloCronometro.joinable()) hiloCronometro.join();
            if (hiloVisual.joinable()) hiloVisual.join();

            historial.registrarEvento("Reproduccion iniciada de: " + titulo);
            cout << ">> Saliendo del reproductor...\n";
            pausar();
            break;
        }
        case 7: { // Ordenar Enlaces Compartidos (Timsort)
            limpiarPantalla();
            dibujarCaja({ "ORDENAMIENTO AVANZADO DE ENLACES (TIMSORT)" });

            if (numCodigosGenerados == 0) {
                cout << "(No hay enlaces generados aun)\n";
            }
            else {
                ordenarCodigosPorInsercion(codigosGenerados, numCodigosGenerados);
                mostrarCodigosOrdenados(codigosGenerados, numCodigosGenerados);
            }

            pausar();
            break;
        }
        }
        break;
    }
    case VALORACIONES: {
        switch (seleccion) {
        case 0: { // Valorar Formato
            limpiarPantalla();
            dibujarCaja({ "VALORAR FORMATO" });
            cout << "Que quieres valorar?\n"
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
                ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion().data();
                int numListas = usuarioLogueado.obtenerListaReproduccion().size();
                for (int i = 0; i < numListas; ++i) {
                    const ListaEnlazada<Cancion>& canciones = listas[i].obtenerCanciones();
                    // Reemplazo para porCada
                    Cancion tempArray[MAX_CANCIONES]; // Temporal para copiar
                    int tempCount = 0;
                    canciones.porCada([&](const Cancion& c) {
                        if (tempCount < MAX_CANCIONES) {
                            tempArray[tempCount++] = c;
                        }
                        });
                    for (int k = 0; k < tempCount; ++k) {
                        if (tempArray[k].obtenerTitulo() == titulo) {
                            existe = true;
                            break;
                        }
                    }
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

            historial.registrarEvento(
                string("Se valoro ") + (tipo == 1 ? "cancion: \"" : "podcast: \"")
                + titulo + "\" con: " + to_string(valor)
            );
            pausar();
            break;
        }
        case 1: { // Ver Valoraciones
            limpiarPantalla();
            dibujarCaja({ "VALORACIONES PROMEDIO" });
            gestorValoracion.listarPromedios();
            pausar();
            break;
        }
        case 2: { // Ver Valoraciones Ordenado (Counting Sort)
            limpiarPantalla();
            dibujarCaja({ "VALORACIONES PROMEDIO ORDENADO (COUNTING SORT)" });
            gestorValoracion.listarPromediosOrdenado();
            pausar();
            break;
        }
        }
        break;
    }
    case ENLACES: {
        switch (seleccion) {
        case 0: { // Agregar Enlace Favorito
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
        case 1: { // Ver Enlaces
            limpiarPantalla();
            dibujarCaja({ "TUS ENLACES FAVORITOS" });
            gestorEnlaces.listarFavoritos();
            pausar();
            break;
        }
        case 2: { // Eliminar Enlace
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR ENLACE FAVORITO" });
            gestorEnlaces.listarFavoritos();
            int idx = leerEnteroEnRango("Indice a eliminar: ", 1, 100); // Rango razonable para indices
            if (gestorEnlaces.eliminarEnlace(idx - 1))
                cout << "-> Enlace eliminado!\n";
            else
                cout << "-> Indice no valido\n";
            pausar();
            break;
        }
        }
        break;
    }
    case PODCAST: {
        switch (seleccion) {
        case 0: { // Registrar Podcast
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
            break;
        }
        case 1: { // Ver Podcasts
            limpiarPantalla();
            dibujarCaja({ "LISTA DE PODCASTS" });
            gestorPodcasts.listarPodcasts();
            pausar();
            break;
        }
        case 2: { // Ordenar Podcasts (MergeSort)
            limpiarPantalla();
            dibujarCaja({ "ORDENAR PODCAST CON MERGESORT" });
            gestorPodcasts.ordenarPorTituloMerge();
            historial.registrarEvento("Se ordenaron los podcasts por Titulo usando MergeSort");
            pausar();
            break;
        }
        }
        break;
    }
    case AYUDA: {
        switch (seleccion) {
        case 0: { // Guia del Usuario
            limpiarPantalla();
            dibujarCaja({ "GUIA DEL USUARIO" });
            estadisticas.mostrarGuia();
            pausar();
            break;
        }
        case 1: { // Historial General
            limpiarPantalla();
            dibujarCaja({ "HISTORIAL GENERAL DE ACTIVIDADES" });
            historial.mostrarHistorial();
            pausar();
            break;
        }
        case 2: { // Creditos
            limpiarPantalla();
            dibujarCaja({ "CREDITOS" });
            Creditos::mostrar();
            break;
        }
        }
        break;
    }
    }
}

void subMenu(
    MenuOpcion opcion,
    Usuario& usuarioLogueado,
    Historial& historial, // Puntero único a referencia
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir,
    std::mutex& mtxTiempo // Referencia al mutex
)
{
    string opciones[MAX_OPCIONES_SUBMENU];
    int numOpciones = 0;
    obtenerOpcionesSubmenu(opcion, opciones, numOpciones);

    int seleccion = 0;
    bool salir = false;

    while (!salir) {
        limpiarPantalla();
        // Reemplazo para std::vector<string>
        string opcionesDibujo[MAX_OPCIONES_SUBMENU];
        for (int i = 0; i < numOpciones; ++i) {
            opcionesDibujo[i] = opciones[i];
        }
        dibujarCajaConSeleccion(opcionesDibujo, seleccion, 50, numOpciones, "MENU PRINCIPAL");

        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) seleccion = (seleccion - 1 + numOpciones) % numOpciones;
            if (tecla == 80) seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13) {
            if (seleccion == numOpciones - 1) { // La ultima opcion es "Volver"
                salir = true;
            }
            else {
                ejecutarAccionSubmenu(opcion, seleccion, usuarioLogueado, historial,
                    gestorPodcasts, gestorValoracion, gestorEnlaces,
                    estadisticas, gestorCompartir, mtxTiempo);
            }
        }
    }
}

void iniciarSesion(Usuario usuarios[], int numUsuarios) {
    limpiarPantalla();
    dibujarCaja({ "INICIAR SESION" });
    string identifier, pass;
    cout << "Correo o nombre de usuario: "; getline(cin, identifier);
    cout << "Contrasena                : "; getline(cin, pass);

    int indice = -1;
    for (int i = 0; i < numUsuarios; ++i) {
        if ((usuarios[i].obtenerNombre() == identifier || usuarios[i].obtenerCorreo() == identifier) &&
            usuarios[i].obtenerContrasena() == pass) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "-> Credenciales invalidas!\n";
        pausar();
        return;
    }

    Usuario& usuarioLogueado = usuarios[indice];

    // Instancias de gestores (no punteros unicos)
    CompartirCancion gestorCompartir;
    DatosValoracion gestorValoracion;
    EnlaceFavorito gestorEnlaces;
    GuiaUsuario estadisticas;
    AdministradorPodcast gestorPodcasts;
    Historial historial; // No unique_ptr

    // Mutex para el reproductor
    std::mutex mtxTiempo;

    bool sesionActiva = true;
    int seleccion = 0;
    bool seleccionHecha = false;

    // Reemplazo para std::vector<string> opciones
    string opcionesMenuPrincipal[MAX_OPCIONES_SUBMENU];
    int numOpcionesMenuPrincipal = 0;
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Playlist";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Canciones";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Valoraciones";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Enlaces";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Podcast";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Ayuda";
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Cerrar Sesion";


    while (sesionActiva) {
        seleccionHecha = false; // Resetear para cada iteracion del menu principal
        while (!seleccionHecha) {
            limpiarPantalla();
            dibujarCajaConSeleccion(opcionesMenuPrincipal, seleccion, 60, numOpcionesMenuPrincipal, "MENU PRINCIPAL");

            int tecla = _getch();
            if (tecla == 224) {
                tecla = _getch();
                if (tecla == 72) seleccion = (seleccion - 1 + numOpcionesMenuPrincipal) % numOpcionesMenuPrincipal;
                if (tecla == 80) seleccion = (seleccion + 1) % numOpcionesMenuPrincipal;
            }
            else if (tecla == 13) {
                seleccionHecha = true;
            }
        }
        int opcion = seleccion; // La seleccion ahora es el indice del arreglo

        switch (opcion) {
        case 0: { // Playlist
            subMenu(PLAYLIST, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 1: { // Canciones
            subMenu(CANCIONES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 2: { // Valoraciones
            subMenu(VALORACIONES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 3: { // Enlaces
            subMenu(ENLACES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 4: { // Podcast
            subMenu(PODCAST, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 5: { // Ayuda
            subMenu(AYUDA, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 6: { // Cerrar Sesion
            sesionActiva = false;
            break;
        }
        default:
            cout << "Opcion no valida!\n";
            pausar();
        }
    }
}

void cargarUsuarios(Usuario usuarios[], int& numUsuarios) {
    ifstream f("usuarios.txt");
    if (!f) return;
    string linea;
    numUsuarios = 0;

    while (getline(f, linea) && numUsuarios < MAX_USUARIOS) {
        stringstream ss(linea);
        string n, c, p;
        if (getline(ss, n, ',') && getline(ss, c, ',') && getline(ss, p, ',')) {
            usuarios[numUsuarios] = Usuario(n, c, p);
            numUsuarios++;
        }
    }
}

void guardarUsuarios(const Usuario usuarios[], int numUsuarios) {
    ofstream f("usuarios.txt");
    if (!f) return;

    for (int i = 0; i < numUsuarios; ++i) {
        f << usuarios[i].obtenerNombre() << ","
            << usuarios[i].obtenerCorreo() << ","
            << usuarios[i].obtenerContrasena() << "\n";
    }
}