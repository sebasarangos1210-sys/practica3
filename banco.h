#ifndef BANCO_H
#define BANCO_H
#include <string>

void sistema_bancario();
void crear_sudo();
bool validar_admin();
void registrar_usuario();
void guardar_transaccion(std::string cedula, std::string tipo, double monto);
bool login_usuario(std::string& cedula_logueada);
void actualizar_saldo(std::string cedula, double nuevo_saldo);
double obtener_saldo(std::string cedula);
void consultar_saldo(std::string cedula);
void retirar_dinero(std::string cedula);

#endif
