#include <iostream>
#include <fstream>
using namespace std;

struct dataTrasmitere
{
	int zi;
	int luna;
	int an;
};

struct email
{
	char* destinatar;
	dataTrasmitere d;
	float dimensiune;
};

struct nodCoada
{
	email info;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, email e)
{
	nodCoada* nou = new nodCoada;
	nou->info.destinatar = new char[strlen(e.destinatar) + 1];
	strcpy_s(nou->info.destinatar, strlen(e.destinatar) + 1, e.destinatar);
	nou->info.dimensiune = e.dimensiune;
	nou->info.d.zi = e.d.zi;
	nou->info.d.luna = e.d.luna;
	nou->info.d.an = e.d.an;

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

int get(nodCoada** prim, nodCoada** ultim, email* e)
{
	if (*prim != nullptr && *ultim != nullptr)
	{
		(*e).destinatar = new char[strlen((*prim)->info.destinatar) + 1];
		strcpy_s((*e).destinatar, strlen((*prim)->info.destinatar) + 1, (*prim)->info.destinatar);
		(*e).dimensiune = (*prim)->info.dimensiune;
		(*e).d.zi = (*prim)->info.d.zi;
		(*e).d.luna = (*prim)->info.d.luna;
		(*e).d.an = (*prim)->info.d.an;

		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		delete[] temp->info.destinatar;
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

void traversare(nodCoada* varf)
{
	nodCoada* temp = varf;
	while (temp)
	{
		cout << "Destinatar " << temp->info.destinatar << " dimensiune " << temp->info.dimensiune <<
			" zi " << temp->info.d.zi << " luna " << temp->info.d.luna << " an " << temp->info.d.an << endl;
		temp = temp->next;
	}
}

void main()
{
	int n;
	nodCoada* prim = nullptr, *ultim = nullptr;
	email e;
	char buffer[20];

	ifstream fis;
	fis.open("fisier.txt");

	fis >> n;

	for (int i = 0; i < n; i++)
	{
		fis >> buffer;
		e.destinatar = new char[strlen(buffer) + 1];
		strcpy_s(e.destinatar, strlen(buffer) + 1, buffer);
		fis >> e.dimensiune;
		fis >> e.d.zi;
		fis >> e.d.luna;
		fis >> e.d.an;

		put(&prim, &ultim, e);
		delete[] e.destinatar;
	}
	fis.close();
	traversare(prim);

	email e2;
	while (get(&prim, &ultim, &e2) == 0)
		delete[] e2.destinatar;
}
