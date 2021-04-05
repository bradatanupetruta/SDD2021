#include <stdio.h>
#include <iostream>
using namespace std;

struct apelUrgenta
{
	int prioritate;
	char* numeApelant;
};

struct heap
{
	apelUrgenta* vect;
	int nrElem;
};

void filtrare(heap h, int index)
{
	int indexMax = index;//nod radacina
	int indexS = 2 * index + 1;//fiul stg
	int indexD = 2 * index + 2;//fiul dreapta

	if (indexS < h.nrElem && h.vect[indexS].prioritate > h.vect[indexMax].prioritate)
		indexMax = indexS;//interschimbare indici
	if (indexD < h.nrElem && h.vect[indexD].prioritate > h.vect[indexMax].prioritate)
		indexMax = indexD;

	if (index != indexMax)//interschimbare elemente din vector
	{
		apelUrgenta temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare(h, indexMax);//se reia filtrarea de la pozitia ramasa
	}
}

void inserare(heap* h, apelUrgenta elem)
{
	apelUrgenta* vect1 = new apelUrgenta[(*h).nrElem + 1];
	for (int i = 0; i < (*h).nrElem; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem++;
	delete[](*h).vect;
	(*h).vect = vect1;

	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) //filtrare de la ultimul element
		filtrare((*h), i);
}

void extragere(heap* h, apelUrgenta* elem)
{
	apelUrgenta* vect1 = new apelUrgenta[(*h).nrElem - 1];

	apelUrgenta temp = (*h).vect[0];//interschimbam primul elem cu ultimul din vector
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = temp;

	*elem = (*h).vect[(*h).nrElem - 1];//elementul maxim care se afla acum pe ultima pozitie in vector

	for (int i = 0; i < (*h).nrElem - 1; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem--;
	delete[](*h).vect;
	(*h).vect = vect1;//noul vector

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare((*h), i);//filtrare de jos in sus
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
	{
		cout << "Prioritatea este: " << h.vect[i].prioritate << endl;
		cout << "Numele apelantului este: " << h.vect[i].numeApelant << endl;
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		delete[] h.vect[i].numeApelant;
	delete[] h.vect;
}

void main()
{
	heap h;

	cout << "Nr. elemente: ";
	cin >> h.nrElem;

	char buffer[20];

	h.vect = new apelUrgenta[h.nrElem];

	for (int i = 0; i < h.nrElem; i++)
	{
		cout << "Prioritate: ";
		cin >> h.vect[i].prioritate;

		cout << "\nNumele apelantului: ";
		cin >> buffer;
		h.vect[i].numeApelant = new char[(strlen(buffer) + 1)];
		strcpy(h.vect[i].numeApelant, buffer);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisare(h);
	char nume[20];
	strcpy(nume, "Marcel");
	apelUrgenta s = { 25, nume };
	inserare(&h, s);
	//inserare(&h, 6);

	afisare(h);

	apelUrgenta elem;
	extragere(&h, &elem);
	cout<<"\nElement extras are prioritatea "<< elem.prioritate<<endl;

	afisare(h);

	dezalocare(h);
}
