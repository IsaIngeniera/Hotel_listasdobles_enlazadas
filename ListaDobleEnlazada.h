//
// Created by DevCore on 14/08/2025.
//

#ifndef LISTADOBLEENLAZADA_H
#define LISTADOBLEENLAZADA_H

//#pragma once
#include "Nodo.h"
#include <string>
#include <utility>

class ListaDobleEnlazada {
private:
    Nodo* cabeza;
    Nodo* cola;
    int tam;
    std::string rutaArchivo;

    bool habitacionOcupada(int habitacion) const;
    int sugerirHabitacionCercana(int deseada) const;
    static std::string toLowerCase(const std::string& str);

public:
    ListaDobleEnlazada(const std::string& ruta = "hotel.txt");
    ~ListaDobleEnlazada();

    bool cargarDesdeArchivo();
    void guardarEnArchivo() const;
    bool insertarHuesped(const std::string& nombre, int habitacion);
    bool eliminarHuesped(int habitacion);



    Nodo* buscar(const std::string& nombre) const;
    Nodo* buscar(int habitacion) const;

    void listarAlfabetico() const;
    void listarLlegada() const;
    std::pair<std::string, std::string> vecinos(int habitacion) const;

    bool estaVacia() const;
};



#endif //LISTADOBLEENLAZADA_H
