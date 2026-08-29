#ifndef REPOSICAO_H
#define REPOSICAO_H

#include "Vetor.h"

class Reposicao
{
private:

    int id; // id atribuído automaticamente
    int timestamp; // instante da reposição

    Vetor<int> ids_produtos; // produtos repostos
    Vetor<int> qtd_produtos;

public:

    Reposicao();

    Reposicao(int id, int timestamp,
              const Vetor<int>& ids_produtos,
              const Vetor<int>& qtd_produtos);

    int getId() const;
    int getTimestamp() const;

    // acesso aos vetores sem modificá-los
    const Vetor<int>& getIdsProdutos() const;
    const Vetor<int>& getQtdProdutos() const;
};

#endif