#include <string>
#include "decodificacion.h"

using namespace std;

string decodificar_metodo1(string binario, int n) {
    string resultado = "";
    string bloque_anterior_decodificado = "";

    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_codificado = binario.substr(pos, n);
        string bloque_decodificado = "";

        // Rellenar con ceros si el bloque es incompleto
        while (bloque_codificado.length() < n) {
            bloque_codificado += "0";
        }

        // PRIMER BLOQUE: invertir todos los bits (misma operación que en codificación)
        if (pos == 0) {
            for (int i = 0; i < bloque_codificado.length(); i++) {
                bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
            }
        }
        // BLOQUES SIGUIENTES: aplicar reglas según bloque DECODIFICADO anterior
        else {
            int contador_ceros = 0;
            int contador_unos = 0;

            // IMPORTANTE: Contar en el bloque DECODIFICADO anterior, no en el original
            for (int i = 0; i < bloque_anterior_decodificado.length(); i++) {
                if (bloque_anterior_decodificado[i] == '0') {
                    contador_ceros++;
                } else {
                    contador_unos++;
                }
            }

            // CASO 1: Igual cantidad de 0s y 1s → se había invertido cada bit
            if (contador_unos == contador_ceros) {
                for (int i = 0; i < bloque_codificado.length(); i++) {
                    bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                }
            }
            // CASO 2: Más 0s → se había invertido cada 2 bits (posiciones 0, 2, 4...)
            else if (contador_ceros > contador_unos) {
                for (int i = 0; i < bloque_codificado.length(); i++) {
                    if (i % 2 == 0) {
                        bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                    } else {
                        bloque_decodificado += bloque_codificado[i];
                    }
                }
            }
            // CASO 3: Más 1s → se había invertido cada 3 bits (posiciones 0, 3, 6...)
            else {
                for (int i = 0; i < bloque_codificado.length(); i++) {
                    if (i % 3 == 0) {
                        bloque_decodificado += (bloque_codificado[i] == '0') ? '1' : '0';
                    } else {
                        bloque_decodificado += bloque_codificado[i];
                    }
                }
            }
        }

        resultado += bloque_decodificado;
        bloque_anterior_decodificado = bloque_decodificado;  // Guardar para siguiente iteración
    }

    return resultado;
}

string decodificar_metodo2(string binario, int n) {
    string resultado = "";

    for (int i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);

        //rellenar con ceros si es necesario
        while (bloque.length() < n) {
            bloque += "0";
        }

        //desplazamiento inverso: desplazar a la derecha
        //en codificación: último bit va a la primera posición
        //en decodificación: primera posición va a la última posición
        if (bloque.length() > 1) {
            string bloque_decodificado = "";

            //tomar desde el segundo bit hasta el final
            for (int j = 1; j < bloque.length(); j++) {
                bloque_decodificado += bloque[j];
            }
            //el primer bit va al final
            bloque_decodificado += bloque[0];

            resultado += bloque_decodificado;
        } else {
            //si solo hay 1 bit, no hay desplazamiento
            resultado += bloque;
        }
    }

    return resultado;
}
