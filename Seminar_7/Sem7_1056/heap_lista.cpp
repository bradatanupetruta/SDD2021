#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct ProgramareVaccinare {
	int urgenta;
	char* nume;
	char* tipVaccin;
};

struct heap {
	ProgramareVaccinare* vec;
	int nrElemente;
};

struct nodls {
	ProgramareVaccinare inf;
	nodls* next;
};

void filtrare(heap h, int index) {
	int indexRadacina = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga < h.nrElemente && h.vec[indexStanga].urgenta > h.vec[indexRadacina].urgenta) {
		indexRadacina = indexStanga;
	}
	if (indexDreapta < h.nrElemente && h.vec[indexDreapta].urgenta > h.vec[indexRadacina].urgenta) {
		indexRadacina = indexDreapta;
	}
	if (index != indexRadacina) {
		ProgramareVaccinare aux = h.vec[index];
		h.vec[index] = h.vec[indexRadacina];
		h.vec[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, ProgramareVaccinare p) {
	ProgramareVaccinare* vecNou = new ProgramareVaccinare[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++) {
		vecNou[i] = h.vec[i];
	}
	vecNou[h.nrElemente] = p;
	delete[]h.vec;
	h.nrElemente++;
	h.vec = vecNou;
	for (int i = (h.nrElemente - 1) / 2; i > 0; i--) {
		filtrare(h, i);
	}
	return h;
}
heap extragere(heap h, ProgramareVaccinare* p) {
	ProgramareVaccinare* vecNou = new ProgramareVaccinare[h.nrElemente - 1];
	ProgramareVaccinare aux = h.vec[0];
	h.vec[0] = h.vec[h.nrElemente - 1];
	h.vec[h.nrElemente - 1] = aux;
	*p = h.vec[h.nrElemente - 1];
	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++) {
		vecNou[i] = h.vec[i];
	}
	delete[]h.vec;
	h.vec = vecNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;

}
void afisare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		cout << "Urgenta: " << h.vec[i].urgenta << " Nume: " << h.vec[i].nume << " Tip vaccin: " << h.vec[i].tipVaccin << endl;
	}
}
void dezalocare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		delete[]h.vec[i].nume;
		delete[]h.vec[i].tipVaccin;
	}
	delete[] h.vec;
}
nodls* inserareLista(nodls* cap, ProgramareVaccinare p) {
	nodls* nou = new nodls;
	nou->inf.urgenta = p.urgenta;
	nou->inf.nume = new char[strlen(p.nume) + 1];
	strcpy(nou->inf.nume, p.nume);
	nou->inf.tipVaccin = new char[strlen(p.tipVaccin) + 1];
	strcpy(nou->inf.tipVaccin, p.tipVaccin);
	nou->next = NULL;

	if (cap == NULL) {
		cap = nou;
	}
	else {
		nodls* temp = cap;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	return cap;
}


void traversare(nodls* cap) {
	nodls* temp = cap;
	while (temp != nullptr) {
		cout << "Urgenta: " << temp->inf.urgenta << " Nume: " << temp->inf.nume << " Tip vaccin: " << temp->inf.tipVaccin << endl;
		temp = temp->next;
	}
}
void dezalocare(nodls* cap) {
	nodls* temp = cap;
	while (temp != nullptr) {
		nodls* temp2 = temp->next;
		delete[]temp->inf.nume;
		delete[] temp->inf.tipVaccin;
		delete temp;
		temp = temp2;
	}
}
nodls* conversie(heap h, nodls* cap) {
	ProgramareVaccinare p;
	int numarElem = h.nrElemente;
	for (int i = 0; i < numarElem; i++) {
		h = extragere(h, &p);
		cap = inserareLista(cap, p);
	}
	return cap;
}
void main() {
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vec = new ProgramareVaccinare[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++) {
		f >> h.vec[i].urgenta;
		f >> buffer;
		h.vec[i].nume = new char[strlen(buffer) + 1];
		strcpy(h.vec[i].nume, buffer);
		f >> buffer;
		h.vec[i].tipVaccin = new char[strlen(buffer) + 1];
		strcpy(h.vec[i].tipVaccin, buffer);
	}
	f.close();

	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisare(h);

	ProgramareVaccinare p;
	cout << "Urgenta:"; cin >> p.urgenta;
	cout << "Nume: "; cin >> buffer;
	p.nume = new char[strlen(buffer) + 1];
	strcpy(p.nume, buffer);
	cout << "Tip vaccin: "; cin >> buffer;
	p.tipVaccin = new char[strlen(buffer) + 1];
	strcpy(p.tipVaccin, buffer);

	//h = inserare(h, p);
	cout << endl;
	afisare(h);

	//h = extragere(h, &p);
	//cout << "Elementul extras are urgenta: " << p.urgenta;
	cout << endl;
	//afisare(h);


	nodls* cap = NULL;
	//cap = inserareLista(cap, p);
	cap = conversie(h, cap);
	cout << endl << endl;

	traversare(cap);
	dezalocare(cap);

}