#pragma once
#include "Usuario.h"

const int MAX_USUARIOS = 100;

void registrarse(Usuario usuarios[], int& numUsuarios);
void iniciarSesion(Usuario usuarios[], int numUsuarios);
void cargarUsuarios(Usuario usuarios[], int& numUsuarios);
void guardarUsuarios(const Usuario usuarios[], int numUsuarios);