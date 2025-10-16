#include <string>
#include "codificacion.h"

using namespace std;

string codificar_metodo1(string binario, int n) {
    string resultado = "";

    //recorremos todo el binario en bloques de 'n' bits
    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_actual = binario.substr(pos, n);

        // Rellenar con ceros si el bloque es incompleto
        while (bloque_actual.length() < n) {
            bloque_actual += "0";
        }

        //invertir todos los bits
        if (pos == 0) {
            for (int i = 0; i < bloque_actual.length(); i++) {
                if (bloque_actual[i] == '0') {
                    resultado += "1";
                } else {
                    resultado += "0";
                }
            }
        }
        //aplicar reglas según bloque anterior
        else {
            string bloque_anterior = binario.substr(pos - n, n);
            int contador_ceros = 0;
            int contador_unos = 0;

            //contar 0 y 1 en el bloque anterior
            for (int i = 0; i < bloque_anterior.length(); i++) {
                if (bloque_anterior[i] == '0') {
                    contador_ceros++;
                } else {
                    contador_unos++;
                }
            }

            //igual cantidad de 0 y 1 - invertir todo
            if (contador_unos == contador_ceros) {
                for (int i = 0; i < bloque_actual.length(); i++) {
                    if (bloque_actual[i] == '0') {
                        resultado += "1";
                    } else {
                        resultado += "0";
                    }
                }
            }
            //más ceros - intercambiar cada 2 bits
            else if (contador_ceros > contador_unos) {
                for (int i = 0; i < bloque_actual.length(); i += 2) {
                    if (i + 1 < bloque_actual.length()) {
                        resultado += bloque_actual[i + 1];
                        resultado += bloque_actual[i];
                    } else {
                        resultado += bloque_actual[i];
                    }
                }
            }
            //más unos - rotar cada 3 bits
            else {
                for (int i = 0; i < bloque_actual.length(); i += 3) {
                    if (i + 2 < bloque_actual.length()) {
                        resultado += bloque_actual[i + 2];
                        resultado += bloque_actual[i];
                        resultado += bloque_actual[i + 1];
                    } else {
                        for (int j = i; j < bloque_actual.length(); j++) {
                            resultado += bloque_actual[j];
                        }
                    }
                }
            }
        }
    }
    return resultado;
}
