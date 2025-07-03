#pragma once
#include <string>
#include "AdministradorCompartirCancion.h"
using namespace std;
class CompartirCancion {
private:
    AdministradorCompartirCancion admin;
    const string baseURL = "https://open.spotify.com/intl-es/track/";
public:
    string compartir(const string& titulo) {
        if (!admin.agregarCompartido(titulo, baseURL))
            return "";
        return admin.listarCompartidos(), "";
    }
    void listarCompartidos() const {
        admin.listarCompartidos();
    }
};