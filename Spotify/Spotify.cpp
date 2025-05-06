//#include "pch.h"
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <string>

using namespace std;

// Utilidades de consola
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\n[ENTER] para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Dibuja caja ASCII
void lineaHorizontal(int ancho) {
    cout << "+" << string(ancho - 2, '-') << "+\n";
}

void textoCentrado(const string& texto, int ancho) {
    int relleno = (ancho - texto.size()) / 2;
    cout << "|" << string(relleno, ' ') << texto << string(ancho - 2 - relleno - texto.size(), ' ') << "|\n";
}

void dibujarCaja(const vector<string>& lineas, int ancho = 60) {
    lineaHorizontal(ancho);
    for (const auto& linea : lineas) textoCentrado(linea, ancho);
    lineaHorizontal(ancho);
}

// Estructura de datos genérica: lista enlazada simple
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class ListaEnlazada {
    Nodo<T>* cabeza;
public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada() { limpiar(); }
    void insertar(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (!cabeza) cabeza = nuevo;
        else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente) actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }
    bool eliminar(const function<bool(const T&)>& criterio) {
        Nodo<T>* anterior = nullptr;
        Nodo<T>* actual = cabeza;
        while (actual) {
            if (criterio(actual->dato)) {
                if (anterior) anterior->siguiente = actual->siguiente;
                else cabeza = actual->siguiente;
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }
    bool estaVacia() const { return cabeza == nullptr; }
    void porCada(const function<void(const T&)>& accion) const {
        Nodo<T>* actual = cabeza;
        while (actual) {
            accion(actual->dato);
            actual = actual->siguiente;
        }
    }
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
    }
};

// Pila genérica (LIFO)
template <typename T>
class Pila {
    vector<T> elementos;
public:
    void push(const T& valor) { elementos.push_back(valor); }
    void pop() {
        if (elementos.empty()) throw out_of_range("Pila vacia");
        elementos.pop_back();
    }
    T& top() {
        if (elementos.empty()) throw out_of_range("Pila vacia");
        return elementos.back();
    }
    bool estaVacia() const { return elementos.empty(); }
};

// Cola genérica (FIFO)
template <typename T>
class Cola {
    list<T> elementos;
public:
    void encolar(const T& valor) { elementos.push_back(valor); }
    void desencolar() {
        if (elementos.empty()) throw out_of_range("Cola vacia");
        elementos.pop_front();
    }
    T& frente() {
        if (elementos.empty()) throw out_of_range("Cola vacia");
        return elementos.front();
    }
    bool estaVacia() const { return elementos.empty(); }
};

// Clases del dominio
class Cancion {
    string titulo;
    string artista;
    string album;
    int duracion;
public:
    Cancion() {}
    Cancion(const string& tituloCancion,
        const string& nombreArtista,
        const string& nombreAlbum,
        int duracionSegundos)
        : titulo(tituloCancion), artista(nombreArtista), album(nombreAlbum), duracion(duracionSegundos) {
    }
    string obtenerTitulo() const { return titulo; }
    string obtenerArtista() const { return artista; }
};

class Playlist {
    string nombre;
    string descripcion;
    ListaEnlazada<Cancion> canciones;
public:
    Playlist() {}
    Playlist(const string& nombrePlaylist, const string& descripcionPlaylist)
        : nombre(nombrePlaylist), descripcion(descripcionPlaylist) {
    }
    void agregarCancion(const Cancion& cancion) {
        canciones.insertar(cancion);
    }
    void eliminarCancion(const string& tituloCancion) {
        canciones.eliminar([&](const Cancion& c) {
            return c.obtenerTitulo() == tituloCancion;
            });
    }
    void listarCanciones() const {
        dibujarCaja({ "PLAYLIST: " + nombre, descripcion });
        if (canciones.estaVacia()) {
            cout << "(sin canciones)" << "\n";
        }
        else {
            canciones.porCada([&](const Cancion& c) {
                cout << "- " << c.obtenerTitulo() << " - " << c.obtenerArtista() << "\n";
                });
        }
    }
    string obtenerNombre() const { return nombre; }
};

class Usuario {
    string nombre;
    string correo;
    string contrasena;
    vector<Playlist> misPlaylists;
public:
    Usuario() {}
    Usuario(const string& nombreUsuario,
        const string& correoElectronico,
        const string& contrasenaUsuario)
        : nombre(nombreUsuario), correo(correoElectronico), contrasena(contrasenaUsuario) {
    }
    string obtenerNombre() const { return nombre; }
    string obtenerCorreo() const { return correo; }
    string obtenerContrasena() const { return contrasena; }
    vector<Playlist>& obtenerPlaylists() { return misPlaylists; }
    void crearPlaylist(const Playlist& nuevaPlaylist) {
        misPlaylists.push_back(nuevaPlaylist);
    }
    void eliminarPlaylist(const string& nombrePlaylist) {
        misPlaylists.erase(
            remove_if(
                misPlaylists.begin(),
                misPlaylists.end(),
                [&](const Playlist& p) { return p.obtenerNombre() == nombrePlaylist; }
            ),
            misPlaylists.end()
        );
    }
};

// Persistencia de usuarios
void cargarUsuarios(vector<Usuario>& usuarios) {
    ifstream archivo("usuarios.txt");
    string linea;
    while (getline(archivo, linea)) {
        string nombreUsuario, correoElectronico, contrasenaUsuario;
        stringstream ss(linea);
        getline(ss, nombreUsuario, ',');
        getline(ss, correoElectronico, ',');
        getline(ss, contrasenaUsuario, ',');
        usuarios.emplace_back(nombreUsuario, correoElectronico, contrasenaUsuario);
    }
}

