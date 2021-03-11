#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

//Bardahan Alexandru, grupa 1047

struct produs {
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodls {
	produs inf;
	nodls* next;
	nodls* prev;
};

nodls* inserare(nodls* cap, nodls** coada, produs p) {
	nodls* nou = new nodls;
	nou->inf.cod = new int[1];
	*(nou->inf.cod) = *(p.cod);
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL) {
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		*coada = nou;
	}
	else {
		nodls* temp = cap;
		while (temp->next != cap) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}

	return cap;
}

void traversare(nodls* cap) {
	nodls* temp = cap;
	while (temp->next != cap) {
		cout << "Cod= " << *(temp->inf.cod) << " Denumire= " << temp->inf.denumire << " Pret= " << temp->inf.pret <<
			" Cantitate= " << temp->inf.cantitate << endl;
		temp = temp->next;
	}
	cout << "Cod= " << *(temp->inf.cod) << " Denumire= " << temp->inf.denumire << " Pret= " << temp->inf.pret <<
		" Cantitate= " << temp->inf.cantitate << endl;
}

void traversareInversa(nodls* coada) {
	nodls* temp = coada;
	while (temp->prev != coada) {
		cout << "Cod= " << *(temp->inf.cod) << " Denumire= " << temp->inf.denumire << " Pret= " << temp->inf.pret <<
			" Cantitate= " << temp->inf.cantitate << endl;
		temp = temp->prev;
	}
	cout << "Cod= " << *(temp->inf.cod) << " Denumire= " << temp->inf.denumire << " Pret= " << temp->inf.pret <<
		" Cantitate= " << temp->inf.cantitate << endl;
}

void dezalocare(nodls* cap) {
	nodls* temp = cap;
	while (temp->next != cap) {
		nodls* temp2 = temp->next;
		delete temp->inf.cod;
		delete[] temp->inf.denumire;
		delete temp;
		temp = temp2;
	}
	delete temp->inf.cod;
	delete[] temp->inf.denumire;
	delete temp;
}

produs* copiereElement(int n, nodls* cap) {
	int i = 0;
	produs* vector = new produs[n];
	nodls* temp = cap;
	while (temp->next != cap) {
		vector[i].cod = new int[1];
		*(vector[i].cod) = *(temp->inf.cod);
		vector[i].denumire = new char[strlen(temp->inf.denumire) + 1];
		strcpy(vector[i].denumire, temp->inf.denumire);
		vector[i].pret = temp->inf.pret;
		vector[i].cantitate = temp->inf.cantitate;
		i++;
		temp = temp->next;
	}
	vector[i].cod = new int[1];
	*(vector[i].cod) = *(temp->inf.cod);
	vector[i].denumire = new char[strlen(temp->inf.denumire) + 1];
	strcpy(vector[i].denumire, temp->inf.denumire);
	vector[i].pret = temp->inf.pret;
	vector[i].cantitate = temp->inf.cantitate;
	i++;
	return vector;
}

void main() {
	int n;
	cout << "Nr produse: ";
	cin >> n;
	nodls* cap = NULL;
	nodls* coada = NULL;
	produs p;
	char buffer[20];
	for (int i = 0; i < n; i++) {
		cout << "Cod: ";
		p.cod = new int[1];
		cin >> *(p.cod);
		cout << " Denumire: ";
		cin >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);
		cout << " Pret: ";
		cin >> p.pret;
		cout << " Cantitate: ";
		cin >> p.cantitate;
		cap = inserare(cap, &coada, p);
		delete[] p.denumire;
		delete p.cod;
	}

	traversare(cap);
	traversareInversa(coada);

	produs* vector = new produs[n];
	vector = copiereElement(n, cap);

	cout << "----------Vector-----------------" << endl;
	for (int i = 0; i < n; i++) {
		cout << "Cod= " << *(vector[i].cod) << " Denumire= " << vector[i].denumire << " Pret= " << vector[i].pret <<
			" Cantitate= " << vector[i].cantitate << endl;
	}
	for (int i = 0; i < n; i++)
	{
		delete vector[i].cod;
		delete[] vector[i].denumire;
	}
	delete[] vector;

	dezalocare(cap);

	//fstream file;
	//file.open("fisier.txt", ios::in);

	//if (file.is_open()) {
	//	file >> n;

	//	for (int i = 0; i < n; i++) {
	//		produs p;
	//		char buffer[20];

	//		file >> p.cod;

	//		file >> buffer;
	//		p.denumire = new char[strlen(buffer) + 1];
	//		strcpy(p.denumire, buffer);

	//		file >> p.pret;

	//		file >> p.cantitate;

	//		cap = inserare(cap, p);
	//		delete[] p.denumire;
	//	}

	//

	//	file.close();
	//}
	//else {
	//	cout << "Eroare";
	//}


}
