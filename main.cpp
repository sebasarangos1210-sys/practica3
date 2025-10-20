#include <iostream>
#include <string>
#include "funciones.h"
#include "codificacion.h"
#include "decodificacion.h"
#include "banco.h"
using namespace std;

void banco();

int main() {
    cout << "SISTEMA DE CODIFICACION" << endl;
    cout << "1. Codificar archivo" << endl;
    cout << "2. Decodificar archivo" << endl;
    cout << "3. Sistema bancario" << endl;
    cout << "Seleccione opcion: ";

    int opcion;
    cin >> opcion;

    if (cin.fail()) {
        cout << "Entrada invalida" << endl;
        return 1;
    }

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

        if (cin.fail()) {
            cout << "Error al leer parametros" << endl;
            return 1;
        }

        if (semilla <= 0) {
            cout << "La semilla debe ser mayor a 0" << endl;
            return 1;
        }

        if (metodo != 1 && metodo != 2) {
            cout << "El metodo debe ser 1 o 2" << endl;
            return 1;
        }

        string texto = leer_archivo(entrada);
        if (texto == "") {
            cout << "No se pudo leer el archivo" << endl;
            return 1;
        }

        string binario = texto_a_binario(texto);
        string codificado;

        if (metodo == 1) {
            codificado = codificar_metodo1(binario, semilla);
        } else {
            codificado = codificar_metodo2(binario, semilla);
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

        if (cin.fail()) {
            cout << "Error al leer parametros" << endl;
            return 1;
        }

        if (semilla <= 0) {
            cout << "La semilla debe ser mayor a 0" << endl;
            return 1;
        }

        if (metodo != 1 && metodo != 2) {
            cout << "El metodo debe ser 1 o 2" << endl;
            return 1;
        }

        string binario_cod = leer_archivo(entrada);
        if (binario_cod == "") {
            cout << "No se pudo leer el archivo" << endl;
            return 1;
        }

        string binario_decod;

        if (metodo == 1) {
            binario_decod = decodificar_metodo1(binario_cod, semilla);
        } else {
            binario_decod = decodificar_metodo2(binario_cod, semilla);
        }

        string texto = binario_a_texto(binario_decod);
        escribir_archivo(salida, texto);

    } else if (opcion == 3) {
        banco();

    } else {
        cout << "Opcion invalida" << endl;
        return 1;
    }

    return 0;
}
