#include "../include/Sistema.h"
#include <iostream>

int main() {

    int numAcoes = 100;     // valor “seguro” inicial
    int numClientes = 100;  

    Sistema sistema(numAcoes, numClientes, 0);

    sistema.processarEntrada();

    return 0;
}
