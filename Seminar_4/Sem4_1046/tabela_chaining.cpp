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

struct nodLS {
	produs inf;
	nodLS* next;
};

struct hashT
{
	nodLS** vect;
	int size;
};

int functieHash(int cod, hashT tabela)
{
	return cod % tabela.size;
}

int inserare(hashT tabela, produs p)
{
	if (tabela.vect != nullptr)
	{
		int poz = functieHash(p.cod, tabela);
		nodLS* nou = new nodLS;
		nou->next = nullptr;
		nou->inf.cod = p.cod;
		nou->inf.pret = p.pret;
		nou->inf.cantitate = p.cantitate;
		nou->inf.denumire = new char[strlen(p.denumire) + 1];
		strcpy_s(nou->inf.denumire, strlen(p.denumire) + 1, p.denumire);
		if (tabela.vect[poz] == nullptr)
			tabela.vect[poz] = nou;
		else
		{ //reprezinta situatia de coliziune
			nodLS* temp = tabela.vect[poz];
			while (temp->next != nullptr)
				temp = temp->next;
			temp->next = nou;
		}
		return poz;
	}
	else
		return -1;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != nullptr)
	{
		cout << "Produsul cu codul: " << temp->inf.cod << ", denumire: " << temp->inf.denumire << ", pret:" << temp->inf.pret << ", cantitate:" << temp->inf.cantitate << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitia: " << i << endl;
			traversareLS(tabela.vect[i]);
		}

	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.denumire;
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

			dezalocareLS(tabela.vect[i]);
		}

	}
	delete[] tabela.vect;
}

int main()
{
	int n;
	ifstream fis("fisier.txt");
	fis >> n;
	produs p;
	char buffer[20];
	hashT tabela;
	tabela.size = 101;
	tabela.vect = new nodLS * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		fis >> p.cod;
		fis >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
		fis >> p.pret;
		fis >> p.cantitate;
		inserare(tabela, p);
		delete[] p.denumire;
	}
	fis.close();

	traversareTabela(tabela);
	dezalocareTabela(tabela);

	return 0;
}