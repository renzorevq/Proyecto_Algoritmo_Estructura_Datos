#pragma once

// Cola circular gen�rica (FIFO) basada en un arreglo de tama�o fijo N
// T: tipo de dato almacenado
// N: capacidad m�xima de la cola

template <typename T, size_t N>
class ColaCircular {
private:
    T datos[N];            // buffer circular
    size_t inicio = 0;      // �ndice del siguiente elemento a desencolar
    size_t fin = 0;         // �ndice de la siguiente posici�n libre para encolar
    size_t conteo = 0;      // n�mero de elementos actualmente en la cola

public:
    ColaCircular() = default;

    // Encola un nuevo valor si hay espacio; ignora si est� llena
    void encolar(const T& valor) {
        if (conteo < N) {
            datos[fin] = valor;
            fin = (fin + 1) % N;
            ++conteo;
        }
    }

    // Desencola el elemento en el front; ignora si est� vac�a
    void desencolar() {
        if (conteo > 0) {
            inicio = (inicio + 1) % N;
            --conteo;
        }
    }

    // Accede al elemento en el front (asume no vac�a)
    T& frente() {
        return datos[inicio];
    }

    // Comprueba si la cola est� vac�a
    bool estaVacia() const noexcept {
        return conteo == 0;
    }

    // Comprueba si la cola est� llena
    bool estaLlena() const noexcept {
        return conteo == N;
    }

    // Devuelve el n�mero de elementos en la cola
    size_t tamano() const noexcept {
        return conteo;
    }
};
