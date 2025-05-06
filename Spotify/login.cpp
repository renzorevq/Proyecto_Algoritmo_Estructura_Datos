#include <iostream>
#include <vector>

#include "./login.h"
#include "./utils.h"
#include "./usuario.h"

using namespace std;


void registrarse(vector<Usuario>& usuarios) {
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
        int opcion;

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