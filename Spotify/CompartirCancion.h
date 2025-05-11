#pragma once
#include <string>

class CompartirCancion {
    static const int MAX_COMPARTIDOS = 100;
    std::string titulos[MAX_COMPARTIDOS];
    std::string links[MAX_COMPARTIDOS];
    int conteo = 0;

    // Genera un c�digo aleatorio de 3 d�gitos (cada uno 0�9)
    std::string generarCodigo() const;

public:
    // Genera y devuelve un link para compartir la canci�n.
    // Devuelve cadena vac�a si se supera MAX_COMPARTIDOS.
    std::string compartir(const std::string& titulo);

    // Muestra por consola todos los t�tulos compartidos y sus links
    void listarCompartidos() const;
};
