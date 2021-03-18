#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

struct masina {
	char* marca;
	int nrKm;
	float pret;
	int capacitateCilindrica;
};

struct nodLs
{
	masina inf;
	nodLs* next;
};

struct hashT
{
	nodLs** vect;
	int size; //101 prestabilit
};

int functieHash(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.size;
}

void inserare(hashT tabela, masina m)
{
	if (tabela.vect != nullptr)
	{
		int poz = functieHash(m.marca, tabela);
		nodLs* nou = new nodLs;
		nou->inf.capacitateCilindrica = m.capacitateCilindrica;
		nou->inf.nrKm = m.nrKm;
		nou->inf.pret = m.pret;
		nou->inf.marca = new char[strlen(m.marca) + 1];
		strcpy(nou->inf.marca, m.marca);
		nou->next = nullptr;
		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = nou;
		}
		else  //situatie de coliziune
		{
			nodLs* temp = tabela.vect[poz];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
}

void traversareLs(nodLs* capLs)
{
	nodLs* temp = capLs;
	while (temp)
	{
		cout << temp->inf.capacitateCilindrica << " " << temp->inf.nrKm << " " << temp->inf.pret << " " << temp->inf.marca << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i << endl;
			traversareLs(tabela.vect[i]);
		}
	}
}

void dezalocareLs(nodLs* capLs)
{
	nodLs* temp = capLs;
	while (temp)
	{
		nodLs* temp2 = temp->next;
		delete[] temp->inf.marca;
		delete temp;

		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			dezalocareLs(tabela.vect[i]);
		}
	}
	delete[]tabela.vect;
}

void main()
{
	int n;
	ifstream fis("fisier1.txt");
	fis >> n;
	masina m;

	char buffer[20];
	hashT tabela;
	tabela.size = 101;
	tabela.vect = new nodLs * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		fis >> m.capacitateCilindrica;
		fis >> m.nrKm;
		fis >> m.pret;
		fis >> buffer;
		m.marca = new char[strlen(buffer) + 1];
		strcpy(m.marca, buffer);
		inserare(tabela, m);
		delete[]m.marca;
	}
	fis.close();

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}
