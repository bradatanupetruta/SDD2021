#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

struct nodLs {
	int col, val;
	nodLs* next;
};

struct nodLp {
	nodLs* inf;
	nodLp* next;
};

nodLs* inserareLs(nodLs* capLs, int** matrice, int nrLinii, int nrColoane, int Linie) 
{
	nodLs* nou = new nodLs;
	for (int j = 0; j < nrColoane; j++) {
		if (matrice[Linie][j] != 0) {
			nodLs* nou = new nodLs;
			nou->val = matrice[Linie][j];
			nou->col = j;
			nou->next = nullptr;
			if (capLs == nullptr) {
				capLs = nou;
			}
			else {
				nodLs* temp = capLs;
				while (temp->next != nullptr) {
					temp = temp->next;

				}
				temp->next = nou;

			}
		}
	}
	return capLs;
}

nodLp* inserareLp(nodLp* capLp, nodLs* capLs) {
	nodLp* nou = new nodLp;
	nou->inf = capLs;
	nou->next = nullptr;
	if (capLp == nullptr) {
		capLp = nou;
	}
	else {
		nodLp* temp = capLp;
		while (temp->next != nullptr) {
			temp = temp->next;

		}
		temp->next = nou;

	}
	return capLp;
}

void traversareLs(nodLs* capLs) {
	nodLs* temp = capLs;
	while (temp) {
		cout << "Coloana: " << temp->col << "Valoare: " << temp->val << endl;
		temp = temp->next;
	}
}

void traversareLp(nodLp* capLp) {
	nodLp* temp = capLp;
	while (temp) {
		cout << "SubLista : " << endl;
		traversareLs(temp->inf);
		temp = temp->next;
	}
}

void dezalocareLs(nodLs* capLs) {
	nodLs* temp = capLs;
	while (temp) {
		nodLs* temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

void dezalocareLp(nodLp* capLp) {
	nodLp* temp = capLp;
	while (temp) {
		nodLp* temp2 = temp->next;
		dezalocareLs(temp->inf);
		delete temp;
		temp = temp2;

	}
}

int main() {

	int nrLinii, nrColoane;

	ifstream fisier("fisier1.txt");
	fisier >> nrLinii >> nrColoane;

	int** matrice = new int* [nrLinii];
	for (int i = 0; i < nrLinii; i++) {
		matrice[i] = new int[nrColoane];
	}

	nodLp* capLp = nullptr;

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			fisier >> matrice[i][j];

		}
	}

	fisier.close();

	for (int i = 0; i < nrLinii; i++) {
		nodLs* capLs = nullptr;
		capLs = inserareLs(capLs, matrice, nrLinii, nrColoane, i);
		capLp = inserareLp(capLp, capLs);
	}

	traversareLp(capLp);
	dezalocareLp(capLp);

	return 0;
}
