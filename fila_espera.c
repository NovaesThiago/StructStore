#include <stdio.h>
#include <stdlib.h>
#include "fila_espera.h"
#include "fila_pedidos.h"
#include "produtos.h"

void inicializarFilaEspera(FilaEspera *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

void adicionarPedidoEspera(FilaEspera *fila, int codigoPedido, int codigoProduto, int quantidade)
{
    PedidoEspera *novoPedido = (PedidoEspera *)malloc(sizeof(PedidoEspera));
    novoPedido->codigoPedido = codigoPedido;
    novoPedido->itens = NULL;
    novoPedido->prox = NULL;

    ItemEspera *novoItem = (ItemEspera *)malloc(sizeof(ItemEspera));
    novoItem->codigoProduto = codigoProduto;
    novoItem->quantidade = quantidade;
    novoItem->prox = NULL;

    novoPedido->itens = novoItem;

    if (fila->fim == NULL)
    {
        fila->inicio = novoPedido;
    }
    else
    {
        fila->fim->prox = novoPedido;
    }
    fila->fim = novoPedido;
}

void listarFilaEspera(FilaEspera *fila, ListaProdutos *estoque)
{
    PedidoEspera *atual = fila->inicio;
    if (atual == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }
    while (atual)
    {
        printf("Pedido %d em espera:\n", atual->codigoPedido);
        ItemEspera *item = atual->itens;
        while (item != NULL)
        {
            Produto *produto = buscarProduto(estoque, item->codigoProduto);
            if (produto != NULL)
            {
                printf("  Produto: %s | Quantidade: %d\n", produto->nome, item->quantidade);
            }
            else
            {
                printf("  Produto código %d não encontrado\n", item->codigoProduto);
            }
            item = item->prox;
        }
        atual = atual->prox;
    }
}

void verificarFilaEspera(FilaEspera *fila, ListaProdutos *estoque, FilaPedidos *filaPedidos)
{
    PedidoEspera *anterior = NULL;
    PedidoEspera *atual = fila->inicio;

    while (atual != NULL)
    {
        int podeAtender = 1;
        ItemEspera *item = atual->itens;

        while (item != NULL)
        {
            Produto *produto = buscarProduto(estoque, item->codigoProduto);
            if (produto == NULL || produto->quantidade < item->quantidade)
            {
                podeAtender = 0;
                break;
            }
            item = item->prox;
        }

        if (podeAtender)
        {
            item = atual->itens;
            while (item != NULL)
            {
                Produto *produto = buscarProduto(estoque, item->codigoProduto);
                if (produto != NULL)
                {
                    produto->quantidade -= item->quantidade;
                }
                item = item->prox;
            }

            enfileirarPedido(filaPedidos, estoque, atual->codigoPedido, fila);

            if (anterior == NULL)
            {
                fila->inicio = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            if (fila->fim == atual)
            {
                fila->fim = anterior;
            }

            PedidoEspera *remover = atual;
            atual = atual->prox;
            free(remover);
        }
        else
        {
            anterior = atual;
            atual = atual->prox;
        }
    }
}