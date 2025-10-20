#include <iostream>
#include <fstream>
#include <string>
#include "funciones.h"

using namespace std;

string leer_archivo(string nombre_archivo) {
    ifstream archivo(nombre_archivo, ios::binary);
    string contenido = "";

    if (!archivo) {
        cout << "Error: No se pudo abrir " << nombre_archivo << endl;
        return "";
    }

    // Leer TODO el contenido sin agregar \n
    char c;
    while (archivo.get(c)) {
        contenido += c;
    }

    archivo.close();
    return contenido;
}

void escribir_archivo(string nombre_archivo, string contenido) {
    ofstream archivo(nombre_archivo, ios::binary);

    if (!archivo) {
        cout << "Error: No se pudo crear " << nombre_archivo << endl;
        return;
    }

    archivo << contenido;
    archivo.close();
    cout << "Archivo guardado: " << nombre_archivo << endl;
}
//me crea una mascara de bits para extraer cada bit
string texto_a_binario(string texto) {
    string binario = "";

    for (int i = 0; i < texto.length(); i++) {
        char c = texto[i];
        int ascii = (int)c;

        // Convertir a binario de 8 bits
        for (int j = 7; j >= 0; j--) {
            if (ascii & (1 << j)) {
                binario += "1";
            } else {
                binario += "0";
            }
        }
    }

    return binario;
}

string binario_a_texto(string binario) {
    string texto = "";

    // Procesar en bloques de 8 bits
    for (int i = 0; i < binario.length(); i += 8) {
        if (i + 8 > binario.length()) {
            break; // Ignorar bits incompletos al final
        }

        string byte_str = binario.substr(i, 8);
        int valor = 0;

        // Convertir binario a decimal
        for (int j = 0; j < 8; j++) {
            valor = valor * 2;
            if (byte_str[j] == '1') {
                valor += 1;
            }
        }

        texto += (char)valor;
    }

    return texto;
}
