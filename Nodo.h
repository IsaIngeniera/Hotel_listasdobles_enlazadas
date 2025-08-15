//
// Created by DevCore on 14/08/2025.
//

#ifndef NODO_H
#define NODO_H
#include <string> //Para poder trabajar con strings
//#pragma once // Para no leer el archivo muchas veces


class Nodo {
private:
    std::string nombre;
    int habitacion;
    Nodo* anterior;
    Nodo* siguiente;

public:
    // Constructor
    Nodo(const std::string& nombre, int habitacion);

    // Getters
    std::string getNombre() const;
    int getHabitacion() const;
    Nodo* getAnterior() const;
    Nodo* getSiguiente() const;

    // Setters
    void setNombre(const std::string& nuevoNombre);
    void setHabitacion(int nuevaHabitacion);
    void setAnterior(Nodo* nodoAnterior);
    void setSiguiente(Nodo* nodoSiguiente);
};

#endif //NODO_H
