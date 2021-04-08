#include<iostream>
#include<fstream>
using namespace std;

struct ProgramareVaccinare
{
	int urgenta;
	char* nume;
	char* tipVaccin;
};

struct heap
{
	ProgramareVaccinare* vect;
	int nrElemente;
};

void filtrare(heap h, int index)
{
	int indexRadacina = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;
	if (indexStanga<h.nrElemente && h.vect[indexStanga].urgenta>h.vect[indexRadacina].urgenta)
	{
		indexRadacina = indexStanga;
	}
	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].urgenta>h.vect[indexRadacina].urgenta)
	{
		indexRadacina = indexDreapta;
	}
	if (index != indexRadacina)
	{
		ProgramareVaccinare aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, ProgramareVaccinare p)
{
	ProgramareVaccinare* vectNou = new ProgramareVaccinare[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++)
	{
		vectNou[i] = h.vect[i];
	}
	vectNou[h.nrElemente] = p;
	delete[]h.vect;
	h.nrElemente++;
	h.vect = vectNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, ProgramareVaccinare* p)
{
	ProgramareVaccinare* vectNou = new ProgramareVaccinare[h.nrElemente - 1];
	ProgramareVaccinare aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*p = h.vect[h.nrElemente - 1];
	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++)
	{
		vectNou[i] = h.vect[i];
	}
	delete[]h.vect;
	h.vect = vectNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
	{
		cout << "Urgenta: " << h.vect[i].urgenta << " Nume: " << h.vect[i].nume << " Tip vaccin: " << h.vect[i].tipVaccin << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
	{
		delete[]h.vect[i].nume;
		delete[]h.vect[i].tipVaccin;
	}
	delete[]h.vect;
}

void main()
{
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new ProgramareVaccinare[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++)
	{
		f >> h.vect[i].urgenta;
		f >> buffer;
		h.vect[i].nume = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].nume, strlen(buffer) + 1, buffer);
		f >> buffer;
		h.vect[i].tipVaccin = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].tipVaccin, strlen(buffer) + 1, buffer);
	}
	f.close();
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	afisare(h);
	ProgramareVaccinare p;
	cout << "Urgenta: ";
	cin >> p.urgenta;
	cout << "Nume: ";
	cin >> buffer;
	p.nume = new char[strlen(buffer) + 1];
	strcpy_s(p.nume, strlen(buffer) + 1, buffer);
	cout << "Tip vaccin: ";
	cin >> buffer;
	p.tipVaccin = new char[strlen(buffer) + 1];
	strcpy_s(p.tipVaccin, strlen(buffer) + 1, buffer);
	h = inserare(h, p);
	cout << endl;
	afisare(h);

	h = extragere(h, &p);
	cout << "Elementul extras are urgenta: " << p.urgenta;
	cout << endl;
	afisare(h);

	dezalocare(h);
}