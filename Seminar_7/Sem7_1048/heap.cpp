#include <iostream>
#include <fstream>
using namespace std;

struct ImbarcareAvion
{
	int prioritate;
	char* numePersoana;
	float pretBilet;
};

struct heap
{
	ImbarcareAvion* vect;
	int nrElemente;
};

void filtrare(heap h, int index)
{
	int indexRadacina = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga<h.nrElemente && h.vect[indexStanga].prioritate>h.vect[indexRadacina].prioritate)
		indexRadacina = indexStanga;
	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].prioritate>h.vect[indexRadacina].prioritate)
		indexRadacina = indexDreapta;
	if (index != indexRadacina)
	{
		ImbarcareAvion aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, ImbarcareAvion a)
{
	ImbarcareAvion* vectnou = new ImbarcareAvion[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++)
		vectnou[i] = h.vect[i];
	vectnou[h.nrElemente] = a;

	delete[] h.vect;
	h.nrElemente++;
	h.vect = vectnou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, ImbarcareAvion* a)
{
	ImbarcareAvion* vectnou = new ImbarcareAvion[h.nrElemente - 1];

	ImbarcareAvion aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*a = h.vect[h.nrElemente - 1];

	h.nrElemente--;

	for (int i = 0; i < h.nrElemente; i++)
		vectnou[i] = h.vect[i];
	delete[] h.vect;
	h.vect = vectnou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	return h;

}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
	{
		cout << "Prioritate: " << h.vect[i].prioritate << " Nume Persoana: " << h.vect[i].numePersoana << " Pret Bilet: " << h.vect[i].pretBilet << endl;

	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
		delete[] h.vect[i].numePersoana;
	delete[] h.vect;
}
void main()
{
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new ImbarcareAvion[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++)
	{
		f >> h.vect[i].prioritate;
		f >> buffer;
		h.vect[i].numePersoana = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].numePersoana, strlen(buffer) + 1, buffer);
		f >> h.vect[i].pretBilet;
	}
	f.close();

	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisare(h);
	ImbarcareAvion nou;
	cout << "Prioritate: ";
	cin >> nou.prioritate;
	cout << "Nume Persoana: ";
	cin >> buffer;
	nou.numePersoana = new char[strlen(buffer) + 1];
	strcpy_s(nou.numePersoana, strlen(buffer) + 1, buffer);
	cout << "Pret: ";
	cin >> nou.pretBilet;
	h = inserare(h, nou);
	afisare(h);
	h = extragere(h, &nou);
	cout << "Elementul extras are prioritatea : " << nou.prioritate << endl;
	afisare(h);
	dezalocare(h);
}