Esame (Risolvere il problema delle equazioni del calore):
  Task 1, codice C++:
    prende in input N e genera la lista dei punti interni del dominio = [0,1]^2, coords.txt
      sarà una funzione che genera quello e basta, devo vedere come si genera, funzione void
        funzione void che viaggia verticalmente e orizzontalmente mappando un punto alla volta in maniera sequenziale
          costo = O(N^2)

    genera gli archi dei nodi sopra generati, connectivity.txt
      sarà all'interno della stessa funzione precedente, è ordinato anche negli n1
        parallelamente alla creazione di coords.txt vengono generati mano a mano gli archi necessari

  Task 2, codice C++: (per avere una matrice bella e facile su cui calcolare)
    prende in input i file di testo generati precedentemente e determina su di essi una partizione, deve essere ricorsiva,
    alternare tra divisioni su x e divisioni su y, salvare l'ordinamento finale su un nuovo file
      salvo coords su una matrice 2xN^2 vector
      devo tenere traccia dei nodi che vado a riordinare, prendo in input degli interi che fanno da indici destri e sinistri
      funzione void, il risultato è ricordato attraverso riferimento (ordering.txt è un vector)
        prendo in input un booleano che mi dice se divido sulle x o sulle y
        prendo in input il primo e l'ultimo indice della serie di punti che devo ordinare
        ordering.txt deve essere salvato come vector dove l'indice del vector è già una delle due colonne di ordering.txt (m) => anche ordering.txt avrà la colonna m in ordine
        viene letta la matrice di coords.txt e i punti vengono divisi nei 3 gruppi(vector)
        prendo i 3 vector e li memorizzo con l'ordine adeguato nel vector di ordering
        itero
      fuori dalla funzione salvo tutto sul file di testo in un ciclo apposito

  Task 3, codice C++: A deve avere anche gli 0? A.txt ha N^2 righe, rhs.txt ha N righe, dove deve essere la corrispondenza?
    genero la matrice A del sistema lineare e il vettore dei termini noti
      >A ha la diagonale di -4,
      poi viaggio nel file degli archi e genero 2 punti (simmetrici) per ogni arco facendo attenzione a convertire gli
      n nel nuovo ordinamento (posso ordinare il file ordering.txt in n in modo da avere costo n e
      fare un elemento alla volta, MergeSort?),
      oppure memorizzo ordering.txt in un vector\array? per permetterne la lettura veloce

  Task 4, python:
    legge i file di testo e risolve il sistema lineare

  Task 5:
    verificare i risultati per vari N