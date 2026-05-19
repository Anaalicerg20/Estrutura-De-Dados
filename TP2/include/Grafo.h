#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "../include/No.h"

#define LISTA 0
#define MATRIZ 1

#define GRAFO_SOCIAL 0
#define GRAFO_TEMAS 1

class Grafo {
private:
    //Lista X Matriz (atual)
    int tipoRepresentacao;

    // Social X Temas 
    int tipoGrafo;

    //num_vertices
    int capacidade; //máx q pode ter atualmente
    int quantidadeVertices; // quantos realmente tem

    // vertices[id] -> nó correspondente
    No** vertices;

    //matriz de adjacência
    bool** matriz;

    //lista de adjacência
    int** listas;
    int* graus;

    //Funções

    void inicializarMatriz();
    void destruirMatriz();

    void inicializarListas();
    void destruirListas();

    void aumentarCapacidade();

public:
    // construtor
    Grafo(int tipoRepresentacao, int tipoGrafo);

    // destrutor
    ~Grafo();

    //Vértices
    void inserirVertice(No* no);
    No* obterVertice(int id) const;
    int getCapacidade() const;

    //Arestas
    void inserirAresta(int origem, int destino);
    void removerAresta(int origem, int destino);
    bool existeAresta(int origem, int destino) const;

    //Consultar 
    int getGrau(int id) const; //quantas ligações um vertice tem
    int getAdjacente(int id, int indice) const; //quais sao essas ligações 

    //Representação: lista x matriz / tema x social 
    void alterarRepresentacao(int novaRepresentacao);
   // int getTipoRepresentacao() const;
   // int getTipoGrafo() const;
};

#endif