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

typedef enum
{
    INSERIR,
    ATUALIZAR,
    REMOVER
} TipoOperacao;

typedef struct Movimentacao
{
    TipoOperacao operacao;
    Produto produtoAntes;
    Produto produtoDepois;
    struct Movimentacao *prox;
} Movimentacao;

typedef struct
{
    Movimentacao *topo;
} PilhaMovimentacoes;

void inicializarLista(ListaProdutos *lista);
void inserirProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco);
void inserirProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo, char nome[], int quantidade, float preco);
void listarProdutos(ListaProdutos *lista);
Produto *buscarProduto(ListaProdutos *lista, int codigo);
int atualizarProduto(ListaProdutos *lista, int codigo, char nome[], int quantidade, float preco);
void atualizarProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo, char novoNome[], int novaQtd, float novoPreco);
int removerProduto(ListaProdutos *lista, int codigo);
void removerProdutoComHistorico(ListaProdutos *lista, PilhaMovimentacoes *pilha, int codigo);
void liberarLista(ListaProdutos *lista);

void inicializarPilha(PilhaMovimentacoes *pilha);
int pilhaVazia(PilhaMovimentacoes *pilha);
void pushMovimentacao(PilhaMovimentacoes *pilha, TipoOperacao op, Produto antes, Produto depois);
Movimentacao *popMovimentacao(PilhaMovimentacoes *pilha);
void desfazerMovimentacao(PilhaMovimentacoes *pilha, ListaProdutos *estoque);

#endif