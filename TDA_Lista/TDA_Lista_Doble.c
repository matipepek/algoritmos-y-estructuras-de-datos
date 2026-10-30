#include "TDA_Lista_Doble.h"
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

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
    tNodo *act = *pl;
    tNodo *nue;

    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
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
    nue->sig = act;
    nue->ant = NULL;

    if(act)
    {
        act->ant = nue;
    }

    *pl = nue;

    return TODO_OK;
}

int eliminarPrimero(tLista *pl, void *pd, size_t tamDato)
{
    tNodo *elim = *pl;
 
    if(!elim)
    {
        return LISTA_VACIA;
    }
 
    while(elim->ant)
    {
        elim = elim->ant;
    }
 
    if(elim->sig)
    {
        elim->sig->ant = NULL;
    }
    *pl = elim->sig;
 
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    free(elim->info);
    free(elim);
 
    return TODO_OK;
}
 
int verPrimero(const tLista *pl, void *pd, size_t tamDato)
{
    tNodo *act = *pl;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->ant)
    {
        act = act->ant;
    }
 
    memcpy(pd, act->info, MINIMO(act->tamInfo, tamDato));
 
    return TODO_OK;
}

int insertarAlFinal(tLista *pl, const void *pd, size_t tamDato)
{
    tNodo *act = *pl;
    tNodo *nue;

    if(act)
    {
        while(act->sig)
        {
            act = act->sig;
        }
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
    nue->ant = act;

    if(act)
    {
        act->sig = nue;
    }

    *pl = nue;

    return TODO_OK;
}

int eliminarUltimo(tLista *pl, void *pd, size_t tamDato)
{
    tNodo *elim = *pl;
 
    if(!elim)
    {
        return LISTA_VACIA;
    }
 
    while(elim->sig)
    {
        elim = elim->sig;
    }
 
    if(elim->ant)
    {
        elim->ant->sig = NULL;
    }
    *pl = elim->ant;
 
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    free(elim->info);
    free(elim);
 
    return TODO_OK;
}
 
int verUltimo(const tLista *pl, void *pd, size_t tamDato)
{
    tNodo *act = *pl;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->sig)
    {
        act = act->sig;
    }
 
    memcpy(pd, act->info, MINIMO(act->tamInfo, tamDato));
 
    return TODO_OK;
}

int insertarEnPosicion(tLista *pl, const void *pd, size_t tamDato, size_t pos)
{
    tNodo *sig = *pl,
          *ant = NULL,
          *nue;
 
    if(sig)
    {
        while(sig->ant)
        {
            sig = sig->ant;
        }
    }
 
    while(sig && pos > 0)
    {
        ant = sig;
        sig = sig->sig;
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
    nue->sig = sig;
    nue->ant = ant;
 
    if(sig)
    {
        sig->ant = nue;
    }
 
    if(ant)
    {
        ant->sig = nue;
    }
 
    *pl = nue;
 
    return TODO_OK;
}
 
int eliminarPosicion(tLista *pl, void *pd, size_t tamDato, size_t pos)
{
    tNodo *elim = *pl;
 
    if(!elim)
    {
        return LISTA_VACIA;
    }
 
    while(elim->ant)
    {
        elim = elim->ant;
    }
 
    while(elim && pos > 0)
    {
        elim = elim->sig;
        pos--;
    }
 
    if(!elim)
    {
        return POS_INVALIDA;
    }
 
    if(elim->ant)
    {
        elim->ant->sig = elim->sig;
    }
    if(elim->sig)
    {
        elim->sig->ant = elim->ant;
        *pl = elim->sig;
    }
    else
    {
        *pl = elim->ant;
    }
 
    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tamDato));
    free(elim->info);
    free(elim);
 
    return TODO_OK;
}
 
int verPosicion(const tLista *pl, void *pd, size_t tamDato, size_t pos)
{
    tNodo *act = *pl;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->ant)
    {
        act = act->ant;
    }
 
    while(act && pos > 0)
    {
        act = act->sig;
        pos--;
    }
 
    if(!act)
    {
        return POS_INVALIDA;
    }
 
    memcpy(pd, act->info, MINIMO(act->tamInfo, tamDato));
 
    return TODO_OK;
}

