#include "../include/No.h"

No:: No(int id, int indice, char tipo)
    : id(id), indice(indice), tipo(tipo) {
        
}

int No::getId() const {
    return id;
}

int No::getIndice() const {
    return indice;
}  

// Retorna o tipo ('U' ou 'T')
// para o Dicionário saber onde buscar
char No::getTipo() const {
    return tipo;
}