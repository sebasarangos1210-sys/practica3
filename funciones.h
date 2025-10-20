#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>

// Funciones de archivos
std::string leer_archivo(std::string nombre_archivo);
void escribir_archivo(std::string nombre_archivo, std::string contenido);

// Funciones de conversion
std::string texto_a_binario(std::string texto);
std::string binario_a_texto(std::string binario);

#endif
