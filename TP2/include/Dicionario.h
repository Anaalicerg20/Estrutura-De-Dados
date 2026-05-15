#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP

#include "../include/Usuario.h"
#include "../include/Tema.h"
#include "../include/No.h"

class Dicionario {

private:

    int capacidadeUsuarios;
    int capacidadeTemas;

    Usuario** usuarios;
    Tema** temas;

    No** nosSocial;
    No** nosUsuariosTemas;
    No** nosTemas;

    void aumentarCapacidadeUsuarios();
    void aumentarCapacidadeTemas();

public:

    Dicionario();
    ~Dicionario();

    // cadastro
    void inserirUsuario(Usuario* usuario, No* noSocial, No* noTemaUsuario);

    void inserirTema(Tema* tema, No* noTema);

    // acesso
    Usuario* getUsuario(int id) const;
    Tema* getTema(int id) const;

    No* getNoSocial(int id) const;
    No* getNoUsuarioTema(int id) const;
    No* getNoTema(int id) const;
};

#endif