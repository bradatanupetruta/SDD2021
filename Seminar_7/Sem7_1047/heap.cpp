#include <iostream>
#include <fstream>
using namespace std;

struct bonuriDeOrdine {
	int ordine;
	char* titularBon;
	char* data;
};

struct heap {
	bonuriDeOrdine* vect;
	int nrElemente;
};

void filtrare(heap h, int index) {
	int indexRadacina = index;
	int indexStanga = index * 2 + 1;
	int indexDreapta = index * 2 + 2;
	if (indexStanga<h.nrElemente && h.vect[indexStanga].ordine>h.vect[indexRadacina].ordine) {
		indexRadacina = indexStanga;
	}

	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].ordine>h.vect[indexRadacina].ordine) {
		indexRadacina = indexDreapta;
	}

	if (index != indexRadacina) {
		bonuriDeOrdine aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, bonuriDeOrdine b) {
	bonuriDeOrdine* vectNou = new bonuriDeOrdine[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	vectNou[h.nrElemente] = b;
	delete[] h.vect;
	h.vect = vectNou;
	h.nrElemente++;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, bonuriDeOrdine* b) {
	bonuriDeOrdine* vectNou = new bonuriDeOrdine[h.nrElemente - 1];
	//*b = h.vect[0];
	bonuriDeOrdine aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*b = h.vect[h.nrElemente - 1];
	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	delete[] h.vect;
	h.vect = vectNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

void afisare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		cout << "Nr ordine: " << h.vect[i].ordine << " Titular bon: " << h.vect[i].titularBon << " Data: " << h.vect[i].data << endl;

	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		delete[] h.vect[i].titularBon;
		delete[] h.vect[i].data;
	}
	delete[] h.vect;
}

int main() {
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new bonuriDeOrdine[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++) {
		f >> h.vect[i].ordine;
		f >> buffer;
		h.vect[i].titularBon = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].titularBon, strlen(buffer) + 1, buffer);
		f >> buffer;
		h.vect[i].data = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].data, strlen(buffer) + 1, buffer);

	}
	f.close();
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisare(h);
	bonuriDeOrdine b;
	cout << "Introduceti ordinea: ";
	cin >> b.ordine;
	cout << "Introduceti titular";
	cin >> buffer;
	b.titularBon = new char[strlen(buffer) + 1];
	strcpy_s(b.titularBon, strlen(buffer) + 1, buffer);
	cout << "Introduceti data: ";
	cin >> buffer;
	b.data = new char[strlen(buffer) + 1];
	strcpy_s(b.data, strlen(buffer) + 1, buffer);

	h = inserare(h, b);
	afisare(h);
	h = extragere(h, &b);
	cout << endl << endl;

	cout << "Nr ordine: " << b.ordine << " Titular bon: " << b.titularBon << " Data: " << b.data << endl << endl;

	afisare(h);

	dezalocare(h);
}

