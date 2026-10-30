#include "TDA_Cola_Dinamica.h"
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

void crearCola(tCola *pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

int colaVacia(const tCola *pc)
{
    return pc->pri == NULL;
}

int colaLlena(const tCola *pc, size_t tamDato)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tamDato);

    free(aux);
    free(info);

    return !aux || !info;
}

int ponerEnCola(tCola *pc, const void *pd, size_t tamDato)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return SIN_MEMORIA;
    }

    nue->info = malloc(tamDato);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEMORIA;
    }

    nue->tamInfo = tamDato;
    memcpy(nue->info, pd, tamDato);
    nue->sig = NULL;

    if(pc->ult)
    {
        pc->ult->sig = nue;
    }
    else
    {
        pc->pri = nue;
    }

    pc->ult = nue;

    return TODO_OK;
}

int sacarDeCola(tCola *pc, void *pd, size_t tamDato)
{
    tNodo *elim = pc->pri;
    if(!elim)
    {
        return COLA_VACIA;
    }

    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    pc->pri = elim->sig;

    if(!pc->pri)
    {
        pc->ult = NULL;
    }

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verPrimero(const tCola *pc, void *pd, size_t tamDato)
{
    if(!pc->pri)
    {
        return COLA_VACIA;
    }

    memcpy(pd, pc->pri->info, MINIMO(pc->pri->tamInfo, tamDato));

    return TODO_OK;
}

void vaciarCola(tCola *pc)
{
    while(pc->pri)
    {
        tNodo *elim = pc->pri;
        pc->pri = elim->sig;

        free(elim->info);
        free(elim);
    }

    pc->ult = NULL;
}