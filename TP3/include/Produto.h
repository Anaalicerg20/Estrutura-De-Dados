#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto
{
private:

    int id; //id atribuido automaticamnete 
    int qtd; //quantidade atual em estoque

    double preco;

    std::string nome;
    std::string categoria;
    std::string marca;
    std::string condicao;

public:

    Produto();

    Produto(int id, std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao);

    int getId() const;
    int getQtd() const;
    double getPreco() const;

    std::string getNome() const;
    std::string getCategoria() const;
    std::string getMarca() const;
    std::string getCondicao() const;

    //qtd é definido incialmente no cadastro do produto
    void aumentarQtd(int quantidade); //incrementado por reposições 
    void diminuirQtd(int quantidade); //decrementado em compras válidas 
};

#endif