#include "../include/Usuario.h"

// construtor padrão
Usuario::Usuario()
{
    id = -1;
    idade = 0;

    nome = "";
    cidade = "";
    estado = "";
    nacionalidade = "";
}

// construtor com parâmetros 
Usuario::Usuario(int id, std::string nome, int idade, std::string cidade,std::string estado, std::string nacionalidade)
{
    this->id = id;
    this->nome = nome;
    this->idade = idade;
    this->cidade = cidade;
    this->estado = estado;
    this->nacionalidade = nacionalidade;
}

// get
int Usuario::getId() const
{
    return id;
}

int Usuario::getIdade() const
{
    return idade;
}

std::string Usuario::getNome() const
{
    return nome;
}

std::string Usuario::getCidade() const
{
    return cidade;
}

std::string Usuario::getEstado() const
{
    return estado;
}

std::string Usuario::getNacionalidade() const
{
    return nacionalidade;
}