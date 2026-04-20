#include "../include/Sistema.h"
#include <iostream>

/*int main() {

    int numAcoes = 6;     // valor “seguro” inicial
    int numClientes = 1;  

    Sistema sistema(numAcoes, numClientes, 0);

    sistema.processarEntrada();

    return 0;
} */

int main() {

    int numAcoes, numClientes, w;

    std::cin >> numAcoes >> numClientes >> w;

    Sistema sistema(numAcoes, numClientes, w);

    sistema.processarEntrada();

    return 0;
}