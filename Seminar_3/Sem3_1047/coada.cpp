#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;


struct contribuabil
{
	float sumaDePlata;
	char* nume;
	int cod;
};

struct nodCoada
{
	contribuabil inf;
	nodCoada* next;
};


void put(nodCoada** prim, nodCoada** ultim, contribuabil c)
{
	nodCoada* nou = new nodCoada;
	nou->inf.cod = c.cod;
	nou->inf.sumaDePlata = c.sumaDePlata;
	nou->inf.nume = new char[strlen(c.nume) + 1];
	strcpy(nou->inf.nume, c.nume);
	nou->next = NULL;

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


int get(nodCoada** prim, nodCoada** ultim, contribuabil* c)
{
	if (*prim != nullptr && *ultim != nullptr)
	{
		(*c).cod = (*prim)->inf.cod;
		(*c).sumaDePlata = (*prim)->inf.sumaDePlata;
		(*c).nume = new char[strlen((*prim)->inf.nume) + 1];
		strcpy((*c).nume, (*prim)->inf.nume);
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
	while (temp != NULL)
	{
		cout << "Codul este " << temp->inf.cod << ", numele " << temp->inf.nume << " si suma de plata este " << temp->inf.sumaDePlata << endl;
		temp = temp->next;
	}

}

int main()
{
	int n;
	contribuabil c;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	char buffer[20];
	ifstream fin;
	fin.open("fisier.txt");
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		fin >> c.cod;
		fin >> buffer;
		c.nume = new char[strlen(buffer) + 1];
		strcpy(c.nume, buffer);
		fin >> c.sumaDePlata;

		put(&prim, &ultim, c);
		delete[] c.nume;
	}
	fin.close();
	traversare(prim);

	contribuabil c2;
	while (get(&prim, &ultim, &c2) == 0)
	{
		delete[] c2.nume;
	}
}




