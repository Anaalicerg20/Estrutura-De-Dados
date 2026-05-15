#include <iostream>
#include <sstream>
#include <string>

#include "../include/Usuario.h"
#include "../include/Tema.h"
#include "../include/No.h"
#include "../include/Grafo.h"
#include "../include/Dicionario.h"

using namespace std;

int main() {
    const int OFFSET_TEMAS = 5000;

    // começa com lista
    int representacaoAtual = LISTA;

    // cria os grafos
    Grafo grafoSocial(LISTA, GRAFO_SOCIAL);
    Grafo grafoTemas(LISTA, GRAFO_TEMAS);

    // cria dicionário
    Dicionario dicionario;

    // ids automáticos
    int proxIdUsuario = 0;
    int proxIdTema = 0;

    string linha;

    while (getline(cin, linha)) {

        if (linha.empty()) {
            continue;
        }

        stringstream ss(linha);

        string comando;
        ss >> comando;

        // =========================
        // ALTERAR REPRESENTAÇÃO
        // =========================

        if (comando == "A") {

            char modo;
            ss >> modo;

            if (modo == 'L') {
                representacaoAtual = LISTA;
            }
            else {
                representacaoAtual = MATRIZ;
            }

            grafoSocial.alterarRepresentacao(representacaoAtual);
            grafoTemas.alterarRepresentacao(representacaoAtual);

            std :: cout << "A " << modo << endl;
        }

        // =========================
        // CADASTRAR TEMA
        // =========================

        else if (comando == "T") {

            string nomeTema;
            char tipoTema;

            ss >> nomeTema >> tipoTema;

            int idTema = proxIdTema;

            Tema* tema = new Tema(idTema, nomeTema, tipoTema);

            // nó do tema no grafo bipartido
            No* noTema = new No(idTema, OFFSET_TEMAS + idTema, 'T');

            grafoTemas.inserirVertice(noTema);

            dicionario.inserirTema(tema, noTema);

            std :: cout << "T " << idTema << endl;

            proxIdTema++;
        }

        // =========================
        // CADASTRAR USUÁRIO
        // =========================

        else if (comando == "U") {

            string nome;
            int idade;

            ss >> nome >> idade;

            int idUsuario = proxIdUsuario;

            Usuario* usuario =
                new Usuario(idUsuario, nome, idade);

            // nó no grafo social
            No* noSocial =
                new No(idUsuario,
                       idUsuario, //MUDANÇA: grafoSocial.getQuantidadeVertices()
                       'U');

            // nó no grafo temas
            No* noTemaUsuario =
                new No(idUsuario,
                       idUsuario,
                       'U');

            grafoSocial.inserirVertice(noSocial);
            grafoTemas.inserirVertice(noTemaUsuario);

            dicionario.inserirUsuario(usuario,
                                      noSocial,
                                      noTemaUsuario);

            // inserir arestas usuário-tema
            int idTema;

            while (ss >> idTema) {

                No* noTema =
                    dicionario.getNoTema(idTema);

                grafoTemas.inserirAresta(
                    noTemaUsuario->getIndice(),
                    noTema->getIndice()
                );
            }

            std :: cout << "U " << idUsuario << endl;

            proxIdUsuario++;
        }

/*        else if (comando == "S") {
        int u, v;
        ss >> u >> v;

        // Acessando índices via Dicionário de forma direta
        grafoSocial.inserirAresta(dicionario.getNoSocial(u)->getIndice(), 
                              dicionario.getNoSocial(v)->getIndice());

        std:: cout << "S " << dicionario.getUsuario(u)->getNome() << " " 
            << dicionario.getUsuario(v)->getNome() << endl;
        }
*/

        // =========================
        // SEGUIR
        // =========================

        else if (comando == "S") {

            int u, v;

            ss >> u >> v;

            No* origem =
                dicionario.getNoSocial(u);

            No* destino =
                dicionario.getNoSocial(v);

            grafoSocial.inserirAresta(
                origem->getIndice(),
                destino->getIndice()
            );

            Usuario* usuarioU =
                dicionario.getUsuario(u);

            Usuario* usuarioV =
                dicionario.getUsuario(v);

            std :: cout << "S "
                 << usuarioU->getNome()
                 << " "
                 << usuarioV->getNome()
                 << endl;
        }
    

        // =========================
        // REMOVER SEGUIMENTO
        // =========================

        else if (comando == "R") {

            int u, v;

            ss >> u >> v;

            No* origem =
                dicionario.getNoSocial(u);

            No* destino =
                dicionario.getNoSocial(v);

            grafoSocial.removerAresta(
                origem->getIndice(),
                destino->getIndice()
            );

            Usuario* usuarioU =
                dicionario.getUsuario(u);

            Usuario* usuarioV =
                dicionario.getUsuario(v);

            std :: cout << "R "
                 << usuarioU->getNome()
                 << " "
                 << usuarioV->getNome()
                 << endl;
        }

        // =========================
        // LISTAR TEMAS
        // =========================

        else if (comando == "LT") {

            int idUsuario;
            ss >> idUsuario;

            Usuario* usuario =
                dicionario.getUsuario(idUsuario);

            No* noUsuario =
                dicionario.getNoUsuarioTema(idUsuario);

            std :: cout << "LT "
                 << usuario->getNome();

            int grau =
                grafoTemas.getGrau(
                    noUsuario->getIndice()
                );

            for (int i = 0; i < grau; i++) {

                int adj =
                    grafoTemas.getAdjacente(
                        noUsuario->getIndice(),
                        i
                    );

                No* noTema =
                    grafoTemas.obterVertice(adj);

                Tema* tema =
                    dicionario.getTema(noTema->getId());

                std :: cout << " "
                     << tema->getNome();
            }

            std :: cout << endl;
        }

        // =========================
        // LISTAR SEGUIDORES
        // =========================

        else if (comando == "LC") {

            int idUsuario;
            ss >> idUsuario;

            Usuario* usuario =
                dicionario.getUsuario(idUsuario);

            No* noUsuario =
                dicionario.getNoSocial(idUsuario);

            std :: cout << "LC "
                 << usuario->getNome();

            for (int i = 0;
                 i < grafoSocial.getCapacidade();
                 i++) {

                No* candidato =
                    grafoSocial.obterVertice(i);

                if (candidato == nullptr) {
                    continue;
                }

                if (grafoSocial.existeAresta(
                        candidato->getIndice(),
                        noUsuario->getIndice()
                    )) {

                    Usuario* seguidor =
                        dicionario.getUsuario(
                            candidato->getId()
                        );

                    std :: cout << " "
                         << seguidor->getNome();
                }
            }

            std :: cout << endl;
        }

        // =========================
        // LISTAR SEGUIDOS
        // =========================

        else if (comando == "LS") {

            int idUsuario;
            ss >> idUsuario;

            Usuario* usuario =
                dicionario.getUsuario(idUsuario);

            No* noUsuario =
                dicionario.getNoSocial(idUsuario);

            std :: cout << "LS "
                 << usuario->getNome();

            int grau =
                grafoSocial.getGrau(
                    noUsuario->getIndice()
                );

            for (int i = 0; i < grau; i++) {

                int adj =
                    grafoSocial.getAdjacente(
                        noUsuario->getIndice(),
                        i
                    );

                No* noSeguido =
                    grafoSocial.obterVertice(adj);

                Usuario* seguido =
                    dicionario.getUsuario(
                        noSeguido->getId()
                    );

                std :: cout << " "
                     << seguido->getNome();
            }

            std :: cout << endl;
        }

        // =========================
        // LISTAR AMIGOS
        // =========================

        else if (comando == "LA") {

            int idUsuario;
            ss >> idUsuario;

            Usuario* usuario =
                dicionario.getUsuario(idUsuario);

            No* noUsuario =
                dicionario.getNoSocial(idUsuario);

            std :: cout << "LA "
                 << usuario->getNome();

            for (int i = 0;
                 i < grafoSocial.getCapacidade();
                 i++) {

                No* candidato =
                    grafoSocial.obterVertice(i);

                if (candidato == nullptr) {
                    continue;
                }

                bool ida =
                    grafoSocial.existeAresta(
                        noUsuario->getIndice(),
                        candidato->getIndice()
                    );

                bool volta =
                    grafoSocial.existeAresta(
                        candidato->getIndice(),
                        noUsuario->getIndice()
                    );

                if (ida && volta) {

                    Usuario* amigo =
                        dicionario.getUsuario(
                            candidato->getId()
                        );

                    std :: cout << " "
                         << amigo->getNome();
                }
            }

            std :: cout << endl;
        }

        // =========================
        // CONSULTA RELAÇÃO
        // =========================

        else if (comando == "Q") {

            int u, v;

            ss >> u >> v;

            No* noU =
                dicionario.getNoSocial(u);

            No* noV =
                dicionario.getNoSocial(v);

            bool uv =
                grafoSocial.existeAresta(
                    noU->getIndice(),
                    noV->getIndice()
                );

            bool vu =
                grafoSocial.existeAresta(
                    noV->getIndice(),
                    noU->getIndice()
                );

            int valor = 0;

            if (uv && vu) {
                valor = 3;
            }
            else if (uv) {
                valor = 1;
            }
            else if (vu) {
                valor = 2;
            }

            std :: cout << "Q "
                 << dicionario.getUsuario(u)->getNome()
                 << " "
                 << dicionario.getUsuario(v)->getNome()
                 << " "
                 << valor
                 << endl;
        }

        // =========================
        // CONSULTA INTERESSE
        // =========================

        else if (comando == "G") {

            int idUsuario, idTema;

            ss >> idUsuario >> idTema;

            Usuario* usuario =
                dicionario.getUsuario(idUsuario);

            Tema* tema =
                dicionario.getTema(idTema);

            No* noUsuario =
                dicionario.getNoUsuarioTema(idUsuario);

            No* noTema =
                dicionario.getNoTema(idTema);

            bool existe =
                grafoTemas.existeAresta(
                    noUsuario->getIndice(),
                    noTema->getIndice()
                );

            std :: cout << "G "
                 << usuario->getNome()
                 << " "
                 << tema->getNome()
                 << " "
                 << (existe ? 1 : 0)
                 << endl;
        }

        // =========================
        // CONSULTA POPULARIDADE
        // =========================

        else if (comando == "F") {

            int idTema;

            ss >> idTema;

            Tema* tema =
                dicionario.getTema(idTema);

            No* noTema =
                dicionario.getNoTema(idTema);

            int popularidade =
                grafoTemas.getGrau(
                    noTema->getIndice()
                );

            std :: cout << "F "
                 << tema->getNome()
                 << " "
                 << popularidade
                 << endl;
        }
    }

    return 0;
}