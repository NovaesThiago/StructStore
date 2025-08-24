#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H
#include "produtos.h"

typedef struct Item
{
    int codigoProduto;
    int quantidade;
    struct Item *prox;
} Item;

typedef struct Pedido
{
    int codigo;
    Item *itens;
    struct Pedido *prox;
} Pedido;

typedef struct
{
    Pedido *inicio;
    Pedido *fim;
} FilaPedidos;
struct FilaEspera;
typedef struct FilaEspera FilaEspera;

void inicializarFila(FilaPedidos *fila);
void adicionarItemPedido(Pedido *pedido, int codigoProduto, int quantidade);
int enfileirarPedido(FilaPedidos *fila, ListaProdutos *estoque, int codigo, FilaEspera *filaEspera);
int desenfileirarPedido(FilaPedidos *fila);
void listarPedidos(FilaPedidos *fila, ListaProdutos *estoque);
void liberarFila(FilaPedidos *fila);

#endif