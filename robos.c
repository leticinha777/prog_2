#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "robos.h"

struct lista *cria_lista()
{
    struct lista *l = malloc(sizeof(struct lista));
    if(!l)
        return NULL;

    l->contagem = 0;
    l->inicio = NULL;

    return l;

}

struct robo *cria_robo (int id, int ciclo)
{
    struct robo *novo = malloc(sizeof(struct robo));
    if(!novo)
        return NULL;
    novo->prox = NULL;
    novo->ciclo = ciclo;
    novo->id = id;

    return novo;
}

void inserir_lista(struct robo *elemento, struct lista *l)
{
    if(!l || !elemento)
        return;

    //quando a fila está vazia
    if(l->contagem == 0)
    {
        l->contagem++;
        l->inicio = elemento;
        elemento->prox = elemento;
        printf("Inseriu robô na lista vazia, id %d, ciclos %d\n", elemento->id, elemento->ciclo);
        return;
    }

    struct robo * aux = l->inicio;
    while(aux->prox != l->inicio)
        aux = aux->prox;

    aux->prox = elemento;
    elemento->prox = l->inicio;
    l->contagem++;

    printf("Inseriu robô na lista, id %d, ciclos %d\n", elemento->id, elemento->ciclo);
    return;  
}

struct robo *retirar_lista (struct lista *l)
{
    if(!l || l->contagem == 0)
        return NULL;

    struct robo * aux = l->inicio; 

    if(l->contagem == 1)
    {
        l->inicio = NULL;
        l->contagem--;
        return aux;
    }

    while (aux->prox != l->inicio)
        aux = aux->prox;

    struct robo * temp = l->inicio;
    aux->prox = l->inicio->prox;
    l->inicio = l->inicio->prox;
    l->contagem--;
    return temp;
}

void destroi_robo(struct robo *elemento)
{
    if(!elemento)
        return;

    elemento->prox = NULL;
    free(elemento);
}

void destroi_lista(struct lista *l)
{
    if(!l)
        return;

    if(l->contagem == 0)
    {
        l->inicio = NULL;
        free(l);
        return;
    }

    struct robo * aux = l->inicio;
    struct robo *temp;
    while(l->contagem >0 && aux !=NULL)
    {
        temp = aux->prox;
        aux->prox = NULL;
        free(aux);
        aux = temp;
        l->contagem--;
    }

    l->inicio = NULL;
    free(l);
    return;
}

void ciclo (struct lista *l)
{
    if(!l || l->contagem == 0)
    {
        printf("Não há robôs a serem carregados");
        return;
    }
        

    struct robo * aux;
    //só é feito um ciclo de carga
    if(l->contagem == 1)
    {
        l->inicio->ciclo--;
        printf("Ciclo de carga, robô %d\n", l->inicio->id);
        if(l->inicio->ciclo == 0)
        {
            aux = retirar_lista(l);
            printf("Robô retirado, id: %d",aux->id);
            destroi_robo(aux);  
        }
        return;            
    }


    int i = 2;
    while(i>0)
    {
        l->inicio->ciclo--;
        printf("Ciclo de carga, robô %d\n", l->inicio->id);

        if(l->inicio->ciclo == 0)
        {
            aux = retirar_lista(l);
            destroi_robo(aux);
        }
        else
        {
            l->inicio = l->inicio->prox;
        }
        i--;
    }
    return;
}