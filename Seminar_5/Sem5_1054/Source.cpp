#include <iostream>
#include <fstream>
using namespace std;

struct nodls {
	int col, val;
	nodls* next;
};

struct nodlp {
	nodls* inf;
	nodlp* next;
	nodlp* prev;
};

nodls* inserarels(nodls* cap, int **mat, int nrLin, int nrCol, int indiceLinie);
nodlp* inserarelp(nodlp* caplp, nodls* capls, nodlp **coada);
void traversarels(nodls* cap);
void traversarelp(nodlp* cap);
void dezalocarels(nodls* cap);
void dezalocarelp(nodlp* cap);
int numarare(nodlp* cap);

int main(void)
{
	int nrLin, nrCol;
	int** mat;
	
	nodlp* caplp = NULL;
	nodlp* coada = NULL;
	
	ifstream f("fisier.txt");
	f >> nrLin;
	f >> nrCol;
	mat = new int* [nrLin];
	for (int i = 0; i < nrLin; i++)
		mat[i] = new int[nrCol];

	for (int i = 0; i < nrLin; i++)
		for (int j = 0; j < nrCol; j++)
			f >> mat[i][j];
	f.close();
	
	for (int i = 0; i < nrLin; i++)
	{
		nodls* capls = nullptr;
		capls = inserarels(capls, mat, nrLin, nrCol, i);
		caplp = inserarelp(caplp, capls, &coada);
	}

	traversarelp(caplp);
	dezalocarelp(caplp);
	
	for (int i = 0; i < nrLin; i++)
		delete[] mat[i];
	delete[] mat;
}

nodls* inserarels(nodls* cap, int** mat, int nrLin, int nrCol, int indiceLinie)
{
	for (int j = 0; j < nrCol; j++)
	{
		if (mat[indiceLinie][j] != 0)
		{
			nodls* nou = new nodls;
			nou->col = j;
			nou->val = mat[indiceLinie][j];
			nou->next = nullptr;

			if (cap == nullptr)
			{
				cap = nou;
			}
			else
			{
				nodls* tmp = cap;
				while (tmp->next != NULL)
				{
					tmp = tmp->next;
				}
				tmp->next = nou;
			}
		}
	}
	return cap;
}

nodlp* inserarelp(nodlp* caplp, nodls* capls, nodlp** coada) {
	nodlp* nou = new nodlp;
	nou->inf = capls;
	nou->next = nullptr;
	nou->prev = nullptr;

	if (caplp == nullptr)
	{
		caplp = nou;
		*coada = nou;
	}
	else
	{
		nodlp* tmp = caplp;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = nou;
		nou->prev = tmp;
		*coada = nou;
	}
	return caplp;
}

void traversarels(nodls* cap)
{
	nodls* tmp = cap;
	while (tmp != NULL)
	{
		cout << "Coloana: " << tmp->col << " , Valoare: " << tmp->val << endl;
		tmp = tmp->next;
	}
}

void traversarelp(nodlp* cap)
{
	nodlp* tmp = cap;
	int i = 0;
	while (tmp != NULL)
	{
		cout << "Sublista: " << i + 1 << endl;
		traversarels(tmp->inf);
		tmp = tmp->next;
		i++;
	}
}

void dezalocarels(nodls* cap)
{
	while (cap != NULL)
	{
		nodls* tmp = cap->next;
		delete[] cap;
		cap = tmp;
	}
}

void dezalocarelp(nodlp* cap)
{
	while (cap != NULL)
	{
		nodlp* tmp = cap->next;
		dezalocarels(cap->inf);
		delete[] cap;
		cap = tmp;
	}
}
