# Course Schedule

Implementazione in linguaggio C di un algoritmo su grafi per determinare l'ordine in cui sostenere degli esami universitari 
preso atto dei vincoli di propedeuticità: in altre parole se gli esami $X$ ed $Y$ sono prerequisito per l'esame $Z$, allora l'algoritmo dovrà restituire che prima 
di poter sostenere l'esame $Z$ lo studente dovrà sostenere gli esami $X$ ed $Y$.  
Nella modellizzazione su grafo, ciascun corso sarà un nodo di un grafo orientato; detti $v, w$ due nodi del grafo l'arco non pesato $(v,w)$ da $v$ in $w$ indicherà che il corso $v$ è
prerequisito per il corso $w$.  
L'input, ovverosia il numero di esami ed il modo in cui essi si intrecciano sotto forma di rispettivi prerequisiti saranno presi da un file di testo formattato, 
modificabile anche da un utente.

## 1. Il Problema
Il problema richiede di trovare un ordine in cui sostenere una serie di esami universitari, garantendo che nessun esame venga affrontato prima di aver 
superato tutti i suoi prerequisiti.  
Si osservi che non è detto che l'ordine sia unico, tuttavia, se per un dato input esistono più soluzioni ugualmente accettabili, l'algoritmo 
convergerà ad una di queste.  
Non è nemmeno detto che per il generico input la soluzione esista, in effetti, se il grafo orientato presenta dei cicli, allora sicuramente il problema non ammette 
soluzioni; analogamente, se il grafo risulta essere partizionabile in più componenti (semplicemente) connesse, dove in una di queste non sia presente un nodo 
che abbia zero prerequisiti, allora, ancora una volta, sicuramente l'input non ammette soluzione (e sarà presente almeno un ciclo).  
Se il problema non ammette soluzione, l'algoritmo stamperà a video un appropriato messaggio di testo. Alternativamente, se l'input ammette soluzioni, l'algoritmo 
stamperà a video l'elenco ordinato in cui sostenere gli esami.  
I nodi del grafo saranno gestiti con numeri anziché con stringhe, per non appesantire la ricerca e le varie azioni sul grafo, si creerà quindi una biezione tra 
gli N esami universitari ed {0, 1, ..., N} $\subseteq$ ℕ.  
Si consideri il seguente esempio:  
- algebra lineare 1 (prerequisito per analisi 2 e per algebra lineare 2)  
- algebra lineare 2  
- analisi 1 (prerequisito per analisi 2)  
- analisi 2 (prerequisito per analisi 3)  
- analisi 3 (prerequisito per analisi 4)  
- algebra astratta 1 (prerequisito per topologia)  
- topologia (prerequisito per analisi 4)  
- analisi 4 (prerequisito per probabilità)  
- probabilità (prerequisito per statistica)
- statistica

agli esami sarà assegnato un intero progressivo e sfruttando tale intero si maneggerà il grafo. Utilizzando ad esempio l'intero progressivo di lettura,
nell'esempio di cui sopra si avrà:  
&nbsp; &nbsp; &nbsp; 0 $\longleftrightarrow$ algebra lineare 1  
&nbsp; &nbsp; &nbsp; 1 $\longleftrightarrow$ algebra lineare 2  
&nbsp; &nbsp; &nbsp; 2 $\longleftrightarrow$ analisi 1  
&nbsp; &nbsp; &nbsp; 3 $\longleftrightarrow$ analisi 2  
&nbsp; &nbsp; &nbsp; 4 $\longleftrightarrow$ analisi 3  
&nbsp; &nbsp; &nbsp; 5 $\longleftrightarrow$ algebra astratta 1  
&nbsp; &nbsp; &nbsp; 6 $\longleftrightarrow$ topologia  
&nbsp; &nbsp; &nbsp; 7 $\longleftrightarrow$ analisi 4  
&nbsp; &nbsp; &nbsp; 8 $\longleftrightarrow$ probabilità  
&nbsp; &nbsp; &nbsp; 9 $\longleftrightarrow$ statistica  
ed il grafo associato sarà della forma:
<img width="768" height="420" alt="image" src="https://github.com/user-attachments/assets/6f2ba970-5b6a-486a-bd74-cd2d3d241719" />

Con tale input, una possibile soluzione può essere: &nbsp; "5 6 0 2 1 3 4 7 8 9",  
tuttavia anche &nbsp; "0 1 2 5 6 3 4 7 8 9" &nbsp; è una soluzione accettabile

