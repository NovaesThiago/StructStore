#include <stdio.h>
#include <stdlib.h>
#include "fila_pedidos.h"
#include "produtos.h"
#include "fila_espera.h"

void inicializarFila(FilaPedidos *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

void adicionarItemPedido(Pedido *pedido, int codigoProduto, int quantidade)
{
    Item *novo = (Item *)malloc(sizeof(Item));
    novo->codigoProduto = codigoProduto;
    novo->quantidade = quantidade;
    novo->prox = pedido->itens;
    pedido->itens = novo;
}

Pedido *buscarPedido(FilaPedidos *fila, int codigo)
{
    Pedido *atual = fila->inicio;
    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int enfileirarPedido(FilaPedidos *fila, ListaProdutos *estoque, int codigo, FilaEspera *filaEspera)
{
    int opcao;
    if (buscarPedido(fila, codigo) != NULL)
    {
        printf("Pedido com o código %d já existe.\n", codigo);
        return 0;
    }

    Pedido *novo = (Pedido *)malloc(sizeof(Pedido));

    novo->codigo = codigo;
    novo->itens = NULL;
    novo->prox = NULL;

    int qtdItens;
    printf("Quantos itens neste pedido? ");
    scanf("%d", &qtdItens);

    for (int i = 0; i < qtdItens; i++)
    {
        int codProd, qtd;
        printf("Item %d - Codigo do produto: ", i + 1);
        scanf("%d", &codProd);
        Produto *p = buscarProduto(estoque, codProd);
        if (p == NULL)
        {
            printf("Produto não encontrado, item ignorado.\n");
            continue;
        }
        printf("Quantidade: ");
        scanf("%d", &qtd);
        if (qtd > p->quantidade)
        {
            printf("Quantidade insuficiente no estoque! Disponível: %d\n", p->quantidade);
            // alteração para fila de espera
            printf("Deseja adicionar o item à fila de espera? (1 - Sim, 0 - Não): ");
            scanf("%d", &opcao);
            if (opcao == 1)
            {
                adicionarPedidoEspera(filaEspera, codigo, codProd, qtd);
                printf("Item adicionado à fila de espera.\n");
            }
            continue;
        }
        adicionarItemPedido(novo, codProd, qtd);
        p->quantidade -= qtd;
    }
    if (opcao != 1)
    {
        if (novo->itens == NULL)
        {
            printf("Nenhum item válido foi adicionado. Pedido cancelado.\n");
            free(novo);
            return 0;
        }

        if (fila->fim == NULL)
        {
            fila->inicio = novo;
            fila->fim = novo;
        }
        else
        {
            fila->fim->prox = novo;
            fila->fim = novo;
        }
        printf("Pedido %d adicionado à fila.\n", codigo);
        return 1;
    }
}

int desenfileirarPedido(FilaPedidos *fila)
{
    if (fila->inicio == NULL)
    {
        printf("Fila de pedidos vazia.\n");
        return 0;
    }

    Pedido *removido = fila->inicio;
    fila->inicio = removido->prox;
    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    printf("Pedido %d removido da fila.\n", removido->codigo);

    Item *itemAtual = removido->itens;
    while (itemAtual)
    {
        Item *temp = itemAtual;
        itemAtual = itemAtual->prox;
        free(temp);
    }
    free(removido);
    return 1;
}

void listarPedidos(FilaPedidos *fila, ListaProdutos *estoque)
{
    Pedido *atual = fila->inicio;
    if (atual == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }

    while (atual)
    {
        printf("Pedido %d:\n", atual->codigo);
        Item *itemAtual = atual->itens;

        while (itemAtual)
        {
            Produto *p = buscarProduto(estoque, itemAtual->codigoProduto);
            if (p)
            {
                printf("  Produto: %s | Quantidade: %d | Preço unitário: R$ %.2f\n", p->nome, itemAtual->quantidade, p->preco);
            }
            else
            {
                printf("  Produto com código %d não encontrado no estoque.\n", itemAtual->codigoProduto);
            }
            itemAtual = itemAtual->prox;
        }
        atual = atual->prox;
    }
}

void liberarFila(FilaPedidos *fila)
{
    while (fila->inicio)
    {
        desenfileirarPedido(fila);
    }
}