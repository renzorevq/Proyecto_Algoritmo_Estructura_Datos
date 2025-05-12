#pragma once
#include <string>

class DatosComentario {
    static const int MAX_COMENTARIOS = 100;
    std::string claves[MAX_COMENTARIOS];    // t�tulo de la canci�n o playlist
    std::string textos[MAX_COMENTARIOS];    // texto del comentario
    int conteo = 0;

public:
    // Agrega un comentario para la clave dada. Devuelve false si el arreglo est� lleno.
    bool agregarComentario(const std::string& clave, const std::string& texto);

    // Lista todos los comentarios en consola, con �ndice base 1.
    void listarComentarios() const;

    // Elimina el comentario en la posici�n idx (0-based). Devuelve true si tuvo �xito.
    bool eliminarComentario(int idx);

    // Devuelve cu�ntos comentarios hay actualmente.
    int obtenerCantidad() const noexcept;
};
