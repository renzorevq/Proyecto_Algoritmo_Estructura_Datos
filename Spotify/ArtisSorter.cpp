#include "ArtisSorter.h"
#include <string>

using namespace std;


void ArtisSorter::ordenarArtista(Cancion canciones[], int artista) {

	for (int i = 1; i < artista; i++) {
		Cancion clave = canciones[i];
		int j = i - 1;

		while (j >= 0 && canciones[j].obtenerArtista() > clave.obtenerArtista()) {
			canciones[j + 1] = canciones[j];
			j = j - 1;

		}

		canciones[j + 1] = clave;

	}

}
