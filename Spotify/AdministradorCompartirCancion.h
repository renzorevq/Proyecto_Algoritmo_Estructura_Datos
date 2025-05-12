#pragma once
#include <string>

// ----------------------------------------------------------------
// AdministradorCompartirCancion.h
// Gestiona internamente el arreglo de canciones compartidas y sus links.
// ----------------------------------------------------------------
class AdministradorCompartirCancion {
private:
    static const int MAX_COMPARTIDOS = 100;
    std::string titulos[MAX_COMPARTIDOS];
    std::string links[MAX_COMPARTIDOS];
    int conteo = 0;

    // Genera un c�digo aleatorio de 3 d�gitos (cada uno 0�9)
    std::string generarCodigo() const;

public:
    // Agrega un nuevo compartido; devuelve false si est� lleno
    bool agregarCompartido(const std::string& titulo, const std::string& link);

    // Obtiene el n�mero de compartidos actuales
    int obtenerCantidad() const;

    // Muestra por consola todos los t�tulos compartidos y sus links
    void listarCompartidos() const;
};
