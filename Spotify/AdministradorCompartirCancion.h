#pragma once

using namespace std;
class AdministradorCompartirCancion {
private:
    static const int MAX_COMPARTIDOS = 100;
    string titulos[MAX_COMPARTIDOS];
    string links[MAX_COMPARTIDOS];
    int conteo = 0;


    string generarCodigo() const;

public:
    // Agrega un nuevo compartido; devuelve false si est� lleno
    bool agregarCompartido(const string& titulo, const string& link);

    // Obtiene el n�mero de compartidos actuales
    int obtenerCantidad() const;

    // Muestra por consola todos los t�tulos compartidos y sus links
    void listarCompartidos() const;
};
