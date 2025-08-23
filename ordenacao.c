#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

int contarProdutos(ListaProdutos *lista)
{
    int count = 0;
    Produto *atual = lista->inicio;
    while (atual != NULL)
    {
        count++;
        atual = atual->prox;
    }
    return count;
}

void ordenarQuantidade(ListaProdutos *lista)
{
    int n = contarProdutos(lista);
    Produto *vetor[n];
    Produto *atual = lista->inicio;
    for (int i = 0; i < n; i++)
    {
        vetor[i] = atual;
        atual = atual->prox;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (vetor[j]->quantidade < vetor[j + 1]->quantidade)
            {
                Produto *temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("\nOrdenado por quantidade:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s - %d unidades\n", vetor[i]->nome, vetor[i]->quantidade);
    }
}

void ordenarValorTotal(ListaProdutos *lista)
{
    int n = contarProdutos(lista);
    Produto *vetor[n];
    Produto *atual = lista->inicio;
    for (int i = 0; i < n; i++)
    {
        vetor[i] = atual;
        atual = atual->prox;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            float valor_j = vetor[j]->quantidade * vetor[j]->preco;
            float valor_j1 = vetor[j + 1]->quantidade * vetor[j + 1]->preco;
            if (valor_j < valor_j1)
            {
                Produto *temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("\nOrdenado por valor total:\n");
    for (int i = 0; i < n; i++)
    {
        float total = vetor[i]->quantidade * vetor[i]->preco;
        printf("%s - R$ %.2f\n", vetor[i]->nome, total);
    }
}