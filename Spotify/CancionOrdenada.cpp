#include "CancionOrdenada.h"
#include "chrono" 
#include <iostream>

void CancionOrdenada::ordenarCancion(Cancion canciones[], int cantidad) {

	clock_t start = clock();

	for (int i = 0; i < cantidad - 1; i++) {
		for (int j = 0; j < cantidad - 1 - i; j++) {

			if (canciones[j].obtenerTitulo() > canciones[j + 1].obtenerTitulo()) {

				Cancion temp = canciones[j];
				canciones[j] = canciones[j + 1];
				canciones[j + 1] = temp;
			}
		}
	}

	clock_t end = clock();

	double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;

	cout << "El tiempo de ordenamiento fue: " << duration << " milisegundos.\n";

	for (int i = 0; i < cantidad; i++) {
		cout << "Cancion " << i + 1 << ": " << canciones[i].obtenerTitulo() << endl;
	}

}
