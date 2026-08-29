#ifndef VETOR_H
#define VETOR_H

template <typename T>
class Vetor
{
private:
    T* elementos;

    int tamanho;
    int capacidade;

    void redimensionar(int novaCapacidade);

public:

    Vetor();
    Vetor(const Vetor<T>& outro);

    ~Vetor();

    bool estaVazio() const;
    int getTamanho() const;
    void limpar(); 

    void adicionar(const T& elemento);

    T& operator[](int indice); //cadastro de usuário, atualizar: estoque/histórico,  preencher vetores de id na hash map 
    const T& operator[](int indice) const; //consultas LU / LP / LC / LR, imprimir resultados, percorrer índices invertidos, comparar ids(intersecção)

    Vetor<T>& operator=(const Vetor<T>& outro); //copiar um vetor já existente
    
};


//implementações (template)
template <typename T> Vetor<T>::Vetor()
{
    capacidade = 10;
    tamanho = 0;
    elementos = new T[capacidade];
}

template <typename T> Vetor<T>::Vetor(const Vetor<T>& outro)
{
    tamanho = outro.tamanho;
    capacidade = outro.capacidade;

    elementos = new T[capacidade];

    for (int i = 0; i < tamanho; i++)
    {
        elementos[i] = outro.elementos[i];
    }
}

template <typename T> Vetor<T>::~Vetor()
{
    delete[] elementos;
}

template <typename T>
void Vetor<T>::redimensionar(int novaCapacidade)
{
    T* novoVetor = new T[novaCapacidade];

    for (int i = 0; i < tamanho; i++)
    {
        novoVetor[i] = elementos[i];
    }

    delete[] elementos;

    elementos = novoVetor;
    capacidade = novaCapacidade;
}

template <typename T> bool Vetor<T>::estaVazio() const
{
    return tamanho == 0;
}

template <typename T> int Vetor<T>::getTamanho() const
{
    return tamanho;
}

template <typename T> void Vetor<T>::limpar()
{
    tamanho = 0;
}

template <typename T> void Vetor<T>::adicionar(const T& elemento)
{
    if (tamanho == capacidade)
    {
        redimensionar(capacidade * 2);
    }

    elementos[tamanho] = elemento;
    tamanho++;
}

template <typename T> T& Vetor<T>::operator[](int indice)
{
    return elementos[indice];
}

template <typename T> const T& Vetor<T>::operator[](int indice) const
{
    return elementos[indice];
}

template <typename T> Vetor<T>& Vetor<T>::operator=(const Vetor<T>& outro)
{
    if (this == &outro)
    {
        return *this;
    }

    delete[] elementos;

    tamanho = outro.tamanho;
    capacidade = outro.capacidade;

    elementos = new T[capacidade];

    for (int i = 0; i < tamanho; i++)
    {
        elementos[i] = outro.elementos[i];
    }

    return *this;
}

#endif