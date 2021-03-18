#include <iostream>
#include <fstream>
using namespace std;

struct contact {
	char* nume;
	char* prenume;
	int nr_tel;
};

struct nodls {
	contact inf;
	nodls* next;
};

struct hashT {
	nodls** vect;
	int dim;

};

int functie_dispersie(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.dim;
}

void inserare(hashT tabela, contact c)
{
	if (tabela.vect != nullptr)
	{
		int poz = functie_dispersie(c.nume, tabela);
		nodls* nou = new nodls;
		nou->inf.nr_tel = c.nr_tel;
		nou->inf.nume = new char[strlen(c.nume) + 1];
		strcpy_s(nou->inf.nume, strlen(c.nume) + 1, c.nume);
		nou->inf.prenume = new char[strlen(c.prenume) + 1];
		strcpy_s(nou->inf.prenume, strlen(c.prenume) + 1, c.prenume);
		nou->next = nullptr;

		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = nou;
		}
		else//situatia de coliziune
		{
			nodls* tmp = tabela.vect[poz];
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			tmp->next = nou;
		}
	}
}

void traversarels(nodls* cap)
{
	nodls* tmp = cap;
	while (tmp != nullptr)
	{
		cout << "Nume: " << tmp->inf.nume << " ,prenume: " << tmp->inf.prenume << ", nr.tel: " << tmp->inf.nr_tel << endl;
		tmp = tmp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i + 1 << endl;
			traversarels(tabela.vect[i]);
		}
	}
}

void dezalocarels(nodls* cap)
{
	while (cap != nullptr)
	{
		nodls* tmp = cap->next;
		delete[] cap->inf.nume;
		delete[] cap->inf.prenume;
		delete[] cap;
		cap = tmp;
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			dezalocarels(tabela.vect[i]);
		}
	}
	delete[] tabela.vect;
}

void stergeNod(nodls* nod)
{
	delete[] nod->inf.nume;
	delete nod;
}

int stergere(hashT tabela, char nume[20])
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functie_dispersie(nume, tabela);
		if (tabela.vect[pozitie] == NULL)
			return -1;
		else
		{
			if (strcmp(tabela.vect[pozitie]->inf.nume, nume) == 0)
			{
				if (tabela.vect[pozitie]->next == NULL)
				{
					/*nodLS* temp = tabela.vect[pozitie];
					free(temp->inf.nume);
					free(temp);*/
					stergeNod(tabela.vect[pozitie]);
					tabela.vect[pozitie] = NULL;
				}
				else
				{
					nodls* temp = tabela.vect[pozitie];
					tabela.vect[pozitie] = temp->next;
					/*free(temp->inf.nume);
					free(temp);*/
					stergeNod(temp);
				}
			}
			else
			{
				nodls* temp = tabela.vect[pozitie];
				while (temp->next != NULL && strcmp(temp->next->inf.nume, nume) != 0)
					temp = temp->next;
				nodls* p = temp->next;
				if (p->next != NULL)
				{
					temp->next = p->next;
					/*free(p->inf.nume);
					free(p);*/
					stergeNod(p);
				}
				else
				{
					temp->next = NULL;
					/*free(p->inf.nume);
					free(p);*/
					stergeNod(p);
				}
			}
		}
	}
	return pozitie;
}

int main(void)
{

	int n = 0;
	char buffer[20];
	contact c;
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new nodls * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = nullptr;
	}

	ifstream f("Text.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> buffer;
		c.nume = new char[strlen(buffer) + 1];
		strcpy_s(c.nume, strlen(buffer) + 1, buffer);
		f >> buffer;
		c.prenume = new char[strlen(buffer) + 1];
		strcpy_s(c.prenume, strlen(buffer) + 1, buffer);
		f >> c.nr_tel;
		inserare(tabela, c);


		delete[] c.nume;
		delete[] c.prenume;
	}
	f.close();
	traversareTabela(tabela);

	char buffer2[20];
	cin >> buffer2;
	stergere(tabela, buffer2);

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}