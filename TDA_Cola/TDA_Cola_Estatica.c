#include "TDA_Cola_Estatica.h"
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))

void crearCola(tCola *pc)
{
    pc->tamDisp = TAM_COLA;
    pc->pri = TAM_COLA - OFFSET_COLA;
    pc->ult = TAM_COLA - OFFSET_COLA;
}

int colaVacia(const tCola *pc)
{
    return pc->tamDisp == TAM_COLA;
}

int colaLlena(const tCola *pc, size_t tamDato)
{
    return pc->tamDisp < (tamDato + sizeof(size_t));
}

int ponerEnCola(tCola *pc, const void *pd, size_t tamDato)
{
    size_t ini,
           fin;

    if(pc->tamDisp < (tamDato + sizeof(size_t)))
    {
        return SIN_MEMORIA;
    }

    if((ini = MINIMO(TAM_COLA - pc->ult, sizeof(tamDato))) > 0)
    {
        memcpy(pc->cola + pc->ult, &tamDato, ini);
    }

    if((fin = sizeof(tamDato) - ini) > 0)
    {
        memcpy(pc->cola, ((char*)&tamDato) + ini, fin);
    }

    pc->ult = fin ? fin : pc->ult + sizeof(size_t);

    if((ini = MINIMO(TAM_COLA - pc->ult, tamDato)) > 0)
    {
        memcpy(pc->cola + pc->ult, pd, ini);
    }

    if((fin = tamDato - ini) > 0)
    {
        memcpy(pc->cola, ((char*)pd) + ini, fin);
    }

    pc->ult = fin ? fin : pc->ult + ini;
    pc->tamDisp -= tamDato + sizeof(size_t);

    return TODO_OK;
}

int sacarDeCola(tCola *pc, void *pd, size_t tamDato)
{
    size_t ini,
           fin,
           tamDatoInfo;

    if(pc->tamDisp == TAM_COLA)
    {
        return COLA_VACIA;
    }

    if((ini = MINIMO(TAM_COLA - pc->pri, sizeof(size_t))) > 0)
    {
        memcpy(&tamDatoInfo, pc->cola + pc->pri, ini);
    }

    if((fin = sizeof(size_t) - ini) > 0)
    {
        memcpy((char*)&tamDatoInfo + ini, pc->cola, fin);
    }

    pc->pri = fin ? fin : pc->pri + sizeof(size_t);
    pc->tamDisp += tamDatoInfo + sizeof(size_t);
    tamDatoInfo = MINIMO(tamDatoInfo, tamDato);

    if((ini = MINIMO(TAM_COLA - pc->pri, tamDatoInfo) > 0))
    {
        memcpy(pd, pc->cola + pc->pri, MINIMO(ini, tamDato));
    }

    if((fin = tamDatoInfo - ini) > 0 && (tamDato - ini) > 0)
    {
          memcpy((char*)pd + ini, pc->cola, MINIMO(fin, tamDato - ini));
    }

    pc->pri = fin ? fin : pc->pri + tamDatoInfo;

    return TODO_OK;
}

int verPrimero(const tCola *pc, void *pd, size_t tamDato)
{
    size_t tamDatoInfo,
           ini,
           fin,
           pos = pc->pri;

    if(pc->tamDisp == TAM_COLA)
    {
        return COLA_VACIA;
    }

    if((ini = MINIMO(TAM_COLA - pos, sizeof(size_t))) > 0)
    {
        memcpy(&tamDatoInfo, pc->cola + pos, ini);
    }

    if((fin = sizeof(size_t) - ini) > 0)
    {
        memcpy((char*)&tamDatoInfo + ini, pc->cola, fin);
    }

    pos = fin ? fin : pos + sizeof(size_t);
    tamDatoInfo = MINIMO(tamDatoInfo, tamDato);

    if((ini = MINIMO(TAM_COLA - pos, tamDatoInfo) > 0))
    {
        memcpy(pd, pc->cola + pos, ini);
    }

    if((fin = tamDatoInfo - ini) > 0)
    {
        memcpy((char*)pd + ini, pc->cola, fin);
    }
    
    return TODO_OK;
}

void vaciarCola(tCola *pc)
{
    pc->ult = pc->pri;
    pc->tamDisp = TAM_COLA;
}