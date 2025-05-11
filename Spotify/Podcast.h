#pragma once
#include <string>
#include <iostream>

class Podcast {
private:
    std::string titulo;
    std::string creador;
    int duracion; // en segundos
public:
    Podcast();
    Podcast(const std::string& titulo, const std::string& creador, int duracion);

    std::string obtenerTitulo() const;
    std::string obtenerCreador() const;
    int obtenerDuracion() const;
};

