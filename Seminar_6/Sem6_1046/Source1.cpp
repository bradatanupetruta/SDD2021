#include <iostream>
#include <fstream>

using namespace std;

struct produs
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodarb
{
	produs inf;
	nodarb* stanga, * dreapta;
};

nodarb* creare_nod(produs, nodarb*, nodarb*);
nodarb* inserare_nod(produs, nodarb*);
void traversare_preordine(nodarb*);
void traversare_inordine(nodarb*);
void traversare_postordine(nodarb*);
void dezalocare(nodarb*);
nodarb* cautare(nodarb*, int);
int maxim(int, int);
int nr_niveluri(nodarb*);

int main(void)
{
	int n;
	produs p;
	ifstream f("fisier.txt");
	char buffer[20];
	nodarb* rad = NULL;

	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> p.cod;
		f >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
		f >> p.pret;
		f >> p.cantitate;

		rad = inserare_nod(p, rad);

		delete[] p.denumire;
	}
	f.close();

	cout << "Preordine: " << endl;
	traversare_preordine(rad);
	cout << endl << "Postordine: " << endl;
	traversare_postordine(rad);
	cout << endl << "Inordine: " << endl;
	traversare_inordine(rad);
	nodarb* gasit = NULL;
	cout << endl << "Gasit: " << endl;
	gasit = cautare(rad, 7);
	if (gasit != NULL)
	{
		cout << "Cod = " << gasit->inf.cod << ", denumire = " << gasit->inf.denumire << ", pret = "
			<< gasit->inf.pret << ", cantitate = " << gasit->inf.cantitate << "." << endl;
	}
	cout << endl << "Inaltime: ";
	cout << nr_niveluri(rad) << endl;
	int grad_echilibru = nr_niveluri(rad->dreapta) - nr_niveluri(rad->stanga);
	if (grad_echilibru <= 1)
	{
		cout << "Arborele este echilibrat grad: " << grad_echilibru << endl;
	}
	else
	{
		cout << "Nu este echilibrat grad: " << grad_echilibru << endl;
	}
	dezalocare(rad);
}

nodarb* creare_nod(produs p, nodarb* stanga, nodarb* dreapta)
{
	nodarb* nou = new nodarb;
	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(p.denumire) + 1, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;
}

nodarb* inserare_nod(produs p, nodarb* rad)
{
	nodarb* tmp = rad;

	if (rad == NULL) {
		tmp = creare_nod(p, NULL, NULL);
		return tmp;
	}
	else
	{
		while (true)
		{
			if (p.cod < tmp->inf.cod)
			{
				if (tmp->stanga != NULL)
				{
					tmp = tmp->stanga;
				}
				else
				{
					tmp->stanga = creare_nod(p, NULL, NULL);
					return rad;
				}
			}
			else if (p.cod > tmp->inf.cod)
			{
				if (tmp->dreapta != NULL)
				{
					tmp = tmp->dreapta;
				}
				else
				{
					tmp->dreapta = creare_nod(p, NULL, NULL);
					return rad;
				}
			}
			else {
				return rad;
			}
		}
	}
}

void traversare_preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		cout << "Cod = " << rad->inf.cod << ", denumire = " << rad->inf.denumire << ", pret = "
			<< rad->inf.pret << ", cantitate = " << rad->inf.cantitate << "." << endl;
		traversare_preordine(rad->stanga);
		traversare_preordine(rad->dreapta);
	}
}

void traversare_inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		traversare_preordine(rad->stanga);
		cout << "Cod = " << rad->inf.cod << ", denumire = " << rad->inf.denumire << ", pret = "
			<< rad->inf.pret << ", cantitate = " << rad->inf.cantitate << "." << endl;
		traversare_preordine(rad->dreapta);
	}
}

void traversare_postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		traversare_preordine(rad->stanga);
		traversare_preordine(rad->dreapta);
		cout << "Cod = " << rad->inf.cod << ", denumire = " << rad->inf.denumire << ", pret = "
			<< rad->inf.pret << ", cantitate = " << rad->inf.cantitate << "." << endl;
	}
}

nodarb* cautare(nodarb* rad, int cod)
{
	if (rad != NULL)
	{
		if (rad->inf.cod == cod)
		{
			return rad;
		}
		else if (rad->inf.cod > cod)
		{
			return cautare(rad->stanga, cod);
		}
		else
		{
			return cautare(rad->dreapta, cod);
		}
	}
	return NULL;
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b) max = b;
	return max;
}

int nr_niveluri(nodarb* rad)
{
	if (rad != NULL)
	{
		int st = nr_niveluri(rad->stanga);
		int dr = nr_niveluri(rad->dreapta);
		return 1 + maxim(st, dr);
	}
	else
	{
		return 0;
	}
}

void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* stanga = rad->stanga;
		nodarb* dreapta = rad->dreapta;

		delete[] rad->inf.denumire;
		delete rad;
		dezalocare(stanga);
		dezalocare(dreapta);
	}
}