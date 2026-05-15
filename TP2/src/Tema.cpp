#include "../include/Tema.h"

Tema::Tema(int id, std::string nome, char tipo)
    : id(id), nome(nome), tipo(tipo) {
}

int Tema::getId() const {
    return id;
}

std::string Tema::getNome() const {
    return nome;
}

char Tema::getTipo() const {
    return tipo;
}