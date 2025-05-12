#include "CompartirCancionOrdenada.h"
#include "chrono" 
#include <iostream>

void CompartirCancionOrdenado::compartirOrdenado(Cancion canciones[], int cantidad) {

	for (int gap = cantidad / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < cantidad; i++) {
			Cancion temp = canciones[i];
			int j = i;

			while (j >= gap && canciones[j - gap].obtenerAlbum() > temp.obtenerAlbum()) {

				canciones[j] = canciones[j - gap];
				j -= gap;

			}
			canciones[j] = temp;
		}
	}
}
