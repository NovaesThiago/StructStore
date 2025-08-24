#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H
#include "fila_pedidos.h"
#include "produtos.h"

typedef struct ItemEspera
{
    int codigoProduto;
    int quantidade;
    struct ItemEspera *prox;
} ItemEspera;

typedef struct PedidoEspera
{
    int codigoPedido;
    ItemEspera *itens;
    struct PedidoEspera *prox;
} PedidoEspera;

typedef struct FilaEspera
{
    PedidoEspera *inicio;
    PedidoEspera *fim;
} FilaEspera;

void inicializarFilaEspera(FilaEspera *fila);
void adicionarPedidoEspera(FilaEspera *fila, int codigoPedido, int codigoProduto, int quantidade);
void listarFilaEspera(FilaEspera *fila, ListaProdutos *estoque);
void verificarFilaEspera(FilaEspera *fila, ListaProdutos *estoque, FilaPedidos *filaPedidos);

#endif