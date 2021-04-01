#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;



//arbori
struct produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodArb {
	produs inf;
	nodArb* stanga;
	nodArb* dreapta;
};
//pas 1 - creare nod
nodArb* creareNod(nodArb* stanga, nodArb* dreapta, produs p) {

	nodArb* nou = new nodArb;

	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->dreapta = stanga;
	nou->stanga = dreapta;

	return nou;
}
//pas 2 - inserarea pe pozitia corespunzatoare
nodArb* inserare(produs p, nodArb* rad) {

	nodArb* aux = rad; //ma ajuta sa explorez toata nodurile mai intai pozitionandu-se pe rad si apoi trecand de la nod la nod
	if (rad == NULL) {
		aux = creareNod(NULL, NULL, p);
		return aux; //returneaza un singur nod
	}
	else {
		//caut pozitia unde vreau sa inserez
		while (true) {
			if (p.cod < aux->inf.cod) {
				//verif daca exista fiu in stanga
				if (aux->stanga) {
					aux = aux->stanga;
				}
				else {
					aux->stanga = creareNod(NULL, NULL, p);
					return rad; 
				}
			}
			else if (p.cod > aux->inf.cod) {
				//verif daca exista fiu in dreapta
				if (aux->dreapta) {
					aux = aux->dreapta;
				}
				else {
					aux->dreapta = creareNod(NULL, NULL, p);
					return rad; 
				}
			}
			else {
				return rad; //cheie duplicata
			}
		}
	}
}

//preordine
void traversare_preordine(nodArb* rad) {
	if (rad) {
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate;
		traversare_preordine(rad->stanga);
		traversare_preordine(rad->dreapta);
	}
}

//practic le sorteaza
void traversare_inordine(nodArb* rad) {
	if (rad) {
		traversare_inordine(rad->stanga);
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate;
		traversare_inordine(rad->dreapta);
	}
}

void traversare_postordine(nodArb* rad) {
	if (rad) {
		traversare_postordine(rad->stanga);
		traversare_postordine(rad->dreapta);
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate;

	}
}

void dezalocare(nodArb* rad) {

	if (rad) {
		//salvez copiii pt a nu ii pierde
		nodArb* stang = rad->stanga;
		nodArb* drep = rad->dreapta;

		delete[] rad->inf.denumire;
		delete rad;

		dezalocare(stang);
		dezalocare(drep);
	}
}

//fct de cautare
nodArb* cautare(nodArb* rad, int cheie) {
	if (rad) {
		if (rad->inf.cod == cheie) {
			return rad;
		}
		else {
			if (rad->inf.cod > cheie) {
				return cautare(rad->stanga, cheie);
			}
			else
				return cautare(rad->dreapta, cheie);

		}
	}
	return NULL;
}

//determinam numarul de niveluri ale arborelui
int maxim(int a, int b) {

	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}

int nr_niveluri(nodArb* rad) {
	if (rad) {

		int s = nr_niveluri(rad->stanga);
		int dr = nr_niveluri(rad->dreapta);
		return 1 + maxim(s, dr);

		//return 1 + maxim(nr_niveluri(rad->stanga), nr_niveluri(rad->dreapta));
	}
	else {
		return 0;
	}
}

//fct ce det elem din arb care au pret > de un prag
void detElem(nodArb* rad, produs* vect, int* nr, float prag) {
	if (rad) {
		if (rad->inf.pret > prag) {
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].denumire = new char[strlen(rad->inf.denumire) + 1];
			strcpy(vect[*nr].denumire, rad->inf.denumire);
			vect[*nr].pret = rad->inf.pret;
			vect[*nr].cantitate = rad->inf.cantitate;
			(*nr)++;
		}
		detElem(rad->stanga, vect, nr, prag);
		detElem(rad->dreapta, vect, nr, prag);
	}
}

void main() {

	nodArb* rad = NULL;

	int nrProduse;
	char buffer[20];
	produs p;

	ifstream fis;
	fis.open("fisier.txt");
	fis >> nrProduse;

	for (int i = 0; i < nrProduse; i++) {

		fis >> p.cod;
		fis >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);
		fis >> p.pret;
		fis >> p.cantitate;

		rad = inserare(p, rad);

		delete[] p.denumire;
	}
	fis.close();

	cout << "-------preordine-----";
	traversare_preordine(rad);

	cout << "\n-------inordine-----";
	traversare_inordine(rad);

	cout << "\n-------postordine-----";
	traversare_postordine(rad);

	cout << "\n-------cautare-----";
	nodArb* gasit = NULL;
	gasit = cautare(rad, 6);
	if (gasit) {
		cout << "\ncod: " << gasit->inf.cod << " ,denumire: " << gasit->inf.denumire <<
			" ,pret: " << gasit->inf.pret << " ,cantitate: " << gasit->inf.cantitate;
	}
	else {
		cout << "\nnodul nu exista!\n";
	}

	cout << "\n-------nr niveluri arbore = inaltime arbore-----";
	cout << nr_niveluri(rad);

	cout << "\n\n";
	int gradEchilibru = nr_niveluri(rad->dreapta) - nr_niveluri(rad->stanga);
	if (gradEchilibru <= 1) {
		cout << "\narbore echilibrat, grad echilibru: " << gradEchilibru;
	}
	else {
		cout << "\nnu este echilibrat\n";
	}

	cout << "\n\n----det---:\n";
	produs* v = new produs[nrProduse];
	int dim = 0;
	detElem(rad, v, &dim, 5);
	for (int i = 0; i < dim; i++) {
		cout << "\ncod: " << v[i].cod << " ,denumire: " << v[i].denumire <<
			" ,pret: " << v[i].pret << " ,cantitate: " << v[i].cantitate;
	}
	for (int i = 0; i < dim; i++) {
		delete[] v[i].denumire;
	}
	delete[] v;

	dezalocare(rad);
}