//
// Created by DevCore on 14/08/2025.
//

#include "ListaDobleEnlazada.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>

// Función auxiliar: pasar a minúsculas
std::string ListaDobleEnlazada::toLowerCase(const std::string& str) {
    std::string res = str;
    for (char& c : res) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return res;
}

ListaDobleEnlazada::ListaDobleEnlazada(const std::string& ruta)
    : cabeza(nullptr), cola(nullptr), tam(0), rutaArchivo(ruta) {}

ListaDobleEnlazada::~ListaDobleEnlazada() {
    Nodo* actual = cabeza;
    while (actual) {
        Nodo* sig = actual->getSiguiente();
        delete actual;
        actual = sig;
    }
}

bool ListaDobleEnlazada::estaVacia() const {
    return cabeza == nullptr;
}

bool ListaDobleEnlazada::habitacionOcupada(int habitacion) const {
    return buscar(habitacion) != nullptr;
}

int ListaDobleEnlazada::sugerirHabitacionCercana(int deseada) const {
    int maxDistancia = 100; // Un límite para no buscar infinitamente
    for (int dist = 1; dist < maxDistancia; ++dist) {

        // Comprobar la habitación anterior a la distancia actual
        int habitacionAbajo = deseada - dist;
        if (habitacionAbajo >= 1 && !habitacionOcupada(habitacionAbajo)) {
            return habitacionAbajo;
        }

        // Comprobar la habitación siguiente a la distancia actual
        int habitacionArriba = deseada + dist;
        // Podrías añadir una condición de límite superior si tienes un número máximo de habitaciones
        // ej: if (habitacionArriba <= TOTAL_HABITACIONES && !habitacionOcupada(habitacionArriba))
        if (!habitacionOcupada(habitacionArriba)) {
            return habitacionArriba;
        }
    }

    return -1; // No se encontró ninguna habitación cercana disponible
}
void ListaDobleEnlazada::guardarEnArchivo() const {
    std::ofstream out(rutaArchivo, std::ios::trunc); // trunc = sobrescribir
    if (!out.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar.\n";
        return;
    }
    Nodo* actual = cabeza;
    while (actual) {
        out << actual->getNombre() << "\n" << actual->getHabitacion() << "\n";
        actual = actual->getSiguiente();
    }
}


bool ListaDobleEnlazada::cargarDesdeArchivo() {
    std::ifstream in(rutaArchivo);
    if (!in.is_open()) return false;

    std::string nombre;
    int habitacion;

    while (std::getline(in, nombre) && (in >> habitacion)) {
        in.ignore();
        Nodo* nuevo = new Nodo(nombre, habitacion);
        if (estaVacia()) {
            cabeza = cola = nuevo;
        } else {
            cola->setSiguiente(nuevo);
            nuevo->setAnterior(cola);
            cola = nuevo;
        }
        tam++;
    }
    return true;
}

