
#include "../include/Acao.h"
#include <cmath>  
#include <iostream>

//construtor padrão 
Acao::Acao() {
    id = -1;
    w = 0;
    qtd_precos = 0;
    cotacoes_recentes = nullptr;
}

Acao::Acao(int id, int w) : id(id), qtd_precos(0), w(w){
    cotacoes_recentes = new double[w];
}

Acao::~Acao() {
    delete[] cotacoes_recentes;
}

void Acao::inicializar(int id, int w) {

    if (cotacoes_recentes != nullptr) {
        delete[] cotacoes_recentes;
    }

    this->id = id;
    this->qtd_precos = 0;
    this->w = w;

    cotacoes_recentes = new double[w];
}

int Acao::getId() {
    return id;
}

void Acao::adicionarPreco(double preco) {

    //quando o num de preços é menor do que a quantidade de cotações consideradas para cálculo: add um preço no sinal do vetor de cotações
    if (qtd_precos < w) {
        cotacoes_recentes[qtd_precos] = preco;
        qtd_precos++;
    } else {
        // no caso que w < qtd_preços move os elementos do vetor para a esquerda
        for (int i = 1; i < w; i++) {
            cotacoes_recentes[i - 1] = cotacoes_recentes[i];
        }
        //add o novo preço 
        cotacoes_recentes[w - 1] = preco;
    }
}

//util para as métricas
double Acao::calcularRetornoElemento(int i) {
    double elemento = (cotacoes_recentes[i] / cotacoes_recentes[i - 1]) - 1.0;
    return elemento;
}

//métricas

//retorno acumulado 
double Acao::calcularRET() {
    if (qtd_precos < 2) return 0.0;

    int base = qtd_precos - w;
    if (base < 0){
        base = 0;
    }

    //debug 

 /* std::cout << "DEBUG RET - Acao " << id << ": ";
    for (int i = 0; i < qtd_precos; i++) {
        std::cout << cotacoes_recentes[i] << " ";
    }
    std::cout << " | base=" << base << " ultimo=" << qtd_precos - 1 << "\n"; */


    double RET = (cotacoes_recentes[qtd_precos - 1] /cotacoes_recentes[base]) - 1.0;
    return RET;
}

//média dos retornos 
double Acao::calcularAVGRET(){
    if (qtd_precos < 2) return 0.0;
    
    int inicio = 0;

    if (qtd_precos > w) {
        inicio = qtd_precos - w;
    }
    
    double somatorio = 0.0;
    int count = 0;

    for(int i = inicio + 1; i < qtd_precos; i++){
        somatorio += calcularRetornoElemento(i);
        count ++;
    }

    if (count == 0) {
        return 0.0;
    }

    double AVGRET = somatorio / count;

    return AVGRET;
}

//estabilidade
double Acao::calcularSTAB() {
    if (qtd_precos < 2) return 1.0; 

    double media = calcularAVGRET();
    double soma = 0.0;

    int inicio = 0;

    if (qtd_precos > w) {
        inicio = qtd_precos - w;
    }

    int count = 0;

    for (int i = inicio + 1; i < qtd_precos; i++) {
        double ri = calcularRetornoElemento(i);
        soma += (ri - media) * (ri - media);
        count++;
    }

    if (count == 0) {
        return 1.0;
    }

    double variancia = soma / count;
    double vol = sqrt(variancia);

    double STAB = 1.0 / (1.0 + vol);

    return STAB;
}

//consistência dos retornos
double Acao::calcularCONS() {
    if (qtd_precos < 2) return 0.0;

    int inicio = 0;

    if (qtd_precos > w) {
        inicio = qtd_precos - w;
    }

    int positivos = 0;
    int count = 0;

    for (int i = inicio + 1; i < qtd_precos; i++) {
        if (calcularRetornoElemento(i) > 0.0) {
            positivos++;
        }
        count ++; 
    }

    if (count == 0) {
        return 0.0;
    }

    double CONS = (1.0 * positivos) / count;
    return CONS;
}