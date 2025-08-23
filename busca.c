#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "fila_pedidos.h"

Produto* buscarProduto(Produto* inicio, int codigo){
    while (inicio != NULL){
        if (inicio->codigo == codigo){
            return inicio;
        }
    }
    return NULL;
}

void buscarProdutoNome(Produto* inicio, const char* nome) {
    while (inicio != NULL) {
        if (strstr(inicio->nome, nome) != NULL)
            printf("Encontrado: %s (Código %d)\n", inicio->nome, inicio->codigo);
        inicio = inicio->prox;
    }
}
