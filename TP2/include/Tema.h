#ifndef TEMA_HPP
#define TEMA_HPP

#include <string>

class Tema {
private:
    int id;
    std::string nome;
    char tipo; // A = acadêmico, P = pessoal

public:
    // construtor
    Tema(int id, std::string nome, char tipo);

    // gets
    int getId() const;
    std::string getNome() const;
    char getTipo() const;
};

#endif