int insertarOrdenado(tLista *pl, const void *pd, size_t tamDato,
                     int (*cmp)(const void *, const void *),
                     int (*acumular)(void **, size_t *, const void *, size_t))
{
    tNodo *act = *pl,
          *sig = NULL,
          *ant = NULL,
          *nue;

    if(act)
    {
        int aux;

        while(act->sig && cmp(act->info, pd) < 0)
        {
            act = act->sig;
        }
        while(act->ant && cmp(act->info, pd) > 0)
        {
            act = act->ant;
        }

        aux = cmp(act->info, pd);

        if(aux == 0)
        {
            *pl = act;

            if(!acumular)
            {
                return DUPLICADO;
            }

            if(acumular(&act->info, &act->tamInfo, pd, tamDato) == 0)
            {
                return SIN_MEMORIA;
            }

            return TODO_OK;
        }

        if(aux < 0)
        {
            ant = act;
            sig = act->sig;
        }
        else
        {
            ant = act->ant;
            sig = act;
        }
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
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
    {
        sig->ant = nue;
    }

    if(ant)
    {
        ant->sig = nue;
    }

    *pl = nue;

    return TODO_OK;
}

int insertarOrdenadoConRepetidos(tLista *pl, const void *pd, size_t tamDato, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *sig = NULL,
          *ant = NULL,
          *nue;
 
    if(act)
    {
        while(act->sig && cmp(act->info, pd) < 0)
        {
            act = act->sig;
        }
        while(act->ant && cmp(act->ant->info, pd) >= 0)
        {
            act = act->ant;
        }
 
        if(cmp(act->info, pd) < 0)
        {
            ant = act;
            sig = act->sig;
        }
        else
        {
            ant = act->ant;
            sig = act;
        }
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
    nue->sig = sig;
    nue->ant = ant;
 
    if(sig)
    {
        sig->ant = nue;
    }
 
    if(ant)
    {
        ant->sig = nue;
    }
 
    *pl = nue;
 
    return TODO_OK;
}



int ordenarLista(tLista *pl, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *ini,
          *fin;
    int marca = 1;

    if(!act)
    {
        return LISTA_VACIA;
    }

    while(act->ant)
    {
        act = act->ant;
    }
    ini = act;

    while(act->sig)
    {
        act = act->sig;
    }
    fin = act;

    while(marca && ini != fin)
    {
        marca = 0;
        act = ini;

        while(act != fin)
        {
            if(cmp(act->info, act->sig->info) > 0)
            {
                void *infoAux = act->info;
                size_t tamAux = act->tamInfo;

                marca = 1;
                act->info = act->sig->info;
                act->tamInfo = act->sig->tamInfo;
                act->sig->info = infoAux;
                act->sig->tamInfo = tamAux;
            }

            act = act->sig;
        }

        fin = fin->ant;

        if(marca && ini != fin)
        {
            marca = 0;
            act = fin;

            while(act != ini)
            {
                if(cmp(act->info, act->ant->info) < 0)
                {
                    void *infoAux = act->info;
                    size_t tamAux = act->tamInfo;

                    marca = 1;
                    act->info = act->ant->info;
                    act->tamInfo = act->ant->tamInfo;
                    act->ant->info = infoAux;
                    act->ant->tamInfo = tamAux;
                }

                act = act->ant;
            }

            ini = ini->sig;
        }
    }

    return TODO_OK;
}

void mapLista(tLista *pl, void (*accion)(void *, void *), void *param)
{
    tNodo *act = *pl;

    if(act)
    {
        accion(NULL, NULL);
        while(act->ant)
        {
            act = act->ant;
        }

        while(act)
        {
            accion(act->info, param);
            act = act->sig;
        }
    }
}

void mapInversoLista(tLista *pl, void (*accion)(void *, void *), void *param)
{
    tNodo *act = *pl;

    if(act)
    {
        accion(NULL, NULL);
        while(act->sig)
        {
            act = act->sig;
        }

        while(act)
        {
            accion(act->info, param);
            act = act->ant;
        }
    }
}

void filterLista(tLista *pl, int (*filtro)(void *, void *), void *param)
{
    tNodo *act = *pl,
          *sig,
          *prim = NULL,
          *ult = NULL;
 
    if(!act)
    {
        return;
    }
 
    while(act->ant)
    {
        act = act->ant;
    }
 
    while(act)
    {
        sig = act->sig;
 
        if(filtro(act->info, param))
        {
            act->ant = ult;
            if(ult)
            {
                ult->sig = act;
            }
            else
            {
                prim = act;
            }
            ult = act;
        }
        else
        {
            free(act->info);
            free(act);
        }
 
        act = sig;
    }
 
    if(ult)
    {
        ult->sig = NULL;
    }
 
    *pl = prim;
}
 
void reduceLista(tLista *pl, void *acum, void (*accion)(void *, void *, void*), void *param)
{
    tNodo *act = *pl;
 
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
 
        while(act)
        {
            accion(act->info, acum, param);
            act = act->sig;
        }
    }
}

int insertarOrdenadoTopN(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *ant = NULL,
          *nue,
          *ult,
          *elim;
    size_t ce = 0;
 
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
    }
 
    while(act && ce < n && cmp(act->info, pd) <= 0)
    {
        ant = act;
        act = act->sig;
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
    nue->sig = act;
    nue->ant = ant;
 
    if(ant)
    {
        ant->sig = nue;
    }
    if(act)
    {
        act->ant = nue;
    }
 
    ce++;
    ult = nue;
 
    while(ult->sig && ce < n)
    {
        ult = ult->sig;
        ce++;
    }
 
    elim = ult->sig;
    ult->sig = NULL;
 
    while(elim)
    {
        act = elim->sig;
 
        free(elim->info);
        free(elim);
        elim = act;
    }
 
    *pl = nue;
 
    return TODO_OK;
}
 
int insertarEnPodio(tLista *pl, const void *pd, size_t tamDato, size_t n, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *ant = NULL,
          *nue,
          *ult,
          *elim;
    size_t ce = 0;
 
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
    }
 
    while(act && ce < n && cmp(act->info, pd) < 0)
    {
        ant = act;
        act = act->sig;
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
    nue->sig = act;
    nue->ant = ant;
 
    if(ant)
    {
        ant->sig = nue;
    }
    if(act)
    {
        act->ant = nue;
    }
 
    ce++;
    ult = nue;
 
    while(ult->sig && ce < n)
    {
        ult = ult->sig;
        ce++;
    }
 
    elim = ult->sig;
 
    while(elim && cmp(elim->info, ult->info) == 0)
    {
        ult = elim;
        elim = elim->sig;
    }
 
    ult->sig = NULL;
 
    while(elim)
    {
        act = elim->sig;
 
        free(elim->info);
        free(elim);
        elim = act;
    }
 
    *pl = nue;
 
    return TODO_OK;
}

void mapTopN(tLista *pl, size_t n, void (*accion)(void *, void *), void *param)
{
    tNodo *act = *pl;
 
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
 
        while(act && n > 0)
        {
            accion(act->info, param);
            act = act->sig;
            n--;
        }
    }
}

