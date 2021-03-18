#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

struct Film
{
	char* denumire;
	float durata;
	float rating;
	int limitaVarsta;
};

struct nodLS
{
	Film inf;
	nodLS* next;
};

struct hashT
{
	nodLS** vect;
	int dim;
};

int functieHash(float cheie, hashT tabela)
{
	return (int)cheie % tabela.dim;
}

void inserare(hashT tabela, Film f)
{
	if (tabela.vect != nullptr)
	{
		int poz = functieHash(f.rating, tabela);
		nodLS* nou = new nodLS;
		nou->inf.denumire = new char[strlen(f.denumire) + 1];
		strcpy_s(nou->inf.denumire, strlen(f.denumire) + 1, f.denumire);
		nou->inf.durata = f.durata;
		nou->inf.rating = f.rating;
		nou->inf.limitaVarsta = f.limitaVarsta;
		nou->next = nullptr;
		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = nou;
		}
		else
		{   //situatia pentru coliziune
			nodLS* temp = tabela.vect[poz];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != nullptr)
	{
		cout << temp->inf.denumire << " " << temp->inf.durata << " " << temp->inf.rating << " " << temp->inf.limitaVarsta << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i << endl;
			traversareLS(tabela.vect[i]);
		}
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != nullptr)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.denumire;
		delete temp;
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			dezalocareLS(tabela.vect[i]);
		}
	}
	delete[] tabela.vect;
}

void main()
{
	int n;
	Film f;
	char buffer[20];

	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new nodLS * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = nullptr;
	}

	ifstream fis("fisier.txt");
	fis >> n;
	for (int i = 0; i < n; i++)
	{
		fis >> buffer;
		f.denumire = new char[strlen(buffer) + 1];
		strcpy_s(f.denumire, strlen(buffer) + 1, buffer);
		fis >> f.durata;
		fis >> f.rating;
		fis >> f.limitaVarsta;
		inserare(tabela, f);
		delete[] f.denumire;
	}
	fis.close();

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}