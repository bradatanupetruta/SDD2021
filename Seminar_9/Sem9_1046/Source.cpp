#include<iostream>
#include<fstream>
using namespace std;

struct Produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct NodArb {
	Produs inf;
	NodArb* stanga, * dreapta;
};

//pas 1 - crearea nod
NodArb* creareNod(Produs p, NodArb* st, NodArb* dr) {
	NodArb* nou = new NodArb;
	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(p.denumire) + 1, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}

//pasul 2 - inserare pe poz coresp
NodArb* inserareNod(Produs p, NodArb* rad) {
	NodArb* aux = rad;

	if (rad == nullptr) {
		aux = creareNod(p, nullptr, nullptr);
		return aux;
	}
	else {
		while (true) {
			if (p.cod < aux->inf.cod) { //ramura st
				if (aux->stanga != nullptr) {
					aux = aux->stanga;
				}
				else {
					aux->stanga = creareNod(p, nullptr, nullptr);
					return rad;
				}
			}
			else if (p.cod > aux->inf.cod) { //ramura dr
				if (aux->dreapta != nullptr) {
					aux = aux->dreapta;
				}
				else {
					aux->dreapta = creareNod(p, nullptr, nullptr);
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
void traversarePreordine(NodArb* rad) {
	if (rad != nullptr) {
		cout << "\nCod= " << rad->inf.cod << ", Denumire= " << rad->inf.denumire << ", Pret= " << rad->inf.pret << ", Cantitate= " << rad->inf.cantitate;

		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);
	}
}

//inordine
void traversareInordine(NodArb* rad) {
	if (rad != nullptr) {
		traversareInordine(rad->stanga);

		cout << "\nCod= " << rad->inf.cod << ", Denumire= " << rad->inf.denumire << ", Pret= " << rad->inf.pret << ", Cantitate= " << rad->inf.cantitate;

		traversareInordine(rad->dreapta);
	}
}

//postordine
void traversarePostordine(NodArb* rad) {
	if (rad != nullptr) {
		traversarePostordine(rad->stanga);

		traversarePostordine(rad->dreapta);

		cout << "\nCod= " << rad->inf.cod << ", Denumire= " << rad->inf.denumire << ", Pret= " << rad->inf.pret << ", Cantitate= " << rad->inf.cantitate;

	}
}

//dezalocare
void dezalocare(NodArb* rad) {
	if (rad != nullptr) {
		NodArb* st = rad->stanga;
		NodArb* dr = rad->dreapta;

		delete[] rad->inf.denumire;
		delete rad;

		dezalocare(st);
		dezalocare(dr);
	}
}

void main() {
	int n;
	Produs p;
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	char  buffer[20];
	NodArb* rad = nullptr;

	for (int i = 0; i < n; i++) {
		f >> p.cod;

		f >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);

		f >> p.pret;

		f >> p.cantitate;

		rad = inserareNod(p, rad);

		delete[] p.denumire;
	}
	f.close();


	cout << "\n--- PREordine ---";
	traversarePreordine(rad);

	cout << "\n--- INordine ---";
	traversareInordine(rad);

	cout << "\n--- POSTordine ---";
	traversarePostordine(rad);

	dezalocare(rad);
}