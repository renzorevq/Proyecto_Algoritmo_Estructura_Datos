#include "DatosComentario.h"
#include <iostream>

bool DatosComentario::agregarComentario(const std::string& titulo, const std::string& texto) {
    if (contador >= MAX) return false;
    comentarios[contador++] = { titulo, texto };
    return true;
}

void DatosComentario::listarComentarios() const {
    if (contador == 0) {
        std::cout << "(no hay comentarios)\n";
        return;
    }
    for (int i = 0; i < contador; ++i) {
        std::cout << i + 1 << ". [" << comentarios[i].titulo << "] "
            << comentarios[i].texto << "\n";
    }
}

bool DatosComentario::eliminarComentario(int idx) {
    if (idx < 0 || idx >= contador) return false;
    // desplaza hacia atrás
    for (int i = idx; i + 1 < contador; ++i) {
        comentarios[i] = comentarios[i + 1];
    }
    --contador;
    return true;
}

int DatosComentario::obtenerCantidad() const {
    return contador;
}