## 2. Strutture dati utilizzate e loro implementazione
Per risolvere il problema sono state utilizzate le linked list, i grafi, i vettori e le code di interi.

Le liste sono state implementate come linked list cicliche bidirezionali con sentinella.  
Un nodo di questa lista è una struct contenete tre campi: l'elemento, il puntatore al nodo successivo ed il puntatore al nodo precedente.  
La lista sarà un puntatore ad un nodo della lista stessa, e tale nodo sarà il cosiddetto "nodo sentinella", cioè un nodo fittizio, la sua presenza 
è utile per capire se in ciclo for o while ho scorso tutta la lista (sei puntatore successivo al nodo che ho in mano è uguale al puntatore lista, allora
ho scorso tutta la lista).
<br>
<div align="center">
<img width="732" height="288" alt="Linked_List drawio" src="https://github.com/user-attachments/assets/414b0147-7e9f-4ac5-94b3-8ddea1e93068" />  
</div>
<br>

Il vantaggio delle linked list è che, a differenza dei vettori, consentono inserimenti e cancellazioni in tempo $\theta(1)$ poiché sarebbe sufficiente creare 
un nuovo nodo e sistemare 4 puntatori, mentre invece in un vettore si renderebbe necessario anche traslare tutti gli altri elementi. Tuttavia,
lo svantaggio delle linked list è che per accedere all'elemento k-esimo della lista il costo computazionale sarebbe $\theta(k)$ poichè si renderebbe 
necessario far scorrere tutti i k-1 puntatori "succ" precedenti, a differenza dei vettori dove l'accesso all'elemento k-esimo avviene in tempo costante 
$\theta(1)$.

I grafi sono stati implementati con liste forward-stars.  
In questa implementazione, un grafo è una struct contente $n:=|V|, m:=|E|$ ed un puntatore ad un vettore (detto costola) di puntatori a liste di archi.  
Un nodo di una lista di archi è una struct contenente il nodo origine, il nodo destinazione, il puntatore all'arco successivo ed il puntatore 
all'arco precedente. La lista forward star del nodo v è la lista degli archi uscenti dal nodo v. La costola del grafo è il vettore delle liste forward star,
in particolare, l'lemento k-esimo della costola sarà un puntatore alla lista degli archi uscenti dal nodo k. Le liste forward star sono state implementata come 
linked list cirolari bidirezionali con sentinella.  
Rappresentativamente, il grafo apparirà come:  

<div align="center">
<img width="646" height="446" alt="Grafo FS drawio" src="https://github.com/user-attachments/assets/9fcf6d37-6b70-4a3e-b80a-2649b9db499e" />  
</div>

Il vantaggio di rappresentare il grafo mediante liste forward stars, anziché tramite matrici di adiacenza, è il notevole risparmio di memoria allocata, in effetti
lo spazio necessario per allocare un grafo con liste FS è pari a $\theta(n+m)$ tra costola e liste, mentre lo spazio necessario ad allocare
un grafo mediante liste di adiacenza è di $\theta(n^2)$, pertanto, eccezion fatta per il caso (molto atipico in questo contesto) di grafi densi dove $m \approx n^2$ ) il risparmio di spazio è considerevole poichè si abbatte da quadratico a lineare.  
Lo svantaggio è tuttavia che il costo computazionale necessario per accedere
all'arco $(v,w)$ è pari a $\delta_{v}^{+}$, dove $\delta_{v}^{+}$ indica il numero di archi uscenti dal nodo $v$.

Tra le altre strutture dati utilizzate ci sono anche i vettori e le code di interi.  
La coda di interi è stata per semplicità implementata mediante vettore e due indici posizione (che fungono da puntatori) Front e Rear.  
La coda di interi rispetta la gerarchia FIFO (first in first out) tipica di tutte le code di priorità.


## 3. Formato di input

Il programma legge i dati da un file di testo (es. Input_01.txt). Il file deve essere strutturato nel seguente modo:  
La prima riga contiene un intero $N$, che rappresenta il numero totale dei corsi universitari da seguire. La seconda riga contiene una sequenza di coppie di interi nel formato [corso, prerequisito] separate da virgola. Esempio di input:  

4  
[1,0], [2,0], [3,1], [3,2]

In questo esempio ci sono 4 corsi (numerati da 0 a 3). L'esame 0 è propedeutico sia per il corso 1 che per il corso 2. Gli esami 1 e 2 sono 
prerequisito per il 3.  
In questo caso una possibile soluzione sarà: &nbsp; "0 2 1 3"  


## 4. Algoritmo di risoluzione

## 5. Costi computazionali

