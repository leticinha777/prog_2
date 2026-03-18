#ifndef __ROBOS__
#define __ROBOS__

struct robo
{
    int id;
    int ciclo;
    struct robo *prox;
};

struct lista
{
    struct robo *inicio;
    int contagem;
};

struct lista *cria_lista();
struct robo *cria_robo (int id, int ciclo);
void inserir_lista(struct robo *elemento, struct lista *l);
struct robo *retirar_lista (struct lista *l);
void destroi_robo(struct robo *elemento);
void destroi_lista(struct lista *l);
void ciclo (struct lista *l);




#endif 