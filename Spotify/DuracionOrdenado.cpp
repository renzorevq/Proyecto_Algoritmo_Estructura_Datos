#include "DuracionOrdenado.h"

void DuracionOrdenado::ordenarporDuracion(Cancion canciones[], int cantidad) {

	for (int i = 0; i < cantidad; i++) {
		for (int j = 0; j < cantidad - i - 1; j++) {
			if (canciones[j].obtenerDuracion() > canciones[j + 1].obtenerDuracion()) {

				Cancion temp = canciones[j];
				canciones[j] = canciones[j + 1];
				canciones[j + 1] = temp;
			}
		}
	}
}

