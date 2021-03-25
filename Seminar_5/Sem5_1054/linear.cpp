#include <iostream>
#include <fstream>
using namespace std;

struct contact {
	char* nume;
	char* prenume;
	int nr_tel;
};

struct hashT {
	contact** vect;
	int dim;

};

int functie_dispersie(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.dim;
}

void inserare(hashT tabela, contact* c)
{
	int poz = functie_dispersie((*c).nume, tabela);
	if (tabela.vect[poz] == nullptr)
	{
		tabela.vect[poz] = c;
	}
	else {
		int index = 1;
		while (poz + index < tabela.dim)
		{
			if (tabela.vect[poz + index] == nullptr)
			{
				poz += index;
				tabela.vect[poz] = c;
				break;
			}
			index++;
		}
	}
}
void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i + 1 << endl;
			cout << "Nume: " << tabela.vect[i]->nume << " ,prenume: " << tabela.vect[i]->prenume << ", nr.tel: " << tabela.vect[i]->nr_tel << endl;
		}
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			delete[] tabela.vect[i]->nume;
			delete[] tabela.vect[i]->prenume;
			delete tabela.vect[i];
		}
	}
	delete[] tabela.vect;
}

int stergere(hashT tabela, char *nume)
{
	int poz = functie_dispersie(nume, tabela);
	if (tabela.vect[poz] == nullptr)
	{
		return -1;
	}
	else
	{
		if (strcmp(nume, tabela.vect[poz]->nume) == 0)
		{
			delete[] tabela.vect[poz]->nume;
			delete[] tabela.vect[poz]->prenume;
			delete tabela.vect[poz];
			tabela.vect[poz] = nullptr;
		}
		else
		{
			int index = 1;
			while (poz + index < tabela.dim)
			{
				if (strcmp(nume, tabela.vect[poz+index]->nume) == 0)
				{
					poz += index;
					delete[] tabela.vect[poz]->nume;
					delete[] tabela.vect[poz]->prenume;
					delete tabela.vect[poz];
					tabela.vect[poz] = nullptr;
					break;
				}
				index++;
			}
		}
	}
}
int main(void)
{

	int n = 0;
	char buffer[20];
	contact* c;
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new contact * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = nullptr;
	}

	ifstream f("Text.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> buffer;
		c = new contact;
		c->nume = new char[strlen(buffer) + 1];
		strcpy_s(c->nume, strlen(buffer) + 1, buffer);
		f >> buffer;
		c->prenume = new char[strlen(buffer) + 1];
		strcpy_s(c->prenume, strlen(buffer) + 1, buffer);
		f >> c->nr_tel;
		inserare(tabela, c);
	}
	f.close();
	traversareTabela(tabela);

	char buffer2[20];
	cin >> buffer2;
	stergere(tabela, buffer2);
	contact *c2;
	c2 = new contact;
	cin >> buffer;
	c2->nume = new char[strlen(buffer) + 1];
	strcpy_s(c2->nume, strlen(buffer) + 1, buffer);
	cin >> buffer;
	c2->prenume = new char[strlen(buffer) + 1];
	strcpy_s(c2->prenume, strlen(buffer) + 1, buffer);
	cin >> c2->nr_tel;
	inserare(tabela, c2);
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}