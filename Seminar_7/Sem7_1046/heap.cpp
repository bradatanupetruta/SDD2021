#include<iostream>
#include<fstream>
using namespace std;

struct programareVaccin {
	int prioritate;
	char* nume;
	char* tipVaccin;

};
struct heap {
	programareVaccin* vect;
	int nrElemente;
};

void filtrare(heap h, int index) {
	int indexRadacina = index;
	int indexStanga = index * 2 + 1;
	int indexDreapta = index * 2 + 2;
	if (indexStanga<h.nrElemente && h.vect[indexStanga].prioritate>h.vect[indexRadacina].prioritate)
		indexRadacina = indexStanga;
	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].prioritate>h.vect[indexRadacina].prioritate)
		indexRadacina = indexDreapta;
	if (index != indexRadacina)
	{
		programareVaccin aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);

	}
}

heap inserare(heap h, programareVaccin v)
{
	programareVaccin* vectNou = new programareVaccin[h.nrElemente + 1];
	for (int i = 0; i < h.nrElemente; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.nrElemente] = v;
	delete[] h.vect;
	h.vect = vectNou;
	h.nrElemente++;
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, programareVaccin* p)
{
	programareVaccin* vectNou = new programareVaccin[h.nrElemente - 1];
	programareVaccin aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*p = h.vect[h.nrElemente - 1];
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
		cout << "Prioritate:" << h.vect[i].prioritate << " Nume:" << h.vect[i].nume << " Tip vaccin:" << h.vect[i].tipVaccin << endl;

}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElemente; i++)
	{
		delete[] h.vect[i].nume;
		delete[] h.vect[i].tipVaccin;
	}
	delete[] h.vect;
}

int main()
{
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new programareVaccin[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++)
	{
		f >> h.vect[i].prioritate;
		f >> buffer;
		h.vect[i].nume = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].nume, strlen(buffer) + 1, buffer);
		f >> buffer;
		h.vect[i].tipVaccin = new char[strlen(buffer) + 1];
		strcpy_s(h.vect[i].tipVaccin, strlen(buffer) + 1, buffer);

	}
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisare(h);
	programareVaccin p;
	cout << "Introduceti programarea: " << endl;
	cout << "Prioritate:";
	cin >> p.prioritate;
	cout << "Nume:";
	cin >> buffer;
	p.nume = new char[strlen(buffer) + 1];
	strcpy_s(p.nume, strlen(buffer) + 1, buffer);
	cout << "Tip vaccin:";
	cin >> buffer;
	p.tipVaccin = new char[strlen(buffer) + 1];
	strcpy_s(p.tipVaccin, strlen(buffer) + 1, buffer);

	h = inserare(h, p);
	afisare(h);
	h = extragere(h, &p);
	cout << p.prioritate << endl;
	afisare(h);
	delete[] p.nume;
	delete[] p.tipVaccin;
	dezalocare(h);

	f.close();
	return 0;
}