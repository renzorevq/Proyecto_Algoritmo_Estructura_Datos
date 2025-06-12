// login.h
#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <vector>
#include "Usuario.h"

void registrarse(std::vector<Usuario>& usuarios);
void iniciarSesion(std::vector<Usuario>& usuarios);
void cargarUsuarios(std::vector<Usuario>& usuarios);
void guardarUsuarios(const std::vector<Usuario>& usuarios);

#endif
