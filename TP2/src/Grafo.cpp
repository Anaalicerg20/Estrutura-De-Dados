#include "../include/Grafo.h"

//construtor
Grafo::Grafo(int tipoRepresentacao, int tipoGrafo): tipoRepresentacao(tipoRepresentacao), tipoGrafo(tipoGrafo), capacidade(10), vertices(nullptr), matriz(nullptr), listas(nullptr), graus(nullptr) {

    //inicializa os 10 vertices 
    vertices = new No*[capacidade];
    for (int i = 0; i < capacidade; i++) {
        vertices[i] = nullptr;
    }

    // inicializa representação escolhida
    if (tipoRepresentacao == MATRIZ) {
        inicializarMatriz();
    }
    else {
        inicializarListas();
    }
}

//destrutor
Grafo::~Grafo() {

    delete[] vertices;

    // libera matriz
    destruirMatriz();

    // libera listas
    destruirListas();
}


// FUNÇÕES PRIVADAS, REPRESENTAÇÃO: LISTA E MATRIZ 

void Grafo::inicializarMatriz() {

    matriz = new bool*[capacidade]; //vetor de linhas da matriz 

    for (int i = 0; i < capacidade; i++) { //percorre as linhas 
        matriz[i] = new bool[capacidade]; //cria as colunas da linha i 
        for (int j = 0; j < capacidade; j++) {
            matriz[i][j] = false; //incializa todos os elementos com 0 (não exkiste conexões ainda)
        }
    }
}

