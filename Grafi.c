
#include "Grafi.h"


/* Funzioni ausiliarie per maneggiare grafi */




grafo* CreaGrafo(int n){

    grafo *pG;
    int cont;

    pG = (grafo *) malloc(sizeof(grafo));
    if (pG == NULL){
        fprintf(stderr,"Errore nell'allocazione del vettore delle forward star!\n");
        exit(EXIT_FAILURE);
    }

    pG->FS = (listaarchi*) malloc(n*sizeof(listaarchi));

    if (pG->FS == NULL){
        fprintf(stderr,"Errore nell'allocazione del vettore delle forward star!\n");
        exit(EXIT_FAILURE);
    }

    for(cont=0; cont<n; cont++){
        pG->FS[cont] = CreaLista();
    }

    pG->n = n;
    pG->m = 0;

    return pG;
}



void InserisceArcoInGrafo(grafo* pG, nodo new_orig, nodo new_dest){

    bool gia_presente=false;
    nodo o, d;
    posarco p;

    for(p=PrimoLista(pG->FS[new_orig]); FineLista(pG->FS[new_orig], p)==false ; p=ElementoSuccessivo(p)){
        LeggeArco(p, &o, &d);
        if(o == new_orig && d == new_dest){
            gia_presente = true;
            break;
        } //end if
    } //end for

    if(gia_presente==false){
        InserisceNuovoArco(pG->FS[new_orig], new_orig, new_dest);
        (pG->m)++;
    } //end if

} //end function



void CancellaArco (nodo o, nodo d, grafo *pG){

    posarco i;

    for( i=PrimoLista(pG->FS[o]); FineLista(pG->FS[o],i)==false; i=ElementoSuccessivo(i) ){
        if(i->dest == d)  break;
    }

    if( FineLista(pG->FS[o],i)==false ){
        (i->prec)->succ = i->succ;
        (i->succ)->prec = i->prec;
        free(i);
        pG->m--;
    }

}




bool EsisteArco(grafo *pG, nodo o, nodo d){

    posarco p;
    bool trovato=false;
    nodo d_candidato;

    for( p=PrimoLista(pG->FS[o]); FineLista(pG->FS[o], p)==false ; p=ElementoSuccessivo(p) ){
        LeggeArco(p, &o, &d_candidato);
        if(d==d_candidato){
            trovato=true;
            break;
        } //end if
    } //end fort

    if(trovato==false) return false;
    else return true;
} //end function




posarco PrimoArcoFS (grafo *pG, nodo o){
    posarco p;
    p= pG->FS[o];
    return ElementoSuccessivo(p);
}




nodo LeggeDestArco (posarco p){
    nodo o, d;
    LeggeArco(p, &o, &d);
    return d;
}




void DeallocaGrafo (grafo *pG){

    nodo orig;

    for(orig=0; orig < pG->n; orig++){
        DeallocaLista(&pG->FS[orig]);
    }

    free(pG->FS);

    free(pG);

}

