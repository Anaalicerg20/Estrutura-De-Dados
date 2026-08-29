TP3 – Sistema de Gerenciamento de Estoque

Trabalho Prático 3 da disciplina DCC221 – Estruturas de Dados (UFMG).

Sobre o Projeto

Este trabalho implementa um sistema de gerenciamento de estoque, permitindo o cadastro de usuários e produtos, o registro de compras e reposições, além da consulta ao histórico de movimentações do sistema.

O sistema mantém informações sobre produtos, quantidades disponíveis em estoque e operações realizadas pelos usuários, processando todas as entradas de forma dinâmica.

Funcionalidades
Cadastro de usuários.
Cadastro de produtos.
Registro de compras.
Registro de reposições de estoque.
Controle da quantidade disponível de cada produto.
Consulta ao histórico de operações.
Busca eficiente de produtos utilizando tabela hash.
Gerenciamento centralizado das operações do sistema.
Estrutura do Projeto
TP/

├── include/

├── src/

├── obj/

├── bin/

└── Makefile
Compilação

Na raiz do projeto execute:

make all

Os executáveis serão gerados em:

bin/tp2.out
bin/tp3.out
Execução

Execute o programa redirecionando um arquivo de entrada:

./bin/tp2.out < entrada.txt

ou

./bin/tp3.out < entrada.txt
Exemplo
Entrada
U 0 Ana
U 1 Bruno
P 0 Notebook 10
P 1 Mouse 25
C 0 1 2
C 1 0 1
R 0 5
R 1 10

H
Saída
U 0
U 1
P 0
P 1
C 0 1 2
C 1 0 1
R 0 5
R 1 10
H

Autor
Ana Alice
Engenharia de Computação – UFMG
DCC221 – Estruturas de Dados (2026/1)
