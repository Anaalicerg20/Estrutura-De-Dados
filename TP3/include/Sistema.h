#ifndef SISTEMA_H
#define SISTEMA_H

#include <sstream>

#include "Vetor.h"
#include "HashMap.h"

#include "Usuario.h"
#include "Produto.h"
#include "Compra.h"
#include "Reposicao.h"
#include "Historico.h"

class Sistema
{
private:

    // entidades principais
    Vetor<Usuario> usuarios;
    Vetor<Produto> produtos;
    Vetor<Compra> compras;
    Vetor<Reposicao> reposicoes;

    // contadores automáticos de IDs
    int proximoIdUsuario;
    int proximoIdProduto;
    int proximoIdCompra;
    int proximoIdReposicao;

    // índices invertidos de usuários
    HashMap indiceUsuarioId;
    HashMap indiceUsuarioNome;
    HashMap indiceUsuarioIdade;
    HashMap indiceUsuarioCidade;
    HashMap indiceUsuarioEstado;
    HashMap indiceUsuarioNacionalidade;

    // índices invertidos de produtos
    HashMap indiceProdutoId;
    HashMap indiceProdutoNome;
    HashMap indiceProdutoCategoria;
    HashMap indiceProdutoMarca;
    HashMap indiceProdutoCondicao;

    // índices invertidos de compras
    HashMap indiceCompraId;
    HashMap indiceCompraTimestamp;
    HashMap indiceCompraUsuario;
    HashMap indiceCompraProduto;

    // índices invertidos de reposições
    HashMap indiceReposicaoId;
    HashMap indiceReposicaoTimestamp;
    HashMap indiceReposicaoProduto;

    // históricos agregados(posção=id)
    Vetor< Vetor<Historico> > historicoUsuarios;
    Vetor< Vetor<Historico> > historicoProdutos;

    //função auxiliar: histórico
    void atualizarHistoricoUsuario(int idUsuario, int idProduto, int quantidade);
    void atualizarHistoricoProduto(int idProduto, int idUsuario, int quantidade);
    
    // função auxiliar para consultas
    Vetor<int> intersecao(const Vetor<int>& a, const Vetor<int>& b);

public:

    Sistema();

    //Cadastro 
    void cadastrarUsuario(const std::string& nome, int idade, const std::string& cidade, const std::string& estado, const std::string& nacionalidade);
    void cadastrarProduto(const std::string& nome, double preco, int qtd, const std::string& categoria, const std::string& marca, const std::string& condicao);

    // comandos que recebem o restante da linha de entrada 

    //processamentos
    void processarReposicao(std::stringstream& ss);
    void processarCompra(std::stringstream& ss);

    //operações
    void consultarUsuarios(std::stringstream& ss);
    void consultarProdutos(std::stringstream& ss);
    void consultarCompras(std::stringstream& ss);
    void consultarReposicoes(std::stringstream& ss);
};

#endif