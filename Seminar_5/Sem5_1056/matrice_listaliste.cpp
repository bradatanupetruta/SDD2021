#include <iostream>
#include <fstream>
using namespace std;

struct nodLS {
	int col, val;
	nodLS* next;
};

struct nodLP {
	nodLS* inf;
	nodLP* next;
};

nodLS* inserareLS(nodLS* cap, int** mat, int nrLin, int nrCol, int indiceLinie) {
	
	for (int j = 0; j < nrCol; j++)
	{
		if (mat[indiceLinie][j] != 0)
		{
			nodLS* nod = new nodLS;
			nod->col = j;
			nod->val = mat[indiceLinie][j];
			nod->next = nullptr;
			if (cap == nullptr) {
				cap = nod;
			}
			else {
				nodLS* temp = cap;
				while (temp->next) {
					temp = temp->next;
				}
				temp->next = nod;
			}
		}
	}
	return cap;
}

nodLP* inserareLP(nodLP* capLP, nodLS* capLS) {
	nodLP* nod = new nodLP;
	nod->inf = capLS;
	nod->next = nullptr;
	
	if (capLP == nullptr) {
		capLP = nod;
	}
	else {
		nodLP* temp = capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nod;
		
	}
	return capLP;
}

void traversareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		cout << "Coloana: " << temp->col << ", Valoarea: " << temp->val << endl;
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP) {
	nodLP* temp = capLP;
	while (temp) {
		cout << "Linia din matrice:" << endl;
		traversareLS(temp->inf);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;

	while (temp) {
		nodLS* temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP) {
	nodLP* temp = capLP;

	while (temp) {
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		delete temp;
		temp = temp2;
	}
}

void main() {

	int nrLinii;
	int nrColoane;
	int** mat;
	
	nodLP* capLP = nullptr;

	ifstream fisier("Text.txt");
	fisier >> nrLinii;
	fisier >> nrColoane;

	mat = new int* [nrLinii];
	for (int i = 0; i < nrLinii; i++)
		mat[i] = new int[nrColoane];

	for (int i = 0; i < nrLinii; i++) 
		for (int j = 0; j < nrColoane; j++)
		{
			fisier >> mat[i][j];
		}
	fisier.close();

	for (int i = 0; i < nrLinii; i++)
	{
		nodLS* capLS = nullptr;
		capLS = inserareLS(capLS, mat, nrLinii, nrColoane, i);
		capLP = inserareLP(capLP, capLS);
	}

	traversareLP(capLP);
	dezalocareLP(capLP);

	for (int i = 0; i < nrLinii; i++)
		delete[] mat[i];
	delete[] mat;
}