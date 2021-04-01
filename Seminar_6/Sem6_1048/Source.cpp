#include <iostream>
#include <fstream>
using namespace std;

struct Angajat
{
	int cod;
	char* nume;
	float salariu;
};

struct nodArb
{
	Angajat inf;
	nodArb* stanga, * dreapta;
};

nodArb* creareNod(Angajat a, nodArb* st, nodArb* dr)
{
	nodArb* nou = new nodArb;
	nou->inf.cod = a.cod;
	nou->inf.nume = new char[strlen(a.nume) + 1];
	strcpy_s(nou->inf.nume, strlen(a.nume) + 1, a.nume);
	nou->inf.salariu = a.salariu;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(Angajat a, nodArb* rad)
{
	nodArb* temp = rad;
	if (rad == nullptr)
	{
		temp = creareNod(a, nullptr, nullptr);
		return temp;
	}
	else
	{
		while (true)
		{
			if (a.cod < temp->inf.cod)
			{
				if (temp->stanga != nullptr)
				{
					temp = temp->stanga;
				}
				else
				{
					temp->stanga = creareNod(a, nullptr, nullptr);
					return rad;
				}
			}
			else
				if (a.cod > temp->inf.cod)
				{
					if (temp->dreapta != nullptr)
					{
						temp = temp->dreapta;
					}
					else
					{
						temp->dreapta = creareNod(a, nullptr, nullptr);
						return rad;
					}
				}
				else
					return rad;
		}
	}
}

void traversarePreOrdine(nodArb* rad)
{
	if (rad != nullptr)
	{
		cout << "Codul " << rad->inf.cod << " numele " << rad->inf.nume << " salariul " << rad->inf.salariu << endl;
		traversarePreOrdine(rad->stanga);
		traversarePreOrdine(rad->dreapta);
	}
}

void traversareInOrdine(nodArb* rad)
{
	if (rad != nullptr)
	{
		traversareInOrdine(rad->stanga);
		cout << "Codul " << rad->inf.cod << " numele " << rad->inf.nume << " salariul " << rad->inf.salariu << endl;
		traversareInOrdine(rad->dreapta);
	}
}

void traversarePostOrdine(nodArb* rad)
{
	if (rad != nullptr)
	{
		traversarePostOrdine(rad->stanga);
		traversarePostOrdine(rad->dreapta);
		cout << "Codul " << rad->inf.cod << " numele " << rad->inf.nume << " salariul " << rad->inf.salariu << endl;
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != nullptr)
	{
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		delete[] rad->inf.nume;
		delete rad;
		dezalocare(st);
		dezalocare(dr);
	}
}

void angajatiSalPesteVal(nodArb* rad, Angajat* vect, int* nr, int prag)
{
	if (rad != nullptr)
	{
		if (rad->inf.salariu > prag)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		angajatiSalPesteVal(rad->stanga, vect, nr, prag);
		angajatiSalPesteVal(rad->dreapta, vect, nr, prag);
	}
}

void main()
{
	int n;
	char buffer[20];
	nodArb* rad = nullptr;
	Angajat a;
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> a.cod;
		f >> buffer;
		a.nume = new char[strlen(buffer) + 1];
		strcpy_s(a.nume, strlen(buffer) + 1, buffer);
		f >> a.salariu;
		rad = inserareNod(a, rad);
		delete[] a.nume;
	}
	f.close();

	traversareInOrdine(rad);
	cout << endl;
	traversarePostOrdine(rad);
	cout << endl;
	traversarePreOrdine(rad);
	cout << endl;

	Angajat* vect = new Angajat[n];
	int nr = 0;
	angajatiSalPesteVal(rad, vect, &nr, 1850);
	for (int i = 0; i < nr; i++)
	{
		cout << "Codul " << vect[i].cod << " numele " << vect[i].nume << " salariul " << vect[i].salariu << endl;
	}
	delete[] vect;

	dezalocare(rad);
}