int eliminarPorClave(tLista *pl, void *pd, size_t tamDato, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl;
    int aux;

    if(!act)
    {
        return LISTA_VACIA;
    }

    while(act->sig && cmp(act->info, pd) < 0)
    {
        act = act->sig;
    }
    while(act->ant && cmp(act->info, pd) > 0)
    {
        act = act->ant;
    }

    aux = cmp(act->info, pd);

    if(aux == 0)
    {
        tNodo *ant = act->ant,
              *sig = act->sig;

        if(ant)
        {
            ant->sig = sig;
        }
        if(sig)
        {
            sig->ant = ant;
            *pl = sig;
        }
        else
        {
            *pl = ant;
        }

        memcpy(pd, act->info, MINIMO(act->tamInfo, tamDato));
        free(act->info);
        free(act);

        return TODO_OK;
    }

    return NO_ENCONTRADO;
}

int eliminarUltimosN(tLista *pl, size_t n)
{
    tNodo *act = *pl,
          *aux;
    size_t ce = 0;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->sig)
    {
        act = act->sig;
    }
 
    aux = act;
    while(aux && ce < n)
    {
        aux = aux->ant;
        ce++;
    }
 
    if(ce < n)
    {
        return POS_INVALIDA;
    }
 
    while(ce > 0)
    {
        aux = act->ant;
 
        free(act->info);
        free(act);
        act = aux;
        ce--;
    }
 
    if(act)
    {
        act->sig = NULL;
    }
 
    *pl = act;
 
    return TODO_OK;
}

int eliminarDuplicados(tLista *pl, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *rec,
          *sig;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->ant)
    {
        act = act->ant;
    }
 
    *pl = act;
 
    while(act)
    {
        rec = act->sig;
 
        while(rec)
        {
            sig = rec->sig;
 
            if(cmp(act->info, rec->info) == 0)
            {
                rec->ant->sig = rec->sig;
                if(rec->sig)
                {
                    rec->sig->ant = rec->ant;
                }
 
                free(rec->info);
                free(rec);
            }
 
            rec = sig;
        }
 
        act = act->sig;
    }
 
    return TODO_OK;
}
 
int eliminarApariciones(tLista *pl, const void *pd, int (*cmp)(const void *, const void *))
{
    tNodo *act = *pl,
          *sig,
          *prim = NULL,
          *ult = NULL;
 
    if(!act)
    {
        return LISTA_VACIA;
    }
 
    while(act->ant)
    {
        act = act->ant;
    }
 
    while(act)
    {
        sig = act->sig;
 
        if(cmp(act->info, pd) == 0)
        {
            free(act->info);
            free(act);
        }
        else
        {
            act->ant = ult;
            if(ult)
            {
                ult->sig = act;
            }
            else
            {
                prim = act;
            }
            ult = act;
        }
 
        act = sig;
    }
 
    if(ult)
    {
        ult->sig = NULL;
    }
 
    *pl = prim;
 
    return TODO_OK;
}
 
void invertirLista(tLista *pl)
{
    tNodo *act = *pl,
          *aux;
 
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
 
        while(act)
        {
            aux = act->sig;
            act->sig = act->ant;
            act->ant = aux;
            act = aux;
        }
    }
}

void vaciarLista(tLista *pl)
{
    tNodo *act = *pl;

    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }

        while(act)
        {
            tNodo *aux = act->sig;

            free(act->info);
            free(act);
            act = aux;
        }

        *pl = NULL;
    }
}