#pragma once
#include <string>
using namespace std;

// Limpieza y pausa
void limpiarPantalla();
void pausar();

// Dibujo de cajas
void dibujarCaja(const string lineas[], int numLineas, int ancho = 60);
void lineaHorizontal(int ancho);
void textoCentrado(const string& texto, int ancho, bool seleccion = false);
void dibujarCajaConSeleccion(const string opciones[], int seleccion, int ancho, int numOpciones, const string titulo);

// Lectura con validación
int leerEntero(const string& mensaje);
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo);
