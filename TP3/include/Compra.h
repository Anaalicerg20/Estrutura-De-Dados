#ifndef COMPRA_H
#define COMPRA_H

#include "Vetor.h"

class Compra
{
private:

    int id; //id atribuido automaticamnete 
    int timestamp; //instante da compra 
    int id_usuario;  // usuário que realizou a compra

    Vetor<int> ids_produtos; 
    Vetor<int> qtd_produtos;

public:

    Compra();

    Compra(int id, int timestamp, int id_usuario, const Vetor<int>& ids_produtos, const Vetor<int>& qtd_produtos);

    int getId() const;
    int getTimestamp() const;
    int getIdUsuario() const;

    //Acesso aos vetores sem alterá-los
    const Vetor<int>& getIdsProdutos() const;  //id_produtos[x,y]
    const Vetor<int>& getQtdProdutos() const; //qtd_produtos[qtd_x, qtd_y]

    int getQuantidadeProdutos() const;
};

#endif