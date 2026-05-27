#include <iostream>
#include <fstream>

using namespace std;

void genera_lista_punti(const int& N) {
	ofstream coords("coords.txt");
	ofstream connect("connectivity.txt");
	
	if (!coords.is_open()) {
		cerr << "Errore: impossibile creare il coords" << endl;
		return;
	}
	if (!connect.is_open()) {
		cerr << "Errore: impossibile creare il connectivity" << endl;
		return;
	}

	auto h = 1.0 / (N + 1);
	auto n = 1, e = 1;

	for (auto j = 1;j <= N;j++) { // I punti con indice = 0 || N+1 sono quelli sul bordo, non si mettono
		for (auto i = 1;i <= N;i++) {
			coords << n << " " << i << " " << j << " " << h * i << " " << h * j << endl;
			if (i > 1) {
				connect << e << " " << n << " " << n - 1 << endl;
				e++;
			}
			if (j > 1) {
				connect << e << " " << n << " " << n - N << endl;
				e++;
			}

			n++;
		}
	}

	coords.close();
	connect.close();
	cout << "Files creati con successo" << endl;
	return;
}

int main() {
	int N;
	cout << "Inserisci N intero:";
	cin >> N;

	if (N == 0) {
		cerr << "Errore: fallita immissione di N";
		cin.clear();

		cout << "Premi invio per chiudere..." << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		return 0;
	}
	cout << "N immesso correttamente" <<endl;

	genera_lista_punti(N);

	cout << "Operazione eseguita con successo|" << endl;

	cout << "Premi invio per chiudere..." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora il newline residuo
	//cin.get();     // Attende un nuovo input
	return 0;
}
/*
Pulire il buffer di cin:
cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Svuota tutto il buffer fino a newline



*/