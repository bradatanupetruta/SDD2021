#include <iostream>
#include <fstream>
using namespace std;

struct departament
{
	int cod;
	char* denumire;
	int nrAngajati;
};

struct nodArb
{
	departament inf;
	nodArb* stanga, * dreapta;
};

nodArb* creareNod(departament d, nodArb* st, nodArb* dr)
{
	nodArb* nou = new nodArb;
	nou->inf.cod = d.cod;
	nou->inf.denumire = new char[strlen(d.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(d.denumire) + 1, d.denumire);
	nou->inf.nrAngajati = d.nrAngajati;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(departament d, nodArb* rad)
{
	nodArb* temp = rad;
	if (rad == nullptr)
	{
		temp = creareNod(d, nullptr, nullptr);
		return temp;
	}
	else
	{
		while (true)
		{
			if (d.cod < temp->inf.cod) {
				if (temp->stanga != nullptr) {
					temp = temp->stanga;
				}
				else {
					temp->stanga = creareNod(d, nullptr, nullptr);
					return rad;
				}
			}
			else if (d.cod > temp->inf.cod) {
				if (temp->dreapta != nullptr) {
					temp = temp->dreapta;
				}
				else {
					temp->dreapta = creareNod(d, nullptr, nullptr);
					return rad;
				}
			}
			else {
				return rad;
			}
		}
	}
}

void traversarePreordine(nodArb* rad) {
	if (rad != nullptr) {
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " << rad->inf.nrAngajati << endl;
		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);
	}
}

void traversareInordine(nodArb* rad) {
	if (rad != nullptr) {
		traversareInordine(rad->stanga);
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " << rad->inf.nrAngajati << endl;
		traversareInordine(rad->dreapta);
	}
}

void traversarePostordine(nodArb* rad) {
	if (rad != nullptr) {
		traversarePostordine(rad->stanga);
		traversarePostordine(rad->dreapta);
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " << rad->inf.nrAngajati << endl;
	}
}

void dezalocare(nodArb* rad) {
	if (rad != nullptr) {
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		delete[]rad->inf.denumire;
		delete rad;
		dezalocare(st);
		dezalocare(dr);
	}
}

nodArb* cautare(nodArb* rad, int cod) {
	if (rad != nullptr) {
		if (cod == rad->inf.cod) {
			return rad;
		}
		else {
			if (cod < rad->inf.cod) {
				return cautare(rad->stanga, cod);
			}
			else {
				return cautare(rad->dreapta, cod);
			}
		}
	}
	else {
		return nullptr;
	}
}

void departCuAngPestePrag(nodArb* rad, nodArb** rad2, int prag)
{
	if (rad != nullptr)
	{
		if (rad->inf.nrAngajati > prag)
			*rad2 = inserareNod(rad->inf, *rad2);
		departCuAngPestePrag(rad->stanga, rad2, prag);
		departCuAngPestePrag(rad->dreapta, rad2, prag);
	}
}

void departCuAngPestePragVector(nodArb* rad, departament* vect, int* nr, int prag)
{
	if (rad != nullptr)
	{
		if (rad->inf.nrAngajati > prag)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		departCuAngPestePragVector(rad->stanga, vect, nr, prag);
		departCuAngPestePragVector(rad->dreapta, vect, nr, prag);
	}
}

void main() {
	int n;
	departament d;
	char buffer[20];
	nodArb* rad = nullptr;
	ifstream f("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> d.cod;
		f >> buffer;
		d.denumire = new char[strlen(buffer) + 1];
		strcpy_s(d.denumire, strlen(buffer) + 1, buffer);
		f >> d.nrAngajati;
		rad = inserareNod(d, rad);
		delete[]d.denumire;
	}
	f.close();
	traversareInordine(rad);
	cout << endl;
	traversarePreordine(rad);
	cout << endl;
	traversarePostordine(rad);
	cout << endl;
	nodArb* cautat = cautare(rad, 7);
	if (cautat != nullptr) {
		cout << "Cod: " << cautat->inf.cod << " Denumire: " << cautat->inf.denumire << " Nr angajati: " << cautat->inf.nrAngajati << endl;
	}

	cout << endl;

	nodArb* rad2 = nullptr;
	departCuAngPestePrag(rad, &rad2, 10);
	traversareInordine(rad2);
	dezalocare(rad2);

	cout << endl;

	departament* vect = new departament[n];
	int nr = 0;
	departCuAngPestePragVector(rad, vect, &nr, 10);
	for(int i=0;i<nr;i++)
		cout << "Cod: " << vect[i].cod << " Denumire: " << vect[i].denumire << " Nr angajati: " << vect[i].nrAngajati << endl;
	delete[] vect;

	dezalocare(rad);
}