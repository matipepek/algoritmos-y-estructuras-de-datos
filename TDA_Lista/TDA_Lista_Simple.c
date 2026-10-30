#include "TDA_Lista_Simple.h"
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

tLista *buscarMenorLista(tLista *pl, int (*cmp)(const void *, const void *));
void reinsertarNodoMenor(tLista *pl, tLista *men);

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista *pl, size_t tamDato)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tamDato);

    free(aux);
    free(info);

    return !aux || !info;
}

int insertarAlComienzo(tLista *pl, const void *pd, size_t tamDato)
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

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}

int eliminarPrimero(tLista *pl, void *pd, size_t tamDato)
{
    tNodo *elim = *pl;

    if(!*pl)
    {
        return LISTA_VACIA;
    }

    *pl = elim->sig;
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verPrimero(const tLista *pl, void *pd, size_t tamDato)
{
    if(!*pl)
    {
        return LISTA_VACIA;
    }

    memcpy(pd, (*pl)->info, MINIMO((*pl)->tamInfo, tamDato));

    return TODO_OK;
}

int insertarAlFinal(tLista *pl, const void *pd, size_t tamDato)
{
    tNodo *nue;

    while(*pl)
    {
        pl = &(*pl)->sig;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    *pl = nue;

    return TODO_OK;
}

int eliminarUltimo(tLista *pl, void *pd, size_t tamDato)
{
    tNodo *elim;

    if(!*pl)
    {
        return LISTA_VACIA;
    }

    while((*pl)->sig)
    {
        pl = &(*pl)->sig;
    }

    elim = *pl;
    *pl = NULL;

    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    
    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verUltimo(const tLista *pl, void *pd, size_t tamDato)
{
    if(!*pl)
    {
        return LISTA_VACIA;
    }

    while((*pl)->sig)
    {
        pl = &(*pl)->sig;
    }

    memcpy(pd, (*pl)->info, MINIMO((*pl)->tamInfo, tamDato));

    return TODO_OK;
}

int insertarEnPosicion(tLista *pl, const void *pd, size_t tamDato, size_t pos)
{
    tNodo *nue;
    
    while(*pl && pos > 0)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    if(pos > 0)
    {
        return POS_INVALIDA;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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
    
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;
    
    return TODO_OK;
}

int eliminarPosicion(tLista *pl, void *pd, size_t tamDato, size_t pos)
{
    tNodo *elim;
    
    if(!*pl)
    {
        return LISTA_VACIA;
    }
    
    while(*pl && pos > 0)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    if(!*pl || pos)
    {
        return POS_INVALIDA;
    }
    
    elim = *pl;
    *pl = elim->sig;
    
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    
    free(elim->info);
    free(elim);
    
    return TODO_OK;
}

int verPosicion(const tLista *pl, void *pd, size_t tamDato, size_t pos)
{
    if(!*pl)
    {
        return LISTA_VACIA;
    }
    
    while(*pl && pos > 0)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    if(!*pl || pos)
    {
        return POS_INVALIDA;
    }
    
    memcpy(pd, (*pl)->info, MINIMO((*pl)->tamInfo, tamDato));
    
    return TODO_OK;
}

int insertarOrdenado(tLista *pl, const void *pd, size_t tamDato, int (*cmp)(const void *, const void *))
{
    tNodo *nue;

    while(*pl && cmp((*pl)->info, pd) < 0)
    {
        pl = &(*pl)->sig;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}

int insertarOrdenadoAcum(tLista *pl, const void *pd, size_t tamDato,
                         int (*cmp)(const void *, const void *),
                         int (*acumular)(void **, size_t *, const void *, size_t))
{
    tNodo *nue;
    int aux = 1;
 
    while(*pl && (aux = cmp((*pl)->info, pd)) < 0)
    {
        pl = &(*pl)->sig;
    }
 
    if(*pl && aux == 0)
    {
        if(!acumular)
        {
            return DUPLICADO;
        }
 
        if(acumular(&(*pl)->info, &(*pl)->tamInfo, pd, tamDato) == 0)
        {
            return SIN_MEMORIA;
        }
 
        return TODO_OK;
    }
 
    nue = (tNodo*)malloc(sizeof(tNodo));
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
 
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;
 
    return TODO_OK;
}

int ordenarSeleccionLista(tLista *pl, int (*cmp)(const void *, const void *))
{   
    if(!*pl)
    {
        return LISTA_VACIA;
    }

    while(*pl)
    {
        tNodo **menor = buscarMenorLista(pl, cmp);

        if(menor != pl)
        {
            reinsertarNodoMenor(pl, menor);
        }

        pl = &(*pl)->sig;
    }

    return TODO_OK;
}

tLista *buscarMenorLista(tLista *pl, int (*cmp)(const void *, const void *))
{
    tLista *menor = pl;
    if(!*pl)
    {
        return NULL;
    }

    pl = &(*pl)->sig;

    while(*pl)
    {
        if(cmp((*pl)->info, (*menor)->info) < 0)
        {
            menor = pl;
        }

        pl = &(*pl)->sig;
    }

    return menor;
}

void reinsertarNodoMenor(tLista *pl, tLista *men)
{
    tNodo *aux = *men;
    *men = aux->sig;

    aux->sig = *pl;
    *pl = aux;
}

void mapLista(tLista *pl, void (*accion)(void *, void *), void *param)
{
    while(*pl)
    {
        accion((*pl)->info, param);
        pl = &(*pl)->sig;
    }
}

void mapInversoLista(tLista *pl, void (*accion)(void *, void *), void *param)
{
    if(*pl)
    {
        mapInversoLista(&(*pl)->sig, accion, param);
        accion((*pl)->info, param);
    }
}

void filterLista(tLista *pl, int (*filtro)(void *, void *), void *param)
{
    while(*pl)
    {
        if(filtro((*pl)->info, param))
        {
            pl = &(*pl)->sig;
        }
        else
        {
            tNodo *elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
    }
}

void reduceLista(tLista *pl, void *acum, void (*accion)(void *, void *, void*), void *param)
{
    while(*pl)
    {
        accion((*pl)->info, acum, param);
        pl = &(*pl)->sig;
    }
}

int insertarOrdenadoTopN(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *))
{
    tNodo *nue;
    size_t ce = 0;

    while(*pl && ce < n && cmp((*pl)->info, pd) <= 0)
    {
        pl = &(*pl)->sig;
        ce++;
    }

    if(ce >= n)
    {
        return NO_ENTRA;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;
    ce++;

    pl = &nue->sig;

    while(*pl && ce < n)
    {
        pl = &(*pl)->sig;
        ce++;
    }

    while(*pl)
    {
        tNodo *elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    return TODO_OK;
}

int insertarEnPodio(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *))
{
    tNodo *nue;
    tNodo *ult = NULL;
    size_t ce = 0;

    while(*pl && ce < n && cmp((*pl)->info, pd) < 0)
    {
        pl = &(*pl)->sig;
        ce++;
    }

    if(ce >= n)
    {
        return NO_ENTRA;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
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

    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *pl;
    *pl = nue;

    while(*pl && ce < n)
    {
        ult = *pl;
        pl = &(*pl)->sig;
        ce++;
    }

    while(*pl && cmp((*pl)->info, ult->info) == 0)
    {
        pl = &(*pl)->sig;
    }

    while(*pl)
    {
        tNodo *elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    return TODO_OK;
}

void mapTopN(tLista *pl, size_t n, void (*accion)(void *, void *), void *param)
{
    while(*pl && n > 0)
    {
        accion((*pl)->info, param);
        pl = &(*pl)->sig;
        n--;
    }
}

int eliminarPorClave(tLista *pl, void *pd, size_t tamDato, int (*cmp)(const void *, const void *))
{
    tNodo *elim;
    int aux = 1;
 
    if(!*pl)
    {
        return LISTA_VACIA;
    }
 
    while(*pl && (aux = cmp((*pl)->info, pd)) < 0)
    {
        pl = &(*pl)->sig;
    }
 
    if(!*pl || aux != 0)
    {
        return NO_ENCONTRADO;
    }
 
    elim = *pl;
    *pl = elim->sig;
 
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    free(elim->info);
    free(elim);
 
    return TODO_OK;
}

int eliminarUltimosN(tLista *pl, size_t n)
{
    tNodo *adelante = *pl;
    size_t ce = 0;

    if(!*pl)
    {
        return LISTA_VACIA;
    }

    while(adelante && ce < n)
    {
        adelante = adelante->sig;
        ce++;
    }

    if(ce < n)
    {
        return POS_INVALIDA;
    }

    while(adelante)
    {
        adelante = adelante->sig;
        pl = &(*pl)->sig;
    }

    while(*pl)
    {
        tNodo *elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    return TODO_OK;
}

int eliminarDuplicados(tLista *pl, int (*cmp)(const void *, const void *))
{
    tNodo *actual;
    tNodo *elim;
    tLista *plAux;

    if(!*pl)
    {
        return LISTA_VACIA;
    }

    actual = *pl;

    while(actual)
    {
        plAux = &actual->sig;

        while(*plAux)
        {
            if(cmp(actual->info, (*plAux)->info) == 0)
            {
                elim = *plAux;
                *plAux = elim->sig;

                free(elim->info);
                free(elim);
            }
            else
            {
                plAux = &(*plAux)->sig;
            }
        }

        actual = actual->sig;
    }

    return TODO_OK;
}

int eliminarApariciones(tLista *pl, const void *pd, int (*cmp)(const void *, const void *))
{
    if(!*pl)
    {
        return LISTA_VACIA;
    }

    while(*pl)
    {
        if(cmp((*pl)->info, pd) == 0)
        {
            tNodo *elim = *pl;
            *pl = elim->sig;

            free(elim->info);
            free(elim);
        }
        else
        {
            pl = &(*pl)->sig;
        }
    }

    return TODO_OK;
}

void invertirLista(tLista *pl)
{
    tNodo *ant = NULL;
    tNodo *act = *pl;
    tNodo *sig;

    while(act)
    {
        sig = act->sig;
        act->sig = ant;
        ant = act;
        act = sig;
    }

    *pl = ant;
}

void vaciarLista(tLista *pl)
{
    while(*pl)
    {
        tNodo *elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }
}