#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

void limpiarPantalla();
void pausar();
void dibujarCaja(const vector<string>& lineas, int ancho = 60);
void lineaHorizontal(int ancho);
void textoCentrado(const string& texto, int ancho);

#endif UTILS_H