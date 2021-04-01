#include<iostream>
#include<fstream>
using namespace std;

struct Persoana {
	int cod;
	char* nume;
	int varsta;
};

struct NodArb {
	Persoana inf;
	NodArb* stanga, * dreapta;
};

NodArb* creareNod(Persoana p, NodArb* st, NodArb* dr)
{
	NodArb* nou = new NodArb();
	nou->inf.cod = p.cod;
	nou->inf.nume = new char[strlen(p.nume) + 1];
	strcpy_s(nou->inf.nume, strlen(p.nume) + 1, p.nume);
	nou->inf.varsta = p.varsta;

	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}

NodArb* inserareNod(Persoana p, NodArb* rad)
{
	NodArb* temp = rad;
	if (rad == nullptr)
	{
		temp = creareNod(p, nullptr, nullptr);
		return temp;
	}
	else
	{
		while (true)
		{
			if (p.cod < temp->inf.cod)
			{
				if (temp->stanga != nullptr)
				{
					temp = temp->stanga;
				}
				else
				{
					temp->stanga = creareNod(p, nullptr, nullptr);
					return rad;
				}
			}
			else
				if (p.cod > temp->inf.cod)
				{
					if (temp->dreapta != nullptr)
					{
						temp = temp->dreapta;
					}
					else
					{
						temp->dreapta = creareNod(p, nullptr, nullptr);
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

void traversarePreordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		cout << "Cod= " << rad->inf.cod << " nume= " << rad->inf.nume << " varsta= " << rad->inf.varsta << endl;
		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);

	}
}

void traversareInordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		traversareInordine(rad->stanga);
		cout << "Cod= " << rad->inf.cod << " nume= " << rad->inf.nume << " varsta= " << rad->inf.varsta << endl;
		traversareInordine(rad->dreapta);
	}
}

void traversarePostordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		traversarePostordine(rad->stanga);
		traversarePostordine(rad->dreapta);
		cout << "Cod= " << rad->inf.cod << " nume= " << rad->inf.nume << " varsta= " << rad->inf.varsta << endl;
	}
}

void dezalocare(NodArb* rad)
{
	if (rad != nullptr)
	{
		NodArb* st = rad->stanga;
		NodArb* dr = rad->dreapta;

		delete[] rad->inf.nume;
		delete rad;
		dezalocare(st);
		dezalocare(dr);
	}
}

NodArb* cautare(NodArb* rad, int cod)
{
	if (rad != nullptr)
	{
		if (cod == rad->inf.cod)
		{
			return rad;
		}
		else
		{
			if (cod < rad->inf.cod)
			{
				return cautare(rad->stanga, cod);
			}
			else
			{
				return cautare(rad->dreapta, cod);
			}
		}
	}
	else
	{
		return nullptr;
	}
}

void main() {
	int n;
	char buffer[20];
	Persoana p;
	NodArb* rad = nullptr;
	ifstream f("fisier.txt");

	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> p.cod;
		f >> buffer;
		p.nume = new char[strlen(buffer) + 1];
		strcpy_s(p.nume, strlen(buffer) + 1, buffer);
		f >> p.varsta;
		rad = inserareNod(p, rad);
		delete[]  p.nume;
	}
	f.close();

	traversarePreordine(rad);
	cout << endl;
	traversareInordine(rad);
	cout << endl;
	traversarePostordine(rad);
	cout << endl;

	NodArb* cautat = cautare(rad, 6);
	if (cautat != nullptr)
	{
		cout << "Cod= " << cautat->inf.cod << " nume= " << cautat->inf.nume << " varsta= " << cautat->inf.varsta << endl;
	}
	else
	{
		cout << "Nu exista" << endl;
	}
	dezalocare(rad);
}