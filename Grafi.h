
#ifndef GRAFI_H
#define GRAFI_H


#include "Liste_Archi.h"

/* Grafo implementato con liste forward-stars */
/* Ciascuna lista forward star sarà una lista bidirezionale ciclica con sentinella */

typedef struct _grafo grafo;
struct _grafo{
  int n;
  int m;
  listaarchi *FS;
};



/* Dichiarazioni funzioni di libreria */

grafo* CreaGrafo(int n);

void InserisceArcoInGrafo(grafo* pG, nodo new_orig, nodo new_dest);

void CancellaArco (nodo o, nodo d, grafo *pG);

bool EsisteArco(grafo *pG, nodo o, nodo d);

posarco PrimoArcoFS (grafo *pG, nodo o);

nodo LeggeDestArco (posarco p);

void DeallocaGrafo (grafo *pG);


#endif

