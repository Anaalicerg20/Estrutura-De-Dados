#ifndef HISTORICO_H
#define HISTORICO_H

class Historico
{
private:
    int id;
    int quantidade;

public:
    Historico();

    Historico(int id, int quantidade);

    int getId() const;
    int getQuantidade() const;

    void adicionarQuantidade(int qtd);
};

#endif