#include "TDA_Cola_Circular.h"
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

void crearCola(tCola *pc)
{
    *pc = NULL;
}

int colaVacia(const tCola *pc)
{
    return *pc == NULL;
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

    if(*pc)
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    else
    {
        nue->sig = nue;
    }

    *pc = nue;

    return TODO_OK;
}

int sacarDeCola(tCola *pc, void *pd, size_t tamDato)
{
    tNodo *elim;
    if(!*pc)
    {
        return COLA_VACIA;
    }

    elim = (*pc)->sig;
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));

    if(*pc == elim)
    {
        *pc = NULL;
    }
    else
    {
        (*pc)->sig = elim->sig;
    }

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verPrimero(const tCola *pc, void *pd, size_t tamDato)
{
    if(!*pc)
    {
        return COLA_VACIA;
    }

    memcpy(pd, (*pc)->sig->info, MINIMO((*pc)->sig->tamInfo, tamDato));

    return TODO_OK;
}

void vaciarCola(tCola *pc)
{
    while(*pc)
    {
        tNodo *elim = (*pc)->sig;

        if(*pc == elim)
        {
            *pc = NULL;
        }
        else
        {
            (*pc)->sig = elim->sig;
        }

        free(elim->info);
        free(elim);
    }
}