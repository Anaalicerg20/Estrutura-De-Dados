#include "../include/Sistema.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

Sistema::Sistema(int numAcoes, int numClientes, int w) : numAcoes(numAcoes), numClientes(numClientes), w(w) {
    acoes = new Acao[numAcoes];
    clientes = new Cliente[numClientes];
}

//desalocar a memória
Sistema::~Sistema() {
    delete[] acoes;
    delete[] clientes;
}

void Sistema::processarEntrada() {
    char tipo;

    std::cin >> tipo;

    if (tipo == 'M') {
        std::cin >> this->w;

        std::cin.ignore();

        std::string linhaM;
        std::getline(std::cin, linhaM); // Pega o resto da linha M
        std::stringstream ss(linhaM);

        std::string metrica;
        qtdMetricasPermitidas = 0;

        while (ss >> metrica) {
            metricasPermitidas[qtdMetricasPermitidas] = metrica;
            qtdMetricasPermitidas++;
        }
    }

    ofcNumAcoes = 0;
    ofcNumClientes = 0;

    // leitura das linhas A
    while (std::cin >> tipo && tipo == 'A') {
        int id;
        std::cin >> id;

        acoes[id].inicializar(id, w);
        ofcNumAcoes++;
    }
    //std::cout << "TOTAL ACOES: " << ofcNumAcoes << "\n"; //debug

    // leitura das linhas U
    do {
        if (tipo == 'U') {
            int id;
            std::cin >> id;

            clientes[id].inicializar(id, ofcNumAcoes);
            ofcNumClientes++;
        }
    } while (std::cin >> tipo && tipo == 'U');

    // leitura de P, B, V, Q em qualquer ordem
    do { 
        //std::cout << "LI TIPO: " << tipo << "\n"; //debug
        if (tipo == 'P') {
            int acao_id;
            double preco;

            std::cin >> acao_id >> preco;
            acoes[acao_id].adicionarPreco(preco);

          //  std::cout << "DEBUG P: acao_id = " << acao_id << "\n"; //debug
          //  std::cout << "ofcNumAcoes = " << ofcNumAcoes << "\n"; //debug
        }

        else if (tipo == 'B') {
            int cliente_id, acao_id;

            std::cin >> cliente_id >> acao_id;
            clientes[cliente_id].comprarAcao(acao_id);
        }

        else if (tipo == 'V') {
            int cliente_id, acao_id;

            std::cin >> cliente_id >> acao_id;
            clientes[cliente_id].venderAcao(acao_id);
        }

        else if (tipo == 'Q') {
            int id_consulta, cliente_id, n, m;

            std::cin >> id_consulta >> cliente_id >> n >> m;

            std::string metricas[4];
            double pesos[4];

            for (int i = 0; i < m; i++) {
                std::cin >> metricas[i] >> pesos[i];
            }

            bool valido = true;

            //Comparando as metricas de Q com as permitidas em M
            for (int i = 0; i < m; i++) {
                bool encontrada = false;

                for (int j = 0; j < qtdMetricasPermitidas; j++) {
                    if (metricas[i] == metricasPermitidas[j]) {
                        encontrada = true;
                        break;
                    }
                }

                if (!encontrada) {
                    valido = false;
                    break;
                }
            }

            if (valido) {
                executarConsulta(id_consulta, cliente_id, n, metricas, pesos, m);
            }
        }

    } while (std::cin >> tipo);
}

void Sistema :: executarConsulta(int id_consulta, int cliente_id, int n, const std::string* metricas, const double* pesos, int m) {

    double pontuacao[ofcNumAcoes];
    double valores[4][ofcNumAcoes];

    // inicializar pontuação com 0
    for (int i = 0; i < ofcNumAcoes; i++) {
        pontuacao[i] = 0;
    }

    //calcular as métricas
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < ofcNumAcoes; j++) {
            valores[i][j] = calcularMetrica(j, metricas[i]);
        }
    }


    //ordenar as ações para cada métrica
    for (int k = 0; k < m; k++) {
        int indices[ofcNumAcoes];

        for (int i = 0; i < ofcNumAcoes; i++) {
            indices[i] = i;
        }

        ordenar(indices, valores[k], ofcNumAcoes);

      //  std::cout << "DEBUG Ordem Metrica: ";
//for(int k=0; k<ofcNumAcoes; k++) std::cout << indices[k] << " ";
//std::cout << std::endl;

        //pontuação N-1 multiplicado pelos pesos e soma das métricas = pontuação final global para cada ação.
        for(int i = 0; i < ofcNumAcoes; i++) {
            int acao_id = indices[i];
            pontuacao[acao_id] += (ofcNumAcoes - i) * pesos[k];
        }
    }

    //filtrar ações de um cliente
    int lista[ofcNumAcoes];
    int total = 0;

    //debug
   /* std::cout << "DEBUG CLIENTE " << cliente_id << ":\n";
for (int i = 0; i < ofcNumAcoes; i++) {
    if (clientes[cliente_id].possuiAcao(i)) {
        std::cout << "cliente tem acao " << i << "\n";
    }
} */

    for (int i = 0; i < ofcNumAcoes; i++) {
        if (clientes[cliente_id].possuiAcao(i)) {
            lista[total] = i;
            total = total +1;
        }
    }

    //debug

   /* std::cout << "ANTES DA ORDENACAO:\n";
for (int i = 0; i < total; i++) {
    std::cout << "lista[" << i << "] = " << lista[i]
              << " pontuacao = " << pontuacao[lista[i]] << "\n";
} */

    //ordenar ações do cliente
    ordenar(lista, pontuacao, total);
//debug
    /*std::cout << "DEPOIS DA ORDENACAO:\n";
for (int i = 0; i < total; i++) {
    std::cout << "lista[" << i << "] = " << lista[i]
              << " pontuacao = " << pontuacao[lista[i]] << "\n";
} */

    //printar melhores e piores
    int limite;

    if (total < n) {
        limite = total;
    } else {
        limite = n;
    }

    for (int i = 0; i < limite; i++) {
        int acao_id = lista[i];

        std::cout << "R " << id_consulta
                  << " M " << i
                  << " " << acao_id
                  << " " << std::fixed << std::setprecision(2)
                  << pontuacao[acao_id]
                  << "\n";
    }

    for (int i = 0; i < limite; i++) {
        int acao_id = lista[total - 1 - i];

        std::cout << "R " << id_consulta
                  << " P " << i
                  << " " << acao_id
                  << " " << std::fixed << std::setprecision(2)
                  << pontuacao[acao_id]
                  << "\n";
    }
}

//funções auxiliares para executarConsulta
double Sistema::calcularMetrica(int acao_id, const std::string& metrica) {

    if (metrica == "RET")
        return acoes[acao_id].calcularRET();

    if (metrica == "AVGRET")
        return acoes[acao_id].calcularAVGRET();

    if (metrica == "STAB")
        return acoes[acao_id].calcularSTAB();

    if (metrica == "CONS")
        return acoes[acao_id].calcularCONS();

    return 0;
}

//ordenação bubble sort
void Sistema::ordenar(int* indices, double* valores, int tamanho) {

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 1; j < tamanho - i; j++) {

            int a = indices[j - 1];
            int b = indices[j];

            // ordem decrescente + desempate por menor id
            if (valores[b] > valores[a] ||
                (valores[b] == valores[a] && b < a)) {

                std::swap(indices[j - 1], indices[j]);
            }
        }
    }
}