#pragma once
#include <string>
#include "AdministradorCompartirCancion.h"

class CompartirCancion {
private:
    AdministradorCompartirCancion admin;
    const std::string baseURL = "https://open.spotify.com/intl-es/track/";
public:
    std::string compartir(const std::string& titulo) {
        if (!admin.agregarCompartido(titulo, baseURL))
            return "";
        // El admin ya añade el código al final del link
        return admin.listarCompartidos(), ""; // opcional devolver último link
    }
    void listarCompartidos() const {
        admin.listarCompartidos();
    }
};
