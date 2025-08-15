#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "fila_pedidos.h"

int main()
{
    ListaProdutos estoque;
    FilaPedidos fila;

    inicializarLista(&estoque);
    inicializarFila(&fila);

    int opcao, codigo, quantidade;
    char nome[50];
    float preco;

    do
    {
        printf("\n=== Sistema Estoque & Pedidos ===\n");
        printf("1 - Inserir produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Atualizar produto\n");
        printf("4 - Remover produto\n");
        printf("5 - Adicionar pedido\n");
        printf("6 - Remover pedido\n");
        printf("7 - Listar pedidos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o código do produto: ");
            scanf("%d", &codigo);
            while (getchar() != '\n');

            printf("Digite o nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite a quantidade do produto: ");
            scanf("%d", &quantidade);

            printf("Digite o preço do produto: ");
            scanf("%f", &preco);

            inserirProduto(&estoque, codigo, nome, quantidade, preco);
            break;

        case 2:
            listarProdutos(&estoque);
            break;

        case 3:
            printf("Digite o código do produto a ser atualizado: ");
            scanf("%d", &codigo);
            while (getchar() != '\n');

            printf("Digite o novo nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite a nova quantidade do produto: ");
            scanf("%d", &quantidade);

            printf("Digite o novo preço do produto: ");
            scanf("%f", &preco);

            if (atualizarProduto(&estoque, codigo, nome, quantidade, preco))
                printf("Produto atualizado.\n");
            else
                printf("Produto não encontrado.\n");
            break;

        case 4:
            printf("Digite o código do produto a ser removido: ");
            scanf("%d", &codigo);

            if (removerProduto(&estoque, codigo))
                printf("Produto removido.\n");
            else
                printf("Produto não encontrado.\n");
            break;

        case 5:
            printf("Digite o código do pedido: ");
            scanf("%d", &codigo);
            enfileirarPedido(&fila, &estoque, codigo);
            break;
        
        case 6:
            desenfileirarPedido(&fila);
            break;
        
        case 7:
            listarPedidos(&fila, &estoque);
            break;

        case 0:
            liberarLista(&estoque);
            liberarFila(&fila);
            printf("Programa finalizado.\n");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}