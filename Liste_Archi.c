
#include "Liste_Archi.h"


/* Funzioni ausiliarie per maneggiare liste */




listaarchi CreaLista(){

    listaarchi L;
    L = (listaarchi) malloc(sizeof(arco));
    if(L==NULL){
        fprintf(stderr,"Memoria insufficiente per allocare un arco!\n");
        exit(EXIT_FAILURE);
    }

    L->orig = 0;
    L->dest = 0;
    L->prec = L;
    L->succ = L;

    return L;
}



posarco PrimoLista (listaarchi L){
    return L->succ;
}



posarco UltimoLista (listaarchi L){
    return L->prec;
}



posarco ElementoSuccessivo (posarco p){
    return p->succ;
}



posarco ElementoPrecedente (posarco p){
    return p->prec;
}



bool ListaVuota(listaarchi L){
    if(L->succ == L) return true;
    else return false;
}



bool FineLista(listaarchi L, posarco p){
    if(p == L) return true;
    else return false;
}



void SovrascriveArco(posarco p, nodo new_orig, nodo new_dest){
    p->orig = new_orig;
    p->dest = new_dest;
}



void LeggeArco (posarco p, nodo *porig, nodo *pdest){
  *porig = p->orig;
  *pdest = p->dest;
}



void InserisceNuovoArco(listaarchi L, nodo new_orig, nodo new_dest){
    posarco A;
    posarco p;
    p = UltimoLista(L);
    A = (posarco) malloc(sizeof(arco));
    if(A==NULL){
        fprintf(stderr,"Memoria insufficiente per allocare l'arco (%d, %d)\n", new_orig, new_dest);
        exit(EXIT_FAILURE);
    }
    
    A->orig = new_orig;
    A->dest = new_dest;
    A->succ = L;
    A->prec = UltimoLista(L);

    p->succ = A;
    L->prec = A;
}



void CancellaElemento(posarco *pp){

    posarco p;
    p = *pp;

    /* Faccio puntare *pp all'arco successivo a quello da eliminare o avrò in mano un puntatore ad una cella non più allocata */
    *pp = ElementoSuccessivo(p);

    (p->prec)->succ = p->succ;
    (p->succ)->prec = p->prec;

    free(p);

}



void DeallocaLista(listaarchi *pL){

    posarco p;
    p=PrimoLista(*pL);

    while( FineLista(*pL,p)==false ){
        p=PrimoLista(*pL);
        CancellaElemento(&p);
    }

    /* Dealloco infine la sentinella */
    free(p);

    *pL = NULL;

}

