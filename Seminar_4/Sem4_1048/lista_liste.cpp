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

struct nodLS {
	Film inf;
	nodLS* next;
};

struct nodLP {
	nodLS* inf;
	nodLP* next;
};

nodLS* inserareLS(nodLS* capLS, Film f)
{
	nodLS* nou = new nodLS;
	nou->inf.denumire = new char[strlen(f.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(f.denumire) + 1, f.denumire);
	nou->inf.durata = f.durata;
	nou->inf.rating = f.rating;
	nou->inf.limitaVarsta = f.limitaVarsta;
	nou->next = nullptr;
	if (capLS == nullptr)
	{
		capLS = nou;
	}
	else
	{
		nodLS* temp = capLS;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	return capLS;
}

nodLP* inserareLP(nodLP* capLP, nodLS* capLS)
{
	nodLP* nou = new nodLP;
	nou->inf = capLS;
	nou->next = nullptr;
	if (capLP == nullptr)
	{
		capLP = nou;
	}
	else
	{
		nodLP* temp = capLP;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	return capLP;
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		cout << temp->inf.denumire << " " << temp->inf.durata << " " << temp->inf.rating << " " << temp->inf.limitaVarsta << endl;
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		cout << "Sublista: ";
		cout << endl;
		traversareLS(temp->inf);
		temp = temp->next;
	}
}
void nrFilme(nodLP* capLP, int durata, int* nr)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLS* tempLS = temp->inf;
		while (tempLS)
		{
			if (tempLS->inf.durata > durata)
				(*nr)++;
			tempLS = tempLS->next;
		}
		temp = temp->next;
	}

}
void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.denumire;
		delete temp;
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		delete temp;
		temp = temp2;
	}
}

void main()
{
	int n;
	Film f;
	char buffer[20];
	nodLP* capLP = nullptr;
	nodLS* capLS1 = nullptr;
	nodLS* capLS2 = nullptr;
	ifstream fis("fisier.txt");
	fis >> n;
	for (int i = 0; i < n; i++)
	{
		fis >> buffer;
		f.denumire = new char[strlen(buffer) + 1];
		strcpy_s(f.denumire, strlen(buffer) + 1, buffer);
		fis >> f.durata;
		fis >> f.rating;
		fis >> f.limitaVarsta;

		if (f.limitaVarsta < 15)
			capLS1 = inserareLS(capLS1, f);
		else
			capLS2 = inserareLS(capLS2, f);
		delete[] f.denumire;
	}
	fis.close();

	capLP = inserareLP(capLP, capLS1);
	capLP = inserareLP(capLP, capLS2);

	int nr = 0; //filme sub 3 ore
	int durata;
	cout << "Durata film : ";
	cin >> durata;
	nrFilme(capLP, durata, &nr);
	cout << nr;

	//traversareLP(capLP);
	dezalocareLP(capLP);
}