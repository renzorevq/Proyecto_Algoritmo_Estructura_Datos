
#pragma once
#ifndef LOGIN_H
#define LOGIN_H


#include "Usuario.h"

using namespace std;

void registrarse(vector<Usuario>& usuarios);
void iniciarSesion(vector<Usuario>& usuarios);
void cargarUsuarios(vector<Usuario>& usuarios);
void guardarUsuarios(const vector<Usuario>& usuarios);

#endif
