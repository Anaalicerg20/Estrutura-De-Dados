#include "../include/Compra.h"

// construtor padrão
Compra::Compra()
{
    id = -1;
    timestamp = 0;
    id_usuario = -1;
}

// construtor com parâmetros
Compra::Compra(int id, int timestamp, int id_usuario, const Vetor<int>& ids_produtos, const Vetor<int>& qtd_produtos)
{
    this->id = id;
    this->timestamp = timestamp;
    this->id_usuario = id_usuario;

    this->ids_produtos = ids_produtos;
    this->qtd_produtos = qtd_produtos;
}

// get
int Compra::getId() const
{
    return id;
}

int Compra::getTimestamp() const
{
    return timestamp;
}

int Compra::getIdUsuario() const
{
    return id_usuario;
}

int Compra::getQuantidadeProdutos() const
{
    return ids_produtos.getTamanho();
}

//acesso aos vetores

const Vetor<int>& Compra::getIdsProdutos() const
{
    return ids_produtos;
}

const Vetor<int>& Compra::getQtdProdutos() const
{
    return qtd_produtos;
}