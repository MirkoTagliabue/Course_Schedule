
/*  OSS: si compila con: 
        gcc Course_Schedule.c Liste_Archi.c Grafi.c Code_Di_Interi.c -Wall -Wextra -pedantic -o Course_Schedule.exe
    E si avvia il file con:
        .\Course_Schedule.exe Input_01.txt
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Grafi.h"
#include "Code_Di_Interi.h"


#define ROW_LENGTH 256



    /* Dichiarazione procedure secondarie del codice */

void Interpreta_Linea_Di_Comando(int argc, char *argv[], char* file_dati);

void Gestisce_Input(char *file_dati, int *numero_corsi, int *dimensione_prerequisiti, int ***pprerequisiti);

void Carica_Grafo(grafo *pG, int** prerequisiti, int dimensione_prerequisiti);

void Calcola_Numero_Di_Prerequisiti_Per_Ciascun_Corso(int *numero_di_prerequisiti, grafo *pG);

void Calcola_Ordine_Esami(grafo *pG, int *numero_di_prerequisiti, int *soluzione, bool *esiste_soluzione);

void Calcola_Dimensione_Soluzione(bool esiste_soluzione, int **soluzione, int *dimensione_soluzione, int numero_corsi);

void Stampa_Soluzione(int *soluzione, int dimensione_soluzione);

void Dealloca_Prerequisiti(int ***pprerequisiti, int dimensione_prerequisiti);







int main(int argc, char* argv[]) {
    

    /* Prima parte Dichiarativa e prime inizializzazioni */

    char file_dati[ROW_LENGTH];

    int numero_corsi;
    int dimensione_prerequisiti;
    int** prerequisiti;

    Interpreta_Linea_Di_Comando(argc, argv, file_dati);

    Gestisce_Input(file_dati, &numero_corsi, &dimensione_prerequisiti, &prerequisiti);


    /* Seconda parte introduttiva ed inizializzazioni */
    grafo *pG;  /*G è il grafo dei prerequisiti*/

    int numero_di_prerequisiti[numero_corsi];  
    /* Numero_di_prerequisiti[i] indica quanti corsi prerequisito si richiede di seguire prima di seguire il corso numero i */

    int *soluzione;
    soluzione = (int *) malloc(numero_corsi*sizeof(int));
    int dimensione_soluzione;

    bool esiste_soluzione;

    pG = CreaGrafo(numero_corsi); 
    Carica_Grafo(pG, prerequisiti, dimensione_prerequisiti);
    Calcola_Numero_Di_Prerequisiti_Per_Ciascun_Corso(numero_di_prerequisiti, pG);



    /* Cuore del codice: */
    Calcola_Ordine_Esami(pG, numero_di_prerequisiti, soluzione, &esiste_soluzione);
    Calcola_Dimensione_Soluzione(esiste_soluzione, &soluzione, &dimensione_soluzione, numero_corsi);


    /* Stampa risultato finale */
    Stampa_Soluzione(soluzione, dimensione_soluzione);


    /* Dealloca le strutture dati utilizzate */
    DeallocaGrafo(pG);
    Dealloca_Prerequisiti(&prerequisiti, dimensione_prerequisiti);


    return EXIT_SUCCESS;
    
} // end main





/* ________________________________________________________________________________________________________ */


/* Funzioni secondarie del main */



