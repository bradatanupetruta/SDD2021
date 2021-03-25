#include <iostream>
#include <fstream>
using namespace std;

struct produs
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct hashT
{
	produs** vect;
	int size;
};


int functieHash(int cod, hashT tabela)
{
	return cod % tabela.size;
}

void inserare(hashT tabela, produs* p)
{
	int pozitie = functieHash((*p).cod, tabela);
	if (tabela.vect[pozitie] == nullptr) {
		tabela.vect[pozitie] = p;
	}
	else {
		int index = 1;
		while (pozitie + index < tabela.size) {
			if (tabela.vect[pozitie + index] == nullptr) {
				pozitie += index;
				tabela.vect[pozitie] = p;
				break;
			}
			index++;
		}
	}
}

void traversare(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitia: " << i << endl;
			cout << "Produsul cu codul: " << tabela.vect[i]->cod << ", denumire: " << tabela.vect[i]->denumire
				<< ", pret:" << tabela.vect[i]->pret << ", cantitate:" << tabela.vect[i]->cantitate << endl;
		}
}

void dezalocare(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
		if (tabela.vect[i] != nullptr)
		{
			delete[] tabela.vect[i]->denumire;
			delete tabela.vect[i];
		}
	delete[] tabela.vect;
}

int stergere(hashT tabela, int codProdus)
{
	int pozitie = functieHash(codProdus, tabela);
	if (tabela.vect[pozitie] == nullptr)
		return -1;
	else {
		if (tabela.vect[pozitie]->cod == codProdus) {
			delete[] tabela.vect[pozitie]->denumire;
			delete tabela.vect[pozitie];
			tabela.vect[pozitie] = nullptr;
		}
		else
		{
			int index = 1;
			while (pozitie + index < tabela.size) {
				if (tabela.vect[pozitie + index]->cod == codProdus) {
					pozitie += index;
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

float sumaTotala(hashT tabela) {
	float suma = 0;
	for (int i = 0; i < tabela.size; i++)
		if (tabela.vect[i] != nullptr)
			suma += tabela.vect[i]->pret * tabela.vect[i]->cantitate;
	return suma;
}
void main()
{
	int n;
	ifstream fis("fisier.txt");
	fis >> n;
	produs* p;
	char buffer[20];
	hashT tabela;
	tabela.size = 101;
	tabela.vect = new produs * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		p = new produs;
		fis >> p->cod;
		fis >> buffer;
		p->denumire = new char[strlen(buffer) + 1];
		strcpy_s(p->denumire, strlen(buffer) + 1, buffer);
		fis >> p->pret;
		fis >> p->cantitate;
		inserare(tabela, p);
	}
	fis.close();

	traversare(tabela);

	stergere(tabela, 404);
	stergere(tabela, 202);

	cout << endl << "------------------------------------------------------------------------------------------" << endl;

	traversare(tabela);

	cout << endl << "------------------------------------------------------------------------------------------" << endl;

	cout << sumaTotala(tabela);

	dezalocare(tabela);
}