void Grafo::destruirMatriz() {

    if (matriz != nullptr) {
        for (int i = 0; i < capacidade; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz = nullptr;
    }
}

void Grafo::inicializarListas() {

    listas = new int*[capacidade]; //vetor de ponteiros, cada posição aponta para um vetor adjacente 
    graus = new int[capacidade]; //vetor d einteiros, quantos adjacente cada vértice tem

    for (int i = 0; i < capacidade; i++) { //percorre todos os vértices: iniclamnete sem adjacentes 
        listas[i] = nullptr;
        graus[i] = 0;
    }
}

void Grafo::destruirListas() {

    if (listas != nullptr) {
        for (int i = 0; i < capacidade; i++) {
            delete[] listas[i];
        }
        delete[] listas;
        listas = nullptr;
    }

    if (graus != nullptr) {
        delete[] graus;
        graus = nullptr;
    }
}
void Grafo::aumentarCapacidade() {

    int capacidadeAntiga = capacidade;
    capacidade = capacidade * 2;

    //vertices
    No** novosVertices = new No*[capacidade];

    for (int i = 0; i < capacidade; i++) {
        novosVertices[i] = nullptr;
    }

    for (int i = 0; i < capacidadeAntiga; i++) {
        novosVertices[i] = vertices[i];
    }

    delete[] vertices;
    vertices = novosVertices;

//matriz
    if (tipoRepresentacao == MATRIZ) {

        // guarda matriz antiga
        bool** matrizAntiga = matriz;

        // cria nova matriz usando a função
        inicializarMatriz();

        // copia valores antigos
        for (int i = 0; i < capacidadeAntiga; i++) {
            for (int j = 0; j < capacidadeAntiga; j++) {
                matriz[i][j] = matrizAntiga[i][j];
            }
        }

        // libera matriz antiga
        for (int i = 0; i < capacidadeAntiga; i++) {
            delete[] matrizAntiga[i];
        }

        delete[] matrizAntiga;
    }

//lista
    else {

        // guarda estruturas antigas
        int** listasAntigas = listas;
        int* grausAntigos = graus;

        // cria novas estruturas usando a função
        inicializarListas();

        // copia conteúdos
        for (int i = 0; i < capacidadeAntiga; i++) {

            graus[i] = grausAntigos[i];

            if (grausAntigos[i] > 0) {

                listas[i] = new int[grausAntigos[i]];

                for (int j = 0; j < grausAntigos[i]; j++) {
                    listas[i][j] = listasAntigas[i][j];
                }
            }
        }

        // libera listas antigas
        for (int i = 0; i < capacidadeAntiga; i++) {
            delete[] listasAntigas[i];
        }

        delete[] listasAntigas;
        delete[] grausAntigos;
    }
}

//FUNÇÕES PÚBLICAS: AÇÕES POSSÍVEIS EM UM GRAFO 

//Vértices
void Grafo::inserirVertice(No* no) {

    int indice = no->getIndice();

    while (indice >= capacidade) {
        aumentarCapacidade();
    }

    vertices[indice] = no;

}


No* Grafo::obterVertice(int indice) const {

    if (indice < 0 || indice >= capacidade) {
        return nullptr;
    }

    return vertices[indice];
}

//int Grafo::getQuantidadeVertices() const {
 //   return quantidadeVertices;
//}

int Grafo::getCapacidade() const {
    return capacidade;
}

//Arestas 
void Grafo::inserirAresta(int origem, int destino) {

    if (tipoGrafo == GRAFO_SOCIAL) {

        // Matriz
        if (tipoRepresentacao == MATRIZ) {
            matriz[origem][destino] = true; //direcionado
        }

        //Lista
        else {

            int* nova = new int[graus[origem] + 1];

            for (int i = 0; i < graus[origem]; i++) {
                nova[i] = listas[origem][i];
            }

            nova[graus[origem]] = destino; //direcionado

            delete[] listas[origem];
            listas[origem] = nova;

            graus[origem]++;
        }
    }

    else if (tipoGrafo == GRAFO_TEMAS) {

        No* noOrigem = vertices[origem];
        No* noDestino = vertices[destino];

        if (noOrigem->getTipo() != noDestino->getTipo()) { //bipartido

            // Matriz
            if (tipoRepresentacao == MATRIZ) {

                matriz[origem][destino] = true;
                matriz[destino][origem] = true; //não direcionado
            }

            // Lista
            else {

                // origem -> destino
                int* novaOrigem = new int[graus[origem] + 1];

                for (int i = 0; i < graus[origem]; i++) {
                    novaOrigem[i] = listas[origem][i];
                }

                novaOrigem[graus[origem]] = destino;

                delete[] listas[origem];
                listas[origem] = novaOrigem;

                graus[origem]++;

                // destino -> origem
                int* novaDestino = new int[graus[destino] + 1];

                for (int i = 0; i < graus[destino]; i++) {
                    novaDestino[i] = listas[destino][i];
                }

                novaDestino[graus[destino]] = origem;

                delete[] listas[destino];
                listas[destino] = novaDestino;

                graus[destino]++;
            }
        }
    }
}


//checar 
void Grafo::removerAresta(int origem, int destino) {

    // REPRESENTAÇÃO POR MATRIZ
    if (tipoRepresentacao == MATRIZ) {

        matriz[origem][destino] = false;

        if (tipoGrafo == GRAFO_TEMAS) {
            matriz[destino][origem] = false;
        }
    }

    // REPRESENTAÇÃO POR LISTA
    else {

        int grauOrigem = graus[origem];

        int* novaLista = nullptr;

        if (grauOrigem - 1 > 0) {
            novaLista = new int[grauOrigem - 1];
        }

        int k = 0;

        // copia tudo MENOS o destino
        for (int i = 0; i < grauOrigem; i++) {

            if (listas[origem][i] != destino) {
                novaLista[k++] = listas[origem][i];
            }
        }

        // libera lista antiga
        delete[] listas[origem];

        // atualiza ponteiro
        listas[origem] = novaLista;

        // atualiza grau
        graus[origem]--;

        if (tipoGrafo == GRAFO_TEMAS) {

            int grauDestino = graus[destino];

            int* novaListaDestino = nullptr;

            if (grauDestino - 1 > 0) {
                novaListaDestino = new int[grauDestino - 1];
            }

            k = 0;

            for (int i = 0; i < grauDestino; i++) {

                if (listas[destino][i] != origem) {
                    novaListaDestino[k++] = listas[destino][i];
                }
            }

            delete[] listas[destino];

            listas[destino] = novaListaDestino;

            graus[destino]--;
        }
    }
}

bool Grafo::existeAresta(int origem, int destino) const {

    if (tipoRepresentacao == MATRIZ) {
        return matriz[origem][destino];
    }

    else{
        for (int i = 0; i < graus[origem]; i++) {
            if (listas[origem][i] == destino) {
                return true;
            }
        }
        return false;
    }
}

int Grafo::getGrau(int id) const {

    if (id < 0 || id >= capacidade) {
        return 0;
    }

    //lista
    if (tipoRepresentacao == LISTA) {
        return graus[id];
    }

    //matriz
    int grau = 0;

    for (int j = 0; j < capacidade; j++) {
        if (matriz[id][j]) {
            grau++;
        }
    }

    return grau;
}

int Grafo::getAdjacente(int id, int indice) const {

    if (id < 0 || id >= capacidade) {
        return -1;
    }

    if (indice < 0) {
        return -1;
    }

    //lista
    if (tipoRepresentacao == LISTA) {

        if (indice >= graus[id]) {
            return -1;
        }

        return listas[id][indice];
    }

    //matriz
    int contador = 0;

    for (int j = 0; j < capacidade; j++) {

        if (matriz[id][j]) {

            if (contador == indice) {
                return j;
            }

            contador++;
        }
    }

    return -1;
}

void Grafo::alterarRepresentacao(int novaRepresentacao) {

    if (novaRepresentacao == tipoRepresentacao) {
        return;
    }

    if (novaRepresentacao == MATRIZ) {
        if (tipoRepresentacao == MATRIZ) return;

        if (matriz != nullptr) {
        destruirMatriz();
        }

        inicializarMatriz();

        // reconstruir arestas a partir das listas
        for (int i = 0; i < capacidade; i++) {
                for (int j = 0; j < graus[i]; j++) {
                    int destino = listas[i][j];
                    matriz[i][destino] = true;
                }
        }

        // liberar listas antigas
        destruirListas();
        listas = nullptr;
        graus = nullptr;
        tipoRepresentacao = MATRIZ;
        }

    else if (novaRepresentacao == LISTA) {
        if (tipoRepresentacao == LISTA) return;

        // destrói listas antigas
        if (listas != nullptr) {
            destruirListas();;
        }


        inicializarListas();

        // contar graus
        for (int i = 0; i < capacidade; i++) {
            for (int j = 0; j < capacidade; j++) {
                if (matriz[i][j]) {
                    graus[i]++;
                }
            }
        }

        // alocar listas
        for (int i = 0; i < capacidade; i++) {
            if (graus[i] > 0) {
                listas[i] = new int[graus[i]];

                int k = 0;
                for (int j = 0; j < capacidade; j++) {
                    if (matriz[i][j]) {
                        listas[i][k++] = j;
                    }
                }
            }
        }

        // liberar matriz antiga
        destruirMatriz();
        matriz = nullptr;
        tipoRepresentacao = LISTA;
    }
}

//int Grafo::getTipoRepresentacao() const {
//    return tipoRepresentacao;
//}

//int Grafo::getTipoGrafo() const {
  //  return tipoGrafo;
//}


