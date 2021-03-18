#include <iostream>
#include <fstream>
using namespace std;

struct calculator {
	int spatiuStocare;
	float frecventaProcesor;
	char* producator;
};

struct nodLS {
	calculator inf;
	nodLS* next;
};

struct nodLP {
	nodLS* inf;
	nodLP* next;
	nodLP* prev;
};

nodLS* inserareLS(nodLS* cap, calculator calc) {
	nodLS* nod = new nodLS;
	nod->inf.frecventaProcesor = calc.frecventaProcesor;
	nod->inf.producator = new char[strlen(calc.producator) + 1];
	strcpy_s(nod->inf.producator, strlen(calc.producator) + 1, calc.producator);
	nod->inf.spatiuStocare = calc.spatiuStocare;
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
	return cap;
}

nodLP* inserareLP(nodLP* capLP, nodLS* capLS) {
	nodLP* nod = new nodLP;
	nod->inf = capLS;
	nod->next = nullptr;
	nod->prev = nullptr;

	if (capLP == nullptr) {
		capLP = nod;
	}
	else {
		nodLP* temp = capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nod;
		nod->prev = temp;
	}
	return capLP;
}

void traversareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		cout << "Spatiu stocare:" << temp->inf.spatiuStocare << endl;
		cout << "Producator: " << temp->inf.producator << endl;
		cout << "Frecventa: " << temp->inf.frecventaProcesor << endl;
		temp = temp->next;
	}
}

int nrLaptopLenovo(nodLP* capLP) {
	int numar = 0;
	nodLP* temp = capLP;

	while (temp) {
		nodLS* temp2 = temp->inf;
		while (temp2) {
			if (strcmp(temp2->inf.producator, "Lenovo") == 0) {
				numar++;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return numar;
}

void traversareLP(nodLP* capLP) {
	nodLP* temp = capLP;
	while (temp) {
		cout << "Sublista:" << endl;
		traversareLS(temp->inf);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;

	while (temp) {
		nodLS* temp2 = temp->next;
		delete[]temp->inf.producator;
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

	int n;
	int numar;
	calculator calc;
	nodLP* capLP = nullptr;
	nodLS* capLS1 = nullptr;
	nodLS* capLS2 = nullptr;

	ifstream fisier("fisier.txt");
	fisier >> n;
	char buffer[20];
	for (int i = 0; i < n; i++) {
		fisier >> buffer;
		calc.producator = new char[strlen(buffer) + 1];
		strcpy_s(calc.producator, strlen(buffer) + 1, buffer);
		fisier >> calc.frecventaProcesor;
		fisier >> calc.spatiuStocare;

		if (calc.spatiuStocare > 512) {
			capLS1 = inserareLS(capLS1, calc);
		}
		else {
			capLS2 = inserareLS(capLS2, calc);
		}
		delete[] calc.producator;
	}
	fisier.close();
	capLP = inserareLP(capLP, capLS1);
	capLP = inserareLP(capLP, capLS2);

	numar = nrLaptopLenovo(capLP);
	cout << "Nr laptop lenovo: " << numar;

	traversareLP(capLP);
	dezalocareLP(capLP);
}