#include "AdministradorCancion.h"
#include "AdministradorCompartirCancion.h"
#include "AdministradorDatosValoracion.h"
#include "AdministradorPodcast.h"
#include "Cancion.h"
#include "CompartirCancion.h"
#include "Creditos.h"
#include "DatosValoracion.h"
#include "EnlaceFavorito.h"
#include "GuiaUsuario.h"
#include "Historial.h"
#include "Podcast.h"
#include "Usuario.h"
#include "Utilidades.h"
#include "Login.h"
#include <chrono>
#include <conio.h>
#include <mutex>
#include <thread>
#include <sstream>
#include <fstream>
#include "GrafoCanciones.h"

using namespace std;
GrafoCanciones gestorGrafoCanciones;

// Definición de constantes
const int MAX_OPCIONES_SUBMENU = 10;

// Implementación de Árbol Binario

template <typename T>
class NodoArbol {
public:
    T valor;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(const T& val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
};

template <typename T>
class ArbolBinario {
private:
    NodoArbol<T>* raiz;

    // Función auxiliar para insertar recursivamente
    NodoArbol<T>* insertarRecursivo(NodoArbol<T>* nodo, const T& valor) {
        if (nodo == nullptr) {
            return new NodoArbol<T>(valor);
        }

        // Comparamos valores para decidir dónde insertar
        if (valor < nodo->valor) {
            nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
        }
        else if (valor > nodo->valor) {
            nodo->derecho = insertarRecursivo(nodo->derecho, valor);
        }

        return nodo;
    }
    
    // Recorrido inorden recursivo
    void inordenRecursivo(NodoArbol<T>* nodo, void (*funcion)(const T&), int nivel = 0) const {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izquierdo, funcion, nivel + 1);

            // Imprimir indentación según nivel
            for (int i = 0; i < nivel; i++) {
                cout << "  ";
            }
            cout << "/─ ";
            funcion(nodo->valor);

            inordenRecursivo(nodo->derecho, funcion, nivel + 1);
        }
    }

    // Eliminar recursivamente todos los nodos
    void limpiarRecursivo(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            limpiarRecursivo(nodo->izquierdo);
            limpiarRecursivo(nodo->derecho);
            delete nodo;
        }
    }

public:
    ArbolBinario() : raiz(nullptr) {}

    // Destructor para liberar memoria
    ~ArbolBinario() {
        limpiarRecursivo(raiz);
    }

    // Insertar un valor en el árbol
    void insertar(const T& valor) {
        raiz = insertarRecursivo(raiz, valor);
    }

    // Recorrer el árbol en orden (izquierda-raiz-derecha)
    void inorden(void (*funcion)(const T&)) const {
        inordenRecursivo(raiz, funcion);
    }

    // Verificar si el árbol está vacío
    bool estaVacio() const {
        return raiz == nullptr;
    }

    // Visualizar la estructura del árbol
    void visualizar() const {
        if (estaVacio()) {
            cout << "Árbol vacío\n";
            return;
        }

        cout << "Estructura del árbol:\n";
        inorden([](const T& valor) {
            cout << valor << "\n";
            });
    }
};

// 1. Convertir el arreglo de códigos generados en un template
template <typename T, int MAX_SIZE = 100>
class ArregloFijo {
private:
    T elementos[MAX_SIZE];
    int cantidad = 0;

public:
    void agregar(const T& valor) {
        if (cantidad < MAX_SIZE) {
            elementos[cantidad++] = valor;
        }
    }

    T& operator[](int indice) {
        return elementos[indice];
    }

    const T& operator[](int indice) const {
        return elementos[indice];
    }

    int getCantidad() const {
        return cantidad;
    }
};


ArregloFijo<string, 100> codigosGenerados;

// 2. Convertir estructura de progreso en un template
template <typename K, typename V, int MAX_SIZE = 100>
class MapaFijo {
private:
    K claves[MAX_SIZE];
    V valores[MAX_SIZE];
    int cantidad = 0;

public:
    bool agregar(const K& clave, const V& valor) {
        if (cantidad < MAX_SIZE) {
            claves[cantidad] = clave;
            valores[cantidad] = valor;
            cantidad++;
            return true;
        }
        return false;
    }

