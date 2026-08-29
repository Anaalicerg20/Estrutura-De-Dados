#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include "Vetor.h"

class EntradaHash //nó dentro de uma lista encadeada 
{
public:

    std::string chave;
    Vetor<int> ids; //usuários que possuem determinada chave 
    EntradaHash* proximo; //proximo nó


    EntradaHash();
    EntradaHash(const std::string& chave);
};

class HashMap //índice invertido 
{
private:

    EntradaHash** tabela; //vetor de buckets
    int capacidade; //numero de buckets 
    unsigned int funcaoHash(const std::string& chave) const; //transforma as chaves(strings) em números (int) - posição na tabela

public:

    HashMap(int capacidade = 1031); 
    ~HashMap();

    void inserir(const std::string& chave, int id); //verifica a lista de ids que um elemento deve ser adicionado
    const Vetor<int>* buscar(const std::string& chave) const; //verifica quais ids tem determinado atributo
};

#endif