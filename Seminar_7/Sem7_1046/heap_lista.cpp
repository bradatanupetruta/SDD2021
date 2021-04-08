#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

struct ProgramareVaccin {
	int prioritate;
	char* numePersoana;
	char* tipVaccin;
};

struct heap {
	ProgramareVaccin* vect;
	int nrElem;
};

//fct de filtrare
void filtrare(heap h, int indexPornire) {

	int indexRadacina = indexPornire;
	int indexStanga = 2 * indexPornire + 1;
	int indexDreapa = 2 * indexPornire + 2;

	//fac comparatie cu index stanga si apoi cu dreapta
	//dar amai fac si comparare sa vada adaca exista index stanga sau dreapta
	if (indexStanga<h.nrElem && h.vect[indexStanga].prioritate > h.vect[indexRadacina].prioritate) {
		indexRadacina = indexStanga;
	}
	if (indexDreapa < h.nrElem && h.vect[indexDreapa].prioritate>h.vect[indexRadacina].prioritate) {
		indexRadacina = indexDreapa;
	}

	if (indexPornire != indexRadacina) {
		//s-a produs dezachilibru si interschimb
		//fac shallow copy
		ProgramareVaccin aux = h.vect[indexPornire];
		h.vect[indexPornire] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;

		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, ProgramareVaccin v) {//primesc *h pt ca nu il mai returnez si pt ca vectorul se mofiica pt ca mai are spatiu pt un elem in plus si se modifica si nr de elem pt ca creste cu 1

	ProgramareVaccin* vectNou = new ProgramareVaccin[h.nrElem + 1];
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];

	vectNou[h.nrElem] = v;

	delete[] h.vect;
	//refac referinta lui h.vect ce ia valoarea lui vect nou
	h.vect = vectNou;
	h.nrElem++;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	return h;
}

heap extragere(heap h, ProgramareVaccin* p) {//pt ca se modifica tipul

	//*p pt ca returnez prin param
	ProgramareVaccin* vectNou = new ProgramareVaccin[h.nrElem - 1];
	ProgramareVaccin aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*p = h.vect[h.nrElem - 1];

	h.nrElem--;

	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	delete[] h.vect;

	h.vect = vectNou;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	return h;
}

void afisare(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		cout << "\nPrioritate = " << h.vect[i].prioritate << " ,Nume = " << h.vect[i].numePersoana <<
			" ,tip vaccine = " << h.vect[i].tipVaccin;
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		delete[] h.vect[i].numePersoana;
		delete[] h.vect[i].tipVaccin;
	}
	delete[] h.vect;
}

struct nodls {
	ProgramareVaccin inf;
	nodls* next;
};
void inserare_ls(nodls** cap, ProgramareVaccin a) {

	nodls* nou = new nodls;

	nou->inf.prioritate = a.prioritate;
	nou->inf.numePersoana = new char[strlen(a.numePersoana) + 1];
	strcpy(nou->inf.numePersoana, a.numePersoana);
	nou->inf.tipVaccin = new char[strlen(a.tipVaccin) + 1];
	strcpy(nou->inf.tipVaccin, a.tipVaccin);

	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodls* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}
void dezalocare_ls(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		nodls* temp2 = temp->next;
		delete[] temp->inf.numePersoana;
		delete[] temp->inf.tipVaccin;
		delete temp;
		temp = temp2;
	}
}
void traversare_ls(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		cout << "\nprioritate: " << temp->inf.prioritate << " ,nume persoana: " << temp->inf.numePersoana << " ,tip vaccin =" << temp->inf.tipVaccin << endl;
		temp = temp->next;
	}
}
heap conversie_heap_ls(heap h, nodls** cap) {
	ProgramareVaccin pa;

	int n = h.nrElem;
	for (int i = 0; i < n; i++) {
		h = extragere(h, &pa);
		inserare_ls(cap, pa);
	}
	delete[] pa.numePersoana;
	delete[] pa.tipVaccin;

	return h;
}

void main() {

	heap h;
	char buffer[20];

	ifstream fis("fisier.txt");
	fis >> h.nrElem;

	h.vect = new ProgramareVaccin[h.nrElem];

	for (int i = 0; i < h.nrElem; i++) {
		fis >> h.vect[i].prioritate;

		fis >> buffer;
		h.vect[i].numePersoana = new char[strlen(buffer) + 1];
		strcpy(h.vect[i].numePersoana, buffer);

		fis >> buffer;
		h.vect[i].tipVaccin = new char[strlen(buffer) + 1];
		strcpy(h.vect[i].tipVaccin, buffer);

	}
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	afisare(h);

	cout << "\n\n--------introduceti programarea-------";
	ProgramareVaccin p;
	cout << "\nPrioritate: ";
	cin >> p.prioritate;
	char buffer2[20];
	cout << "Nume: ";
	cin >> buffer;
	p.numePersoana = new char[strlen(buffer) + 1];
	strcpy(p.numePersoana, buffer);
	cout << "Tip vaccin: ";
	cin >> buffer;
	p.tipVaccin = new char[strlen(buffer) + 1];
	strcpy(p.tipVaccin, buffer);
	h = inserare(h, p);

	afisare(h);

	h = extragere(h, &p);
	cout << "\n" << p.prioritate << endl;
	afisare(h);

	//aici am dezalocat ce am alocat la inserare
	delete[] p.numePersoana;
	delete[] p.tipVaccin;

	cout << "\n\nconversie din heap in lista simpla: ";
	nodls* cap = NULL;
	h = conversie_heap_ls(h, &cap);
	traversare_ls(cap);

	dezalocare_ls(cap);

	dezalocare(h);

	fis.close();
}