#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;



int main() {
	double k;
	cout << "Inserisci il parametro k:";
	cin >> k;
    double bordo;
    cout << "Inserisci la temperatura al bordo della piastra:";
    cin >> bordo;

    ifstream file_2("coords.txt");

    // Verificare se il file è aperto
    if (!file_2.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    // lettura del file coords salvando coords = vector {i, j}
    vector<vector<int>> coords = { {NULL,NULL} }; // indice 0 vuoto cosi n coincide con l'indice del vettore 
    int n, i, j;
    double x, y;
    file_2 >> n >> i >> j >> x >> y;
    coords.push_back({ i,j });
    double h = x; // salvo il valore di h alla prima iterazione
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
    vector<int> ordering = { NULL };
    int m;
    while (file >> m >> n) { 
        m += 1; // per correggere e avere gli indici da 0 a N^2 - 1
        // memorizzo ordering.txt
        if (n >= ordering.size()) { // Ridimensiona il vettore se necessario
            ordering.resize(n + 1, -1);  // -1 come valore "vuoto"
            //n_max = n;
        }
        ordering[n] = m; //SCAMBIO

        //bordo = static_cast<double>(coords[n][0] + coords[n][1]) / N; // per sperimentare un po'
        // scrivo rhs.txt
        if (coords[n][0] == 1 || coords[n][1] == 1 || coords[n][0] == N || coords[n][1] == N) {
            if ((coords[n][0] == 1 && coords[n][1] == 1) || (coords[n][0] == N && coords[n][1] == N))
                rhs << exp(-10 * ((coords[n][0] * coords[n][0] * h * h) + (coords[n][1] * coords[n][1] * h * h))) + 2 * coef * bordo << endl;
            else
                rhs << exp(-10 * ((coords[n][0] * coords[n][0] * h * h) + (coords[n][1] * coords[n][1] * h * h))) + coef * bordo << endl;
        }
        else {
            rhs << exp(-10 * ((coords[n][0] * coords[n][0] * h * h) + (coords[n][1] * coords[n][1] * h * h))) << endl;
        }
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

    cout << "Premi invio per chiudere..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();     // Attende un nuovo input
	return 0;
}
/*



*/