void guardarUsuarios(const vector<Usuario>& usuarios) {
    ofstream archivo("usuarios.txt");
    for (const auto& u : usuarios) {
        archivo << u.obtenerNombre() << ","
            << u.obtenerCorreo() << ","
            << u.obtenerContrasena() << "\n";
    }
}

int main() {
    vector<Usuario> usuarios;
    cargarUsuarios(usuarios);
    bool ejecutando = true;
    while (ejecutando) {
        limpiarPantalla();
        dibujarCaja({ "MINI SPOTIFY", "1. Registrarse", "2. Iniciar Sesion", "3. Salir" });
        cout << "Seleccione opcion: ";
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opcion == 1) {
            limpiarPantalla();
            dibujarCaja({ "REGISTRARSE" });
            string nombreUsuario, correoElectronico, contrasenaUsuario;
            cout << "Nombre: "; getline(cin, nombreUsuario);
            cout << "Correo: "; getline(cin, correoElectronico);
            cout << "Contrasena: "; getline(cin, contrasenaUsuario);
            usuarios.emplace_back(nombreUsuario, correoElectronico, contrasenaUsuario);
            cout << "-> Usuario registrado!" << "\n";
            pausar();
        }
        else if (opcion == 2) {
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
                cout << "-> Usuario no existe!" << "\n";
                pausar();
            }
            else if (it->obtenerContrasena() != contrasenaUsuario) {
                cout << "-> Contrasena incorrecta!" << "\n";
                pausar();
            }
            else {
                Usuario& usuarioLogueado = *it;
                bool sesionActiva = true;
                while (sesionActiva) {
                    limpiarPantalla();
                    dibujarCaja({
                        "SESION: " + usuarioLogueado.obtenerNombre(),
                        "1.Crear Playlist", "2.Eliminar Playlist",
                        "3.Listar Playlists", "4.Agregar Cancion",
                        "5.Eliminar Cancion", "6.Listar Canciones",
                        "7.Cerrar Sesion"
                        });
                    cout << "Seleccione opcion: ";
                    cin >> opcion;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opcion == 1) {
                        limpiarPantalla();
                        dibujarCaja({ "CREAR PLAYLIST" });
                        string nombrePlaylist, descripcionPlaylist;
                        cout << "Nombre Playlist: "; getline(cin, nombrePlaylist);
                        cout << "Descripcion     : "; getline(cin, descripcionPlaylist);
                        usuarioLogueado.crearPlaylist(Playlist(nombrePlaylist, descripcionPlaylist));
                        cout << "-> Playlist creada!" << "\n";
                        pausar();
                    }
                    else if (opcion == 2) {
                        limpiarPantalla();
                        dibujarCaja({ "ELIMINAR PLAYLIST" });
                        string nombrePlaylist;
                        cout << "Nombre Playlist: "; getline(cin, nombrePlaylist);
                        usuarioLogueado.eliminarPlaylist(nombrePlaylist);
                        cout << "-> Eliminada si existia!" << "\n";
                        pausar();
                    }
                    else if (opcion == 3) {
                        limpiarPantalla();
                        dibujarCaja({ "TUS PLAYLISTS" });
                        for (const auto& p : usuarioLogueado.obtenerPlaylists()) {
                            cout << "* " << p.obtenerNombre() << "\n";
                        }
                        pausar();
                    }
                    else if (opcion == 4) {
                        limpiarPantalla();
                        dibujarCaja({ "AGREGAR CANCION" });
                        string nombrePlaylist, tituloCancion, artistaCancion, albumCancion;
                        int duracionCancion;
                        cout << "Playlist      : "; getline(cin, nombrePlaylist);
                        cout << "Titulo Cancion: "; getline(cin, tituloCancion);
                        cout << "Artista       : "; getline(cin, artistaCancion);
                        cout << "Album         : "; getline(cin, albumCancion);
                        cout << "Duracion (s)  : "; cin >> duracionCancion; cin.ignore();
                        for (auto& p : usuarioLogueado.obtenerPlaylists()) {
                            if (p.obtenerNombre() == nombrePlaylist) {
                                p.agregarCancion(Cancion(tituloCancion, artistaCancion, albumCancion, duracionCancion));
                            }
                        }
                        cout << "-> Cancion agregada!" << "\n";
                        pausar();
                    }
                    else if (opcion == 5) {
                        limpiarPantalla();
                        dibujarCaja({ "ELIMINAR CANCION" });
                        string nombrePlaylist, tituloCancion;
                        cout << "Playlist      : "; getline(cin, nombrePlaylist);
                        cout << "Titulo Cancion: "; getline(cin, tituloCancion);
                        for (auto& p : usuarioLogueado.obtenerPlaylists()) {
                            if (p.obtenerNombre() == nombrePlaylist) {
                                p.eliminarCancion(tituloCancion);
                            }
                        }
                        cout << "-> Eliminada si existia!" << "\n";
                        pausar();
                    }
                    else if (opcion == 6) {
                        limpiarPantalla();
                        dibujarCaja({ "LISTAR CANCIONES" });
                        string nombrePlaylist;
                        cout << "Playlist: "; getline(cin, nombrePlaylist);
                        for (const auto& p : usuarioLogueado.obtenerPlaylists()) {
                            if (p.obtenerNombre() == nombrePlaylist) {
                                p.listarCanciones();
                            }
                        }
                        pausar();
                    }
                    else if (opcion == 7) {
                        sesionActiva = false;
                    }
                }
            }
        }
        else if (opcion == 3) {
            ejecutando = false;
        }
    }
    guardarUsuarios(usuarios);
    return 0;
}