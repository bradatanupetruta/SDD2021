#include<iostream>
#include<fstream>
using namespace std;

struct comandaMancare
{
	int timpAsteptare;
	char* numeLivrator;
	float pret;
};

struct heap
{
	comandaMancare* vect;
	int nrElem;
};

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].timpAsteptare > h.vect[indexRad].timpAsteptare)
	{
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vect[indexDr].timpAsteptare > h.vect[indexRad].timpAsteptare)
	{
		indexRad = indexDr;
	}

	if (index != indexRad)
	{
		comandaMancare aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, comandaMancare cm)
{
	comandaMancare* vectNou = new comandaMancare[h.nrElem + 1];
	for (int i = 0; i < h.nrElem; i++)
	{
		vectNou[i] = h.vect[i];
	}
	vectNou[h.nrElem] = cm;
	h.nrElem++;
	delete[] h.vect;
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, comandaMancare* cm)
{
	comandaMancare* vectNou = new comandaMancare[h.nrElem - 1];
	comandaMancare aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*cm = h.vect[h.nrElem - 1];
	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++)
	{
		vectNou[i] = h.vect[i];
	}

	delete[]h.vect;
	h.vect = vectNou;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
	{
		cout << "Timp asteptare: " << h.vect[i].timpAsteptare << " Livrator: " << h.vect[i].numeLivrator << " Pret: " << h.vect[i].pret << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
	{
		delete[]h.vect[i].numeLivrator;
	}
	delete[] h.vect;
}

void main()
{
	heap h;
	char buffer[20];
	ifstream f("Fisier.txt");
	f >> h.nrElem;

	h.vect = new comandaMancare[h.nrElem];
	for (int i = 0; i < h.nrElem; i++)
	{
		f >> h.vect[i].timpAsteptare;
		f >> buffer;
		h.vect[i].numeLivrator = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].numeLivrator, strlen(buffer) + 1, buffer);
		f >> h.vect[i].pret;
	}
	f.close();

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}

	afisare(h);

	comandaMancare c;
	cout << "Timp asteptare: ";
	cin >> c.timpAsteptare;
	cout << "Nume livrator: ";
	cin >> buffer;
	c.numeLivrator = new char[strlen(buffer) + 1];
	strcpy_s(c.numeLivrator, strlen(buffer) + 1, buffer);
	cout << "Pret: ";
	cin >> c.pret;

	h = inserare(h, c);
	cout << endl;
	afisare(h);

	h = extragere(h, &c);
	cout << "Comanda extrasa are timpul " << c.timpAsteptare << endl;
	afisare(h);

	dezalocare(h);
}