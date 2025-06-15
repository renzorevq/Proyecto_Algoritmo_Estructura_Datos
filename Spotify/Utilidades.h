#pragma once
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>

using namespace std;

void limpiarPantalla();
void pausar();
void dibujarCaja(const vector<string>& lineas, int ancho = 60);
void lineaHorizontal(int ancho);
void textoCentrado(const string& texto, int ancho, bool seleccion = false);
void dibujarCajaConSeleccion(const vector<string>& opciones, int seleccion, int ancho = 40, const string titulo = "");


#endif UTILIDADES_H