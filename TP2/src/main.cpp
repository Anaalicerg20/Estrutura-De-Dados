#include <iostream>
#include <sstream>
#include <string>

#include "../include/Usuario.h"
#include "../include/Tema.h"
#include "../include/No.h"
#include "../include/Grafo.h"
#include "../include/Dicionario.h"

// Ordena ids em ordem crescente
void ordenar(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                std::swap(vetor[j], vetor[j + 1]);
            }
        }
    }
}

int main() {
    //garante que usuario e temas não serao guardados no mesmo local na memoria 
    const int OFFSET_TEMAS = 5000;
    int representacaoAtual = LISTA;

    Grafo grafoSocial(LISTA, GRAFO_SOCIAL);
    Grafo grafoTemas(LISTA, GRAFO_TEMAS);
    Dicionario dicionario;

    int proxIdUsuario = 0;
    int proxIdTema = 0;
    std::string linha;

    while (std::getline(std::cin, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string comando;
        ss >> comando;

        // Alterar representação
        if (comando == "A") {
            char modo;
            ss >> modo;

            if (modo == 'L') {
                representacaoAtual = LISTA;
            } else {
                representacaoAtual = MATRIZ;
            }

            grafoSocial.alterarRepresentacao(representacaoAtual);
            grafoTemas.alterarRepresentacao(representacaoAtual);

            std::cout << "A " << modo << std::endl;
        }

        // Mudar tema 
        else if (comando == "T") {
            std::string nomeTema;
            char tipoTema;
            ss >> nomeTema >> tipoTema;

            Tema* tema = new Tema(proxIdTema, nomeTema, tipoTema);
            No* noTema = new No(proxIdTema, OFFSET_TEMAS + proxIdTema, 'T');

            grafoTemas.inserirVertice(noTema);
            dicionario.inserirTema(tema, noTema);

            std::cout << "T " << proxIdTema << std::endl;
            proxIdTema++;
        }

        // Cadastra usuário 
        else if (comando == "U") {
            std::string nome;
            int idade;
            ss >> nome >> idade;

            Usuario* usuario = new Usuario(proxIdUsuario, nome, idade);
            No* noSocial = new No(proxIdUsuario, proxIdUsuario, 'U');
            No* noTemaUsuario = new No(proxIdUsuario, proxIdUsuario, 'U');

            grafoSocial.inserirVertice(noSocial);
            grafoTemas.inserirVertice(noTemaUsuario);
            dicionario.inserirUsuario(usuario, noSocial, noTemaUsuario);

            int idTema;
            while (ss >> idTema) {
                grafoTemas.inserirAresta(noTemaUsuario->getIndice(), dicionario.getNoTema(idTema)->getIndice());
            }

            std::cout << "U " << proxIdUsuario << std::endl;
            proxIdUsuario++;
        }

        //Seguir
        else if (comando == "S") {
            int u, v;
            ss >> u >> v;

            grafoSocial.inserirAresta(dicionario.getNoSocial(u)->getIndice(), dicionario.getNoSocial(v)->getIndice());
            std::cout << "S " << dicionario.getUsuario(u)->getNome() << " " << dicionario.getUsuario(v)->getNome() << std::endl;
        }

        // Remover seguimento
        else if (comando == "R") {
            int u, v;
            ss >> u >> v;

            grafoSocial.removerAresta(dicionario.getNoSocial(u)->getIndice(), dicionario.getNoSocial(v)->getIndice());
            std::cout << "R " << dicionario.getUsuario(u)->getNome() << " " << dicionario.getUsuario(v)->getNome() << std::endl;
        }

        // Listar temas de um usuário
        else if (comando == "LT") {
            int idUsuario;
            ss >> idUsuario;

            std::cout << "LT " << dicionario.getUsuario(idUsuario)->getNome();

            int grau = grafoTemas.getGrau(dicionario.getNoUsuarioTema(idUsuario)->getIndice());
            int* temas = new int[grau];

            for (int i = 0; i < grau; i++) {
                int adj = grafoTemas.getAdjacente(dicionario.getNoUsuarioTema(idUsuario)->getIndice(), i);
                temas[i] = grafoTemas.obterVertice(adj)->getId();
            }

            ordenar(temas, grau);

            for (int i = 0; i < grau; i++) {
                std::cout << " " << dicionario.getTema(temas[i])->getNome();
            }

            delete[] temas;
            std::cout << std::endl;
        }

        // Listar seguidores
        else if (comando == "LC") {
            int idUsuario;
            ss >> idUsuario;

            std::cout << "LC " << dicionario.getUsuario(idUsuario)->getNome();

            int quantidade = 0;
            int indiceAlvo = dicionario.getNoSocial(idUsuario)->getIndice();

            for (int i = 0; i < grafoSocial.getCapacidade(); i++) {
                if (grafoSocial.obterVertice(i) != nullptr && grafoSocial.existeAresta(grafoSocial.obterVertice(i)->getIndice(), indiceAlvo)) {
                    quantidade++;
                }
            }

            int* seguidores = new int[quantidade];
            int k = 0;

            for (int i = 0; i < grafoSocial.getCapacidade(); i++) {
                if (grafoSocial.obterVertice(i) != nullptr && grafoSocial.existeAresta(grafoSocial.obterVertice(i)->getIndice(), indiceAlvo)) {
                    seguidores[k++] = grafoSocial.obterVertice(i)->getId();
                }
            }

            ordenar(seguidores, quantidade);

            for (int i = 0; i < quantidade; i++) {
                std::cout << " " << dicionario.getUsuario(seguidores[i])->getNome();
            }

            delete[] seguidores;
            std::cout << std::endl;
        }

        // Listar seguidos
        else if (comando == "LS") {
            int idUsuario;
            ss >> idUsuario;

            std::cout << "LS " << dicionario.getUsuario(idUsuario)->getNome();

            int grau = grafoSocial.getGrau(dicionario.getNoSocial(idUsuario)->getIndice());
            int* seguidos = new int[grau];

            for (int i = 0; i < grau; i++) {
                int adj = grafoSocial.getAdjacente(dicionario.getNoSocial(idUsuario)->getIndice(), i);
                seguidos[i] = grafoSocial.obterVertice(adj)->getId();
            }

            ordenar(seguidos, grau);

            for (int i = 0; i < grau; i++) {
                std::cout << " " << dicionario.getUsuario(seguidos[i])->getNome();
            }

            delete[] seguidos;
            std::cout << std::endl;
        }

        // Listar amigos 
        else if (comando == "LA") {
            int idUsuario;
            ss >> idUsuario;

            std::cout << "LA " << dicionario.getUsuario(idUsuario)->getNome();

            int quantidade = 0;
            int indiceAlvo = dicionario.getNoSocial(idUsuario)->getIndice();

            for (int i = 0; i < grafoSocial.getCapacidade(); i++) {
                if (grafoSocial.obterVertice(i) == nullptr) {
                    continue;
                }

                int indiceCandidato = grafoSocial.obterVertice(i)->getIndice();
                if (grafoSocial.existeAresta(indiceAlvo, indiceCandidato) && grafoSocial.existeAresta(indiceCandidato, indiceAlvo)) {
                    quantidade++;
                }
            }

            int* amigos = new int[quantidade];
            int k = 0;

            for (int i = 0; i < grafoSocial.getCapacidade(); i++) {
                if (grafoSocial.obterVertice(i) == nullptr) {
                    continue;
                }

                int indiceCandidato = grafoSocial.obterVertice(i)->getIndice();
                if (grafoSocial.existeAresta(indiceAlvo, indiceCandidato) && grafoSocial.existeAresta(indiceCandidato, indiceAlvo)) {
                    amigos[k++] = grafoSocial.obterVertice(i)->getId();
                }
            }

            ordenar(amigos, quantidade);

            for (int i = 0; i < quantidade; i++) {
                std::cout << " " << dicionario.getUsuario(amigos[i])->getNome();
            }

            delete[] amigos;
            std::cout << std::endl;
        }

        // Consulta relação
        else if (comando == "Q") {
            int u, v;
            ss >> u >> v;

            int indiceU = dicionario.getNoSocial(u)->getIndice();
            int indiceV = dicionario.getNoSocial(v)->getIndice();

            bool uv = grafoSocial.existeAresta(indiceU, indiceV);
            bool vu = grafoSocial.existeAresta(indiceV, indiceU);

            int valor = 0;
            if (uv && vu) {
                valor = 3;
            } else if (uv) {
                valor = 1;
            } else if (vu) {
                valor = 2;
            }

            std::cout << "Q " << dicionario.getUsuario(u)->getNome() << " " << dicionario.getUsuario(v)->getNome() << " " << valor << std::endl;
        }

        // Consulta interesse
        else if (comando == "G") {
            int idUsuario, idTema;
            ss >> idUsuario >> idTema;

            bool existe = grafoTemas.existeAresta(dicionario.getNoUsuarioTema(idUsuario)->getIndice(), dicionario.getNoTema(idTema)->getIndice());

            int resultadoInteresse = 0;
            if (existe) {
                resultadoInteresse = 1;
            } else {
                resultadoInteresse = 0;
            }

            std::cout << "G " << dicionario.getUsuario(idUsuario)->getNome() << " " << dicionario.getTema(idTema)->getNome() << " " << resultadoInteresse << std::endl;
        }

        // Consulta popularidade de tema
        else if (comando == "F") {
            int idTema;
            ss >> idTema;

            std::cout << "F " << dicionario.getTema(idTema)->getNome() << " " << grafoTemas.getGrau(dicionario.getNoTema(idTema)->getIndice()) << std::endl;
        }
    }

    return 0;
}