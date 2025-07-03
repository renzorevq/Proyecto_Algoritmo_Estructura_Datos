#pragma once
#include <string>

using namespace std;

void limpiarPantalla();
void pausar();
void dibujarCaja(const string lineas[], int numLineas, int ancho = 60);
void lineaHorizontal(int ancho);
void textoCentrado(const string& texto, int ancho, bool seleccion = false);
void dibujarCajaConSeleccion(const string opciones[], int seleccion, int ancho, int numOpciones, const string titulo);