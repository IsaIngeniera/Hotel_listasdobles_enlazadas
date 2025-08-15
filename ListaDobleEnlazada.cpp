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
    if (!habitacionOcupada(deseada - 1) && deseada > 1) return deseada - 1;
    if (!habitacionOcupada(deseada + 1)) return deseada + 1;
    return -1;
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
    while (habitacionOcupada(habitacion)) {
        int sugerida = sugerirHabitacionCercana(habitacion);
        if (sugerida != -1) {
            std::cout << "La habitación " << habitacion << " está ocupada. "
                      << "Sugerida: " << sugerida << "\n";
            std::cout << "¿Desea tomar la sugerida? (s/n): ";
            char resp;
            std::cin >> resp;
            if (resp == 's' || resp == 'S') {
                habitacion = sugerida;
                break;
            }
        }
        std::cout << "Ingrese otro número de habitación: ";
        std::cin >> habitacion;
    }

    Nodo* nuevo = new Nodo(nombre, habitacion);
    if (estaVacia()) {
        cabeza = cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
    tam++;

    guardarEnArchivo();


    std::cout << "Huésped agregado correctamente: " << nombre
              << " - Habitación " << habitacion << "\n";
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
        std::cout << "❌ No se encontró un huésped en la habitación " << habitacion << ".\n";
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
    std::cout << "✅ Huésped eliminado correctamente.\n";
    return true;
}
