#pragma once
#include <string>

class DatosComentario {
    static const int MAX_COMENTARIOS = 100;
    std::string claves[MAX_COMENTARIOS];    // título de la canción o playlist
    std::string textos[MAX_COMENTARIOS];    // texto del comentario
    int conteo = 0;

public:
    // Agrega un comentario para la clave dada. Devuelve false si el arreglo está lleno.
    bool agregarComentario(const std::string& clave, const std::string& texto);

    // Lista todos los comentarios en consola, con índice base 1.
    void listarComentarios() const;

    // Elimina el comentario en la posición idx (0-based). Devuelve true si tuvo éxito.
    bool eliminarComentario(int idx);

    // Devuelve cuántos comentarios hay actualmente.
    int obtenerCantidad() const noexcept;
};
