#include <string>
#include "codificacion.h"

using namespace std;

string codificar_metodo1(string binario, int n) {
    string resultado = "";

    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_actual = binario.substr(pos, n);

        // NO rellenar con ceros - procesar solo lo que hay
        int tam_bloque = bloque_actual.length();

        if (pos == 0) {
            // PRIMER BLOQUE: invertir todos los bits
            for (int i = 0; i < tam_bloque; i++) {
                resultado += (bloque_actual[i] == '0') ? '1' : '0';
            }
        }
        else {
            // Analizar el bloque anterior ORIGINAL (sin codificar)
            string bloque_anterior = binario.substr(pos - n, n);
            int contador_ceros = 0;
            int contador_unos = 0;

            for (int i = 0; i < bloque_anterior.length(); i++) {
                if (bloque_anterior[i] == '0') {
                    contador_ceros++;
                } else {
                    contador_unos++;
                }
            }

            if (contador_unos == contador_ceros) {
                // Invertir cada bit
                for (int i = 0; i < tam_bloque; i++) {
                    resultado += (bloque_actual[i] == '0') ? '1' : '0';
                }
            }
            else if (contador_ceros > contador_unos) {
                // Invertir cada 2 bits (posiciones 0, 2, 4...)
                for (int i = 0; i < tam_bloque; i++) {
                    if (i % 2 == 0) {
                        resultado += (bloque_actual[i] == '0') ? '1' : '0';
                    } else {
                        resultado += bloque_actual[i];
                    }
                }
            }
            else {
                // Invertir cada 3 bits (posiciones 0, 3, 6...)
                for (int i = 0; i < tam_bloque; i++) {
                    if (i % 3 == 0) {
                        resultado += (bloque_actual[i] == '0') ? '1' : '0';
                    } else {
                        resultado += bloque_actual[i];
                    }
                }
            }
        }
    }
    return resultado;
}

string codificar_metodo2(string binario, int n) {
    string resultado = "";

    for (int i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        int tam_bloque = bloque.length();

        if (tam_bloque > 1) {
            string bloque_rotado = "";
            // Último bit va primero
            bloque_rotado += bloque[tam_bloque - 1];
            for (int j = 0; j < tam_bloque - 1; j++) {
                bloque_rotado += bloque[j];
            }
            resultado += bloque_rotado;
        } else {
            resultado += bloque;
        }
    }
    return resultado;
}
