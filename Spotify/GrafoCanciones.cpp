#include "GrafoCanciones.h"
#include "Usuario.h"
#include "ListaReproduccion.h"
#include "Cancion.h"
#include "ListaEnlazada.h"
#include "Utilidades.h"
#include <iostream>



using namespace std;

GrafoCanciones::GrafoCanciones() : total(0) {
    for (int i = 0; i < MAX_GRAFO; ++i)
        for (int j = 0; j < MAX_GRAFO; ++j)
            matrizAdy[i][j] = false;
}

int GrafoCanciones::buscarIndice(const string& nombre) {
    for (int i = 0; i < total; ++i)
        if (nodos[i] == nombre) return i;
    return -1;
}

bool GrafoCanciones::agregarCancion(const string& nombre) {
    if (total >= MAX_GRAFO || buscarIndice(nombre) != -1) return false;
    nodos[total++] = nombre;
    return true;
}

bool GrafoCanciones::agregarConexion(const string& a, const string& b) {
    int i = buscarIndice(a), j = buscarIndice(b);
    if (i == -1 || j == -1) return false;
    matrizAdy[i][j] = matrizAdy[j][i] = true;
    return true;
}

void GrafoCanciones::mostrarGrafo() {
    cout << "\n--- GRAFO DE CANCIONES ---\n";
    for (int i = 0; i < total; ++i) {
        cout << nodos[i] << " -> ";
        for (int j = 0; j < total; ++j)
            if (matrizAdy[i][j])
                cout << nodos[j] << "  ";
        cout << "\n";
    }
}

void GrafoCanciones::interactuar(Usuario& usuario) {
    bool salir = false;
    while (!salir) {
        limpiarPantalla();
        cout << "+------------------------------------------+\n";
        cout << "|         DESCARGAS OFFLINE DISPONIBLES   |\n";
        cout << "+------------------------------------------+\n";
        cout << "1. Descargar Canciones Disponibles\n";
        cout << "2. Vincular Reproducciones Sugeridas\n";
        cout << "3. Ver Canciones Descargadas\n";
        cout << "4. Volver\n";


        int op = leerEnteroEnRango("Seleccione: ", 1, 4);
        switch (op) {
        case 1: {
            // Recorremos todas las canciones de todas las playlists del usuario
            int agregadas = 0;
            ListaReproduccion* listas = usuario.obtenerListaReproduccion();
            int numListas = usuario.obtenerCantidadListas();
            for (int i = 0; i < numListas; ++i) {
                ListaEnlazada<Cancion>& canciones = listas[i].obtenerCanciones();
                canciones.porCada([&](const Cancion& c) {
                    if (agregarCancion(c.obtenerTitulo())) {
                        agregadas++;
                    }
                    });
            }
            cout << "-> Se descargaron " << agregadas << " canciones para escuchar sin conexión.\n";
            pausar();
            break;
        }
        case 2: {
            cout << "\nCanciones disponibles:\n";
            for (int i = 0; i < total; ++i) {
                cout << i + 1 << ". " << nodos[i] << "\n";
            }
            if (total < 2) {
                cout << "-> Agrega más canciones primero.\n";
                pausar();
                break;
            }
            int i = leerEnteroEnRango("Origen: ", 1, total) - 1;
            int j = leerEnteroEnRango("Destino: ", 1, total) - 1;
            if (i == j) {
                cout << "-> No puedes conectar una canción consigo misma.\n";
            }
            else if (matrizAdy[i][j]) {
                cout << "-> Ya están conectadas.\n";
            }
            else {
                matrizAdy[i][j] = matrizAdy[j][i] = true;
                cout << "-> Reproducciones relacionadas correctamente.\n";

            }
            pausar();
            break;
        }
        case 3: {
            cout << "\n--- Canciones Descargadas y Reproducciones Sugeridas ---\n";
            for (int i = 0; i < total; ++i) {
                cout << "* " << nodos[i] << " --> ";
                bool tieneConexiones = false;
                for (int j = 0; j < total; ++j) {
                    if (matrizAdy[i][j]) {
                        cout << nodos[j] << " ";
                        tieneConexiones = true;
                    }
                }
                if (!tieneConexiones)
                    cout << "(sin conexiones)";
                cout << "\n";
            }
            pausar();
            break;
        }
        case 4:
            salir = true;
            break;
        }
    }
}