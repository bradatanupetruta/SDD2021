#include<stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

struct farfurie {
	int diametru;
	char* tip;
	float pret;
};

struct nodStiva {
	farfurie inf;
	nodStiva* next;
};

nodStiva* push(nodStiva* varf, farfurie f) {
	nodStiva* nou = new nodStiva;
	nou->inf.diametru = f.diametru;
	nou->inf.pret = f.pret;
	nou->inf.tip = new char[strlen(f.tip) + 1];
	strcpy(nou->inf.tip, f.tip);
	nou->next = nullptr;
	if (varf == nullptr) {
		varf = nou;
	}
	else {
		nou->next = varf;
		varf = nou;
	}
	return varf;
}


int pop(nodStiva** varf, farfurie* f) {
	if (*varf == nullptr) {
		return-1;  //stiva e vida
	}
	else {
		(*f).diametru = (*varf)->inf.diametru;
		(*f).pret = (*varf)->inf.pret;
		(*f).tip = new char[strlen((*varf)->inf.tip) + 1];
		strcpy((*f).tip, (*varf)->inf.tip);
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		delete[] temp->inf.tip;
		delete temp;
		return 0;
	}
}


void traversare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != nullptr) {
		cout << "Diametru= " << temp->inf.diametru << ", tip= " << temp->inf.tip << ", pret= " << temp->inf.pret << endl;
		temp = temp->next;
	}
}



int main() {
	int n;
	farfurie f;
	nodStiva* varf = nullptr;
	char buffer[20];
	ifstream fin;
	fin.open("fisier.txt");
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> f.diametru;
		fin >> buffer;
		f.tip = new char[strlen(buffer) + 1];
		strcpy(f.tip, buffer);
		fin >> f.pret;
		varf = push(varf, f);
		delete[] f.tip;
	}
	fin.close();
	traversare(varf);

	farfurie f2;
	while (pop(&varf, &f2) == 0) {
		delete[] f2.tip;
	}

}