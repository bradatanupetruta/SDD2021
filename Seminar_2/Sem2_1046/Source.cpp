#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

//Mihai-Andrei Manolache, gr. 1046

struct produs
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodls
{
	produs inf;
	nodls* next;
	nodls* prev;
};

nodls* inserare(nodls* cap, nodls** coada, produs p)
{
	nodls* nou = new nodls;
	//nou->inf.cod = p.cod;
	nou->inf.cod = new int[1];
	//nou->inf.cod = p.cod; // shallow copy
	*(nou->inf.cod) = *(p.cod); // deep copy

	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}

	return cap;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		cout << "Cod = " << *(temp->inf.cod) << " Denumire = " << temp->inf.denumire << " Pret = " << temp->inf.pret << " Cantitate = " << temp->inf.cantitate << endl;
		temp = temp->next;
	}
}

void traversareInversa(nodls* coada)
{
	nodls* temp = coada;
	while (temp != NULL)
	{
		cout << "Cod = " << *(temp->inf.cod) << " Denumire = " << temp->inf.denumire << " Pret = " << temp->inf.pret << " Cantitate = " << temp->inf.cantitate << endl;
		temp = temp->prev;
	}
}

void conversieListaVector(nodls* cap, produs* vect, int* nr)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		//	vect[*nr] = temp->inf;
		vect[*nr].cod = new int[1];
		*(vect[*nr].cod) = *(temp->inf.cod);
		vect[*nr].denumire = new char[strlen(temp->inf.denumire) + 1];
		strcpy(vect[*nr].denumire, temp->inf.denumire);
		vect[*nr].pret = temp->inf.pret;
		vect[*nr].cantitate = temp->inf.cantitate;
		(*nr)++;
		//nodls* temp2 = temp->next;
		//free(temp);
		temp = temp->next;
	}
}

void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		delete[] temp->inf.denumire;
		delete temp->inf.cod;
		delete temp;
		temp = temp2;
	}
}

void main()
{
	int n;
	/*cout << "Numar produse: ";
	cin >> n;*/

	nodls* cap = NULL;

	nodls* coada = NULL;

	produs p;

	char buffer[20];

	/*for (int i = 0; i < n; i++)
	{
		cout << "Cod = ";
		cin >> p.cod;

		cout << " Denumire = ";
		cin >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);

		cout << " Pret = ";
		cin >> p.pret;

		cout << " Cantitate = ";
		cin >> p.cantitate;

		cap = inserare(cap, p);

		delete[] p.denumire;

	}*/

	//traversare(cap);

	//dezalocare(cap);

	fstream f;
	f.open("fisier.txt", ios::in);

	f >> n;

	for (int i = 0; i < n; i++)
	{
		p.cod = new int[1];
		f >> *(p.cod);

		f >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);

		f >> p.pret;

		f >> p.cantitate;

		cap = inserare(cap, &coada, p);

		delete[] p.denumire;
		delete p.cod;
	}

	f.close();

	traversare(cap);

	cout << endl;

	traversareInversa(coada);

	cout << endl;

	printf("\n-------conversie-----------");
	produs* vect = new produs[n];
	//(produs**)malloc(n*sizeof(produs*));
	int nr = 0;
	conversieListaVector(cap, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(vect[i].cod), vect[i].denumire, vect[i].pret, vect[i].cantitate);
	for (int i = 0; i < nr; i++)
	{
		free(vect[i].denumire);
		free(vect[i].cod);
	}
	free(vect);

	dezalocare(cap);

}