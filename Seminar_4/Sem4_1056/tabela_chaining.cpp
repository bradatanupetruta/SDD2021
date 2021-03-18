#include <iostream>
#include <fstream>
using namespace std;

struct calculator
{
	int spatiuStocare;
	float frecventaProcesor;
	char* producator;
};

struct nodLS
{
	calculator inf;
	nodLS* next;
};

struct hashT {
	nodLS** vect;
	int dim;
};

int functie_dispersie(hashT tabela, char cheie[20]) {
	return cheie[0] % tabela.dim;
}

void inserare(hashT tabela, calculator calc) {
	if (tabela.vect != nullptr) {
		int poz = functie_dispersie(tabela, calc.producator);
		nodLS* nod = new nodLS;
		nod->inf.frecventaProcesor = calc.frecventaProcesor;
		nod->inf.producator = new char[strlen(calc.producator) + 1];
		strcpy_s(nod->inf.producator, strlen(calc.producator) + 1, calc.producator);
		nod->inf.spatiuStocare = calc.spatiuStocare;
		nod->next = nullptr;

		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = nod;
		}
		else // situatie de coliziune, cel putin un nod este pe pozitia respectiva
		{
			nodLS* temp = tabela.vect[poz];
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = nod;
		}
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		cout << "Spatiu stocare: " << temp->inf.spatiuStocare << " Frecventa: " << temp->inf.frecventaProcesor << " Producator: " << temp->inf.producator << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vect[i] != nullptr) {
			cout << "Pozitie: " << i << endl;
			traversareLS(tabela.vect[i]);
		}
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.producator;
		delete[] temp;
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vect[i] != nullptr) {
			dezalocareLS(tabela.vect[i]);
		}
	}
	delete[]tabela.vect;
}

void main() {

	int n;
	calculator calc;
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = new nodLS * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vect[i] = nullptr;
	}
	ifstream fisier("fisier.txt");
	fisier >> n;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		fisier >> buffer;
		calc.producator = new char[strlen(buffer) + 1];
		strcpy_s(calc.producator, strlen(buffer) + 1, buffer);
		fisier >> calc.frecventaProcesor;
		fisier >> calc.spatiuStocare;
		inserare(tabela, calc);

		delete[] calc.producator;
	}
	fisier.close();

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}