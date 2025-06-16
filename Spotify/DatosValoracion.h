#pragma once
#include "AdministradorDatosValoracion.h"
#include <string>
using namespace std;
class DatosValoracion : public AdministradorDatosValoracion {
public:
   
    bool agregarValoracion(const string& titulo, int valor);

    
    void listarPromedios() const;

    void listarPromediosOrdenado() const;

    float obtenerPromedio(const string& titulo) const;

    int obtenerCantidad() const { return conteo; }
};
