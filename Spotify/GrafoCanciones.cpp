#include <vector>
#include "GrafoCanciones.h"
#include "Usuario.h"
#include "ListaReproduccion.h"
#include "Cancion.h"
#include "ListaEnlazada.h"
#include "Utilidades.h"
#include <iostream>
#include <windows.h>
#include <conio.h>



using namespace std;

GrafoCanciones::GrafoCanciones() : total(0) {
    for (int i = 0; i < MAX_GRAFO; ++i)
        for (int j = 0; j < MAX_GRAFO; ++j)
            matrizAdy[i][j] = false;
}

void ubicar(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void dibujarLinea(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (true) {
        ubicar(x0, y0);
        // elige el carácter según la dirección del paso
        if (dx > abs(dy)) cout << (sx > 0 ? '─' : '─');
        else cout << (sy > 0 ? '│' : '│');
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
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

void GrafoCanciones::mostrarGrafoVisual() {
    system("cls");
    cout << "=== GRAFO DE CANCIONES (VISUAL) ===\n\n";
    if (total == 0) {
        cout << "-> No hay canciones cargadas.\n";
        pausar();
        return;
    }

    // 1) Coloca nodos en una cuadrícula
    const int cols = 4;
    const int spanX = 20, spanY = 6;
    const int ox = 5, oy = 3;
    // en lugar de vector, dos arrays fijos:
    int posX[MAX_GRAFO];
    int posY[MAX_GRAFO];

    for (int i = 0; i < total; ++i) {
        int r = i / cols, c = i % cols;
        posX[i] = ox + c * spanX;
        posY[i] = oy + r * spanY;
        ubicar(posX[i], posY[i]);
        string label = nodos[i].substr(0, 10);
        cout << "┌" << string(label.size(), '─') << "┐";
        ubicar(posX[i], posY[i] + 1);
        cout << "│" << label << "│";
        ubicar(posX[i], posY[i] + 2);
        cout << "└" << string(label.size(), '─') << "┘";
    }

    // 2) Dibuja conexiones con Bresenham
    for (int i = 0; i < total; ++i) {
        for (int j = i + 1; j < total; ++j) {
            if (matrizAdy[i][j]) {
                int x0 = posX[i] + (int)nodos[i].substr(0, 10).size() / 2 + 1;
                int y0 = posY[i] + 1;
                int x1 = posX[j] + (int)nodos[j].substr(0, 10).size() / 2 + 1;
                int y1 = posY[j] + 1;
                dibujarLinea(x0, y0, x1, y1);
            }
        }
    }

    ubicar(0, oy + ((total + cols - 1) / cols) * spanY + 3);
    cout << "\n-> Presione ENTER para volver...";
    while (_getch() != 13) {}
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
                const ListaEnlazada<Cancion>& canciones = listas[i].obtenerCanciones();
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