#include "../include/Cliente.h"

//construtor padrão
Cliente::Cliente() {
    id = -1;
    numAcoes = 0;
    carteiraAcoes = nullptr;
}

Cliente::Cliente(int id, int numAcoes) : id(id), numAcoes(numAcoes) {

    //aloca um vetor para guardar as ações e inicializa ele em 0;

    carteiraAcoes = new int[numAcoes];

    for (int i = 0; i < numAcoes; i++) {
        carteiraAcoes[i] = 0;
    }
}

//não vazar memória
Cliente::~Cliente() {
    delete[] carteiraAcoes;
}

void Cliente::inicializar(int id, int numAcoes) {

    if (carteiraAcoes != nullptr) {
        delete[] carteiraAcoes;
    }

    this->id = id;
    this->numAcoes = numAcoes;

    carteiraAcoes = new int[numAcoes];

    for (int i = 0; i < numAcoes; i++) {
        carteiraAcoes[i] = 0;
    }
}


int Cliente::getId() {
    return id;
}

//ação existe: add na carteira = 1
void Cliente::comprarAcao(int acao_id) {
    if (acao_id >= 0 && acao_id < numAcoes) {
        carteiraAcoes[acao_id] = 1;
    }
}

//ação existe: tira da carteira = 0
void Cliente::venderAcao(int acao_id) {
    if (acao_id >= 0 && acao_id < numAcoes) {
        carteiraAcoes[acao_id] = 0;
    }
}

bool Cliente::possuiAcao(int acao_id) {
    if (acao_id >= 0 && acao_id < numAcoes) {
        return carteiraAcoes[acao_id];
    }
    return false;
}

