
#ifndef LISTE_ARCHI_H
#define LISTE_ARCHI_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Liste implementate come liste bidirezionali cicliche con sentinella */


typedef int nodo;

typedef struct _arco arco;
typedef arco* posarco;
struct _arco{
    nodo orig;
    nodo dest;
    posarco prec;
    posarco succ;
};
typedef arco* listaarchi;



/* Dichiarazioni funzioni di libreria */

listaarchi CreaLista();

posarco PrimoLista (listaarchi L);

posarco UltimoLista (listaarchi L);

posarco ElementoSuccessivo (posarco p);

posarco ElementoPrecedente (posarco p);

bool ListaVuota(listaarchi L);

bool FineLista(listaarchi L, posarco p);

void SovrascriveArco(posarco p, nodo new_orig, nodo new_dest);

void LeggeArco (posarco p, nodo *porig, nodo *pdest);

void InserisceNuovoArco(listaarchi L, nodo new_orig, nodo new_dest);

void CancellaElemento(posarco *p);

void DeallocaLista(listaarchi *pL);


#endif

