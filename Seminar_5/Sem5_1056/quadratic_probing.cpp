#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct calculator
{
	int spatiuStocare;
	float frecventaProcesor;
	char* producator;
};

struct hashT {
	calculator** vect;
	int dim;
};

int functie_dispersie(hashT tabela, char cheie[20]) {
	return cheie[0] % tabela.dim;
}

void inserare(hashT tabela, calculator* calc) {
	int poz = functie_dispersie(tabela, (*calc).producator);

	if (tabela.vect[poz] == nullptr) {
		tabela.vect[poz] = calc;
	}
	else {
		int index = 1;
		int c = 2;
		while (poz + c * index * index < tabela.dim) {
			if (tabela.vect[poz + c * index * index] == nullptr) {
				poz += c * index * index;
				tabela.vect[poz] = calc;
				break;
			}
			index++;
		}
	}
}

void traversareTabela(hashT tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vect[i] != nullptr) {
			cout << "Pozitie: " << i << endl;
			cout << "Spatiu stocare: " << tabela.vect[i]->spatiuStocare << " Frecventa: " << tabela.vect[i]->frecventaProcesor << " Producator: " << tabela.vect[i]->producator << endl;
		}
	}
}

void dezalocareTabela(hashT tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vect[i] != nullptr) {
			delete[]tabela.vect[i]->producator;
			delete tabela.vect[i];
		}

	}
	delete[] tabela.vect;
}

int stergere(hashT tabela, char denumire[20]) {
	int poz = functie_dispersie(tabela, denumire);

	if (tabela.vect[poz] == nullptr) {
		return -1;
	}

	else {
		if (strcmp(tabela.vect[poz]->producator, denumire) == 0) {
			delete[]tabela.vect[poz]->producator;
			delete tabela.vect[poz];
			tabela.vect[poz] = nullptr;
		}

		else {
			int index = 1;
			int c = 2;
			while (poz + c * index * index < tabela.dim) {
				if (strcmp(tabela.vect[poz + c * index * index]->producator, denumire) == 0) {
					poz += c * index * index;
					delete[]tabela.vect[poz]->producator;
					delete tabela.vect[poz];
					tabela.vect[poz] = nullptr;
					break;
				}
				index++;
			}
		}
	}
	return poz;
}

void main() {
	int n;
	calculator* calc;
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new  calculator * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vect[i] = nullptr;
	}
	ifstream fisier("fisier.txt");
	fisier >> n;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		calc = new calculator;
		fisier >> buffer;
		calc->producator = new char[strlen(buffer) + 1];
		strcpy_s(calc->producator, strlen(buffer) + 1, buffer);
		fisier >> calc->frecventaProcesor;
		fisier >> calc->spatiuStocare;
		inserare(tabela, calc);
	}
	fisier.close();
	traversareTabela(tabela);
	cin >> buffer;
	stergere(tabela, buffer);
	cout << endl;
	cout << endl;
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}