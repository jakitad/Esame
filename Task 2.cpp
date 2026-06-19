#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void ordina(const vector<vector<int>>& coords, vector<int>& ordering, int sx, int dx, bool x=true, int depth = 1) {
    if (dx - sx <= depth) { // check di non aver raggiunto la fine
        return;
    }
    vector<int> va, vb, vs;
    if (x) { // if per decidere la divisione sulle x o sulle y
        int s = (coords[ordering[dx]][0] + coords[ordering[sx]][0]) / 2; // descriminante sulle i che divide a metà l'insieme
        // l'indice dx ha l'i minima e l'indice sx ha l'i massima semplicemente perché sono agli estremid del dominio che sto analizzando
        for (int k = sx;k <= dx;k++) { // smisto gli insiemi in va, vb e vs
            int i = coords[ordering[k]][0];
            if (i < s) {
                va.push_back(ordering[k]);
            }
            else if (i > s) {
                vb.push_back(ordering[k]);
            }
            else if (i == s) {
                vs.push_back(ordering[k]);
            }
            else {
                cerr << "Errore: impossibile allocare coordinata indice " << ordering[k] << endl;
            }
        }
	}
	else {
        int s = (coords[ordering[dx]][1] + coords[ordering[sx]][1]) / 2; // descriminante sulle j che divide a metà l'insieme
        // l'indice dx ha il j minimo e l'indice sx ha il j massimo semplicemente perché sono agli estremid del dominio che sto analizzando
        for (int k = sx;k <= dx;k++) { // smisto gli insiemi in va, vb e vs
            int j = coords[ordering[k]][1];
            if (j < s) {
                va.push_back(ordering[k]);
            }
            else if (j > s) {
                vb.push_back(ordering[k]);
            }
            else if (j == s) {
                vs.push_back(ordering[k]);
            }
            else {
                cerr << "Errore: impossibile allocare coordinata indice " << ordering[k] << endl;
            }
        }
	}

    // Ordino gli oggetti nella maniera appropriata nel vector "ordering"
    int o = sx; // sx_va = sx
    int size = va.size();
    for (int h = 0;h < size;h++) {
        ordering[o] = va[h];
        o++;
        //cout << o << endl;
    }
    int sx_vb = o; // dx_va = sx_vb - 1
    size = vb.size();
    for (int h = 0;h < size;h++) {
        ordering[o] = vb[h];
        o++;
        //cout << o << endl;
    }
    int sx_vs = o; // dx_vb = sx_vs - 1
    size = vs.size();
    for (int h = 0;h < size;h++) {
        ordering[o] = vs[h];
        o++;
        //cout << o << endl;
    } // dx_vs = dx

    if ((o - 1) != dx) {
        cerr << "Errore: gli indici non tornano" << endl;
        return;
    }

    // Itero di processo
    ordina(coords, ordering, sx, sx_vb - 1, !x);
    ordina(coords, ordering, sx_vb, sx_vs - 1, !x);
}


int main() {
    ifstream file("coords.txt");

    // Verificare se il file è aperto
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file" << endl;
        return 1;
    }

    // lettura del file coords.txt
    vector<vector<int>> coords = { {NULL,NULL} }; // indice 0 vuoto cosi n coincide con l'indice del vettore 
    int n, i, j;
    float x, y;
    while (file >> n >> i >> j >> x >> y) {
        //cout << x << "," << y << endl;
        coords.push_back({ i,j });
    }
    //cout << coords[0][0] << endl;
    cout << "Lettura completata" << endl;
    file.close();

    vector<int> ordering;  // creazione del vettore di ordering di base
    for (int i = 0;i <= n;i++) {
        ordering.push_back(i);
        //cout << i << ordering[i] << endl;
    }

    cout << "Ordino?" << endl;
    bool ok;
    cin >> ok;
    if (ok)
        ordina(coords, ordering, 1, ordering.size() - 1);

    // trascrivo il vettore sul file di testo
    ofstream ordering_file("ordering.txt");

    if (!ordering_file.is_open()) {
        cerr << "Errore: impossibile creare il file" << endl;
        return 0;
    }

    for (int i = 1;i < ordering.size();i++) {
        ordering_file << i << " " << ordering[i] << endl; //cambio i in (i - 1) se voglio farlo giusto come dice la consegna
    }

    ordering_file.close();

    cout << "File creato" << endl;

    cout << "Premi invio per chiudere..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();     // Attende un nuovo input
	return 0;
}
/*



*/