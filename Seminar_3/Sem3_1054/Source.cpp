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

struct nodStiva
{
	email info;
	nodStiva* next;
};

nodStiva* push(nodStiva* varf, email e)
{
	nodStiva* nou = new nodStiva;
	nou->info.destinatar = new char[strlen(e.destinatar) + 1];
	strcpy_s(nou->info.destinatar, strlen(e.destinatar) + 1, e.destinatar);
	nou->info.dimensiune = e.dimensiune;
	nou->info.d.zi = e.d.zi;
	nou->info.d.luna = e.d.luna;
	nou->info.d.an = e.d.an;

	nou->next = nullptr;

	if (varf == nullptr)
		varf = nou;
	else
	{
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf, email* e)
{
	if (*varf == nullptr)
		return -1;
	else
	{
		(*e).destinatar = new char[strlen((*varf)->info.destinatar) + 1];
		strcpy_s((*e).destinatar, strlen((*varf)->info.destinatar) + 1, (*varf)->info.destinatar);
		(*e).dimensiune = (*varf)->info.dimensiune;
		(*e).d.zi = (*varf)->info.d.zi;
		(*e).d.luna= (*varf)->info.d.luna;
		(*e).d.an = (*varf)->info.d.an;

		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		delete[] temp->info.destinatar;
		delete temp;

		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
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
	nodStiva* varf = nullptr;
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

		varf = push(varf, e);
		delete[] e.destinatar;
	}
	fis.close();
	traversare(varf);

	email e2;
	while (pop(&varf, &e2) == 0)
		delete[] e2.destinatar;
}