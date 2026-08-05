
#include "Code_Di_Interi.h"

/* Funzioni ausiliarie per maneggiare code di interi */




void CreaCodaInt (coda_int *pQ, int size){

    pQ->V = (int *) calloc(size, sizeof(int));
    if (pQ->V == NULL){
        fprintf(stderr,"Errore nell'allocazione della coda!\n");
        exit(EXIT_FAILURE);
    }

    pQ->dim = size;
    pQ->head = 0;
    pQ->tail = 0;
}



void DeallocaCodaInt (coda_int *pQ){
    free(pQ->V);
    pQ->V = NULL;

    pQ->dim = 0;
    pQ->head = 0;
    pQ->tail = 0;

}



bool CodaVuota (coda_int *pQ){
    if(pQ->head == pQ->tail) return true;
    else return false;
}



int Front (coda_int *pQ){
    return pQ->V[pQ->head];
}



void Enqueue (int i, coda_int *pQ){
    pQ->V[pQ->tail] = i;
    pQ->tail++;
}



void Dequeue (coda_int *pQ){
    pQ->V[pQ->head] = -1;
    pQ->head++;
}

