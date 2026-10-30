#ifndef TDA_COLA_CIRCULAR_H_INCLUDED
#define TDA_COLA_CIRCULAR_H_INCLUDED

#include <stddef.h>

#define TODO_OK 0
#define SIN_MEMORIA 1
#define COLA_VACIA 2

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tCola;

void crearCola(tCola *pc);
int colaVacia(const tCola *pc);
int colaLlena(const tCola *pc, size_t tamDato);
int ponerEnCola(tCola *pc, const void *pd, size_t tamDato);
int sacarDeCola(tCola *pc, void *pd, size_t tamDato);
int verPrimero(const tCola *pc, void *pd, size_t tamDato);
void vaciarCola(tCola *pc);

#endif // TDA_COLA_CIRCULAR_H_INCLUDED
