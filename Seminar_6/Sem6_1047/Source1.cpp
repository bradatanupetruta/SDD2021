#include<iostream>
#include<fstream>
using namespace std;

struct carte {

	int cod;
	char* editura;
	float pret;
	int an;
};

struct nodArb {
	carte inf;
	nodArb* stanga, * dreapta;
};

nodArb* creareNod(carte c, nodArb* st, nodArb* dr) {
	nodArb* nou = new nodArb;
	nou->inf.cod = c.cod;
	nou->inf.editura = new char[strlen(c.editura) + 1];
	strcpy_s(nou->inf.editura, strlen(c.editura) + 1, c.editura);
	nou->inf.pret = c.pret;
	nou->inf.an = c.an;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(carte c, nodArb* rad) {
	nodArb* temp = rad;
	if (rad == nullptr) {
		temp = creareNod(c, nullptr, nullptr);
		return temp;
	}
	else {
		while (true) {
			if (c.cod < temp->inf.cod) {
				if (temp->stanga != nullptr) {
					temp = temp->stanga;
				}
				else {
					temp->stanga = creareNod(c, nullptr, nullptr);
					return rad;
				}
			}
			else if (c.cod > temp->inf.cod) {
				if (temp->dreapta != nullptr) {
					temp = temp->dreapta;
				}
				else {
					temp->dreapta = creareNod(c, nullptr, nullptr);
					return rad;
				}
			}
			else { return rad; }
		}
	}
}

void traversarePreordine(nodArb* rad) {
	if (rad != nullptr) {
		cout << "Cod  " << rad->inf.cod << "  editura " << rad->inf.editura
			<< "  pretul  " << rad->inf.pret << " an "
			<< rad->inf.an << endl;
		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);
	}
}

void traversareInordine(nodArb* rad) {
	if (rad != nullptr) {
		traversareInordine(rad->stanga);
		cout << "Cod  " << rad->inf.cod << "  editura " << rad->inf.editura
			<< "  pretul  " << rad->inf.pret << " an "
			<< rad->inf.an << endl;
		traversareInordine(rad->dreapta);
	}
}

void traversarePostordine(nodArb* rad) {
	if (rad != nullptr) {
		traversarePostordine(rad->stanga);
		traversarePostordine(rad->dreapta);
		cout << "Cod  " << rad->inf.cod << "  editura " << rad->inf.editura
			<< "  pretul  " << rad->inf.pret << " an "
			<< rad->inf.an << endl;
	}
}

void dezalocare(nodArb* rad) {
	if (rad != nullptr) {
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		delete[] rad->inf.editura;
		delete rad;
		dezalocare(st);
		dezalocare(dr);
	}
}

void cartiMaiTarziuDe2018(nodArb* rad, nodArb** aux) {

	if (rad != nullptr) {
		if (rad->inf.an > 2018) {

			*aux = inserareNod(rad->inf, *aux);
		}
		cartiMaiTarziuDe2018(rad->stanga, aux);
		cartiMaiTarziuDe2018(rad->dreapta, aux);
	}
}

void main() {
	int n;
	char buffer[20];
	carte c;
	nodArb* rad = nullptr;
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> c.cod;
		f >> buffer;
		c.editura = new char[strlen(buffer) + 1];
		strcpy_s(c.editura, strlen(buffer) + 1, buffer);
		f >> c.pret;
		f >> c.an;
		rad = inserareNod(c, rad);
		delete[]c.editura;
	}
	f.close();

	cout << "--preordine" << endl;
	traversarePreordine(rad);
	cout << endl << "--inordine" << endl;
	traversareInordine(rad);
	cout << endl << "--postordine" << endl;
	traversarePostordine(rad);
	cout << endl;

	nodArb* aux = nullptr;
	cartiMaiTarziuDe2018(rad, &aux);
	cout << endl << "carti functie" << endl;

	traversarePostordine(aux);

	dezalocare(rad);
	dezalocare(aux);
}