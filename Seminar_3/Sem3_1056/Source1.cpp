#include <iostream>
#include <fstream>
using namespace std;

struct email {
	char* mesaj;
	char* subiect;
	int nrDestinatari;
	float dimensiune;
};

struct nodCoada {
	email info;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, email e)
{
	nodCoada* nou = new nodCoada();
	nou->info.mesaj = new char[strlen(e.mesaj) + 1];
	strcpy_s(nou->info.mesaj, strlen(e.mesaj) + 1, e.mesaj);
	nou->info.subiect = new char[strlen(e.subiect) + 1];
	strcpy_s(nou->info.subiect, strlen(e.subiect) + 1, e.subiect);
	nou->info.nrDestinatari = e.nrDestinatari;
	nou->info.dimensiune = e.dimensiune;

	nou->next = nullptr;

	if (*prim == nullptr && *ultim == nullptr)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, email* e)
{
	if (*prim != nullptr && *ultim != nullptr)
	{
		(*e).mesaj = new char[strlen((*prim)->info.mesaj) + 1];
		strcpy_s((*e).mesaj, strlen((*prim)->info.mesaj) + 1, (*prim)->info.mesaj);
		(*e).subiect = new char[strlen((*prim)->info.subiect) + 1];
		strcpy_s((*e).subiect, strlen((*prim)->info.subiect) + 1, (*prim)->info.subiect);
		(*e).nrDestinatari = (*prim)->info.nrDestinatari;
		(*e).dimensiune = (*prim)->info.dimensiune;
		nodCoada* aux = (*prim);
		*prim = (*prim)->next;
		delete[]aux->info.mesaj;
		delete[]aux->info.subiect;
		delete aux;
		return 0;
	}
	else
	{
		if (*prim == nullptr)
			*ultim = nullptr;
		return -1;
	}
}

void traversare(nodCoada* prim) {
	nodCoada* nou = prim;
	while (nou != NULL) {
		cout << "mesaj: " << nou->info.mesaj << " subiect: " << nou->info.subiect << " nr destinatari: " << nou->info.nrDestinatari << " dimensiune: " << nou->info.dimensiune << endl;
		nou = nou->next;
	}
}

void conversieVector(nodCoada** prim, nodCoada** ultim, email* vector, int* nr, int prag)
{
	email v;
	while (get(prim, ultim, &v) == 0)
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
	nodCoada* prim = nullptr, *ultim = nullptr;
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
		put(&prim, &ultim, e);
		delete[]e.mesaj;
		delete[]e.subiect;

	}
	/*traversare(prim);
	email e2;
	while (get(&prim, &ultim, &e2) == 0) {
		delete[]e2.mesaj;
		delete[]e2.subiect;
	}*/

	email* vector = new email[n];
	int m = 0;
	int prag;
	cout << "prag= ";
	cin >> prag;
	conversieVector(&prim, &ultim, vector, &m, prag);
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