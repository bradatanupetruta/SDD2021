#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct carte {
	int cod;
	char* editura;
	float pret;
	int an_publicare;
};

struct NodArb
{
	carte inf;
	NodArb* st, * dr;
};

NodArb* creareNod(carte c, NodArb* st, NodArb* dr)
{
	NodArb* nou = new NodArb;
	nou->inf.cod = c.cod;
	nou->inf.editura = new char[strlen(c.editura) + 1];
	strcpy(nou->inf.editura, c.editura);
	nou->inf.pret = c.pret;
	nou->inf.an_publicare = c.an_publicare;
	nou->st = st;
	nou->dr = dr;

	return nou;
}

NodArb* inserareNod(carte c, NodArb* rad) {
	NodArb* temp = rad;
	if (rad == nullptr) {
		temp = creareNod(c, nullptr, nullptr);
		return temp;
	}
	else {
		while (true) {
			if (c.cod < temp->inf.cod)
			{
				if (temp->st != nullptr) temp = temp->st;
				else
				{
					temp->st = creareNod(c, nullptr, nullptr);
					return rad;
				}
			}
			else
			{
				if (c.cod > temp->inf.cod)
				{
					if (temp->dr != nullptr) temp = temp->dr;
					else
					{
						temp->dr = creareNod(c, nullptr, nullptr);
						return rad;
					}
				}
				else
				{
					return rad;
				}
			}
		}

	}
}

void traversarePreordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		cout << "PREORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;
		traversarePreordine(rad->st);
		traversarePreordine(rad->dr);

	}
}

void traversareInordine(NodArb* rad)
{
	if (rad != nullptr)
	{

		traversareInordine(rad->st);
		cout << "INORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;
		traversareInordine(rad->dr);

	}
}

void traversarePostordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		traversarePostordine(rad->st);
		traversarePostordine(rad->dr);
		cout << "POSTORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;

	}
}

void determinareCarti(NodArb* rad, int an, carte* vect, int* nr)
{
	if (rad != nullptr)
	{
		if (rad->inf.an_publicare > an)
		{
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].editura = new char[strlen(rad->inf.editura) + 1];
			strcpy(vect[*nr].editura, rad->inf.editura);
			vect[*nr].pret = rad->inf.pret;
			vect[*nr].an_publicare = rad->inf.an_publicare;
			(*nr)++;
		}
		determinareCarti(rad->st, an, vect, nr);
		determinareCarti(rad->dr, an, vect, nr);
	}
}

void dezalocare(NodArb* rad)
{
	if (rad != nullptr)
	{
		NodArb* st = rad->st;
		NodArb* dr = rad->dr;
		delete[] rad->inf.editura;
		delete rad;

		dezalocare(st);
		dezalocare(dr);
	}
}

void dezalocareVector(carte* vect, int n) {
	for (int i = 0; i < n; i++) {
		delete[] vect[i].editura;
	}
	delete vect;
}

void main()
{
	int n;
	char buffer[20];
	NodArb* rad = nullptr;
	carte c;
	ifstream f;
	f.open("fisier.txt");
	f >> n;

	for (int i = 0; i < n; i++)
	{
		f >> c.cod;
		f >> buffer;
		c.editura = new char[strlen(buffer) + 1];
		strcpy(c.editura, buffer);
		f >> c.pret;
		f >> c.an_publicare;
		rad = inserareNod(c, rad);

		delete[] c.editura;
	}
	f.close();

	traversarePreordine(rad);
	cout << endl;
	traversareInordine(rad);
	cout << endl;
	traversarePostordine(rad);

	cout << endl << "==========Cartile publicate dupa 2018==========";
	carte* vectorCarti = new carte[n];
	n = 0;
	determinareCarti(rad, 2018, vectorCarti, &n);
	for (int i = 0; i < n; i++)
	{
		cout << "\nCod= " << vectorCarti[i].cod << ", Editura: " << vectorCarti[i].editura << ", Pret: " << vectorCarti[i].pret << ", An publicare: " << vectorCarti[i].an_publicare << endl;
	}

	//dezaloc vect
	dezalocareVector(vectorCarti, n);

	dezalocare(rad);
}
