#include "TDA_Pila_Dinamica.h"
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

void crearPila(tPila *pp)
{
    *pp = NULL;
}

int pilaVacia(const tPila *pp)
{
    return *pp == NULL;
}

int pilaLlena(const tPila *pp, size_t tamDato)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tamDato);

    free(aux);
    free(info);

    return !aux || !info;
}

int ponerEnPila(tPila *pp, const void *pd, size_t tamDato)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return PILA_LLENA;
    }

    nue->info = malloc(tamDato);
    if(!nue->info)
    {
        free(nue);
        return PILA_LLENA;
    }

    nue->tamInfo = tamDato;
    memcpy(nue->info, pd, tamDato);

    nue->sig = *pp;

    *pp = nue;

    return TODO_OK;
}

int sacarDePila(tPila *pp, void *pd, size_t tamDato)
{
    tNodo *elim = *pp;
    if(!*pp)
    {
        return PILA_VACIA;
    }

    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    *pp = elim->sig;

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verTopePila(const tPila *pp, void *pd, size_t tamDato)
{
    if(!*pp)
    {
        return PILA_VACIA;
    }
    
    memcpy(pd, (*pp)->info, MINIMO((*pp)->tamInfo, tamDato));

    return TODO_OK;
}

void vaciarPila(tPila *pp)
{
    while(*pp)
    {
        tNodo *elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}