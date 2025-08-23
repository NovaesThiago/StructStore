#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "fila_pedidos.h"

int main()
{
    ListaProdutos estoque;
    PilhaMovimentacoes pilha;
    FilaPedidos fila;

    inicializarLista(&estoque);
    inicializarPilha(&pilha);
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
        printf("5 - Desfazer última movimentação\n");
        printf("6 - Adicionar pedido\n");
        printf("7 - Remover pedido\n");
        printf("8 - Listar pedidos\n");
        printf("9 - Buscar produto por nome\n");
        printf("10 - Ordenar por quantidade\n");
        printf("11 - Ordenar por valor total\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o código do produto: ");
            scanf("%d", &codigo);
            while (getchar() != '\n')
                ;

            printf("Digite o nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite a quantidade do produto: ");
            scanf("%d", &quantidade);

            printf("Digite o preço do produto: ");
            scanf("%f", &preco);

            inserirProdutoComHistorico(&estoque, &pilha, codigo, nome, quantidade, preco);
            break;

        case 2:
            listarProdutos(&estoque);
            break;

        case 3:
            printf("Digite o código do produto a ser atualizado: ");
            scanf("%d", &codigo);
            while (getchar() != '\n')
                ;

            printf("Digite o novo nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite a nova quantidade do produto: ");
            scanf("%d", &quantidade);

            printf("Digite o novo preço do produto: ");
            scanf("%f", &preco);

            atualizarProdutoComHistorico(&estoque, &pilha, codigo, nome, quantidade, preco);
            break;

        case 4:
            printf("Digite o código do produto a ser removido: ");
            scanf("%d", &codigo);

            removerProdutoComHistorico(&estoque, &pilha, codigo);
            break;

        case 5:
            desfazerMovimentacao(&pilha, &estoque);
            break;

        case 6:
            printf("Digite o código do pedido: ");
            scanf("%d", &codigo);
            enfileirarPedido(&fila, &estoque, codigo);
            break;

        case 7:
            desenfileirarPedido(&fila);
            break;

        case 8:
            listarPedidos(&fila, &estoque);
            break;

        case 9:
            while (getchar() != '\n');
            printf("Digite o nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            Produto *encontrado = buscarProdutoNome(&estoque, nome);
            if (encontrado)
                printf("Produto encontrado: %s | Código: %d | Quantidade: %d | Preço unitário: R$ %.2f\n",
                       encontrado->nome, encontrado->codigo, encontrado->quantidade, encontrado->preco);
            else
                printf("Produto não encontrado.\n");
            break;

        case 10:
            ordenarQuantidade(&estoque);
            break;

        case 11:
            ordenarValorTotal(&estoque);
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