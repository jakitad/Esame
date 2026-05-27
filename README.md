Esame (Risolvere il problema delle equazioni del calore):
  Task 1, codice C++:
    prende in input N e genera la lista dei punti interni del dominio = [0,1]^2, coords.txt
      >sarà una funzione che genera quello e basta, devo vedere come si genera, funzione void?
        >funzione void che viaggia verticalmente e orizzontalmente mappando un punto alla volta in maniera sequenziale
          >costo = O(N^2)

    genera gli archi dei nodi sopra generati, connectivity.txt
      >sarà all'interno della stessa funzione precedente, è ordinato anche negli n1
        >parallelamente alla creazione di coords.txt vengono generati mano a mano gli archi necessari

  Task 2, codice C++: (per avere una matrice bella e facile su cui calcolare)
    prende in input i file di testo generati precedentemente e determina su di essi una partizione, deve essere ricorsiva,
    alternare tra divisioni su x e divisioni su y, salvare l'ordinamento finale su un nuovo file
      >devo tenere traccia dei nodi che vado a riordinare, prendo in input degli interni che fanno da indici destri e sinistri
      funzione void, il risultato è scritto sul file di testo
        >prendo in input un booleano che mi dice se divido sulle x o sulle y
        >prendo in input il primo e l'ultimo indice della serie di punti che devo ordinare
        >per viaggiare bene ordering.txt deve essere salvato come vector/array (N^2 interi non sono tanti?)
        per permetterne la lettura e modifica veloce

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