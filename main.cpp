#include <iostream>
#include <string>
#include "funciones.h"
#include "codificacion.h"
#include "decodificacion.h"

using namespace std;

int main() {
    cout << "=== SISTEMA DE CODIFICACION ===" << endl;

    int opcion;
    cout << "1. Codificar archivo" << endl;
    cout << "2. Decodificar archivo" << endl;
    cout << "3. Sistema bancario" << endl;
    cout << "Seleccione opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        string entrada, salida;
        int metodo, semilla;

        cout << "Archivo entrada: ";
        cin >> entrada;
        cout << "Archivo salida: ";
        cin >> salida;
        cout << "Metodo (1/2): ";
        cin >> metodo;
        cout << "Semilla: ";
        cin >> semilla;

        if (semilla <= 0) {
            cout << "Semilla debe ser > 0" << endl;
            return 1;
        }

        string texto = leer_archivo(entrada);
        if (texto == "") return 1;

        string binario = texto_a_binario(texto);
        string codificado;

        if (metodo == 1) codificado = codificar_metodo1(binario, semilla);
        else if (metodo == 2) codificado = codificar_metodo2(binario, semilla);
        else {
            cout << "Metodo invalido" << endl;
            return 1;
        }

        escribir_archivo(salida, codificado);

    } else if (opcion == 2) {
        string entrada, salida;
        int metodo, semilla;

        cout << "Archivo entrada: ";
        cin >> entrada;
        cout << "Archivo salida: ";
        cin >> salida;
        cout << "Metodo (1/2): ";
        cin >> metodo;
        cout << "Semilla: ";
        cin >> semilla;

        if (semilla <= 0) {
            cout << "Semilla debe ser > 0" << endl;
            return 1;
        }

        string binario_cod = leer_archivo(entrada);
        if (binario_cod == "") return 1;

        string binario_decod;
        if (metodo == 1) binario_decod = decodificar_metodo1(binario_cod, semilla);
        else if (metodo == 2) binario_decod = decodificar_metodo2(binario_cod, semilla);
        else {
            cout << "Metodo invalido" << endl;
            return 1;
        }

        string texto = binario_a_texto(binario_decod);
        escribir_archivo(salida, texto);

    } else if (opcion == 3) {
        sistema_bancario();
    } else {
        cout << "Opcion invalida" << endl;
    }

    return 0;
}
