#include <iostream>
#include <fstream>
using namespace std;




struct imbarcareAvion
{
	int prioritate;
	char* numePersoana;
	float pretBilet;
};

struct nodls
{
	imbarcareAvion inf;
	nodls* next;
};

struct heap
{
	imbarcareAvion* vect;
	int nrElemente;
};

void filtrare(heap h, int index)
{
	int indexRadacina = index;
	int indexStanga = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (indexStanga<h.nrElemente && h.vect[indexStanga].prioritate> h.vect[indexRadacina].prioritate)
	{
		indexRadacina = indexStanga;
	}
	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].prioritate> h.vect[indexRadacina].prioritate)
	{
		indexRadacina = indexDreapta;
	}
	if (index != indexRadacina)
	{
		imbarcareAvion aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}

heap inserare(heap h, imbarcareAvion a)
{
	imbarcareAvion* vectNou = new imbarcareAvion[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.nrElemente] = a;

	delete[] h.vect;
	h.nrElemente++;
	h.vect = vectNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, imbarcareAvion* a)
{
	imbarcareAvion* vectNou = new imbarcareAvion[h.nrElemente + 1];
	imbarcareAvion aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*a = h.vect[h.nrElemente - 1];

	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++)
		vectNou[i] = h.vect[i];
	delete[] h.vect;
	h.vect = vectNou;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;

}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
	{
		cout << "Prioritate: " << h.vect[i].prioritate << " Nume persoana: " << h.vect[i].numePersoana << " Pret bilet:  " << h.vect[i].pretBilet << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
		delete[] h.vect[i].numePersoana;
	delete[] h.vect;
}

nodls* inserareLista(nodls* cap, imbarcareAvion a)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.prioritate = a.prioritate;
	nou->inf.numePersoana = new char[strlen(a.numePersoana) + 1];
	strcpy_s(nou->inf.numePersoana, strlen(a.numePersoana) + 1, a.numePersoana);
	nou->inf.pretBilet = a.pretBilet;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		cout << "Prioritate: " << temp->inf.prioritate << " Nume persoana: " << temp->inf.numePersoana << " Pret: " << temp->inf.pretBilet << endl;
		temp = temp->next;
	}
}

void dezalocareLista(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		free(temp->inf.numePersoana);
		free(temp);
		temp = temp2;
	}
}

nodls* conversie(heap h)
{
	nodls* cap = NULL;
	while (h.nrElemente > 0)
	{
		imbarcareAvion extras;
		h = extragere(h, &extras);
		cap = inserareLista(cap, extras);
	}
	return cap;
}

void main()
{
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new imbarcareAvion[h.nrElemente];
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
	{
		filtrare(h, i);
	}
	afisare(h);

	/*cout << "Inserare imbarcare noua:\n";
	imbarcareAvion nou;
	cout << "Prioritate: "; cin >> nou.prioritate;
	cout << "Nume persoana: "; cin >> buffer;
	nou.numePersoana = new char[strlen(buffer) + 1];
	strcpy_s(nou.numePersoana, strlen(buffer) + 1, buffer);
	cout << "Pret: "; cin >> nou.pretBilet;
	h = inserare(h, nou);
	afisare(h);

	h = extragere(h, &nou);
	cout << "Elementul extras are prioritatea: " << nou.prioritate<<endl;
	afisare(h);*/

	nodls* cap = conversie(h);
	cout << "Elemente lista simpla:\n";
	traversare(cap);
	dezalocareLista(cap);

}