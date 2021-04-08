#define _CRT_SECURE_NO_WARNINGS
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
	if (indexStanga < h.nrElemente && h.vect[indexStanga].ordine>h.vect[indexRadacina].ordine) {
		indexRadacina = indexStanga;
	}
	if (indexDreapta < h.nrElemente && h.vect[indexDreapta].ordine>h.vect[indexRadacina].ordine) {
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
	//avem *b pt ca il returnez prin parametru
	bonuriDeOrdine* vectNou = new bonuriDeOrdine[h.nrElemente - 1];
	//*b = h.vect[0]; nu facem asa
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
		cout << "Nr ordine: " << h.vect[i].ordine << "Titular cont " << h.vect[i].titularBon << "Data " << h.vect[i].data << endl;

	}
}

struct nodLs {
	bonuriDeOrdine inf;
	nodLs* next;
};

nodLs* inserareLista(nodLs* cap, bonuriDeOrdine b) {
	nodLs* nou = new nodLs;
	nou->inf.ordine = b.ordine;
	nou->inf.data = new char[strlen(b.data) + 1];
	strcpy(nou->inf.data, b.data);
	nou->inf.titularBon = new char[strlen(b.titularBon) + 1];
	strcpy(nou->inf.titularBon, b.titularBon);
	nou->next = nullptr;

	if (cap == nullptr)
	{
		cap = nou;
	}
	else
	{
		nodLs* temp = cap;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	return cap;
}

void traversareLista(nodLs* cap)
{
	nodLs* temp = cap;
	while (temp != nullptr)
	{
		cout << temp->inf.data << temp->inf.ordine << temp->inf.titularBon << endl;
		temp = temp->next;
	}
}

void dezalocareLista(nodLs* cap)
{
	nodLs* temp = cap;
	while (temp != nullptr)
	{
		nodLs* temp2 = temp->next;
		delete[] temp->inf.data;
		delete[] temp->inf.titularBon;
		delete temp;
		temp = temp2;
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		delete[] h.vect[i].titularBon;
		delete[] h.vect[i].data;
	}
	delete[] h.vect;
}

nodLs* conversie(heap h, nodLs* l) {
	bonuriDeOrdine b;
	int n = h.nrElemente;
	for (int i = 0; i < n; i++) {
		h = extragere(h, &b);
		l = inserareLista(l, b);
	}
	return l;
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

	/*bonuriDeOrdine b;
	cout << "Introduceti ordinea: ";
	cin >> b.ordine;
	cout << "Introduceti titular: ";
	cin >> buffer;
	b.titularBon = new char[strlen(buffer) + 1];
	strcpy_s(b.titularBon, strlen(buffer) + 1, buffer);
	cout << "Introduceti data: ";
	cin >> buffer;
	b.data = new char[strlen(buffer) + 1];
	strcpy_s(b.data, strlen(buffer) + 1, buffer);*/

	/*h = inserare(h, b);
	afisare(h);
	h = extragere(h, &b);
	cout << endl << endl;*/

	//cout << "Nr ordine: " << b.ordine << "Titular cont " << b.titularBon << "Data " << b.data << endl << endl;

	afisare(h);
	nodLs* l = nullptr;
	l = conversie(h, l);
	traversareLista(l);
	dezalocareLista(l);

	//dezalocare(h);
}