void Interpreta_Linea_Di_Comando(int argc, char *argv[], char* file_dati){

    if(argc != 2){
        fprintf(stderr,"Errore nella linea di comando!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(file_dati, argv[1]);

}




void Gestisce_Input(char *file_dati, int *numero_corsi, int *dimensione_prerequisiti, int ***pprerequisiti){

    FILE *fp;
    int k;
    int a_k, b_k;


    fp=fopen(file_dati, "r");
    if(fp==NULL){
        fprintf(stderr, "Errore nell'apertura del file %s\n", file_dati);
        exit(EXIT_FAILURE);
    }


    fscanf(fp, "%d", numero_corsi);
    fscanf(fp, "\n");

    /* Leggo una prima volta il file e ricavo quanti prerequisiti ho in mano */
    k=0;
    while( fscanf(fp, "[%d, %d]", &a_k, &b_k) == 2){
        k++;
        fscanf(fp, ", ");
    }
    *dimensione_prerequisiti=k;

    *pprerequisiti = (int **) malloc( *dimensione_prerequisiti * sizeof(int *) );
    if(*pprerequisiti == NULL){
        fprintf(stderr, "Errore nell'allocazione della costola del vettore prerequisiti\n");
        exit(EXIT_FAILURE);
    }


    /* Ora inserisco gli elementi nel vettore prerequisiti */
    rewind(fp);

    /* Leggo la prima riga e non faccio nulla, così faccio scorrere il file pointer fp */
    fscanf(fp, "%d", numero_corsi);
    fscanf(fp, "\n");

    k=0;
    while( fscanf(fp, "[%d, %d]", &a_k, &b_k) == 2){
        k++;
        (*pprerequisiti)[k-1] = malloc(2* sizeof(int));
        if( (*pprerequisiti)[k-1] == NULL){
            fprintf(stderr, "Errore nell'allocazione dell'elemento numero %d del vettore prerequisiti\n", k);
            exit(EXIT_FAILURE);
        }

        (*pprerequisiti)[k-1][0] = a_k;
        (*pprerequisiti)[k-1][1] = b_k;

        fscanf(fp, ", ");
    }

    
    fclose(fp);

}




void Carica_Grafo(grafo *pG, int** prerequisiti, int dimensione_prerequisiti){

    int k;
    int a_k, b_k;
    int *p;


    for( k=0; k<dimensione_prerequisiti; k++){
        p = prerequisiti[k];
        a_k = p[0];
        b_k = p[1];
        InserisceArcoInGrafo(pG, b_k, a_k);

    } //end for

} //end function




void Calcola_Numero_Di_Prerequisiti_Per_Ciascun_Corso(int *numero_di_prerequisiti, grafo *pG){

    int orig, dest;
    int k;
    posarco p;

    // Inizializzo:
    for(k=0; k < pG->n ; k++){
        numero_di_prerequisiti[k] = 0;
    }


    for(orig=0; orig < pG->n; orig++){

        for( p=PrimoArcoFS(pG,orig); FineLista(pG->FS[orig], p) ==false; p=ElementoSuccessivo(p)  ){
            dest = LeggeDestArco(p);
            (numero_di_prerequisiti[dest])++;
        } //end ciclo su lista FS i-esima

    } //end for sulla costola

} //end function




void Calcola_Ordine_Esami(grafo *pG, int *numero_di_prerequisiti, int *soluzione, bool *esiste_soluzione){

    coda_int Q;
    int k;
    int corso;
    int dest;
    int cont_soluz = 0;
    posarco p;


    CreaCodaInt(&Q, pG->n);
    *esiste_soluzione = false;

    for(k=0; k < pG->n ; k++){
  
        if(numero_di_prerequisiti[k]==0){
            Enqueue(k,&Q);
            soluzione[cont_soluz] = k;
            cont_soluz++;
        } 
    }


    // Avvio una BFS (uso però Numero_di_prerequisiti anzichè il classico vettore di incidenza)
    while( CodaVuota(&Q)==false ){
        corso = Front(&Q);
        Dequeue(&Q);

        for( p=PrimoArcoFS(pG,corso); FineLista(pG->FS[corso], p) ==false; p=ElementoSuccessivo(p) ){

            dest=LeggeDestArco(p);
            numero_di_prerequisiti[dest]--;

            if(numero_di_prerequisiti[dest]==0){
                soluzione[cont_soluz] = dest;
                cont_soluz++;
                Enqueue(dest, &Q);
            }

        } //end ciclo for sulla FS del corso

    } //end while(coda_vuota)


    if(cont_soluz == pG->n) *esiste_soluzione=true;
    else *esiste_soluzione=false;

    DeallocaCodaInt(&Q);

} //end function




void Calcola_Dimensione_Soluzione(bool esiste_soluzione, int **soluzione, int *dimensione_soluzione, int numero_corsi){

    if(esiste_soluzione==true)
        *dimensione_soluzione = numero_corsi;
    
    else {
        *dimensione_soluzione = 0;
        free(*soluzione);
        *soluzione=NULL;
    }

}




void Stampa_Soluzione(int *soluzione, int dimensione_soluzione){

    if(dimensione_soluzione == 0){
        printf("Non esiste una soluzione");
    }

    else{
        
        printf("L'ordine con cui sostenere gli esami e' :\n");

        for(int i=0; i<dimensione_soluzione; i++){
            printf("%d ", soluzione[i]);
        }
    }

    printf("\n\n");

} //end Stampa_Soluzione




void Dealloca_Prerequisiti(int ***pprerequisiti, int dimensione_prerequisiti){

    for(int k=0; k<dimensione_prerequisiti; k++){
        free( (*pprerequisiti)[k] );
    }

    free( *pprerequisiti );
    *pprerequisiti = NULL;

}

