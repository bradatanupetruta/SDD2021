#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;

struct pacient {
	int cod;
	char* nume;
	float sumaPlata;
};

struct nodCoada {
	pacient inf;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, pacient p)
{
	nodCoada* nou = new nodCoada;
	nou->inf.cod = p.cod;
	nou->inf.sumaPlata = p.sumaPlata;
	nou->inf.nume = new char[strlen(p.nume) + 1];
	strcpy_s(nou->inf.nume, strlen(p.nume) + 1, p.nume);
	nou->next = nullptr;

	if (*prim == nullptr && *ultim == nullptr)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, pacient* p)
{
	if (*prim != nullptr && *ultim != nullptr)
	{
		(*p).cod = (*prim)->inf.cod;
		(*p).sumaPlata = (*prim)->inf.sumaPlata;
		(*p).nume = new char[strlen((*prim)->inf.nume) + 1];
		strcpy_s((*p).nume, strlen((*prim)->inf.nume) + 1, (*prim)->inf.nume);

		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		delete[] temp->inf.nume;
		delete temp;
		return 0;
	}
	else
	{
		if (*prim == nullptr)
			*ultim = nullptr;
		return -1;
	}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		cout << "Cod " << temp->inf.cod << ", nume " << temp->inf.nume << ", suma de plata " << temp->inf.sumaPlata << endl;
		temp = temp->next;
	}
}

void main()
{
	int n;
	pacient p;
	nodCoada* prim = nullptr;
	nodCoada* ultim = nullptr;
	char buffer[20];

	ifstream fin;
	fin.open("fisier.txt");
	fin >> n;


	for (int i = 0; i < n; i++)
	{
		fin >> p.cod;
		fin >> buffer;
		p.nume = new char[strlen(buffer) + 1];
		strcpy_s(p.nume, strlen(buffer) + 1, buffer);
		fin >> p.sumaPlata;
		put(&prim, &ultim, p);

		delete[] p.nume;
	}
	fin.close();
	traversare(prim);


	pacient p2;
	while (get(&prim, &ultim, &p2) == 0)
	{
		delete[] p2.nume;
	}
}
