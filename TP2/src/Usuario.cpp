#include "../include/Usuario.h"

Usuario::Usuario(int id, std::string nome, int idade)
    : id(id), nome(nome), idade(idade) {
}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNome() const {
    return nome;
}

int Usuario::getIdade() const {
    return idade;
}