    V* buscar(const K& clave) {
        for (int i = 0; i < cantidad; ++i) {
            if (claves[i] == clave) {
                return &valores[i];
            }
        }
        return nullptr;
    }

    K& getClave(int indice) {
        return claves[indice];
    }

    V& getValor(int indice) {
        return valores[indice];
    }

    int getCantidad() const {
        return cantidad;
    }
};

MapaFijo<string, int, 100> progresoCanciones;

// 3. Convertir el estado booleano atomic en un template
template <typename T>
class EstadoVolatil {
private:
    volatile T valor;

public:
    EstadoVolatil(T valorInicial) : valor(valorInicial) {}

    T get() const {
        return valor;
    }

    void set(T nuevoValor) {
        valor = nuevoValor;
    }

    operator T() const {
        return valor;
    }
};


EstadoVolatil<bool> g_enReproduccion(false);
EstadoVolatil<bool> g_detenerHilo(false);

// 4. Convertir algoritmos de ordenamiento en templates
template <typename T>
void ordenarPorInsercion(T arr[], int cantidad) {
    for (int i = 1; i < cantidad; ++i) {
        T clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }
}

template <typename T>
void mostrarOrdenados(const T arr[], int cantidad, const string& titulo) {
    cout << "\n--- " << titulo << " ---\n";
    for (int i = 0; i < cantidad; ++i) {
        cout << "* " << arr[i] << "\n";
    }
    cout << "--------------------------------------------------------------------\n";
}

