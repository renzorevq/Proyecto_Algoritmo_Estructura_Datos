#pragma once
#include <string>

class DatosValoracion {
    static const int MAX_VAL = 100;
    std::string titulos[MAX_VAL];
    int sumaValoracion[MAX_VAL];
    int cantidadValoraciones[MAX_VAL];
    int conteo = 0;

public:
    // Agrega una valoración del 1 al 5
    bool agregarValoracion(const std::string& titulo, int valor);

    // Muestra las valoraciones promedio
    void listarPromedios() const;

    // Devuelve el promedio de una canción específica
    float obtenerPromedio(const std::string& titulo) const;

    int obtenerCantidad() const { return conteo; }
};
