#pragma once

using namespace std;

class GuiaUsuario {
public:
    void mostrarGuia() const {
        cout << "===== GUIA DE USUARIO - MINI SPOTIFY =====\n";
        cout << "\n1. Crear Playlist: Permite crear una nueva lista de reproduccion con nombre y descripcion.\n";
        cout << "2. Eliminar Playlist: Elimina una lista de reproduccion existente.\n";
        cout << "3. Listar Playlists: Muestra todas tus listas creadas.\n";
        cout << "4. Agregar Cancion: Agrega una nueva cancion a una playlist especifica.\n";
        cout << "5. Eliminar Cancion: Elimina una cancion dentro de una playlist.\n";
        cout << "6. Listar Canciones: Muestra todas las canciones en una playlist.\n";
        cout << "7. Compartir Formato: Genera un link para compartir una cancion o podcast.\n";
        cout << "8. Ver Compartidos: Lista todos los formatos compartidos con sus links.\n";
        cout << "9. Valorar Formato: Asigna una calificacion (1-5) a una cancion o podcast.\n";
        cout << "10. Ver Valoraciones: Muestra el promedio de valoraciones de cada formato.\n";
        cout << "11. Agregar Enlace Favorito: Guarda un link personalizado como favorito.\n";
        cout << "12. Ver Enlaces: Muestra todos los enlaces favoritos guardados.\n";
        cout << "13. Eliminar Enlace: Permite borrar un enlace favorito por su indice.\n";
        cout << "14. Reproducir Formato: Inicia la reproduccion de una cancion o podcast (usa hilos).\n";
        cout << "15. Historial General: Muestra un listado de las acciones recientes.\n";
        cout << "16. Registrar Podcast: Permite registrar un nuevo podcast con titulo, creador y duracion.\n";
        cout << "17. Ver Podcasts: Lista todos los podcasts registrados hasta el momento.\n";
        cout << "18. Ordenar Canciones: Ordena una playlist usando QuickSort por criterio (titulo, artista, etc).\n";
        cout << "0. Cerrar Sesion: Finaliza tu sesion de usuario y retorna al menu principal.\n";
        cout << "\n===========================================\n";
    }
};
