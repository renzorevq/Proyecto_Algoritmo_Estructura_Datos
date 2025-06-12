#pragma once
#include <string>
using namespace std;
class DatosComentario {
    static const int MAX_COMENTARIOS = 100;
    string claves[MAX_COMENTARIOS];
    string textos[MAX_COMENTARIOS];
    int conteo = 0;

public:

    bool agregarComentario(const string& clave, const string& texto);

    void listarComentarios() const;

    bool eliminarComentario(int idx);

    int obtenerCantidad() const noexcept;
};
