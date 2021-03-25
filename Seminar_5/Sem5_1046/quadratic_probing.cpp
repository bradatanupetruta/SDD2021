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

//int functieHash(int cod, hashT tabela)
//{
//	return cod % tabela.size;
//}

int functieHash(char* denumire, hashT tabela)
{
	return denumire[0] % tabela.size;
}

void inserare(hashT tabela, produs* p)
{
	int pozitie = functieHash((*p).denumire, tabela);
	if (tabela.vect[pozitie] == nullptr) {
		tabela.vect[pozitie] = p;
	}
	else {
		int c = 2;//o constanta cu val 1, 2 sau 4
		int index = 1;
		while (pozitie + c * index * index < tabela.size) {
			if (tabela.vect[pozitie + c * index * index] == nullptr) {
				pozitie += c * index * index;
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

int stergere(hashT tabela, char* denumire)
{
	int pozitie = functieHash(denumire, tabela);
	if (tabela.vect[pozitie] == nullptr)
		return -1;
	else {
		if (strcmp(tabela.vect[pozitie]->denumire, denumire) == 0) {
			delete[] tabela.vect[pozitie]->denumire;
			delete tabela.vect[pozitie];
			tabela.vect[pozitie] = nullptr;
		}
		else
		{
			int c = 2;
			int index = 1;
			while (pozitie + c * index * index < tabela.size) {
				if (strcmp(tabela.vect[pozitie + c * index * index]->denumire, denumire) == 0) {
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
	cin >> buffer;
	stergere(tabela, buffer);
	cout << endl << "------------------------------------------------------------------------------------------" << endl;
	traversare(tabela);
	cout << endl << "------------------------------------------------------------------------------------------" << endl;
	cout << sumaTotala(tabela);
	dezalocare(tabela);
}