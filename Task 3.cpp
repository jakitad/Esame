#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;



int main() {
	double k;
	cout << "Inserisci il parametro k:";
	cin >> k;

    ifstream file_2("coords.txt");

    // Verificare se il file è aperto
    if (!file_2.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    // lettura del file coords
    vector<vector<int>> coords = { {NULL,NULL} }; // indice 0 vuoto cosi n coincide con l'indice del vettore 
    int n, i, j;
    double x, y;
    file_2 >> n >> i >> j >> x >> y;
    coords.push_back({ i,j });
    double h = x;
    while (file_2 >> n >> i >> j >> x >> y) {
        //cout << x << "," << y << endl;
        coords.push_back({ i,j });
    }
    // l'ultimo n che esce dal ciclo è il max(n) -> #A = n x n 
    int N = coords[n][0];
    double coef = k / (h * h); // coefficiente

    file_2.close();

    ifstream file("ordering.txt");

    // Verificare se il file è aperto
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    ofstream rhs("rhs.txt");

    if (!rhs.is_open()) {
        cerr << "Errore: impossibile creare rhs.txt" << endl;
        return 0;
    }

    // lettura del file ordering.txt
    vector<int> ordering;
    int m;
    while (file >> m >> n) {
        // memorizzo ordering.txt
        if (n >= ordering.size()) { // Ridimensiona il vettore se necessario
            ordering.resize(n + 1, -1);  // -1 come valore "vuoto"
            //n_max = n;
        }
        ordering[n] = m;

        // scrivo rhs.txt
        rhs << exp(-10*((coords[n][0]* coords[n][0]*h*h) + (coords[n][1] * coords[n][1] * h * h))) << endl;
    }

    file.close();
    rhs.close();

    
    cout << "Lettura completata" << endl;
    cout << "Scrittura di rhs.txt completata" << endl;

    
    ofstream A("A.txt");

    if (!A.is_open()) {
        cerr << "Errore: impossibile creare A.txt" << endl;
        return 0;
    }

    // genero la diagonale dei termini -4*coef
    for (i = 1;i <= m;i++) { // m = n_max
        A << i << " " << i << " " << -4 * coef << endl;
    }

    //genero tutti i collegamenti
    ifstream archi("connectivity.txt");

    if (!archi.is_open()) {
        cerr << "Errore: impossibile aprire il file ordering.txt" << endl;
        return 0;
    }

    int e, n1, n2;
    while (archi >> e >> n1 >> n2) {
        A << ordering[n1] << " " << ordering[n2] << " " << coef << endl;
        A << ordering[n2] << " " << ordering[n1] << " " << coef << endl;
    }
    
    A.close();

    cout << "Scrittura di A.txt completata" << endl;

	return 0;
}
/*



*/