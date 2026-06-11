#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



int main() {
	double k;
	cout << "Inserisci il parametro k:";
	cin >> k;

    ifstream file("ordering.txt");

    // Verificare se il file è aperto
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    // lettura del file ordering.txt
    vector<int> ordering;
    int m, n;
    while (file >> m >> n) {
        if (n >= ordering.size()) // Ridimensiona il vettore se necessario
            ordering.resize(n + 1, 0);  // 0 come valore "vuoto"
        ordering[n] = m;
    }

    file.close();

    ifstream file("coords.txt");

    // Verificare se il file è aperto
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    // lettura del file coords
    vector<vector<int>> coords = { {NULL,NULL,NULL,NULL} }; // indice 0 vuoto cosi n coincide con l'indice del vettore 
    int n, i, j;
    double x, y;
    while (file >> n >> i >> j >> x >> y) {
        //cout << x << "," << y << endl;
        coords.push_back({ i,j,x,y });
    }

    file.close();
    cout << "Lettura completata" << endl;

    // l'ultimo n che esce dal ciclo è il max(n) -> #A = n x n 
    double h = coords[1][3];
    int N = coords[n][0];



	return 0;
}
/*



*/