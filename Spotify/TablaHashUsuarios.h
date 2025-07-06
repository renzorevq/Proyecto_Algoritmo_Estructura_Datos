#pragma once
#include <string>
#include "Usuario.h"
#include "Nodo.h"  // Usa el Nodo<T> que ya tienes

const int HASH_SIZE = 10;

class TablaHashUsuarios {
private:
    Nodo<Usuario>* tabla[HASH_SIZE];
    int hash(const std::string& correo);

public:
    TablaHashUsuarios();
    void insertar(const Usuario& u);
    Usuario* buscar(const std::string& correo);
    bool eliminar(const std::string& correo);
    void mostrar();
};
