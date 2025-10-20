#include <string>
#include "codificacion.h"
using namespace std;

string codificar_metodo1(string binario, int n) {
    string resultado = "";

    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_actual = binario.substr(pos, n);

        // Rellenar con ceros si el bloque es incompleto
        while (bloque_actual.length() < n) {
            bloque_actual += "0";
        }

        // PRIMER BLOQUE: invertir todos los bits
        if (pos == 0) {
            for (int i = 0; i < bloque_actual.length(); i++) {
                resultado += (bloque_actual[i] == '0') ? '1' : '0';
            }
        }
        // BLOQUES SIGUIENTES: aplicar reglas según bloque anterior CODIFICADO
        else {
            // Tomar el bloque anterior del RESULTADO (ya codificado)
            string bloque_anterior = resultado.substr(pos - n, n);

            int contador_ceros = 0;
            int contador_unos = 0;

            // Contar 0s y 1s en el bloque anterior
            for (int i = 0; i < bloque_anterior.length(); i++) {
                if (bloque_anterior[i] == '0') {
                    contador_ceros++;
                } else {
                    contador_unos++;
                }
            }

            // IGUAL cantidad: invertir cada bit
            if (contador_unos == contador_ceros) {
                for (int i = 0; i < bloque_actual.length(); i++) {
                    resultado += (bloque_actual[i] == '0') ? '1' : '0';
                }
            }
            // MÁS CEROS: invertir cada 2 bits
            else if (contador_ceros > contador_unos) {
                for (int i = 0; i < bloque_actual.length(); i++) {
                    if (i % 2 == 0) {
                        // Invertir bits en posiciones pares (0, 2, 4...)
                        resultado += (bloque_actual[i] == '0') ? '1' : '0';
                    } else {
                        // Mantener bits en posiciones impares
                        resultado += bloque_actual[i];
                    }
                }
            }
            // MÁS UNOS: invertir cada 3 bits
            else {
                for (int i = 0; i < bloque_actual.length(); i++) {
                    if (i % 3 == 0) {
                        // Invertir bits en posiciones múltiplos de 3 (0, 3, 6...)
                        resultado += (bloque_actual[i] == '0') ? '1' : '0';
                    } else {
                        // Mantener los demás bits
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

        // Rellenar con ceros si es necesario
        while (bloque.length() < n) {
            bloque += "0";
        }

        // Rotación a la DERECHA (desplazamiento a la izquierda)
        // Primer bit codificado = último bit original
        if (bloque.length() > 1) {
            string bloque_rotado = "";
            // El último bit va primero
            bloque_rotado += bloque[bloque.length() - 1];
            // Luego todos los demás bits
            for (int j = 0; j < bloque.length() - 1; j++) {
                bloque_rotado += bloque[j];
            }
            resultado += bloque_rotado;
        } else {
            resultado += bloque;
        }
    }
    return resultado;
}
