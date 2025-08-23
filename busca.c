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

Produto* buscarProdutoNome(Produto* inicio, const char* nome) {
    Produto* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}