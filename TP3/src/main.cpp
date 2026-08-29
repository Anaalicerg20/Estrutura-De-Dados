#include <iostream>
#include <string>
#include <sstream>

#include "../include/Sistema.h"

int main(){
    Sistema sistema;

    std::string linha;

    while (std::getline(std::cin, linha)){
        if (linha.empty()){
            continue;
        }

        std::stringstream ss(linha);

        std::string comando;
        ss >> comando;

        if (comando == "U"){
            std::string nome;
            int idade;
            std::string cidade;
            std::string estado;
            std::string nacionalidade;

            ss >> nome >> idade >> cidade >> estado >> nacionalidade;

            sistema.cadastrarUsuario(nome, idade, cidade, estado, nacionalidade);
        }
        else if (comando == "P"){
            std::string nome;
            double preco;
            int qtd;
            std::string categoria;
            std::string marca;
            std::string condicao;

            ss >> nome >> preco >> qtd >> categoria >> marca >> condicao;

            sistema.cadastrarProduto(nome, preco, qtd, categoria, marca, condicao);

        }


        else if (comando == "R"){
            sistema.processarReposicao(ss);
        }
        else if (comando == "C"){
            sistema.processarCompra(ss);
        }
        else if (comando == "LU"){
            sistema.consultarUsuarios(ss);
        }
        else if (comando == "LP"){
            sistema.consultarProdutos(ss);
        }
        else if (comando == "LC"){
            sistema.consultarCompras(ss);
        }
        else if (comando == "LR"){
            sistema.consultarReposicoes(ss);
        }
    }

    return 0;
}