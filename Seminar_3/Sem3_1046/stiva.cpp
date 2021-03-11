#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct farfurie
{
	int diametru;
	char* culoare;
	float greutate;
};

struct nodStiva
{
	farfurie inf;
	nodStiva* next;
};

nodStiva* push(nodStiva* varf, farfurie f)
{
	nodStiva* nou = new nodStiva;
	nou->inf.diametru = f.diametru;
	nou->inf.greutate = f.greutate;
	nou->inf.culoare = new char[strlen(f.culoare) + 1];
	strcpy_s(nou->inf.culoare, strlen(f.culoare) + 1, f.culoare);
	nou->next = nullptr;

	if (varf == nullptr)
	{
		varf = nou;
	}
	else {
		nou->next = varf;
		varf = nou;
	}
	return varf;
}
//facem un deep copy in farfurie
//face si o stergere obligatoriu
int pop(nodStiva** varf, farfurie* f)
{
	if (*varf == nullptr)
	{
		return -1; //nu putem scoate nimic, stiva e vida
	}
	else
	{
		(*f).diametru = (*varf)->inf.diametru;
		(*f).greutate = (*varf)->inf.greutate;
		(*f).culoare = new char[strlen((*varf)->inf.culoare) + 1];
		strcpy_s((*f).culoare, strlen((*varf)->inf.culoare) + 1, (*varf)->inf.culoare);
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		delete[]temp->inf.culoare;
		delete temp;
		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		cout << "Diametrul " << temp->inf.diametru << " ,culoarea " << temp->inf.culoare << " ,greutatea " << temp->inf.greutate << endl;
		temp = temp->next;
	}
}

void main()
{
	int n;
	farfurie f;
	nodStiva* varf = nullptr;
	char buffer[20];

	ifstream fin;
	fin.open("fisier.txt");
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		fin >> f.diametru;
		fin >> buffer;
		f.culoare = new char[strlen(buffer) + 1];
		strcpy_s(f.culoare, strlen(buffer) + 1, buffer);
		fin >> f.greutate;
		varf = push(varf, f);
		delete[]f.culoare;
	}
	fin.close();

	traversare(varf);

	farfurie f2;

	while (pop(&varf, &f2) == 0)
	{
		delete[]f2.culoare;
	}

}