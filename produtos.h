#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct Produto
{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto *prox;
} Produto;

typedef struct
{
    Produto *inicio;
} ListaProdutos;

void inicializarLista(ListaProdutos *lista);
void inserirProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco);
void listarProdutos(ListaProdutos *lista);
Produto *buscarProduto(ListaProdutos *lista, int codigo);
int atualizarProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco);
int removerProduto(ListaProdutos *lista, int codigo);
void liberarLista(ListaProdutos *lista);

#endif