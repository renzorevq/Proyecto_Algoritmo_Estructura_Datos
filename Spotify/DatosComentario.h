#pragma once
#include <string>

struct Comentario {
    std::string titulo;   // T�tulo de la canci�n o playlist
    std::string texto;    // Texto del comentario
};

class DatosComentario {
    static const int MAX = 100;
    Comentario comentarios[MAX];
    int contador = 0;
public:
    // A�ade un comentario; devuelve false si el arreglo est� lleno
    bool agregarComentario(const std::string& titulo, const std::string& texto);

    // Lista todos los comentarios por pantalla
    void listarComentarios() const;

    // Elimina el comentario en la posici�n idx (0-based); devuelve false si idx inv�lido
    bool eliminarComentario(int idx);

    // Devuelve el n�mero de comentarios actualmente almacenados
    int obtenerCantidad() const;
};