// 5. Convertir la clase QuickSortCanciones para que pueda ordenar cualquier tipo de datos
template <typename T>
class OrdenadorAvanzado {
public:
    // Enum para diferentes criterios de ordenamiento
    enum CriterioOrdenamiento {
        POR_TITULO,
        POR_ARTISTA,
        POR_ALBUM,
        POR_DURACION
    };

private:
    // Método swap genérico
    static void intercambiar(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    static int particion(T arr[], int bajo, int alto, CriterioOrdenamiento criterio) {
        T pivote = arr[alto];
        int i = bajo - 1;

        for (int j = bajo; j <= alto - 1; j++) {
            if (compararElementos(arr[j], pivote, criterio)) {
                i++;
                intercambiar(arr[i], arr[j]);
            }
        }
        intercambiar(arr[i + 1], arr[alto]);
        return i + 1;
    }

    static void quickSortRecursivo(T arr[], int bajo, int alto, CriterioOrdenamiento criterio) {
        if (bajo < alto) {
            int pi = particion(arr, bajo, alto, criterio);
            quickSortRecursivo(arr, bajo, pi - 1, criterio);
            quickSortRecursivo(arr, pi + 1, alto, criterio);
        }
    }

    static bool compararElementos(const T& a, const T& b, CriterioOrdenamiento criterio) {
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
    static void ordenar(T arr[], int cantidad, CriterioOrdenamiento criterio = POR_TITULO) {
        if (cantidad <= 1) return;
        quickSortRecursivo(arr, 0, cantidad - 1, criterio);
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
    string lineas[1] = { "REGISTRARSE" };
    dibujarCaja(lineas, 1);
    string n, c, p;
    cout << "Nombre: ";     getline(cin, n);
    cout << "Correo: ";     getline(cin, c);
    cout << "Contrasena: "; getline(cin, p);

    usuarios[numUsuarios] = Usuario(n, c, p);
    numUsuarios++;

    cout << "-> Usuario registrado!\n";
    pausar();
}

enum MenuOpcion { PLAYLIST, CANCIONES, VALORACIONES, ENLACES, PODCAST, GRAFO_MUSICAL, AYUDA, SALIR };

// Función para obtener opciones de submenú

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
    case GRAFO_MUSICAL:
        opciones[numOpciones++] = "Modo Sin Conexion (Grafo)";
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


// Clase para gestionar estadísticas en árbol binario
class EstadisticasArbol {
private:
    ArbolBinario<string> arbolCategoriasMusica;

public:
    EstadisticasArbol() {
        // Inicializamos el árbol con algunas categorías de música
        arbolCategoriasMusica.insertar("Rock");
        arbolCategoriasMusica.insertar("Pop");
        arbolCategoriasMusica.insertar("Electrónica");
        arbolCategoriasMusica.insertar("Clásica");
        arbolCategoriasMusica.insertar("Jazz");
        arbolCategoriasMusica.insertar("Hip-Hop");
        arbolCategoriasMusica.insertar("Country");
        arbolCategoriasMusica.insertar("R&B");
        arbolCategoriasMusica.insertar("Metal");
        arbolCategoriasMusica.insertar("Folk");
    }

    void mostrarCategorias() {
        cout << "\n-- CATEGORÍAS MUSICALES (ÁRBOL BINARIO) --\n\n";

        arbolCategoriasMusica.inorden([](const string& categoria) {
            cout << categoria << "\n";
            });

        cout << "\n--- Puedes agregar más categorías ---\n";
    }

    void agregarCategoria(const string& categoria) {
        arbolCategoriasMusica.insertar(categoria);
        cout << "-> Categoría '" << categoria << "' agregada al árbol\n";
    }

    void interactuarConArbol() {
        bool salir = false;

        while (!salir) {
            limpiarPantalla();
            string lineas[] = { "EXPLORADOR DE CATEGORÍAS MUSICALES (ÁRBOL BINARIO)" };
            dibujarCaja(lineas, 1);

            mostrarCategorias();

            cout << "\nOpciones:\n";
            cout << "1. Agregar nueva categoría\n";
            cout << "2. Volver\n";

            int opcion = leerEnteroEnRango("Seleccione opción: ", 1, 2);

            switch (opcion) {
            case 1: {
                string nuevaCategoria;
                cout << "\nIngrese nombre de nueva categoría: ";
                getline(cin, nuevaCategoria);

                if (!nuevaCategoria.empty()) {
                    agregarCategoria(nuevaCategoria);
                    cout << "-> Categoría agregada correctamente!\n";
                }
                else {
                    cout << "-> Error: la categoría no puede estar vacía\n";
                }

                pausar();
                break;
            }
            case 2:
                salir = true;
                break;
            }
        }
    }
};

// Instancia global
EstadisticasArbol gestorEstadisticasArbol;


void SubMenu(
   MenuOpcion opcion,
    int seleccion,
    Usuario& usuarioLogueado,
    Historial& historial,
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir,
    mutex& mtxTiempo
) {
    // Variables locales para el reproductor
    int* p_segundos = nullptr; // Puntero al progreso de la cancion actual
    int DURACION_TOTAL = -1;

    // Buscar el progreso de la cancion/podcast actual
    auto buscarProgreso = [&](const string& titulo) {
        for (int i = 0; i < progresoCanciones.getCantidad(); ++i) {
            if (progresoCanciones.getClave(i) == titulo) {
                p_segundos = &progresoCanciones.getValor(i);
                return true;
            }
        }
        // Si no se encuentra, agregarla
        if (progresoCanciones.getCantidad() < 100) {
            progresoCanciones.agregar(titulo, 0);
            p_segundos = &progresoCanciones.getValor(progresoCanciones.getCantidad() - 1);
            return true;
        }
        return false;
        };

    switch (opcion) {
    case PLAYLIST: {
        switch (seleccion) {
        case 0: { // Crear Playlist
            limpiarPantalla();
            string lineas[2] = { "CREAR PLAYLIST" };
            dibujarCaja(lineas, 1);
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
            string lineas[3] = { "ELIMINAR PLAYLIST" };
            dibujarCaja(lineas, 1);
            string nombreP;
            cout << "Nombre Playlist: "; getline(cin, nombreP);
            usuarioLogueado.eliminarListaReproduccion(nombreP);
            cout << "-> Eliminada si existia!\n";
            pausar();
            break;
        }
        case 2: { // Listar Playlists
            limpiarPantalla();
            string lineas[4] = { "TUS PLAYLIST" };
            dibujarCaja(lineas, 1);
           
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
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
            string lineas[5] = { "AGREGAR CANCION" };
            dibujarCaja(lineas, 1);
            string nombreP, t, art, alb;
            int dur;
            cout << "Playlist      : "; getline(cin, nombreP);
            cout << "Titulo Cancion: "; getline(cin, t);
            cout << "Artista       : "; getline(cin, art);
            cout << "Album         : "; getline(cin, alb);
            dur = leerEnteroEnRango("Duracion (s)  : ", 1, 7200);

            bool encontrada = false;
           
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
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
            string lineas[6] = { "ELIMINAR CANCION" };
            dibujarCaja(lineas, 1);
            string nombreP, t;
            cout << "Playlist      : "; getline(cin, nombreP);
            cout << "Titulo Cancion: "; getline(cin, t);
         
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
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
            string lineas[7] = { "LISTAR CANCIONES" };
            dibujarCaja(lineas, 1);
            string nombreP;
            cout << "Playlist: "; getline(cin, nombreP);
           
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP)
                    listas[i].listarCanciones();
            }
            pausar();
            break;
        }
        case 3: { // Compartir Cancion
            limpiarPantalla();
            string lineas[8] = { "COMPARTIR CANCION" };
            dibujarCaja(lineas, 1);
            string titulo;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            string link = gestorCompartir.compartir(titulo);

            if (!link.empty()) {
                // Obtener ultimos 3 caracteres (los digitos aleatorios)
                string codigo = link.substr(link.size() - 3);
                codigosGenerados.agregar(codigo); // Guardar para ordenamiento
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
            string lineas[9] = { "CANCIONES COMPARTIDAS" };
            dibujarCaja(lineas, 1);
            gestorCompartir.listarCompartidos();
            pausar();
            break;
        }
        case 5: { // Ordenar Canciones con QuickSort
            limpiarPantalla();
            string lineas[10] = { "ORDENADAR CANCIONES CON QUICKSORT" };
            dibujarCaja(lineas, 1);

            string nombreP;
            cout << "Nombre de la playlist: "; getline(cin, nombreP);

            bool playlistEncontrada = false;
           
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
            for (int i = 0; i < numListas; ++i) {
                if (listas[i].obtenerNombre() == nombreP) {
                    playlistEncontrada = true;

                    // Obtener canciones para ordenar
                    Cancion cancionesTemp[MAX_CANCIONES];
                    int numCancionesTemp = 0;

                    const ListaEnlazada<Cancion>& cancionesOriginales = listas[i].obtenerCanciones();

                    // Convertir de ListaEnlazada a arreglo para usar QuickSort
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

                    typename OrdenadorAvanzado<Cancion>::CriterioOrdenamiento criterioSeleccionado;
                    switch (criterio) {
                    case 1: criterioSeleccionado = OrdenadorAvanzado<Cancion>::POR_TITULO; break;
                    case 2: criterioSeleccionado = OrdenadorAvanzado<Cancion>::POR_ARTISTA; break;
                    case 3: criterioSeleccionado = OrdenadorAvanzado<Cancion>::POR_ALBUM; break;
                    case 4: criterioSeleccionado = OrdenadorAvanzado<Cancion>::POR_DURACION; break;
                    default:
                        cout << "-> Criterio invalido, usando ordenamiento por titulo\n";
                        criterioSeleccionado = OrdenadorAvanzado<Cancion>::POR_TITULO;
                    }

                    // Medir tiempo de ejecucion del QuickSort
                    auto tiempoInicio = chrono::high_resolution_clock::now();

                    // Aplicar QuickSort
                    OrdenadorAvanzado<Cancion>::ordenar(cancionesTemp, numCancionesTemp, criterioSeleccionado);

                    auto tiempoFin = chrono::high_resolution_clock::now();
                    auto duracionMicrosegundos = chrono::duration_cast<chrono::microseconds>(tiempoFin - tiempoInicio);

                    cout << "\n-> Ordenado en " << duracionMicrosegundos.count() << " microsegundos!\n";

                    // Mostrar canciones ordenadas
                    cout << "\n-> Canciones ordenadas por " << OrdenadorAvanzado<Cancion>::obtenerNombreCriterio(criterioSeleccionado) << ":\n";
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
                        OrdenadorAvanzado<Cancion>::obtenerNombreCriterio(criterioSeleccionado));

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
            string lineas[11] = { "REPRODUCTOR DE CANCION O PODCAST" };
            dibujarCaja(lineas, 1);

            string titulo;
            cout << "Titulo de la cancion o podcast: ";
            getline(cin, titulo);

            // Buscar duracion
            DURACION_TOTAL = -1;

            // Buscar en canciones del usuario
            ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
            int numListas = usuarioLogueado.obtenerCantidadListas();
            for (int i = 0; i < numListas; ++i) {
                const ListaEnlazada<Cancion>& canciones = listas[i].obtenerCanciones();
               
                Cancion tempArray[MAX_CANCIONES]; 
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

            g_enReproduccion.set(false);
            g_detenerHilo.set(false);

            thread hiloCronometro([&]() {
                while (!g_detenerHilo.get()) {
                    if (g_enReproduccion.get() && *p_segundos < DURACION_TOTAL) {
                        this_thread::sleep_for(chrono::seconds(1));
                        {
                            lock_guard<mutex> lock(mtxTiempo);
                            ++(*p_segundos);
                            if (*p_segundos >= DURACION_TOTAL) {
                                g_enReproduccion.set(false);
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
                while (!g_detenerHilo.get()) {
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
                        g_enReproduccion.set(true);
                        cout << ">> Reproduciendo...\n";
                    }
                    break;
                case 2:
                    g_enReproduccion.set(false);
                    cout << ">> Pausado.\n";
                    break;
                case 3:
                    g_detenerHilo.set(true);
                    g_enReproduccion.set(false);
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
            string lineas[12] = { "ORDENAMINETO AVANZADO DE ENLACES(TIMSORT)" };
            dibujarCaja(lineas, 1);

            if (codigosGenerados.getCantidad() == 0) {
                cout << "(No hay enlaces generados aun)\n";
            }
            else {
                string codigos[100]; // Array temporal para ordenar
                for (int i = 0; i < codigosGenerados.getCantidad(); ++i) {
                    codigos[i] = codigosGenerados[i];
                }
                ordenarPorInsercion<string>(codigos, codigosGenerados.getCantidad());
                mostrarOrdenados<string>(codigos, codigosGenerados.getCantidad(), "CODIGOS ORDENADOS (Timsort - 3 ultimos digitos de enlaces)");
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
            string lineas[13] = { "VALORAR FORMATO" };
            dibujarCaja(lineas, 1);
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
                ListaReproduccion* listas = usuarioLogueado.obtenerListaReproduccion();
                int numListas = usuarioLogueado.obtenerCantidadListas();
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
            string lineas[14] = { "VALORACIONES PROMEDIO" };
            dibujarCaja(lineas, 1);
            gestorValoracion.listarPromedios();
            pausar();
            break;
        }
        case 2: { // Ver Valoraciones Ordenado (Counting Sort)
            limpiarPantalla();
            string lineas[15] = { "VALORACIONES PROMEDIO ORDENADO CON COUNTING SORT" };
            dibujarCaja(lineas, 1);
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
            string lineas[16] = { "AGREGAR ENLACE FAVORITO" };
            dibujarCaja(lineas, 1);
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
            string lineas[17] = { "TUS ENLACES FAVORITOS" };
            dibujarCaja(lineas, 1);
            gestorEnlaces.listarFavoritos();
            pausar();
            break;
        }
        case 2: { // Eliminar Enlace
            limpiarPantalla();
            string lineas[18] = { "ELIMINAR ENLACE FAVORITO" };
            dibujarCaja(lineas, 1);
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
            string lineas[19] = { "REGISTRAR PODCAST" };
            dibujarCaja(lineas, 1);
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
            string lineas[20] = { "LISTA DE PODCAST" };
            dibujarCaja(lineas, 1);
            gestorPodcasts.listarPodcasts();
            pausar();
            break;
        }
        case 2: { // Ordenar Podcasts (MergeSort)
            limpiarPantalla();
            string lineas[21] = { "ORDENAR PODCAST CON MERGESORT" };
            dibujarCaja(lineas, 1);
            gestorPodcasts.ordenarPorTituloMerge();
            historial.registrarEvento("Se ordenaron los podcasts por Titulo usando MergeSort");
            pausar();
            break;
        }
        }
        break;
    }
    case GRAFO_MUSICAL: {
        switch (seleccion) {
        case 0:
            limpiarPantalla();
            gestorGrafoCanciones.interactuar(usuarioLogueado); 
            break;
        }
        break;
    }
    case AYUDA: {
        switch (seleccion) {
        case 0: { // Guia del Usuario
            limpiarPantalla();
            string lineas[22] = { "GUIA DE USUARIO" };
            dibujarCaja(lineas, 1);
            estadisticas.mostrarGuia();
            pausar();
            break;
        }
        case 1: { // Historial General
            limpiarPantalla();
            string lineas[23] = { "HISTORIAL GENERAL DE ACTIVIDADES" };
            dibujarCaja(lineas, 1);
            historial.mostrarHistorial();
            pausar();
            break;
        }
        case 2: { // Ver Estadísticas en Árbol
            limpiarPantalla();
            gestorEstadisticasArbol.interactuarConArbol();
            break;
        }
        case 3: { // Creditos
            limpiarPantalla();
            string lineas[24] = { "CREDITOS" };
            dibujarCaja(lineas, 1);
            Creditos::mostrar();
            break;
        }
        }
        break;
    }
    }
}

template <typename T, int MAX_SIZE = 10>
void subMenu(
    MenuOpcion opcion,
    Usuario& usuarioLogueado,
    Historial& historial,
    AdministradorPodcast& gestorPodcasts,
    DatosValoracion& gestorValoracion,
    EnlaceFavorito& gestorEnlaces,
    GuiaUsuario& estadisticas,
    CompartirCancion& gestorCompartir,
    mutex& mtxTiempo
)
{
    string opciones[MAX_OPCIONES_SUBMENU];
    int numOpciones = 0;
    obtenerOpcionesSubmenu(opcion, opciones, numOpciones);

    int seleccion = 0;
    bool salir = false;
    while (!salir) {
        limpiarPantalla();
        dibujarCajaConSeleccion(opciones, seleccion, 60, numOpciones, "MENU PRINCIPAL");
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) seleccion = (seleccion - 1 + numOpciones) % numOpciones;
            if (tecla == 80) seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13) {
            if (seleccion == numOpciones - 1) {
                salir = true;
            }
            else {
                SubMenu(static_cast<MenuOpcion>(opcion), seleccion, usuarioLogueado, historial,
                    gestorPodcasts, gestorValoracion, gestorEnlaces,
                    estadisticas, gestorCompartir, mtxTiempo);
            }
        }
    }
}

void iniciarSesion(Usuario usuarios[], int numUsuarios) {
    limpiarPantalla();
    string lineas[25] = { "INICIAR SESION" };
    dibujarCaja(lineas, 1);
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

    // Instancias de gestores
    CompartirCancion gestorCompartir;
    DatosValoracion gestorValoracion;
    EnlaceFavorito gestorEnlaces;
    GuiaUsuario estadisticas;
    AdministradorPodcast gestorPodcasts;
    Historial historial;

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
    opcionesMenuPrincipal[numOpcionesMenuPrincipal++] = "Grafo Musical";
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
            subMenu<string, MAX_OPCIONES_SUBMENU>(PLAYLIST, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 1: { // Canciones
            subMenu<string, MAX_OPCIONES_SUBMENU>(CANCIONES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 2: { // Valoraciones
            subMenu<string, MAX_OPCIONES_SUBMENU>(VALORACIONES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 3: { // Enlaces
            subMenu<string, MAX_OPCIONES_SUBMENU>(ENLACES, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 4: { // Podcast
            subMenu<string, MAX_OPCIONES_SUBMENU>(PODCAST, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
            break;
        }
        case 5: { // Ayuda
            subMenu<string, MAX_OPCIONES_SUBMENU>(GRAFO_MUSICAL, usuarioLogueado, historial, gestorPodcasts, gestorValoracion, gestorEnlaces, estadisticas, gestorCompartir, mtxTiempo);
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