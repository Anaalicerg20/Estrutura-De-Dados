## TP2 – Rede Social por Afinidade de Tópicos

Trabalho Prático 2 da disciplina DCC221 – Estruturas de Dados (UFMG).

## Sobre o Projeto

Este projeto implementa uma rede social baseada em interesses. O sistema permite cadastrar usuários e tópicos, registrar relações de seguimento entre usuários e realizar consultas sobre afinidades, conexões e recomendações.

As operações são processadas sequencialmente a partir de um arquivo de entrada, atualizando dinamicamente o estado da rede.

## Funcionalidades

Cadastro de tópicos.
Cadastro de usuários.
Registro de relações de seguimento entre usuários.
Associação de usuários a tópicos de interesse.
Consultas sobre:
Tópicos de um usuário.
Seguidores de um usuário.
Usuários seguidos.
Afinidades entre usuários.
Recomendações.
Atualização dinâmica dos interesses dos usuários.

## Estrutura do Projeto

```text
TP/
├── include/
├── src/
├── obj/
├── bin/
└── Makefile
```

## Compilação

Na raiz do projeto execute:

```bash
make all
```

O executável será gerado em:

```bash
bin/tp2.out
```

## Execução

Execute o programa redirecionando um arquivo de entrada:

```bash
./bin/tp2.out < entrada.txt
```

## Limpeza dos Arquivos Gerados

```bash
make clean
```

## Recompilação Completa

```bash
make rebuild
```

## Exemplo

### Entrada

```text
A L
T IA A
T Musica P
T Grafos A
T Futebol P
U Ana 20 0 2
U Bruno 21 1 2
U Carla 22 0 3
U Diego 23 2
U Eva 24 1 3
S 0 1
S 2 0
S 1 2
S 0 2
S 3 0
S 2 1
LT 0
LT 4
LC 0
LS 0
LA 0
Q 0 1
Q 1 0
Q 1 2
G 4 2
F 2
A M
R 0 2
Q 0 2
LA 0
LC 2
LS 2
F 3
```

### Saída

```text
A L
T 0
T 1
T 2
T 3
U 0
U 1
U 2
U 3
U 4
S Ana Bruno
S Carla Ana
S Bruno Carla
S Ana Carla
S Diego Ana
S Carla Bruno
LT Ana IA Grafos
LT Eva Musica Futebol
LC Ana Carla Diego
LS Ana Bruno Carla
LA Ana Carla
Q Ana Bruno 1
Q Bruno Ana 2
Q Bruno Carla 3
G Eva Grafos 0
F Grafos 3
A M
R Ana Carla
Q Ana Carla 2
LA Ana
LC Carla Bruno
LS Carla Ana Bruno
F Futebol 2
```

## Autor

**Ana Alice**
Engenharia de Computação – UFMG
DCC221 – Estruturas de Dados (2026/1)
