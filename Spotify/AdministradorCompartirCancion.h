#pragma once
#include <string>
#include <ctime>
using namespace std;
class AdministradorCompartirCancion {
private:
    static const int MAX_COMPARTIDOS = 100;
    string titulos[MAX_COMPARTIDOS];
    string enlaces[MAX_COMPARTIDOS];
    int cantidadCompartidos = 0;
    mutable unsigned int semilla;
    void inicializarSemilla() const;
    int generarDigitoAleatorio() const;
    string generarCodigo() const;
public:
    AdministradorCompartirCancion();
    bool agregarCompartido(const string& titulo, const string& enlaceBase);
    int obtenerCantidad() const;
    void listarCompartidos() const;
};