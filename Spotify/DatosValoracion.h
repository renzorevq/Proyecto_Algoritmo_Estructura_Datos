#pragma once
#include "AdministradorDatosValoracion.h"

using namespace std;
class DatosValoracion : public AdministradorDatosValoracion {
public:
    static const int MAX_VAL = 100;
    static const int MAX_TITULOS = 100;

    string titulos[MAX_VAL];
    int sumaValoracion[MAX_VAL];
    int cantidadValoraciones[MAX_VAL];
    int conteo = 0;
    bool agregarValoracion(const string& titulo, int valor);

    
    void listarPromedios() const;

    void listarPromediosOrdenado() const;

    float obtenerPromedio(const string& titulo) const;

    int obtenerCantidad() const { return conteo; }
};
