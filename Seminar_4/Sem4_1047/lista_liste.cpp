#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

struct masina {
	char* marca;
	int nrKm;
	float pret;
	int capacitateCilindrica;
};

struct nodLs {
	masina inf;
	nodLs* next;
};

struct nodLp {
	nodLs* inf;
	nodLp* next;
};

nodLs* inserareLs(nodLs* capLs, masina m) {
	nodLs* nou = new nodLs;
	nou->inf.capacitateCilindrica = m.capacitateCilindrica;
	nou->inf.nrKm = m.nrKm;
	nou->inf.pret = m.pret;
	nou->inf.marca = new char[strlen(m.marca) + 1];
	strcpy(nou->inf.marca, m.marca);
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
		cout << temp->inf.capacitateCilindrica << " " << temp->inf.nrKm << " " << temp->inf.pret << " " << temp->inf.marca << endl;
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
		delete[] temp->inf.marca;
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

// o functie suma a preturilor tuturor masinilor din lista principala 
float pretTotal(nodLp* cap)
{
	float total = 0;
	nodLp* temp = cap;
	while (temp)
	{

		nodLs* tempLs = temp->inf;
		while (tempLs)
		{

			total += tempLs->inf.pret;
			tempLs = tempLs->next;
		}
		temp = temp->next;
	}
	return total;
}

int main() {
	int n;
	ifstream fisier("fisier1.txt");
	fisier >> n;
	masina m;
	char buffer[20];
	nodLp* capLp = nullptr;
	nodLs* capLs1 = nullptr;
	nodLs* capLs2 = nullptr;
	for (int i = 0; i < n; i++) {
		fisier >> m.capacitateCilindrica;
		fisier >> m.nrKm;
		fisier >> m.pret;
		fisier >> buffer;
		m.marca = new char[strlen(buffer) + 1];
		strcpy(m.marca, buffer);
		if (m.nrKm > 10000) {
			capLs1 = inserareLs(capLs1, m);
		}
		else {
			capLs2 = inserareLs(capLs2, m);
		}
		delete[] m.marca;
	}
	fisier.close();

	capLp = inserareLp(capLp, capLs1);
	capLp = inserareLp(capLp, capLs2);

	traversareLp(capLp);
	cout << pretTotal(capLp);
	dezalocareLp(capLp);

	return 0;
}


