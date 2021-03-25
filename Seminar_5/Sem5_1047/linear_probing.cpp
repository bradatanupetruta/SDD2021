#define _CRT_SECURE_NO_WARNINGS
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


struct hashT
{
	masina** vect;
	int size; //101 prestabilit
};

int functieHash(char cheie[20], hashT tabela)
{

	return cheie[0] % tabela.size;
}

void inserare(hashT tabela, masina* m) {
	int poz = functieHash((*m).marca, tabela);
	if (tabela.vect[poz] == nullptr) {
		tabela.vect[poz] = m;
	}
	else {
		int index = 1;
		while (poz + index < tabela.size) {
			if (tabela.vect[poz + index] == nullptr) {
				poz += index;
				tabela.vect[poz] = m;
				break;
			}
			index++;
		}
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i << endl;
			cout << tabela.vect[i]->capacitateCilindrica << " " << tabela.vect[i]->nrKm << " " << tabela.vect[i]->pret << " " << tabela.vect[i]->marca << endl;
		}
	}
}

void dezalocareTabela(hashT tabela) {

	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr) {
			delete[] tabela.vect[i]->marca;
			delete tabela.vect[i];
		}

	}
	delete[] tabela.vect;
}


int stergere(hashT tabela, char* marca) {
	int poz = functieHash(marca, tabela);
	if (tabela.vect[poz] == nullptr) {
		return -1;
	}
	else {
		if (strcmp(tabela.vect[poz]->marca, marca) == 0) {
			delete[] tabela.vect[poz]->marca;
			delete tabela.vect[poz];
			tabela.vect[poz] = nullptr;
		}
		else {
			int index = 1;
			while (poz + index < tabela.size) {
				if (strcmp(tabela.vect[poz + index]->marca, marca) == 0) {
					poz += index;
					delete[] tabela.vect[poz]->marca;
					delete tabela.vect[poz];
					tabela.vect[poz] = nullptr;
					break;
				}
				index++;
			}

		}
	}
	return poz;
}

void main()
{
	int n;
	ifstream fis("fisier.txt");
	fis >> n;
	masina* m;

	char buffer[20];
	hashT tabela;
	tabela.size = 101;
	tabela.vect = new masina * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		m = new masina;
		fis >> m->capacitateCilindrica;
		fis >> m->nrKm;
		fis >> m->pret;
		fis >> buffer;
		m->marca = new char[strlen(buffer) + 1];
		strcpy(m->marca, buffer);
		inserare(tabela, m);


	}
	fis.close();
	traversareTabela(tabela);
	cin >> buffer;
	stergere(tabela, buffer);
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}

