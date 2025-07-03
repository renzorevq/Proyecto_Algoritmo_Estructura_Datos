#pragma once
#include "Usuario.h"
// Límite máximo de usuarios
const int MAX_USUARIOS = 100;
// Prototipos usando sólo arreglos, sin vector
void registrarse(Usuario usuarios[], int& numUsuarios);
void iniciarSesion(Usuario usuarios[], int numUsuarios);
void cargarUsuarios(Usuario usuarios[], int& numUsuarios);
void guardarUsuarios(const Usuario usuarios[], int numUsuarios);