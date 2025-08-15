//
// Created by DevCore on 14/08/2025.
//

#include "Nodo.h"

// Constructor
Nodo::Nodo(const std::string& nombre, int habitacion)
    : nombre(nombre), habitacion(habitacion),
      anterior(nullptr), siguiente(nullptr) {}

// Getters
std::string Nodo::getNombre() const { // :: los utilizo para decirle al compilador a donde pertenece el metodo
    return nombre;
}

int Nodo::getHabitacion() const {
    return habitacion;
}

Nodo* Nodo::getAnterior() const {
    return anterior;
}

Nodo* Nodo::getSiguiente() const {
    return siguiente;
}

// Setters
void Nodo::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Nodo::setHabitacion(int nuevaHabitacion) {
    habitacion = nuevaHabitacion;
}

void Nodo::setAnterior(Nodo* nodoAnterior) {
    anterior = nodoAnterior;
}

void Nodo::setSiguiente(Nodo* nodoSiguiente) {
    siguiente = nodoSiguiente;
}

