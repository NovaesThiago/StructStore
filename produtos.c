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

void inserirProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo, char nome[], int quantidade, float preco)
{
    if (buscarProduto(lista, codigo) != NULL)
    {
        printf("Erro: Já existe um produto com o código %d.\n", codigo);
        return;
    }

    Produto depois;
    depois.codigo = codigo;
    strcpy(depois.nome, nome);
    depois.quantidade = quantidade;
    depois.preco = preco;
    depois.prox = NULL;

    inserirProduto(lista, codigo, nome, quantidade, preco);

    Produto vazio = {0}; // Produto "antes" não existe
    pushMovimentacao(pilha, INSERIR, vazio, depois);
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

void atualizarProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo, char novoNome[], int novaQtd, float novoPreco)
{
    Produto *p = buscarProduto(lista, codigo);
    if (p == NULL)
    {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto antes = *p; // Guarda estado antigo

    if (atualizarProduto(lista, codigo, novoNome, novaQtd, novoPreco)) 
    {
        printf("Produto atualizado com sucesso!\n");
    }
    else
    {
        printf("Erro ao atualizar produto.\n");
    }

    Produto depois;
    depois.codigo = codigo;
    strcpy(depois.nome, novoNome);
    depois.quantidade = novaQtd;
    depois.preco = novoPreco;

    pushMovimentacao(pilha, ATUALIZAR, antes, depois);
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

void removerProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo)
{
    Produto *p = buscarProduto(lista, codigo);
    if (p == NULL)
    {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto antes = *p; // Guarda estado antes da remoção

    if (removerProduto(lista, codigo)) 
    {
        printf("Produto removido com sucesso!\n");
    }
    else
    {
        printf("Erro ao remover produto.\n");
    }

    Produto vazio = {0}; // Produto "depois" não existe
    pushMovimentacao(pilha, REMOVER, antes, vazio);
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

void inicializarPilha(PilhaMovimentacoes *pilha)
{
    pilha->topo = NULL;
}

int pilhaVazia(PilhaMovimentacoes *pilha)
{
    return pilha->topo == NULL;
}

void pushMovimentacao(PilhaMovimentacoes *pilha, TipoOperacao op, Produto antes, Produto depois)
{
    Movimentacao *nova = (Movimentacao *)malloc(sizeof(Movimentacao));
    nova->operacao = op;
    nova->produtoAntes = antes;
    nova->produtoDepois = depois;
    nova->prox = pilha->topo;
    pilha->topo = nova;
}

Movimentacao *popMovimentacao(PilhaMovimentacoes *pilha)
{
    if (pilhaVazia(pilha))
        return NULL;
    Movimentacao *removida = pilha->topo;
    pilha->topo = removida->prox;
    return removida;
}

void desfazerMovimentacao(PilhaMovimentacoes *pilha, ListaProdutos *estoque)
{
    Movimentacao *mov = popMovimentacao(pilha);
    if (mov == NULL)
    {
        printf("Nenhuma movimentação para desfazer.\n");
        return;
    }

    switch (mov->operacao)
    {
    case INSERIR:
        removerProduto(estoque, mov->produtoDepois.codigo);
        printf("Desfeita inserção do produto %d.\n", mov->produtoDepois.codigo);
        break;
    case REMOVER:
        inserirProduto(estoque, mov->produtoAntes.codigo, mov->produtoAntes.nome, mov->produtoAntes.quantidade,mov->produtoAntes.preco);
        printf("Desfeita remoção do produto %d.\n", mov->produtoAntes.codigo);
        break;
    case ATUALIZAR:
        atualizarProduto(estoque, mov->produtoAntes.codigo, mov->produtoAntes.nome, mov->produtoAntes.quantidade,mov->produtoAntes.preco);
        printf("Desfeita atualização do produto %d.\n", mov->produtoAntes.codigo);
        break;
    }
    free(mov);
}