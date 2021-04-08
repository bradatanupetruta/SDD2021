#include <iostream>
#include <fstream>
using namespace std;

struct comanda_mancare
{
	int timp_asteptare;
	char* nume_livrator;
	float pret;
};

//LISTA
struct nod
{
	comanda_mancare* cm;
	nod* next;
};

struct heap
{
	comanda_mancare* vect;
	int nr;
};

//HEAP:
void filtrare(heap h, int index);
heap inserare(heap h, comanda_mancare cm);
heap extragere(heap h, comanda_mancare* cm);
void afisare(heap h);
void dezalocare(heap h);

//LISTA: 
nod* inserare_lista(nod* cap, comanda_mancare* cm);
void traversare_lista(nod* cap);
void dezalocare_lista(nod* cap);

int main()
{
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nr;
	h.vect = new comanda_mancare[h.nr];
	for (int i = 0; i < h.nr; i++)
	{
		f >> h.vect[i].timp_asteptare;
		f >> buffer;
		h.vect[i].nume_livrator = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].nume_livrator, strlen(buffer) + 1, buffer);
		f >> h.vect[i].pret;
	}
	f.close();
	for (int i = (h.nr - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	afisare(h);
	comanda_mancare c;
	cout << "Timp asteptare: ";
	cin >> c.timp_asteptare;
	cout << "nume livrator: ";
	cin >> buffer;
	c.nume_livrator = new char[strlen(buffer) + 1];
	strcpy_s(c.nume_livrator, strlen(buffer) + 1, buffer);
	cout << "Pret: ";
	cin >> c.pret;

	h = inserare(h, c);
	cout << endl;
	afisare(h);

	h = extragere(h, &c);
	cout << "Comanda extrasa are timpul " << c.timp_asteptare << endl;
	afisare(h);

	cout << endl << "LISTA" << endl;
	nod* cap = nullptr;

	int limit = h.nr;
	for (int i = 0; i < limit; i++)
	{
		h = extragere(h, &c);
		cap = inserare_lista(cap, &c);
	}
	traversare_lista(cap);
	dezalocare_lista(cap);
	dezalocare(h);
}

void filtrare(heap h, int index)
{
	int rad = index;
	int stanga = 2 * index + 1;
	int dreapta = 2 * index + 2;
	if (stanga < h.nr && h.vect[stanga].timp_asteptare > h.vect[rad].timp_asteptare)
	{
		rad = stanga;
	}
	if (dreapta < h.nr && h.vect[dreapta].timp_asteptare > h.vect[rad].timp_asteptare)
	{
		rad = dreapta;
	}
	if (index != rad)
	{
		comanda_mancare aux = h.vect[index];
		h.vect[index] = h.vect[rad];
		h.vect[rad] = aux;

		filtrare(h, rad);
	}
}

heap inserare(heap h, comanda_mancare cm)
{
	comanda_mancare* vect_nou = new comanda_mancare[h.nr + 1];
	for (int i = 0; i < h.nr; i++)
	{
		vect_nou[i] = h.vect[i];
	}
	vect_nou[h.nr] = cm;
	h.nr++;
	delete[] h.vect;
	h.vect = vect_nou;
	for (int i = (h.nr - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, comanda_mancare* cm)
{
	comanda_mancare* vect_nou = new comanda_mancare[h.nr - 1];
	comanda_mancare aux = h.vect[0];
	h.vect[0] = h.vect[h.nr - 1];
	h.vect[h.nr - 1] = aux;
	*cm = h.vect[h.nr - 1];
	h.nr--;
	for (int i = 0; i < h.nr; i++)
	{
		vect_nou[i] = h.vect[i];
	}
	delete[] h.vect;
	h.vect = vect_nou;
	for (int i = (h.nr - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

void afisare(heap h)
{
	for (int i = 0; i < h.nr; i++)
	{
		cout << "Timp asteptare: " << h.vect[i].timp_asteptare << ", livrator: " << h.vect[i].nume_livrator
			<< ", pret: " << h.vect[i].pret << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nr; i++)
	{
		delete[] h.vect[i].nume_livrator;
	}
	delete[] h.vect;
}

nod* inserare_lista(nod* cap, comanda_mancare* cm)
{
	nod* nou = new nod;
	nou->cm = new comanda_mancare;
	nou->cm->timp_asteptare = cm->timp_asteptare;
	nou->cm->nume_livrator = new char[strlen(cm->nume_livrator) + 1];
	strcpy_s(nou->cm->nume_livrator, strlen(cm->nume_livrator) + 1, cm->nume_livrator);
	nou->cm->pret = cm->pret;
	nou->next = nullptr;

	if (cap == nullptr)
	{
		cap = nou;
	}
	else
	{
		nod* tmp = cap;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		tmp->next = nou;
	}
	return cap;
}

void traversare_lista(nod* cap)
{
	for (nod* tmp = cap; tmp != NULL; tmp = tmp->next)
	{
		cout << "Timp asteptare: " << tmp->cm->timp_asteptare << ", livrator: " << tmp->cm->nume_livrator
			<< ", pret: " << tmp->cm->pret << endl;
	}
}

void dezalocare_lista(nod* cap)
{
	while (cap != NULL)
	{
		nod* tmp = cap->next;
		free(cap->cm->nume_livrator);
		free(cap);
		cap = tmp;
	}
}