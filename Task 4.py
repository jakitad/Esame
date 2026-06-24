"""
Task 4: Risoluzione del sistema lineare tramite fattorizzazione di Cholesky
Legge i file A.txt e rhs.txt e risolve -A*u = rhs usando Cholesky
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.sparse import csc_matrix, coo_matrix
from scipy.sparse.linalg import spsolve_triangular
from sksparse.cholmod import cholesky


def read_sparse_matrix(filename):
    """
    Legge una matrice sparsa dal file nel formato:
    i j A[i,j]
    
    Args:
        filename: percorso del file A.txt
        
    Returns:
        Matrice sparsa in formato COO (sarà convertita a CSC)
    """
    data = np.loadtxt(filename)
    
    # Estrai indici e valori (i indici sono 1-indexed nel file, convertiti a 0-indexed)
    i = (data[:, 0] - 1).astype(int)
    j = (data[:, 1] - 1).astype(int)
    vals = data[:, 2]
    
    # Determina la dimensione della matrice
    n = max(i.max(), j.max()) + 1
    
    # Costruisci la matrice in formato COO, poi converti a CSC
    A = coo_matrix((vals, (i, j)), shape=(n, n))
    return A.tocsc()


def read_rhs(filename):
    """
    Legge il vettore dei termini noti dal file rhs.txt
    
    Args:
        filename: percorso del file rhs.txt
        
    Returns:
        Vettore dei termini noti
    """
    return np.loadtxt(filename)


def read_coords(filename="coords.txt", ordering_file=None):
    """
    Legge le coordinate e gli indici (i, j) dal file coords.txt
    Formato: n i j x y (una riga per nodo)
    
    Se ordering_file è fornito, riordina le righe secondo il file ordering.txt
    Formato ordering.txt: m n (dove m è nuovo indice, n è indice originale)
    
    Args:
        filename: percorso del file coords.txt
        ordering_file: percorso del file ordering.txt (opzionale)
        
    Returns:
        i_indices: array degli indici i (riordinati se ordering_file fornito)
        j_indices: array degli indici j (riordinati se ordering_file fornito)
    """
    data = np.loadtxt(filename)
    i_indices = data[:, 1].astype(int)
    j_indices = data[:, 2].astype(int)
    
    ordering_data = np.loadtxt(ordering_file, dtype=int)
    
    m = ordering_data[:, 0].astype(int)
    n = ordering_data[:, 1].astype(int)
    
    
    new_i = np.zeros_like(i_indices)
    new_j = np.zeros_like(i_indices)
    
    i=0
    while(i<m.size):
        new_i[m[i]-1] = i_indices[n[i]-1]
        new_j[m[i]-1] = j_indices[n[i]-1]
        #print(m[i], n[i], new_i[i], new_j[i], f"\n")
        i+=1
    
    
    return new_i, new_j
    #return i_indices, j_indices


def my_cholesky(A):
    """
    Calcola la fattorizzazione di Cholesky della matrice A
    Utilizza CHOLMOD tramite scikit-sparse
    
    Args:
        A: matrice sparsa in formato CSC (deve essere simmetrica definita negativa)
        
    Returns:
        L: fattore triangolare inferiore tale che -A = L*L^T
    """
    factor = cholesky(A, order="natural")
    return csc_matrix(factor[0])


def solve_system(A, rhs):
    """
    Risolve il sistema lineare -A*u = rhs
    
    Args:
        A: matrice sparsa del sistema (CSC)
        rhs: vettore dei termini noti
        
    Returns:
        u: soluzione del sistema
    """
    # Fattorizzazione di Cholesky di -A
    R = my_cholesky(-A)
    
    # Risolvi L*y = rhs (sistema triangolare inferiore)
    y = spsolve_triangular(R.T, rhs, lower=True)
    
    # Risolvi L^T*u = y (sistema triangolare superiore)
    u = spsolve_triangular(R, y, lower=False)
    
    return u


def plot_solution_heatmap(u, i_indices, j_indices, title="Soluzione - Heatmap"):
    """
    Visualizza come heatmap 2D regolare
    """
    fig, ax = plt.subplots(figsize=(12, 10))
    
    # Crea matrice riempiendo con i valori di u
    i_min, i_max = int(i_indices.min()), int(i_indices.max()) + 1
    j_min, j_max = int(j_indices.min()), int(j_indices.max()) + 1
    
    heatmap = np.full((i_max - i_min, j_max - j_min), np.nan)
    
    for idx in range(0,u.size):
        heatmap[i_indices[idx] - i_min, j_indices[idx] - j_min] = u[idx]
    
    im = ax.imshow(heatmap, cmap='RdBu_r', aspect='auto', origin='upper')
    ax.set_xlabel('j (colonna)', fontsize=12)
    ax.set_ylabel('i (riga)', fontsize=12)
    ax.set_title(title, fontsize=14, fontweight='bold')
    
    cbar = plt.colorbar(im, ax=ax)
    cbar.set_label('u', fontsize=12)
    
    plt.tight_layout()
    return fig, ax



"""
Programma principale: legge i file, fattorizza, risolve e visualizza
"""
# Parametri dei file
A_file = "A.txt"
rhs_file = "rhs.txt"
coords_file = "coords.txt"
ordering_file = "ordering.txt"  # File di ordinamento

A = read_sparse_matrix(A_file) # lettura della matrice sparsa
rhs = read_rhs(rhs_file)

print(f"Dimensione del sistema: {A.shape[0]}")
print(f"Numero di non-zeri in A: {A.nnz}")

u = solve_system(A, rhs)

print(f"Norma della soluzione: {np.linalg.norm(u):.6e}")

np.savetxt("u.txt", u, fmt="%.10e") # Salva la soluzione

# Verifica residuo
residuo = np.linalg.norm(A @ u - rhs) / np.linalg.norm(rhs)
print(f"Residuo relativo: {residuo:.6e}")

# Leggi gli indici (i, j) da coords.txt con riordinamento
print("\nLettura coordinata grid (i, j) da coords.txt...")
try:
    # Prova a leggere con il file di ordinamento
    i_indices, j_indices = read_coords(coords_file, ordering_file)
    print(f"Ordinamento da {ordering_file} applicato")
except FileNotFoundError:
    # Se non trova il file di ordinamento, usa l'ordinamento naturale
    print(f"File {ordering_file} non trovato, uso ordinamento naturale")
    i_indices, j_indices = read_coords(coords_file)

print(f"Min(u) = {u.min():.6e}, Max(u) = {u.max():.6e}")
print(f"Indici i: min={i_indices.min()}, max={i_indices.max()}")
print(f"Indici j: min={j_indices.min()}, max={j_indices.max()}")

# Visualizza
fig, ax = plot_solution_heatmap(u, i_indices, j_indices)

plt.savefig("soluzione_grid.png", dpi=150, bbox_inches='tight') # Salva la figura

plt.show()
