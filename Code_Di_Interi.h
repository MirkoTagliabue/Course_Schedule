
#ifndef CODE_DI_INTERI_H
#define CODE_DI_INTERI_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Implementazione di code di interi */

typedef struct _coda_int coda_int;
struct _coda_int{
    int *V;
    int dim;
    int head;
    int tail;
};



/* Dichiarazioni funzioni di libreria */

void CreaCodaInt (coda_int *pQ, int size);

void DeallocaCodaInt (coda_int *pQ);

bool CodaVuota (coda_int *pQ);

int Front (coda_int *pQ);

void Enqueue (int i, coda_int *pQ);

void Dequeue (coda_int *pQ);


#endif

