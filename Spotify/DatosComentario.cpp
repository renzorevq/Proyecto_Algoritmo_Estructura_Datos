#include "DatosComentario.h"
#include <iostream>

bool DatosComentario::agregarComentario(const std::string& clave, const std::string& texto) {
    if (conteo >= MAX_COMENTARIOS) return false;
    claves[conteo] = clave;
    textos[conteo] = texto;
    ++conteo;
    return true;
}

void DatosComentario::listarComentarios() const {
    if (conteo == 0) {
        std::cout << "(no hay comentarios aún)\n";
        return;
    }
    for (int i = 0; i < conteo; ++i) {
        std::cout << (i + 1) << ". [" << claves[i] << "] " << textos[i] << "\n";
    }
}

bool DatosComentario::eliminarComentario(int idx) {
    if (idx < 0 || idx >= conteo) return false;
    // desplazamos hacia atrás los siguientes
    for (int i = idx; i + 1 < conteo; ++i) {
        claves[i] = claves[i + 1];
        textos[i] = textos[i + 1];
    }
    --conteo;
    return true;
}

int DatosComentario::obtenerCantidad() const noexcept {
    return conteo;
}
