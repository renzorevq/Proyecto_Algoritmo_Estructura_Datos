#pragma once
// using namespace std; // Ya declarado
template <typename T, size_t N>
class ColaCircular {
private:
    T datos[N];
    size_t inicio = 0;
    size_t fin = 0;
    size_t conteo = 0;
public:
    ColaCircular() = default;
    // Encola un nuevo valor si hay espacio; ignora si está llena
    void encolar(const T& valor) {
        if (conteo < N) {
            datos[fin] = valor;
            fin = (fin + 1) % N;
            ++conteo;
        }
    }
    void desencolar() {
        if (conteo > 0) {
            inicio = (inicio + 1) % N;
            --conteo;
        }
    }
    // Accede al elemento en el front (asume no vacía)
    T& frente() {
        return datos[inicio];
    }
    // Comprueba si la cola está vacía
    bool estaVacia() const noexcept {
        return conteo == 0;
    }
    // Comprueba si la cola está llena
    bool estaLlena() const noexcept {
        return conteo == N;
    }
    // Devuelve el número de elementos en la cola
    size_t tamano() const noexcept {
        return conteo;
    }
};