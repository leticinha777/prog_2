#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include "pelucia.h"

int aleat(int max, int min)
{
    return (rand() % (max - min +1)+min);
}

struct maquina_pelucia *cria_maquina (unsigned int id, unsigned int probabilidade)
{
    struct maquina_pelucia *novo = malloc(sizeof (struct maquina_pelucia));
    if(!novo)
    {
        return NULL;
    }

    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->id = id;
    novo->probabilidade = probabilidade;

    return novo;
}

void retira_maquina (struct loja *loja, struct maquina_pelucia *maquina)
{
    if (!loja || !maquina || loja->numero_maquinas <=0)
        return;

    if(maquina->proximo == maquina)
    {
        loja->inicio = NULL;
    }
    else
    {
        maquina->anterior->proximo = maquina->proximo;
        maquina->proximo->anterior = maquina->anterior;

        if(maquina == loja->inicio)
            loja->inicio = maquina->proximo;
    }

    
    maquina->anterior = NULL;
    maquina->proximo = NULL;
    loja->numero_maquinas--;
    free(maquina);

    return ;
}

void insere_maquina (struct loja *loja, struct maquina_pelucia *nova)
{
    if(!loja || !nova)
        return;

    
    // lista vazia
    if(loja->numero_maquinas == 0)
    {
        loja->inicio = nova;
        loja->numero_maquinas++;
        nova->anterior = nova;
        nova->proximo = nova;
        return;
    }

    //quando a prioridade da nova é a maior
    if(nova->probabilidade > loja->inicio->probabilidade)
    {
        loja->inicio->anterior->proximo = nova;
        nova->anterior = loja->inicio->anterior;
        nova->proximo = loja->inicio;
        loja->inicio->anterior = nova;
        loja->inicio = nova;
        loja->numero_maquinas++;
        return;
    }

    //caso geral
    struct maquina_pelucia * aux = loja->inicio;

    while (aux->proximo != loja->inicio && nova->probabilidade < aux->probabilidade)
        aux = aux->proximo;

    if(aux->probabilidade > nova->probabilidade)
    {
        nova->anterior = aux;
        nova->proximo = aux->proximo;
        aux->proximo->anterior = nova;
        aux->proximo = nova;
        loja->numero_maquinas++;
        return;
    }
    else
    {
        nova->anterior = aux->anterior;
        nova->proximo = aux; 
        aux->anterior->proximo = nova;
        aux->anterior = nova;
        loja->numero_maquinas++;
        return;
    } 
}

struct loja* criar_loja (unsigned int numero_maquinas)
{
    struct loja *nova_loja = malloc (sizeof (struct loja));

    if(!nova_loja)
        return NULL;

    nova_loja->inicio = NULL;
    nova_loja->numero_maquinas = 0;

    int i = 0;
    for (i; i<numero_maquinas; i++)
    {
        struct maquina_pelucia * aux;
        aux = cria_maquina(i,aleat(100,0));
        if(!aux)
            return NULL;
        insere_maquina(nova_loja, aux);

    }

    return nova_loja;

}

int jogar(struct loja *loja)
{
    if(!loja || loja->numero_maquinas == 0)
        return -1;

    int a = aleat(loja->numero_maquinas, 0);
    int jogador = aleat(100,0);

    struct maquina_pelucia *aux = loja->inicio;

    while (aux->id != a && aux->proximo != loja->inicio)
        aux = aux->proximo;

    if(aux->proximo->id = a)
        aux = aux->proximo;

    if(aux->id != a)
        return -1;

    if(aux->probabilidade < jogador)
    {
        retira_maquina(loja, aux);
        return 0;
    }

    return -1;
}

void encerrar_dia (struct loja *loja)
{
    if(!loja)
    {
        printf("Erro na leitura do ponteiro\n");
        return;
    }

    if(loja->numero_maquinas == 0)
    {
        printf("Loja Vazia!\n");
        return;
    }

    struct maquina_pelucia * aux = loja->inicio;
    int i =0;

    printf("Máquina número %d\n", i);
    printf("ID da máquina: %d\n", aux->id);
    printf("Probabilidade da máquina: %d\n", aux->probabilidade);
    i++;

    aux = aux->proximo;

    while(aux != loja->inicio)
    {
        printf("Máquina número %d\n", i);
        printf("ID da máquina: %d\n", aux->id);
        printf("Probabilidade da máquina: %d\n", aux->probabilidade);
        aux = aux->proximo;
        i++;
    }
    return;
}

void destruir_loja (struct loja *loja)
{
    if(!loja)
        return;

    int i = 0;
    struct maquina_pelucia * aux = loja->inicio;
    struct maquina_pelucia * temp;


    while (i < loja->numero_maquinas)
    {
        temp = aux->proximo;
        aux->anterior = NULL;
        aux->proximo = NULL;
        free(aux);
        aux = temp;
        i++;
    }
  
    free(loja);
    return;

}