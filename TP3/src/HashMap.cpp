#include "../include/HashMap.h"

//construtores
EntradaHash::EntradaHash()
{
    proximo = nullptr;
}

EntradaHash::EntradaHash(const std::string& chave)
{
    this->chave = chave;
    proximo = nullptr;
}

//lógica de índice invertido 

unsigned int HashMap::funcaoHash(const std::string& chave) const //transformação da chave em enderço na tabela 
{
    unsigned int hash = 0;
    for (unsigned int i = 0; i < chave.size(); i++)
    {
        hash = hash * 31 + chave[i];
    }
    return hash % capacidade;
}

HashMap::HashMap(int capacidade) //cria a tabela hash 
{
    this->capacidade = capacidade;
    tabela = new EntradaHash*[capacidade];

    for (int i = 0; i < capacidade; i++)
    {
        tabela[i] = nullptr;
    }
}

HashMap::~HashMap()
{
    for (int i = 0; i < capacidade; i++)
    {
        EntradaHash* atual = tabela[i];
        while (atual != nullptr)
        {
            EntradaHash* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }

    delete[] tabela;
}

void HashMap::inserir(const std::string& chave, int id) //insere id associado a chave 
{
    unsigned int indice = funcaoHash(chave);
    EntradaHash* atual = tabela[indice];

    while (atual != nullptr)
    {
        if (atual->chave == chave)
        {
            atual->ids.adicionar(id);
            return;
        }

        atual = atual->proximo;
    }

    //caso a chave não exista: nova entrada 
    EntradaHash* novaEntrada = new EntradaHash(chave);
    novaEntrada->ids.adicionar(id);
    novaEntrada->proximo = tabela[indice];
    tabela[indice] = novaEntrada;
}

//retorna lista de ids associados as chaves 
const Vetor<int>* HashMap::buscar(const std::string& chave) const
{
    unsigned int indice = funcaoHash(chave);
    EntradaHash* atual = tabela[indice];

    while (atual != nullptr)
    {
        if (atual->chave == chave)
        {
            return &(atual->ids);
        }

        atual = atual->proximo;
    }
    return nullptr;
}