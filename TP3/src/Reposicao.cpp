#include "../include/Reposicao.h"

// construtor padrão
Reposicao::Reposicao()
{
    id = -1;
    timestamp = 0;
}

// construtor com parâmetros
Reposicao::Reposicao(int id, int timestamp,
                     const Vetor<int>& ids_produtos,
                     const Vetor<int>& qtd_produtos)
{
    this->id = id;
    this->timestamp = timestamp;

    this->ids_produtos = ids_produtos;
    this->qtd_produtos = qtd_produtos;
}

// get
int Reposicao::getId() const
{
    return id;
}

int Reposicao::getTimestamp() const
{
    return timestamp;
}

// acesso aos vetores
const Vetor<int>& Reposicao::getIdsProdutos() const
{
    return ids_produtos;
}

const Vetor<int>& Reposicao::getQtdProdutos() const
{
    return qtd_produtos;
}