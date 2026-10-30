#ifndef TDA_PILA_CIRCULAR_H_INCLUDED
#define TDA_PILA_CIRCULAR_H_INCLUDED

#include <stddef.h>

#define TODO_OK 0
#define PILA_VACIA 1
#define PILA_LLENA 2

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tPila;

void crearPila(tPila *pp);
int pilaVacia(const tPila *pp);
int pilaLlena(const tPila *pp, size_t tamDato);
int ponerEnPila(tPila *pp, const void *pd, size_t tamDato);
int sacarDePila(tPila *pp, void *pd, size_t tamDato);
int verTopePila(const tPila *pp, void *pd, size_t tamDato);
void vaciarPila(tPila *pp);

#endif // TDA_PILA_CIRCULAR_H_INCLUDED
