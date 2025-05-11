#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "EnlaceFavorito.h"
#include "DatosValoracion.h"
#include "DatosComentario.h"
#include "CompartirCancion.h"
#include "Login.h"
#include "Utils.h"
#include "Usuario.h"

using namespace std;

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

    bool sesionActiva = true;
    int  opcion;

    while (sesionActiva) {
        limpiarPantalla();
        dibujarCaja({
            "SESION: " + usuarioLogueado.obtenerNombre(),
            "1. Crear Playlist", "2. Eliminar Playlist",
            "3. Listar Playlists", "4. Agregar Cancion",
            "5. Eliminar Cancion", "6. Listar Canciones",
            "7. Cerrar Sesion",
            "8. Agregar Comentario", "9. Ver Comentarios",
            "10. Eliminar Comentario",
            "11. Compartir Cancion", "12. Ver Compartidos",
            "13. Valorar Cancion", "14. Ver Valoraciones",
            "15. Agregar Enlace Favorito", "16. Ver Enlaces", 
            "17. Eliminar Enlace"
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
            usuarioLogueado.crearPlaylist(Playlist(nombreP, descP));
            cout << "-> Playlist creada!\n";
            pausar();
            break;
        }
        case 2: {
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR PLAYLIST" });
            string nombreP;
            cout << "Nombre Playlist: "; getline(cin, nombreP);
            usuarioLogueado.eliminarPlaylist(nombreP);
            cout << "-> Eliminada si existia!\n";
            pausar();
            break;
        }
        case 3: {
            limpiarPantalla();
            dibujarCaja({ "TUS PLAYLISTS" });
            for (const auto& p : usuarioLogueado.obtenerPlaylists())
                cout << "* " << p.obtenerNombre() << "\n";
            pausar();
            break;
        }
        case 4: {
            limpiarPantalla();
            dibujarCaja({ "AGREGAR CANCION" });
            string nombreP, t, art, alb;
            int    dur;
            cout << "Playlist      : "; getline(cin, nombreP);
            cout << "Titulo Cancion: "; getline(cin, t);
            cout << "Artista       : "; getline(cin, art);
            cout << "Album         : "; getline(cin, alb);
            cout << "Duracion (s)  : "; cin >> dur; cin.ignore();
            for (auto& p : usuarioLogueado.obtenerPlaylists())
                if (p.obtenerNombre() == nombreP)
                    p.agregarCancion(Cancion(t, art, alb, dur));
            cout << "-> Cancion agregada!\n";
            pausar();
            break;
        }
        case 5: {
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR CANCION" });
            string nombreP, t;
            cout << "Playlist      : "; getline(cin, nombreP);
            cout << "Titulo Cancion: "; getline(cin, t);
            for (auto& p : usuarioLogueado.obtenerPlaylists())
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
            for (const auto& p : usuarioLogueado.obtenerPlaylists())
                if (p.obtenerNombre() == nombreP)
                    p.listarCanciones();
            pausar();
            break;
        }
        case 7:
            sesionActiva = false;
            break;

        case 8: {  // Agregar Comentario
            limpiarPantalla();
            dibujarCaja({ "AGREGAR COMENTARIO" });
            string titulo, texto;
            cout << "Titulo (cancion/playlist): "; getline(cin, titulo);
            cout << "Comentario               : "; getline(cin, texto);
            if (gestorComentarios.agregarComentario(titulo, texto))
                cout << "-> Comentario añadido!\n";
            else
                cout << "-> Capacidad de comentarios llena!\n";
            pausar();
            break;
        }
        case 9:  // Ver Comentarios
            limpiarPantalla();
            dibujarCaja({ "LISTA DE COMENTARIOS" });
            gestorComentarios.listarComentarios();
            pausar();
            break;

        case 10: {  // Eliminar Comentario
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

        case 11: {  // Compartir Cancion
            limpiarPantalla();
            dibujarCaja({ "COMPARTIR CANCION" });
            string titulo;
            cout << "Titulo de la cancion: "; getline(cin, titulo);
            string link = gestorCompartir.compartir(titulo);
            if (!link.empty())
                cout << "-> Link generado: " << link << "\n";
            else
                cout << "-> Límite de compartidos alcanzado!\n";
            pausar();
            break;
        }
        case 12: { // Ver Compartidos
            limpiarPantalla();
            dibujarCaja({ "CANCIONES COMPARTIDAS" });
            gestorCompartir.listarCompartidos();
            pausar();
            break;
        }
        case 13: { // VALORAR CANCIÓN
            limpiarPantalla();
            dibujarCaja({ "VALORAR CANCION" });
            std::string titulo;
            int valor;
            std::cout << "Titulo de la cancion: "; getline(std::cin, titulo);
            std::cout << "Valor (1-5): "; std::cin >> valor; std::cin.ignore();

            if (gestorValoracion.agregarValoracion(titulo, valor))
                std::cout << "-> Valoracion guardada!\n";
            else
                std::cout << "-> Valor no valido o capacidad llena\n";
            pausar();
            break;
        }
        case 14: { // VER VALORACIONES
            limpiarPantalla();
            dibujarCaja({ "VALORACIONES PROMEDIO" });
            gestorValoracion.listarPromedios();
            pausar();
            break;
        }
        case 15: {
            limpiarPantalla();
            dibujarCaja({ "AGREGAR ENLACE FAVORITO" });
            std::string titulo, url;
            std::cout << "Titulo de la cancion: "; getline(std::cin, titulo);
            std::cout << "URL externa         : "; getline(std::cin, url);
            if (gestorEnlaces.agregarEnlace(titulo, url))
                std::cout << "-> Enlace guardado!\n";
            else
                std::cout << "-> Límite alcanzado!\n";
            pausar();
            break;
        }
        case 16: {
            limpiarPantalla();
            dibujarCaja({ "TUS ENLACES FAVORITOS" });
            gestorEnlaces.listarFavoritos();
            pausar();
            break;
        }
        case 17: {
            limpiarPantalla();
            dibujarCaja({ "ELIMINAR ENLACE FAVORITO" });
            gestorEnlaces.listarFavoritos();
            std::cout << "Indice a eliminar: ";
            int idx; std::cin >> idx; std::cin.ignore();
            if (gestorEnlaces.eliminarEnlace(idx - 1))
                std::cout << "-> Enlace eliminado!\n";
            else
                std::cout << "-> Indice no válido\n";
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
