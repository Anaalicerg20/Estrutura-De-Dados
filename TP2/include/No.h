#ifndef NO_HPP
#define NO_HPP

class No {
private:
    int id;
    int indice;
    char tipo; // U = usuário, T = tema

public:
    // construtor
    No(int id, int indice, char tipo);

    // gets
    int getId() const;
    int getIndice() const;
    char getTipo() const;
};

#endif