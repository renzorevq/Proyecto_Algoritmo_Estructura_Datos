#include "DatosValoracionOrdenado.h"

void DatosValoracionesOrdenado::ordenarporTitulo(Cancion canciones[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int indiceMinimo = i;
		for (int j = i + 1; j < n; j++) {
			if (canciones[j].obtenerTitulo() < canciones[indiceMinimo].obtenerTitulo()) {
				indiceMinimo = j;
			}

		}

		if (indiceMinimo != i) {
			swap(canciones[i], canciones[indiceMinimo]);
		}

	}

}