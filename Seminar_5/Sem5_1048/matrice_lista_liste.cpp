#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

struct nodLS {
	int coloana, valoare;
	nodLS* next;
};

struct nodLP {
	nodLS* inf;
	nodLP* next;
};

nodLS* inserareLS(nodLS* capLS, int** mat, int nrLinii, int nrColoane, int indiceLinie)
{
	for (int j = 0; j < nrColoane; j++) {
		if (mat[indiceLinie][j] != 0) {
			nodLS* nou = new nodLS;
			nou->coloana = j;
			nou->valoare = mat[indiceLinie][j];
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
		}

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
		cout << "Coloana: " << temp->coloana << " Valoare: " << temp->valoare << endl;
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

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
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
	int nrLinii, nrColoane;
	int** mat;

	nodLP* capLP = nullptr;

	ifstream fis("fisier1.txt");
	fis >> nrLinii;
	fis >> nrColoane;
	mat = new int* [nrLinii];
	for (int i = 0; i < nrLinii; i++)
	{
		mat[i] = new int[nrColoane];
	}
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			fis >> mat[i][j];
		}
	}
	fis.close();
	for (int i = 0; i < nrLinii; i++) {
		nodLS* capLS = nullptr;
		capLS = inserareLS(capLS, mat, nrLinii, nrColoane, i);
		capLP = inserareLP(capLP, capLS);
	}
	traversareLP(capLP);
	dezalocareLP(capLP);
	for (int i = 0; i < nrLinii; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}