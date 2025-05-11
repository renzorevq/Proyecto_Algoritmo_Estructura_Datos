#pragma once
#include <string>

struct Comentario {
    std::string titulo;   // Título de la canción o playlist
    std::string texto;    // Texto del comentario
};

class DatosComentario {
    static const int MAX = 100;
    Comentario comentarios[MAX];
    int contador = 0;
public:
    // Añade un comentario; devuelve false si el arreglo está lleno
    bool agregarComentario(const std::string& titulo, const std::string& texto);

    // Lista todos los comentarios por pantalla
    void listarComentarios() const;

    // Elimina el comentario en la posición idx (0-based); devuelve false si idx inválido
    bool eliminarComentario(int idx);

    // Devuelve el número de comentarios actualmente almacenados
    int obtenerCantidad() const;
};
