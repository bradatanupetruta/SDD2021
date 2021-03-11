#include <iostream>
#include <fstream>
using namespace std;

struct email {
	char* mesaj;
	char* subiect;
	int nrDestinatari;
	float dimensiune;
};

struct nodStiva {
	email info;
	nodStiva* next;
};

nodStiva* push(nodStiva* varf, email e) {
	nodStiva* nou = new nodStiva();
	nou->info.mesaj = new char[strlen(e.mesaj) + 1];
	strcpy_s(nou->info.mesaj, strlen(e.mesaj) + 1, e.mesaj);
	nou->info.subiect = new char[strlen(e.subiect) + 1];
	strcpy_s(nou->info.subiect, strlen(e.subiect) + 1, e.subiect);
	nou->info.nrDestinatari = e.nrDestinatari;
	nou->info.dimensiune = e.dimensiune;

	nou->next = nullptr;

	if (varf == nullptr) {
		varf = nou;
	}
	else
	{
		nou->next = varf;
		varf = nou;
	}

	return varf;
}

int pop(nodStiva** varf, email* e) {
	if (*varf == nullptr) {
		return -1;
	}
	else
	{
		(*e).mesaj = new char[strlen((*varf)->info.mesaj) + 1];
		strcpy_s((*e).mesaj, strlen((*varf)->info.mesaj) + 1, (*varf)->info.mesaj);
		(*e).subiect = new char[strlen((*varf)->info.subiect) + 1];
		strcpy_s((*e).subiect, strlen((*varf)->info.subiect) + 1, (*varf)->info.subiect);
		(*e).nrDestinatari = (*varf)->info.nrDestinatari;
		(*e).dimensiune = (*varf)->info.dimensiune;
		nodStiva* aux = (*varf);
		*varf = (*varf)->next;
		delete[]aux->info.mesaj;
		delete[]aux->info.subiect;
		delete aux;
		return 0;
	}
}

void traversare(nodStiva* varf) {
	nodStiva* nou = varf;
	while (nou != NULL) {
		cout << "mesaj: " << nou->info.mesaj << " subiect: " << nou->info.subiect << " nr destinatari: " << nou->info.nrDestinatari << " dimensiune: " << nou->info.dimensiune << endl;
		nou = nou->next;
	}
}

void conversieVector(nodStiva** varf, email* vector, int* nr, int prag)
{
	email v;
	while (pop(varf, &v) == 0)
	{
		if (v.dimensiune > prag) {
			vector[*nr] = v;
			(*nr)++;
		}
		else {
			delete[]v.mesaj;
			delete[]v.subiect;
		}
	}
}

void main() {
	int n;
	email e;
	nodStiva* varf = nullptr;
	char buffer[30];
	ifstream fisier;
	fisier.open("fisier.txt");
	fisier >> n;
	for (int i = 0; i < n; i++)
	{
		fisier >> buffer;
		e.mesaj = new char[strlen(buffer) + 1];
		strcpy_s(e.mesaj, strlen(buffer) + 1, buffer);
		fisier >> buffer;
		e.subiect = new char[strlen(buffer) + 1];
		strcpy_s(e.subiect, strlen(buffer) + 1, buffer);
		fisier >> e.nrDestinatari;
		fisier >> e.dimensiune;
		varf = push(varf, e);
		delete[]e.mesaj;
		delete[]e.subiect;

	}
	/*traversare(varf);
	email e2;
	while (pop(&varf, &e2) == 0) {
		delete[]e2.mesaj;
		delete[]e2.subiect;
	}*/

	email* vector = new email[n];
	int m = 0;
	int prag;
	cout << "prag= ";
	cin >> prag;
	conversieVector(&varf, vector, &m, prag);
	for (int i = 0; i < m; i++) {
		cout << "Mesaj: " << vector[i].mesaj << " Subiect: " << vector[i].subiect << " Nr destinatari: " << vector[i].nrDestinatari << " Dimensiune" << vector[i].dimensiune;
		cout << endl;
	}
	for (int i = 0; i < m; i++) {
		delete[]vector[i].mesaj;
		delete[]vector[i].subiect;
	}
	delete[]vector;

}