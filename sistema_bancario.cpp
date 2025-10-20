#include <iostream>
#include <fstream>
#include <string>
#include "funciones.h"
#include "codificacion.h"

using namespace std;

const double COSTO = 1000.0;
const int METODO = 1;
const int SEMILLA = 4;

bool validar_admin() {
    string password;
    cout << "Password administrador: ";
    cin >> password;

    string sudo_codificado = leer_archivo("sudo.txt");
    if (sudo_codificado == "") {
        cout << "Error: Archivo sudo.txt no encontrado" << endl;
        return false;
    }

    string sudo_decodificado = binario_a_texto(decodificar_metodo1(sudo_codificado, SEMILLA));

    // Limpiar salto de línea
    if (!sudo_decodificado.empty() && sudo_decodificado.back() == '\n') {
        sudo_decodificado.pop_back();
    }

    return password == sudo_decodificado;
}

void crear_sudo() {
    ifstream test("sudo.txt");
    if (!test) {
        string pass = "admin123";
        string bin = texto_a_binario(pass);
        string cod = codificar_metodo1(bin, SEMILLA);
        escribir_archivo("sudo.txt", cod);
        cout << "Archivo sudo.txt creado con password: admin123" << endl;
    }
    test.close();
}

void registrar_usuario() {
    ofstream archivo("usuarios.txt", ios::app);
    if (!archivo) {
        cout << "Error al crear archivo usuarios.txt" << endl;
        return;
    }

    string cedula, clave;
    double saldo;

    cout << "Cedula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;
    cout << "Saldo inicial: ";
    cin >> saldo;

    archivo << cedula << "," << clave << "," << saldo << "\n";
    archivo.close();
    cout << "Usuario registrado exitosamente" << endl;
}

void guardar_transaccion(string cedula, string tipo, double monto) {
    string transaccion = cedula + "," + tipo + "," + to_string(monto) + "\n";
    string binario = texto_a_binario(transaccion);
    string codificado = codificar_metodo1(binario, SEMILLA);

    ofstream archivo("transacciones.txt", ios::app);
    if (archivo) {
        archivo << codificado;
        archivo.close();
    }
}

bool login_usuario(string& cedula_logueada) {
    string cedula, clave;
    cout << "Cedula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;

    ifstream archivo("usuarios.txt");
    if (!archivo) {
        cout << "No hay usuarios registrados" << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        if (p1 != string::npos && p2 != string::npos) {
            string c = linea.substr(0, p1);
            string cl = linea.substr(p1 + 1, p2 - p1 - 1);
            if (c == cedula && cl == clave) {
                cedula_logueada = cedula;
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}

void actualizar_saldo(string cedula, double nuevo_saldo) {
    ifstream entrada("usuarios.txt");
    string contenido = "";
    string linea;

    while (getline(entrada, linea)) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        if (p1 != string::npos && p2 != string::npos) {
            string c = linea.substr(0, p1);
            string cl = linea.substr(p1 + 1, p2 - p1 - 1);
            if (c == cedula) {
                contenido += c + "," + cl + "," + to_string(nuevo_saldo) + "\n";
            } else {
                contenido += linea + "\n";
            }
        }
    }
    entrada.close();

    ofstream salida("usuarios.txt");
    salida << contenido;
    salida.close();
}

double obtener_saldo(string cedula) {
    ifstream archivo("usuarios.txt");
    if (!archivo) return -1;

    string linea;
    while (getline(archivo, linea)) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        if (p1 != string::npos && p2 != string::npos) {
            string c = linea.substr(0, p1);
            if (c == cedula) {
                double saldo = stod(linea.substr(p2 + 1));
                archivo.close();
                return saldo;
            }
        }
    }
    archivo.close();
    return -1;
}

void consultar_saldo(string cedula) {
    double saldo = obtener_saldo(cedula);
    if (saldo < 0) {
        cout << "Usuario no encontrado" << endl;
        return;
    }

    if (saldo < COSTO) {
        cout << "Saldo insuficiente para consulta" << endl;
        return;
    }

    saldo -= COSTO;
    actualizar_saldo(cedula, saldo);
    cout << "Saldo: $" << saldo << " (costo: $" << COSTO << ")" << endl;
    guardar_transaccion(cedula, "CONSULTA", COSTO);
}

void retirar_dinero(string cedula) {
    double saldo = obtener_saldo(cedula);
    if (saldo < 0) {
        cout << "Usuario no encontrado" << endl;
        return;
    }

    double cantidad;
    cout << "Cantidad a retirar: ";
    cin >> cantidad;

    double total = cantidad + COSTO;
    if (saldo < total) {
        cout << "Saldo insuficiente" << endl;
        return;
    }

    saldo -= total;
    actualizar_saldo(cedula, saldo);
    cout << "Retirado: $" << cantidad << " (costo: $" << COSTO << ")" << endl;
    cout << "Nuevo saldo: $" << saldo << endl;
    guardar_transaccion(cedula, "RETIRO", cantidad);
}

void sistema_bancario() {
    cout << "\n=== SISTEMA BANCARIO ===" << endl;
    crear_sudo();

    while (true) {
        cout << "\n1. Administrador" << endl;
        cout << "2. Cliente" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            if (validar_admin()) {
                cout << "Acceso concedido" << endl;
                registrar_usuario();
            } else {
                cout << "Password incorrecto" << endl;
            }
        } else if (opcion == 2) {
            string cedula;
            if (login_usuario(cedula)) {
                cout << "Bienvenido " << cedula << endl;

                while (true) {
                    cout << "\n1. Consultar saldo" << endl;
                    cout << "2. Retirar dinero" << endl;
                    cout << "3. Salir" << endl;
                    cout << "Opcion: ";

                    int op;
                    cin >> op;

                    if (op == 1) consultar_saldo(cedula);
                    else if (op == 2) retirar_dinero(cedula);
                    else if (op == 3) break;
                    else cout << "Opcion invalida" << endl;
                }
            } else {
                cout << "Login fallido" << endl;
            }
        } else if (opcion == 3) {
            break;
        } else {
            cout << "Opcion invalida" << endl;
        }
    }
}
