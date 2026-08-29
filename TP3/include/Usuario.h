#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario 
{
private:

    int id; //id automatico pelo sistema
    int idade;

    std::string nome;
    std::string cidade;
    std::string estado;
    std::string nacionalidade;

public:

    Usuario();

    Usuario(int id, std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade);

    int getId() const;
    int getIdade() const;

    std::string getNome() const;
    std::string getCidade() const;
    std::string getEstado() const;
    std::string getNacionalidade() const;
};

#endif