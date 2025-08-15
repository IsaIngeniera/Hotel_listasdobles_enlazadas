#include <iostream>
#include "ListaDobleEnlazada.h"
#include <windows.h>
#include <iostream>
#include <fstream>


using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // Verificar ruta del archivo
    std::cout << "Verificando acceso a hotel.txt...\n";
    std::ifstream testIn("hotel.txt");
    if (testIn.is_open()) {
        std::cout << "✅ Archivo encontrado correctamente.\n";
    } else {
        std::cout << "❌ No se encontró el archivo. Revisa la ruta.\n";
    }
    testIn.close();

    ListaDobleEnlazada lista("hotel.txt");
    lista.cargarDesdeArchivo();

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insertar huésped\n";
        cout << "2. Buscar huésped\n";
        cout << "3. Listar huéspedes (orden de llegada)\n";
        cout << "4. Listar huéspedes (orden alfabético)\n";
        cout << "5. Ver vecinos de una habitación\n";
        cout << "6. Eliminar huésped por habitación\n";
        cout << "0. Salir\n";
        cout << "Elija una opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string nombre;
            int habitacion;
            cout << "Ingrese el nombre: ";
            getline(cin, nombre);
            cout << "Ingrese el número de habitación: ";
            cin >> habitacion;
            lista.insertarHuesped(nombre, habitacion);
        }
        else if (opcion == 2) {
            cout << "Buscar por:\n1. Nombre\n2. Número de habitación\nOpción: ";
            int tipo;
            cin >> tipo;
            cin.ignore();

            if (tipo == 1) {
                string nombre;
                cout << "Nombre: ";
                getline(cin, nombre);
                Nodo* res = lista.buscar(nombre);
                if (res) cout << "Encontrado: Habitación " << res->getHabitacion() << "\n";
                else cout << "Ese huésped no fue encontrado.\n";
            } else {
                int hab;
                cout << "Número de habitación: ";
                cin >> hab;
                Nodo* res = lista.buscar(hab);
                if (res) cout << "Encontrado: " << res->getNombre() << "\n";
                else cout << "Ese huésped no fue encontrado.\n";
            }
        }
        else if (opcion == 3) {
            lista.listarLlegada();
        }
        else if (opcion == 4) {
            lista.listarAlfabetico();
        }
        else if (opcion == 5) {
            int hab;
            cout << "Número de habitación: ";
            cin >> hab;
            auto [ant, sig] = lista.vecinos(hab);
            cout << "Vecino anterior: " << ant << "\n";
            cout << "Vecino siguiente: " << sig << "\n";
        }
        else if (opcion == 6) {
                int hab;
                std::cout << "Ingrese el número de habitación a eliminar: ";
                std::cin >> hab;
                lista.eliminarHuesped(hab);

        }

    } while (opcion != 0);

    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.