#ifndef ACAO_H
#define ACAO_H

class Acao {
private:
    int id;
    double* cotacoes_recentes;
    int qtd_precos; //quantos preços há no cotações recentes 
    int w; //o número de cotações mais recentes de uma ação a serem consideradas no cálculo das métricas


public:
    //construtor
    Acao();    
    Acao(int id, int w);
    ~Acao();

    void inicializar(int id, int w); 
    
    int getId();

    void adicionarPreco(double preco);
    
    //utilizado em AVGRET, STAB e CONS
    double calcularRetornoElemento(int i);

    //metricas
    double calcularRET();
    double calcularAVGRET();
    double calcularSTAB();
    double calcularCONS();

};

#endif