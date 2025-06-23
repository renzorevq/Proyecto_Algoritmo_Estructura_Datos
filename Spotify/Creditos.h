#pragma once
#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Creditos {
public:
    static void mostrar() {
        system("cls");
        cout << "|-----------------------------------------------|\n";
        cout << "|              -----CREDITOS-----               |\n";
        cout << "|                                               |\n";
        cout << "| Jari Hassan                                   |\n";
        cout << "|                                               |\n";
        cout << "| Juan Felipe Granados Allende                  |\n";
        cout << "|                                               |\n";
        cout << "| Mathias Acuache                               |\n";
        cout << "|                                               |\n";
        cout << "| Renzo Zamir                                   |\n";
        cout << "|                                               |\n";
        cout << "| Joaquin Armando Gutierrez Quispe              |\n";
        cout << "|                                               |\n";
        cout << "| Universidad Peruana de Ciencias Aplicadas     |\n";
        cout << "|                                               |\n";
        cout << "| PRESIONE LA TECLA ENTER PARA CONTINUAR...     |\n";
        cout << "-------------------------------------------------\n";

        SetANSIColor(31);
        cout << "                 %%                 \n";
        cout << "               %%%%            (.   \n";
        cout << "      #*      %%%%%              #, \n";
        cout << "   #%*      %%%%%%%%*            %# \n";
        cout << "  #%%       (%%%%%%%%%/          (%%\n";
        cout << " #%%%        %%%%%%%%%%%         /%%\n";
        cout << "%%%%         /%%%%%%%%%/        %%%%\n";
        cout << "%%%%#           %%%%%%%#       (%%%%\n";
        cout << "%%%%%#            %%%%%,      %%%%%%\n";
        cout << " %%%%%%#          ,%%%      #%%%%%% \n";
        cout << " %%%%%%%%%/        (%,  (%%%%%%%%%  \n";
        cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   \n";
        cout << "    %%%%%%%%%%%%%%%%%%%%%%%%%%%     \n";
        cout << "        (%%%%%%%%%%%%%%%%%%%        \n";
        cout << "              *%%%%%%%%%*           \n";
        SetANSIColor(0);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

private:
    static void SetANSIColor(int colorCode) {
        cout << "\033[" << colorCode << "m";
    }
};
