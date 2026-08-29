#include "../include/Historico.h"

Historico::Historico()
{
    id = -1;
    quantidade = 0;
}

Historico::Historico(int id, int quantidade)
{
    this->id = id;
    this->quantidade = quantidade;
}

int Historico::getId() const
{
    return id;
}

int Historico::getQuantidade() const
{
    return quantidade;
}

void Historico::adicionarQuantidade(int qtd)
{
    quantidade += qtd;
}