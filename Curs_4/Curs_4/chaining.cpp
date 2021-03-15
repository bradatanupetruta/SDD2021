#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

struct student
{
	int cod;
	char* nume;
	float medie;
};

struct nodLS
{
	student inf;
	nodLS* next;
};

struct hashT
{
	nodLS** vect;
	int size;
};

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

int inserare(hashT tabela, student s)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(s.cod, tabela);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.cod = s.cod;
		nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
		strcpy(nou->inf.nume, s.nume);
		nou->inf.medie = s.medie;
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		cout << "Cod: " << temp->inf.cod
			<< "\nnume: " << temp->inf.nume
			<< "\nmedie: " << temp->inf.medie
			<< endl;

		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != nullptr)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != nullptr)
			{
				cout << "Pozitie: " << i << endl;
				traversareLista(tabela.vect[i]);
			}
		}
	}
}

void traversare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie=%d", i);
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					printf("\nCod=%d, Nume=%s, Medie=%5.2f",
						temp->inf.cod, temp->inf.nume, temp->inf.medie);
					temp = temp->next;
				}
			}
	}
}

void dezalocareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.nume;
		delete temp;
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != nullptr)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != nullptr)
			{
				dezalocareLista(tabela.vect[i]);
			}
		}
		delete[] tabela.vect;
	}
}

void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					nodLS* temp2 = temp->next;
					free(temp->inf.nume);
					free(temp);
					temp = temp2;
				}
			}
		free(tabela.vect);
	}
}

void stergeNod(nodLS* nod)
{
	delete[] nod->inf.nume;
	delete nod;
}

int stergere(hashT tabela, int cod)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(cod, tabela);
		if (tabela.vect[pozitie] == NULL)
			return -1;
		else
		{
			if (tabela.vect[pozitie]->inf.cod == cod)
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
					nodLS* temp = tabela.vect[pozitie];
					tabela.vect[pozitie] = temp->next;
					/*free(temp->inf.nume);
					free(temp);*/
					stergeNod(temp);
				}
			}
			else
			{
				nodLS* temp = tabela.vect[pozitie];
				while (temp->next != NULL && temp->next->inf.cod != cod)
					temp = temp->next;
				nodLS* p = temp->next;
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

void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodLS**)malloc(tabela.size * sizeof(nodLS*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;

	int n;
	/*printf("Nr. studenti=");
	scanf("%d", &n);
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod=");
		scanf("%d", &s.cod);
		printf("\nNume=");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);

		inserare(tabela, s);
	}*/

	ifstream fisier;
	fisier.open("fisier.txt");
	student s;
	char buffer[20];
	fisier >> n;
	for (int i = 0; i < n; i++)
	{
		fisier>> s.cod;
		fisier>> buffer;
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fisier>> s.medie;
		inserare(tabela, s);
	}
	fisier.close();

	traversare(tabela);

	stergere(tabela, 505);

	printf("\n------dupa stergere-------");

	traversare(tabela);

	dezalocare(tabela);
}