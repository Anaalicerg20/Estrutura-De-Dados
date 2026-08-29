#include "../include/Dicionario.h"

//construtor
Dicionario::Dicionario() {

    capacidadeUsuarios = 10;
    capacidadeTemas = 10;

    // usuários
    usuarios = new Usuario*[capacidadeUsuarios];
    nosSocial = new No*[capacidadeUsuarios];
    nosUsuariosTemas = new No*[capacidadeUsuarios];

    for (int i = 0; i < capacidadeUsuarios; i++) {
        usuarios[i] = nullptr;
        nosSocial[i] = nullptr;
        nosUsuariosTemas[i] = nullptr;
    }

    // temas
    temas = new Tema*[capacidadeTemas];
    nosTemas = new No*[capacidadeTemas];

    for (int i = 0; i < capacidadeTemas; i++) {
        temas[i] = nullptr;
        nosTemas[i] = nullptr;
    }
}

//destrutor
Dicionario::~Dicionario() {

    // usuários
    for (int i = 0; i < capacidadeUsuarios; i++) {
        delete usuarios[i];
        delete nosSocial[i];
        delete nosUsuariosTemas[i];
    }


    delete[] usuarios;
    delete[] nosSocial;
    delete[] nosUsuariosTemas;

    // temas
    for (int i = 0; i < capacidadeTemas; i++) {
        delete temas[i];

        if (nosTemas[i] != nullptr) {
            delete nosTemas[i];
        }
    }

    delete[] temas;
    delete[] nosTemas;
}

//aumentar capacidade
void Dicionario::aumentarCapacidadeUsuarios() {

    int novaCapacidade = capacidadeUsuarios * 2;

    Usuario** novosUsuarios = new Usuario*[novaCapacidade];
    No** novosNosSocial = new No*[novaCapacidade];
    No** novosNosTemas = new No*[novaCapacidade];

    for (int i = 0; i < novaCapacidade; i++) {

        novosUsuarios[i] = nullptr;
        novosNosSocial[i] = nullptr;
        novosNosTemas[i] = nullptr;
    }

    for (int i = 0; i < capacidadeUsuarios; i++) {

        novosUsuarios[i] = usuarios[i];
        novosNosSocial[i] = nosSocial[i];
        novosNosTemas[i] = nosUsuariosTemas[i];
    }

    delete[] usuarios;
    delete[] nosSocial;
    delete[] nosUsuariosTemas;

    usuarios = novosUsuarios;
    nosSocial = novosNosSocial;
    nosUsuariosTemas = novosNosTemas;

    capacidadeUsuarios = novaCapacidade;
}

void Dicionario::aumentarCapacidadeTemas() {

    int novaCapacidade = capacidadeTemas * 2;

    Tema** novosTemas = new Tema*[novaCapacidade];
    No** novosNosTemas = new No*[novaCapacidade];

    for (int i = 0; i < novaCapacidade; i++) {

        novosTemas[i] = nullptr;
        novosNosTemas[i] = nullptr;
    }

    for (int i = 0; i < capacidadeTemas; i++) {

        novosTemas[i] = temas[i];
        novosNosTemas[i] = nosTemas[i];
    }

    delete[] temas;
    delete[] nosTemas;

    temas = novosTemas;
    nosTemas = novosNosTemas;

    capacidadeTemas = novaCapacidade;
}


//inserção
void Dicionario::inserirUsuario(Usuario* usuario, No* noSocial, No* noTemaUsuario) {

    int id = usuario->getId();

    while (id >= capacidadeUsuarios) {
        aumentarCapacidadeUsuarios();
    }

    usuarios[id] = usuario;
    nosSocial[id] = noSocial;
    nosUsuariosTemas[id] = noTemaUsuario;
}

void Dicionario::inserirTema(Tema* tema,
                             No* noTema) {

    int id = tema->getId();

    while (id >= capacidadeTemas) {
        aumentarCapacidadeTemas();
    }

    temas[id] = tema;
    nosTemas[id] = noTema;
}


//get
Usuario* Dicionario::getUsuario(int id) const {

    return usuarios[id];
}

Tema* Dicionario::getTema(int id) const {

    return temas[id];
}

No* Dicionario::getNoSocial(int id) const {

    return nosSocial[id];
}

No* Dicionario::getNoUsuarioTema(int id) const {

    return nosUsuariosTemas[id];
}

No* Dicionario::getNoTema(int id) const {

    return nosTemas[id];
}