#pragma once
#include "Usuario.h"

const int MAX_USUARIOS = 100;

void registrarse(Usuario usuarios[], int& numUsuarios);
void iniciarSesion(Usuario usuarios[], int numUsuarios);

void cargarUsuarios(Usuario usuarios[], int& numUsuarios);
void guardarUsuarios(const Usuario usuarios[], int numUsuarios);

void cargarPlaylists(Usuario usuarios[], int& numUsuarios);
void guardarPlaylists(const Usuario usuarios[], int numUsuarios);

void cargarCanciones(Usuario usuarios[], int& numUsuarios);
void guardarCanciones(const Usuario usuarios[], int numUsuarios);

void cargarPodcasts(Usuario usuarios[], int& numUsuarios);
void guardarPodcasts(const Usuario usuarios[], int numUsuarios);
