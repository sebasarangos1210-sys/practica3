#include <string>
#include "decodificacion.h"

using namespace std;

string decodificar_metodo1(string binario, int n) {
    string resultado = "";
    string bloque_anterior_decodificado = "";

    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_codificado = binario.substr(pos, n);
        string bloque_decodificado = "";

        //no rellenar con ceros - procesar solo lo que hay
        int tam_bloque = bloque_codificado.length();

        if (pos == 0) {
            //invertir todos los bits
            for (int i = 0; i < tam_bloque; i++) {
                bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
            }
        }
        else {
            //contar en el bloque procesado anterior
            int contador_ceros = 0;
            int contador_unos = 0;

            for (int i = 0; i < bloque_anterior_decodificado.length(); i++) {
                if (bloque_anterior_decodificado[i] == '0') {
                    contador_ceros++;
                } else {
                    contador_unos++;
                }
            }

            if (contador_unos == contador_ceros) {
                //invertir cada bit
                for (int i = 0; i < tam_bloque; i++) {
                    bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                }
            }
            else if (contador_ceros > contador_unos) {
                //invertir cada 2 bits
                for (int i = 0; i < tam_bloque; i++) {
                    if (i % 2 == 0) {
                        bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                    } else {
                        bloque_decodificado += bloque_codificado[i];
                    }
                }
            }
            else {
                //invertir cada 3 bits
                for (int i = 0; i < tam_bloque; i++) {
                    if (i % 3 == 0) {
                        bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                    } else {
                        bloque_decodificado += bloque_codificado[i];
                    }
                }
            }
        }

        resultado += bloque_decodificado;
        bloque_anterior_decodificado = bloque_decodificado;
    }

    return resultado;
}

string decodificar_metodo2(string binario, int n) {
    string resultado = "";

    for (int i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        int tam_bloque = bloque.length();

        if (tam_bloque > 1) {
            string bloque_decodificado = "";
            //primer bit va al final
            for (int j = 1; j < tam_bloque; j++) {
                bloque_decodificado += bloque[j];
            }
            bloque_decodificado += bloque[0];
            resultado += bloque_decodificado;
        } else {
            resultado += bloque;
        }
    }

    return resultado;
}