bool ListaDobleEnlazada::insertarHuesped(const std::string& nombre, int habitacion) {
    // El bucle se ejecuta mientras la habitación seleccionada esté ocupada
    while (habitacionOcupada(habitacion)) {
        std::cout << "La habitación " << habitacion << " está ocupada. Buscando una alternativa...\n";

        int sugerida = sugerirHabitacionCercana(habitacion);

        // Si se encontró una sugerencia válida
        if (sugerida != -1) {
            std::cout << "Te sugerimos la habitación más cercana disponible: " << sugerida << "\n";
            std::cout << "¿Deseas tomar la sugerida? (s/n): ";
            char resp;
            std::cin >> resp;

            if (resp == 's' || resp == 'S') {
                habitacion = sugerida; // Actualizamos a la habitación sugerida
                // El 'continue' no es estrictamente necesario, el bucle volverá a comprobar
                // pero lo dejamos por claridad. Si la sugerencia está libre, la siguiente
                // comprobación del while() fallará y saldrá del bucle.
            } else {
                std::cout << "Por favor, ingrese otro número de habitación: ";
                std::cin >> habitacion;
            }
        } else {
            // Si ni siquiera la búsqueda expansiva encontró algo
            std::cout << "No se encontraron habitaciones cercanas disponibles.\n";
            std::cout << "Por favor, ingrese otro número de habitación: ";
            std::cin >> habitacion;
        }
    }

    // --- Lógica de inserción (esta parte ya la tenías bien) ---
    Nodo* nuevo = new Nodo(nombre, habitacion);
    if (estaVacia()) {
        cabeza = cola = nuevo;
    } else {
        // Asumiendo que quieres mantener la lista ordenada por número de habitación
        // Si no, tu lógica original de insertar al final está bien.
        // Para este ejemplo, mantengo la inserción al final que tenías.
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
    tam++;

    guardarEnArchivo();
    std::cout << "\n✔️ ¡Huésped agregado correctamente!: " << nombre
              << " en la habitación " << habitacion << "\n";
    return true;
}
Nodo* ListaDobleEnlazada::buscar(const std::string& nombre) const {
    std::string nombreBuscado = toLowerCase(nombre);
    Nodo* actual = cabeza;
    while (actual) {
        if (toLowerCase(actual->getNombre()) == nombreBuscado) {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

Nodo* ListaDobleEnlazada::buscar(int habitacion) const {
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->getHabitacion() == habitacion) {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

void ListaDobleEnlazada::listarAlfabetico() const {
    if (estaVacia()) {
        std::cout << "No hay huéspedes.\n";
        return;
    }
    std::vector<Nodo*> lista;
    Nodo* actual = cabeza;
    while (actual) {
        lista.push_back(actual);
        actual = actual->getSiguiente();
    }
    std::sort(lista.begin(), lista.end(), [](Nodo* a, Nodo* b) {
        return toLowerCase(a->getNombre()) < toLowerCase(b->getNombre());
    });
    for (Nodo* n : lista) {
        std::cout << n->getNombre() << " - Habitación: " << n->getHabitacion() << "\n";
    }
}

void ListaDobleEnlazada::listarLlegada() const {
    Nodo* actual = cabeza;
    while (actual) {
        std::cout << actual->getNombre()
                  << " - Habitación: " << actual->getHabitacion() << "\n";
        actual = actual->getSiguiente();
    }
}

std::pair<std::string, std::string> ListaDobleEnlazada::vecinos(int habitacion) const {
    Nodo* nodo = buscar(habitacion);
    if (!nodo) return {"No encontrado", "No encontrado"};

    std::string anterior = nodo->getAnterior() ? nodo->getAnterior()->getNombre() : "Ninguno";
    std::string siguiente = nodo->getSiguiente() ? nodo->getSiguiente()->getNombre() : "Ninguno";
    return {anterior, siguiente};
}

bool ListaDobleEnlazada::eliminarHuesped(int habitacion) {
    Nodo* objetivo = buscar(habitacion);
    if (!objetivo) {
        std::cout << " No se encontró un huésped en la habitación " << habitacion << ".\n";
        return false;
    }

    // Caso 1: Es la cabeza
    if (objetivo == cabeza) {
        cabeza = objetivo->getSiguiente();
        if (cabeza) cabeza->setAnterior(nullptr);
        else cola = nullptr; // lista queda vacía
    }
    // Caso 2: Es la cola
    else if (objetivo == cola) {
        cola = objetivo->getAnterior();
        if (cola) cola->setSiguiente(nullptr);
    }
    // Caso 3: Está en el medio
    else {
        objetivo->getAnterior()->setSiguiente(objetivo->getSiguiente());
        objetivo->getSiguiente()->setAnterior(objetivo->getAnterior());
    }

    delete objetivo;
    tam--;

    guardarEnArchivo(); // actualizar archivo
    std::cout << " Huésped eliminado correctamente.\n";
    return true;
}
