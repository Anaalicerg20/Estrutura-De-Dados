#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    int id;
    std::string nome;
    int idade;

public:
    // construtor
    Usuario(int id, std::string nome, int idade);

    // gets
    int getId() const;
    std::string getNome() const;
    int getIdade() const;
};

#endif