#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("Text.txt");

//Bulaceanu Alexandra-Irina, gr. 1048

struct produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodLs {
	produs inf;
	nodLs* next;
	nodLs* prev;

};

nodLs* inserare(nodLs* cap, produs p, nodLs** coada) {
	nodLs* nou = new nodLs;
	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(p.denumire) + 1, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;
	nou->next = nullptr;
	nou->prev = nullptr;
	if (cap == nullptr) {
		cap = nou;
		*coada = nou;
	}
	else {
		nodLs* temp = cap;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}

	return cap;
}

void traversareInversa(nodLs* coada) {
	nodLs* temp = coada;
	while (temp != nullptr) {
		cout << "cod= " << temp->inf.cod << " denumire= " << temp->inf.denumire << " pret= " << temp->inf.pret << " cant= " << temp->inf.cantitate << endl;

		temp = temp->prev;
	}

}

void traversare(nodLs* cap) {
	nodLs* temp = cap;
	while (temp != nullptr) {
		cout << "cod= " << temp->inf.cod << " denumire= " << temp->inf.denumire << " pret= " << temp->inf.pret << " cant= " << temp->inf.cantitate << endl;

		temp = temp->next;
	}

}

void dezalocare(nodLs* cap) {
	nodLs* temp = cap;
	while (temp != nullptr) {
		nodLs* temp2 = temp->next;
		if (temp->inf.denumire != nullptr)
			delete[] temp->inf.denumire;
		delete temp;
		temp = temp2;
	}
}

nodLs* citireDinFisier(nodLs* cap, produs p, nodLs** coada) {
	int n;
	char buffer[20];
	
	fin >> n;
	for (int i = 0; i < n; i++) {
		//cout << "cod: ";
		fin >> p.cod;
		//cout << "denumire: ";
		fin >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
		//cout << "pret: ";
		fin >> p.pret;
		fin >> p.cantitate;
		cap = inserare(cap, p, coada);
		delete[] p.denumire;
	}
	
	return cap;
}

void conversieLaVector(nodLs* cap, produs* produse, int* nr)
{
	nodLs* temp = cap;
	while (temp != nullptr)
	{
		//init pe componente
		produse[*nr].cod = temp->inf.cod;
		produse[*nr].denumire = new char[strlen(temp->inf.denumire) + 1];
		strcpy_s(produse[*nr].denumire, strlen(temp->inf.denumire) + 1, temp->inf.denumire);
		produse[*nr].pret = temp->inf.pret;
		produse[*nr].cantitate = temp->inf.cantitate;
		(*nr)++;
		nodLs* temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

void main() {
	int n;
	//cout << "nr prod: ";
	//cin >> n;
	nodLs* cap = nullptr;
	nodLs* coada = nullptr;
	produs p = { 0,nullptr,0,0 };
	/*char buffer[20];
	for (int i = 0; i < n;i++) {
		cout << "cod: ";
		cin >> p.cod;
		cout << "denumire: ";
		cin >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1,buffer);
		cout << "pret: ";
		cin >> p.pret;
		cout << "cant: ";
		cin >> p.cantitate;
		cap = inserare(cap,p);
		delete[] p.denumire;
	}*/
	cap = citireDinFisier(cap, p, &coada);
	
	traversare(cap);
	traversareInversa(coada);

	cout << "---------------Vector-------------" << endl;

	produs* produse = new produs[500];
	int nr = 0;
	conversieLaVector(cap, produse, &nr);
	for (int i = 0; i < nr; i++) {
		cout << "Cod= " << produse[i].cod << " Denumire= " << produse[i].denumire << " Pret= " << produse[i].pret << " Cant= " << produse[i].cantitate;
		cout << endl;
	}
	for (int i = 0; i < nr; i++)
	{
		delete[] produse[i].denumire;
	}
	delete[] produse;

	//dezalocare(cap);

}