Esame (Risolvere il problema delle equazioni del calore):
  Task 1, codice C++:
    prende in input N e genera la lista dei punti interni del dominio = [0,1]^2
      => sarà una funzione che genera quello e basta, devo vedere come si genera, funzione void?
    genera gli archi dei nodi sopra generati
      => sarà all'interno della stessa funzione precedente
  Task 2, codice C++: (per avere una matrice bella e facile su cui calcolare)
    prende in input i file di testo generati precedentemente e determina su di essi una partizione, deve essere ricorsiva,
    alternare tra divisioni su x e divisioni su y, salvare l'ordinamento finale su un nuovo file,
    comparato a quello originale
    => devo tenere traccia dei nodi che vado a riordinare, prendo in input 2 interi
      funzione void, il risultato è scritto sul file di testo
  Task 3, codice C++:
    genero la matrice A del sistema lineare e il vettore dei termini noti
    => A ha la diagonale di -4
      poi viaggio nel file degli archi e genero ogni punto per ogni arco facendo attenzione a convertire gli
      n nel nuovo ordinamento (posso ordinare il file ordering.txt in modo da avere costo n e fare un elemento alla volta)
  Task 4, python:
    legge i file di testo e risolve il sistema lineare
  Task 5:
    verificare i risultati per vari N