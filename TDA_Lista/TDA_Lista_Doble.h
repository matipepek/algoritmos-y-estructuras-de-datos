#ifndef TDA_LISTA_DOBLE_H_INCLUDED
#define TDA_LISTA_DOBLE_H_INCLUDED

#include <stddef.h>

#define TODO_OK 0
#define SIN_MEMORIA 1
#define LISTA_VACIA 2
#define POS_INVALIDA 3
#define NO_ENTRA 4
#define NO_ENCONTRADO 5
#define DUPLICADO 6

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig,
                 *ant;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *pl);
int listaVacia(const tLista *pl);
int listaLlena(const tLista *pl, size_t tamDato);
int insertarAlComienzo(tLista *pl, const void *pd, size_t tamDato);
int eliminarPrimero(tLista *pl, void *pd, size_t tamDato);
int verPrimero(const tLista *pl, void *pd, size_t tamDato);
int insertarAlFinal(tLista *pl, const void *pd, size_t tamDato);
int eliminarUltimo(tLista *pl, void *pd, size_t tamDato);
int verUltimo(const tLista *pl, void *pd, size_t tamDato);
int insertarEnPosicion(tLista *pl, const void *pd, size_t tamDato, size_t pos);
int eliminarPosicion(tLista *pl, void *pd, size_t tamDato, size_t pos);
int verPosicion(const tLista *pl, void *pd, size_t tamDato, size_t pos);
int insertarOrdenado(tLista *pl, const void *pd, size_t tamDato,
                     int (*cmp)(const void *, const void *),
                     int (*acumular)(void **, size_t *, const void *, size_t));
int insertarOrdenadoConRepetidos(tLista *pl, const void *pd, size_t tamDato, int (*cmp)(const void *, const void *));
int ordenarLista(tLista *pl, int (*cmp)(const void *, const void *));
void mapLista(tLista *pl, void (*accion)(void *, void *), void *param);
void mapInversoLista(tLista *pl, void (*accion)(void *, void *), void *param);
void filterLista(tLista *pl, int (*filtro)(void *, void *), void *param);
void reduceLista(tLista *pl, void *acum, void (*accion)(void *, void *, void*), void *param);
int insertarOrdenadoTopN(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *));
int insertarEnPodio(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *));
void mapTopN(tLista *pl, size_t n, void (*accion)(void *, void *), void *param);
int eliminarPorClave(tLista *pl, void *pd, size_t tamDato, int (*cmp)(const void *, const void *));
int eliminarUltimosN(tLista *pl, size_t n);
int eliminarDuplicados(tLista *pl, int (*cmp)(const void *, const void *));
int eliminarApariciones(tLista *pl, const void *pd, int (*cmp)(const void *, const void *));
void invertirLista(tLista *pl);
void vaciarLista(tLista *pl);

#endif // TDA_LISTA_DOBLE_H_INCLUDED
