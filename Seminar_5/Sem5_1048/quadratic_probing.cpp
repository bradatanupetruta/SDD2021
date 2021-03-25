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

struct hashT
{
	Film** vect;
	int dim;
};

int functieHash(float cheie, hashT tabela)
{
	return (int)cheie % tabela.dim;
}

void inserare(hashT tabela, Film* f)
{
	if (tabela.vect != nullptr)
	{
		int poz = functieHash((*f).rating, tabela);
		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = f;
		}
		else
		{   //situatia pentru coliziune
			//c -> constanta care poate avea valorile 1,2 sau 4
			int c = 2;
			int index = 1;
			while (poz + c * index * index < tabela.dim) {
				if (tabela.vect[poz + c * index * index] == nullptr) {
					poz += c * index * index;
					tabela.vect[poz] = f;
					break;
				}
				index++;
			}
		}
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i << endl;
			cout << tabela.vect[i]->denumire << " " << tabela.vect[i]->durata << " " << tabela.vect[i]->rating << " " << tabela.vect[i]->limitaVarsta << endl;
		}
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			delete[] tabela.vect[i]->denumire;
			delete tabela.vect[i];
		}
	}
	delete[] tabela.vect;
}

int stergere(hashT tabela, float rating) {
	int pozitie = functieHash(rating, tabela);
	if (tabela.vect[pozitie] == nullptr) {
		return -1;
	}
	else {
		if (tabela.vect[pozitie]->rating == rating) {
			delete[] tabela.vect[pozitie]->denumire;
			delete tabela.vect[pozitie];
			tabela.vect[pozitie] = nullptr;
		}
		else {
			int c = 2;
			int index = 1;
			while (pozitie + c * index * index < tabela.dim) {
				if (tabela.vect[pozitie + c * index * index]->rating == rating) {
					pozitie += c * index * index;
					delete[] tabela.vect[pozitie]->denumire;
					delete tabela.vect[pozitie];
					tabela.vect[pozitie] = nullptr;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void main()
{
	int n;
	Film* f;
	char buffer[20];

	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new Film * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = nullptr;
	}
	
	ifstream fis("fisier.txt");
	fis >> n;
	for (int i = 0; i < n; i++)
	{
		f = new Film;
		fis >> buffer;
		f->denumire = new char[strlen(buffer) + 1];
		strcpy_s(f->denumire, strlen(buffer) + 1, buffer);
		fis >> f->durata;
		fis >> f->rating;
		fis >> f->limitaVarsta;
		inserare(tabela, f);

	}
	fis.close();
	
	traversareTabela(tabela);

	stergere(tabela, 4.7);

	cout << "Dupa stergere: " << endl;

	traversareTabela(tabela);

	stergere(tabela, 6);
	cout << "Dupa stergerea filmului cu rating 6: " << endl;

	traversareTabela(tabela);

	dezalocareTabela(tabela);
}
