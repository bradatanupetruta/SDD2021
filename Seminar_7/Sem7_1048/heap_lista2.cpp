#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct ImbarcareAvion {
	int prioritate;
	char* numePersoana;
	float pretBilet;
};

struct heap {
	ImbarcareAvion* vect;
	int nrElemente;

};

struct nodLs {
	ImbarcareAvion inf;
	nodLs* next;
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
	{
		filtrare(h, i);
	}
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
	{
		filtrare(h, i);
	}

	return h;
}

void afisare(heap h) {
	for (int i = 0; i < h.nrElemente; i++)
	{
		cout << "Prioritate: " << h.vect[i].prioritate << " Nume persoana: " << h.vect[i].numePersoana << " Pret bilet " << h.vect[i].pretBilet << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
		delete[] h.vect[i].numePersoana;
	delete[] h.vect;
}

nodLs* inserareLista(nodLs* cap, ImbarcareAvion a) {
	nodLs* nou = new nodLs;
	nou->inf.prioritate = a.prioritate;
	nou->inf.numePersoana = new char[strlen(a.numePersoana) + 1];
	strcpy(nou->inf.numePersoana, a.numePersoana);
	nou->inf.pretBilet = a.pretBilet;
	nou->next = nullptr;

	if (cap == nullptr)
	{
		cap = nou;
	}
	else
	{
		nodLs* temp = cap;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = nou;

	}
	return cap;
}

void traversareLs(nodLs* cap)
{
	nodLs* temp = cap;
	while (temp != nullptr)
	{
		cout << "Prioritate: " << temp->inf.prioritate << " Nume persoana: " << temp->inf.numePersoana << " Pret bilet " << temp->inf.pretBilet << endl;
		temp = temp->next;
	}
}

void dezalocareLista(nodLs* cap)
{
	nodLs* temp = cap;
	while (temp != nullptr)
	{
		nodLs* temp2 = temp->next;
		delete[] temp->inf.numePersoana;
		delete temp;
		temp = temp2;
	}
}

nodLs* conversie(heap h, nodLs* cap) {
	ImbarcareAvion a;
	int nr = h.nrElemente;
	for (int i = 0; i < nr; i++) {
		h = extragere(h, &a);
		cap = inserareLista(cap, a);
	}
	return cap;
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

	/*ImbarcareAvion nou;
	cout << "Prioritate: ";
	cin >> nou.prioritate;
	cout << "Nume ";
	cin >> buffer;
	nou.numePersoana = new char[strlen(buffer) + 1];
	strcpy_s(nou.numePersoana, strlen(buffer) + 1, buffer);
	cout << "Pret: ";
	cin >> nou.pretBilet;
	h = inserare(h, nou);
	h = extragere(h,&nou);
	cout << "Elementul extras: " << nou.prioritate << endl;

	afisare(h);*/

	nodLs* cap = NULL;
	cap = conversie(h, cap);
	cout << "Conversia = " << endl;
	traversareLs(cap);
	dezalocareLista(cap);
	//dezalocare(h);
}