#ifndef CLIENTE_H
#define CLIENTE_H

class Cliente {
private:
    int id;
    int numAcoes;
    int* carteiraAcoes;     // vetor binário: indica posse das ações 

public:
    Cliente();
    Cliente(int id, int numAcoes);
    ~Cliente();

    void inicializar(int id, int numAcoes);
    
    int getId();

    //atitudes possíveis em relação a ação
    void comprarAcao(int acao_id);
    void venderAcao(int acao_id);

    bool possuiAcao(int acao_id); //checar se é 0 ou 1 no vetor 

};

#endif