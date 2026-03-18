#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "jukefila.h"

jukefila* criar_jukefila()
{
    struct jukefila *fila = malloc(sizeof(struct jukefila));
    if(!fila)
        return NULL;
    
    fila->inicio = NULL;
    fila->final = NULL;

    return fila;
}

void inserir_jukefila(pedido* elemento, jukefila* fila)
{
    if(!fila || !elemento)
        return;

    struct pedido * aux = fila->inicio;

    //caso em que a fila não tem elementos
    if(aux == NULL)
    {
        fila->inicio = elemento;
        fila->final = elemento;
        return;
    }

    //se o elemento for inserido no inicio da fila (mais caro)
    if(elemento->valor > aux->valor)
    {
        aux->anterior = elemento;
        elemento->proximo = aux;
        fila->inicio = elemento;
        return;
    }

    while (aux->proximo != NULL && aux->valor > elemento->valor)
        aux = aux->proximo;

    if(elemento->valor < aux->valor)
    //inserção no fim da fila
    {
        aux->proximo = elemento;
        elemento->anterior = aux;
        fila->final = elemento;
        return;
    }
    else
    {
        aux->anterior->proximo = elemento;
        elemento->anterior = aux->anterior;
        elemento->proximo = aux;
        aux->anterior = elemento;
        return;
    }

}

pedido* consumir_jukefila(jukefila* fila)
{
    if(!fila || !fila->inicio)
        return NULL;

    struct pedido * aux = fila->inicio;

    if(fila->final == fila->inicio)
    {
        fila->final = NULL;
        fila->inicio = NULL;
        return aux;
    }

    fila->inicio = fila->inicio->proximo;
    if(fila->inicio->proximo == NULL)
    {
        fila->final = fila->inicio;
        return aux;
    }

    fila->inicio->anterior = NULL;

    return aux;
}

unsigned int contar_jukefila(jukefila* fila)
{
    if(!fila || !fila->inicio)
        return 0;
    
    struct pedido * aux = fila->inicio;
    int i = 0; 

    while (aux != NULL)
    {
        i++;
        aux = aux->proximo;
    }

    return i;
}

void destruir_jukefila(jukefila *fila)
{
    if(!fila)
        return;

    struct pedido *aux = fila->inicio;
    struct pedido *temp;

    while(aux != NULL)
    {
        temp = aux->proximo;
        aux->anterior = NULL;
        aux->proximo = NULL;
        free(aux);
        aux = temp;
    }

    free(fila);
}