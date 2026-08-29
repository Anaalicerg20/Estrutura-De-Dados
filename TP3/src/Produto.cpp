#include "../include/Produto.h"

// construtor padrão
Produto::Produto()
{
    id = -1;
    qtd = 0;
    preco = 0.0;

    nome = "";
    categoria = "";
    marca = "";
    condicao = "";
}

// construtor com parâmetros
Produto::Produto(int id, std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao)
{
    this->id = id;
    this->nome = nome;
    this->preco = preco;
    this->qtd = qtd;
    this->categoria = categoria;
    this->marca = marca;
    this->condicao = condicao;
}

// get
int Produto::getId() const
{
    return id;
}

int Produto::getQtd() const
{
    return qtd;
}

double Produto::getPreco() const
{
    return preco;
}

std::string Produto::getNome() const
{
    return nome;
}

std::string Produto::getCategoria() const
{
    return categoria;
}

std::string Produto::getMarca() const
{
    return marca;
}

std::string Produto::getCondicao() const
{
    return condicao;
}

// incrementa estoque após reposição
void Produto::aumentarQtd(int quantidade)
{
    qtd += quantidade;
}

// decrementa estoque após compra válida
void Produto::diminuirQtd(int quantidade)
{
    qtd -= quantidade;
}