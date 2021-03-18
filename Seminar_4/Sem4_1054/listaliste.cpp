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

struct nodlp {
	nodls* inf;
	nodlp* next;
	nodlp* prev;
};

nodls* inserarels(nodls* cap, contact c);
nodlp* inserarelp(nodlp* caplp, nodls* capls);
void traversarels(nodls* cap);
void traversarelp(nodlp* cap);
void dezalocarels(nodls* cap);
void dezalocarelp(nodlp* cap);
int numarare(nodlp* cap);

int main(void)
{
	int n = 0;
	char buffer[20];
	nodlp* caplp = NULL;
	nodls* capls1 = NULL, * capls2 = NULL;
	contact c;
	ifstream f("fisier.txt");
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
		if (i < n / 2)
		{
			capls1 = inserarels(capls1, c);
		}
		else
		{
			capls2 = inserarels(capls2, c);
		}
		delete[] c.nume;
		delete[] c.prenume;
	}
	f.close();
	caplp = inserarelp(caplp, capls1);
	caplp = inserarelp(caplp, capls2);

	traversarelp(caplp);
	int numere;
	numere = numarare(caplp);
	cout << numere;
	dezalocarelp(caplp);
	//Sa se numere cate contacte incep cu litera P
}

nodls* inserarels(nodls* cap, contact c)
{
	nodls* nou = new nodls;
	nou->inf.nr_tel = c.nr_tel;
	nou->inf.nume = new char[strlen(c.nume) + 1];
	strcpy_s(nou->inf.nume, strlen(c.nume) + 1, c.nume);
	nou->inf.prenume = new char[strlen(c.prenume) + 1];
	strcpy_s(nou->inf.prenume, strlen(c.prenume) + 1, c.prenume);
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
	return cap;
}

nodlp* inserarelp(nodlp* caplp, nodls* capls) {
	nodlp* nou = new nodlp;
	nou->inf = capls;
	nou->next = nullptr;
	nou->prev = nullptr;

	if (caplp == nullptr)
	{
		caplp = nou;
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
	}
	return caplp;
}

void traversarels(nodls* cap)
{
	nodls* tmp = cap;
	while (tmp != NULL)
	{
		cout << "Nume: " << tmp->inf.nume << ", prenume: " << tmp->inf.prenume << ", nr. tel: "
			<< tmp->inf.nr_tel << endl;
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
		delete[] cap->inf.nume;
		delete[] cap->inf.prenume;
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

int numarare(nodlp* cap)
{
	int i = 0;
	nodlp* tmp = cap;
	while (tmp != NULL)
	{
		nodls* tmp2 = tmp->inf;
		while (tmp2 != NULL)
		{
			if (tmp2->inf.nume[0] == 'P') i++;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return i;
}