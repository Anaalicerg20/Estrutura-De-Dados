#ifndef SISTEMA_H
#define SISTEMA_H

#include "Acao.h"
#include "Cliente.h"
#include <string>

class Sistema {
private:
    int numAcoes;
    int numClientes;
    int w;

    Acao* acoes; 
    Cliente* clientes; 

    //para armazenar as metricas que serão usadas: determinadas quando se lê M 
    int qtdMetricasPermitidas;
    std :: string metricasPermitidas[4];

    int ofcNumAcoes;
    int ofcNumClientes;

public:
    // construtor e destrutor
    Sistema(int numAcoes, int numClientes, int w);
    ~Sistema();

    // processamento de entrada
    void processarEntrada();

    // cálculo 
    void executarConsulta(int id_consulta, int cliente_id, int n, const std::string* metricas, const double* pesos, int m);

    // funções auxiliares para executarConsulta 
    double calcularMetrica(int acao_id, const std::string& metrica);
    void ordenar(int* indices, double* valores, int tamanho);

};

#endif