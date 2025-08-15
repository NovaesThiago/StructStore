#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

void inicializarLista(ListaProdutos *lista)
{
    lista->inicio = NULL;
}

void inserirProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco)
{
    if (buscarProduto(lista, codigo) != NULL)
    {
        printf("Produto com o código %d já existe.\n", codigo);
        return;
    }

    Produto *novo = (Produto *)malloc(sizeof(Produto));

    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->prox = lista->inicio;
    lista->inicio = novo;
    printf("Produto inserido com sucesso!\n");
}

Produto *buscarProduto(ListaProdutos *lista, int codigo)
{
    Produto *atual = lista->inicio;
    while (atual)
    {
        if (atual->codigo == codigo)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

int atualizarProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco)
{
    Produto *p = buscarProduto(lista, codigo);
    if (p == NULL)
        return 0;

    strcpy(p->nome, nome);
    p->quantidade = quantidade;
    p->preco = preco;
    return 1;
}

int removerProduto(ListaProdutos *lista, int codigo)
{
    Produto *atual = lista->inicio;
    Produto *anterior = NULL;
    while (atual)
    {
        if (atual->codigo == codigo)
        {
            if (anterior)
                anterior->prox = atual->prox;
            else
                lista->inicio = atual->prox;
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

void listarProdutos(ListaProdutos *lista)
{
    Produto *atual = lista->inicio;
    if (atual == NULL)
    {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n==== Lista de Produtos ====\n");
    while (atual)
    {
        printf("Código: %d | Nome: %s | Quantidade: %d | Preço: R$ %.2f\n", atual->codigo, atual->nome, atual->quantidade, atual->preco);
        atual = atual->prox;
    }
}

void liberarLista(ListaProdutos *lista)
{
    Produto *atual = lista->inicio;
    while (atual)
    {
        Produto *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
}