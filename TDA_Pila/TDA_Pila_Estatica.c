#include "TDA_Pila_Estatica.h"
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

void crearPila(tPila *pp)
{
    pp->tope = TAM_PILA;
}

int pilaVacia(const tPila *pp)
{
    return pp->tope >= TAM_PILA;
}

int pilaLlena(const tPila *pp, size_t tamDato)
{
    return pp->tope < (tamDato + sizeof(size_t));
}

int ponerEnPila(tPila *pp, const void *pd, size_t tamDato)
{
    if(pp->tope < (tamDato + sizeof(size_t)))
    {
        return PILA_LLENA;
    }
    
    pp->tope -= tamDato;
    memcpy(pp->pila + pp->tope, pd, tamDato);
    pp->tope -= sizeof(size_t);
    memcpy(pp->pila + pp->tope, &tamDato, sizeof(size_t));
    
    return TODO_OK;
}

int sacarDePila(tPila *pp, void *pd, size_t tamDato)
{
    size_t tamDatoPila;
    
    if(pp->tope >= TAM_PILA)
    {
        return PILA_VACIA;
    }
    
    memcpy(&tamDatoPila, pp->pila + pp->tope, sizeof(size_t));
    pp->tope += sizeof(size_t);
    memcpy(pd, pp->pila + pp->tope, MINIMO(tamDatoPila, tamDato));
    pp->tope += tamDatoPila;
    
    return TODO_OK;
}

int verTopePila(const tPila *pp, void *pd, size_t tamDato)
{
    size_t tamDatoPila;
    
    if(pp->tope >= TAM_PILA)
    {
        return PILA_VACIA;
    }
    
    memcpy(&tamDatoPila, pp->pila + pp->tope, sizeof(size_t));
    memcpy(pd, pp->pila + pp->tope + sizeof(size_t), MINIMO(tamDatoPila, tamDato));
    
    return TODO_OK;
}

void vaciarPila(tPila *pp)
{
    pp->tope = TAM_PILA;
}