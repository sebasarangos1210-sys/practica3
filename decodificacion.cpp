#include <string>
#include "decodificacion.h"

using namespace std;

#include <string>
#include "decodificacion.h"

using namespace std;

string decodificar_metodo1(string binario, int n) {
    string resultado = "";
    string bloque_anterior_decodificado = "";

    for (int pos = 0; pos < binario.length(); pos += n) {
        string bloque_codificado = binario.substr(pos, n);
        string bloque_decodificado = "";

        while (bloque_codificado.length() < n) {
            bloque_codificado += "0";
        }

        if (pos == 0) {
            for (int i = 0; i < bloque_codificado.length(); i++) {
                if (bloque_codificado[i] == '0') {
                    bloque_decodificado += "1";
                } else {
                    bloque_decodificado += "0";
                }
            }
        }
        else {
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
                for (int i = 0; i < bloque_codificado.length(); i++) {
                    if (bloque_codificado[i] == '0') {
                        bloque_decodificado += "1";
                    } else {
                        bloque_decodificado += "0";
                    }
                }
            }
            else if (contador_ceros > contador_unos) {
                for (int i = 0; i < bloque_codificado.length(); i += 2) {
                    if (i + 1 < bloque_codificado.length()) {
                        bloque_decodificado += bloque_codificado[i + 1];
                        bloque_decodificado += bloque_codificado[i];
                    } else {
                        bloque_decodificado += bloque_codificado[i];
                    }
                }
            }
            else {
                for (int i = 0; i < bloque_codificado.length(); i += 3) {
                    if (i + 2 < bloque_codificado.length()) {
                        bloque_decodificado += bloque_codificado[i + 1];
                        bloque_decodificado += bloque_codificado[i + 2];
                        bloque_decodificado += bloque_codificado[i];
                    } else {
                        for (int j = i; j < bloque_codificado.length(); j++) {
                            bloque_decodificado += bloque_codificado[j];
                        }
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

        while (bloque.length() < n) {
            bloque += "0";
        }

        if (bloque.length() > 1) {
            string bloque_decodificado = "";
            bloque_decodificado += bloque[bloque.length() - 1];
            for (int j = 0; j < bloque.length() - 1; j++) {
                bloque_decodificado += bloque[j];
            }
            resultado += bloque_decodificado;
        } else {
            resultado += bloque;
        }
    }
    return resultado;
}
