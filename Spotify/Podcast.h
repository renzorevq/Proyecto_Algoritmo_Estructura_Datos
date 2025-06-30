#pragma once

#include <iostream>
using namespace std;
class Podcast {
private:
    string titulo;
    string creador;
    int duracion;
public:
    Podcast();
    Podcast(const string& titulo, const string& creador, int duracion);

    string obtenerTitulo() const;
    string obtenerCreador() const;
    int obtenerDuracion() const;
};

