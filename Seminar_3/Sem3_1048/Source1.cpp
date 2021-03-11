#include <iostream>
#include <fstream>
using namespace std;

struct notificare
{
	char* mesaj;
	char* aplicatie;
	int ora;
	int prioritate;
};

struct nodCoada
{
	notificare inf;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, notificare notif)
{
	nodCoada* nou = new nodCoada;
	nou->inf.mesaj = new char[strlen(notif.mesaj) + 1];
	strcpy_s(nou->inf.mesaj, strlen(notif.mesaj) + 1, notif.mesaj);
	nou->inf.aplicatie = new char[strlen(notif.aplicatie) + 1];
	strcpy_s(nou->inf.aplicatie, strlen(notif.aplicatie) + 1, notif.aplicatie);
	nou->inf.ora = notif.ora;
	nou->inf.prioritate = notif.prioritate;
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

int get(nodCoada** prim, nodCoada** ultim, notificare* notif)
{
	if (*prim != nullptr && *ultim != nullptr)
	{
		(*notif).mesaj = new char[strlen((*prim)->inf.mesaj) + 1];
		strcpy_s((*notif).mesaj, strlen((*prim)->inf.mesaj) + 1, (*prim)->inf.mesaj);
		(*notif).aplicatie = new char[strlen((*prim)->inf.aplicatie) + 1];
		strcpy_s((*notif).aplicatie, strlen((*prim)->inf.aplicatie) + 1, (*prim)->inf.aplicatie);
		(*notif).ora = (*prim)->inf.ora;
		(*notif).prioritate = (*prim)->inf.prioritate;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		delete[] aux->inf.mesaj;
		delete[] aux->inf.aplicatie;
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

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		cout << "Aplicatie: " << temp->inf.aplicatie << "\nMesaj: " << temp->inf.mesaj << "\nOra: " << temp->inf.ora << "\nPrioritate: " << temp->inf.prioritate;
		cout << endl;
		temp = temp->next;
	}
}

void conversieCoadaVector(nodCoada** prim, nodCoada **ultim, notificare* vect, int* nr, int conditieOra)
{
	notificare ntf;
	while (get(prim, ultim, &ntf) == 0) {
		if (ntf.ora > conditieOra) {
			vect[*nr] = ntf;
			(*nr)++;
		}
		else {
			delete[] ntf.aplicatie;
			delete[] ntf.mesaj;
		}
	}
}

void main()
{
	int n;
	notificare notif;
	nodCoada* prim = nullptr, *ultim = nullptr;
	char buffer[20];
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		f >> notif.ora;
		f >> notif.prioritate;
		f >> buffer;
		notif.aplicatie = new char[strlen(buffer) + 1];
		strcpy_s(notif.aplicatie, strlen(buffer) + 1, buffer);
		f >> buffer;
		notif.mesaj = new char[strlen(buffer) + 1];
		strcpy_s(notif.mesaj, strlen(buffer) + 1, buffer);
		
		put(&prim, &ultim, notif);
		delete[] notif.aplicatie;
		delete[] notif.mesaj;
	}
	traversare(prim);
	/*notificare notif2;
	while (get(&prim, &ultim, &notif2) == 0)
	{
		delete[] notif2.aplicatie;
		delete[] notif2.mesaj;
	}*/

	notificare* vect = new notificare[n];
	int nr = 0;
	int ora;
	cout << "Ora: ";
	cin >> ora;
	conversieCoadaVector(&prim, &ultim, vect, &nr, ora);

	for (int i = 0; i < nr; i++)
		cout << "MESAJ= " << vect[i].mesaj << " " << " APLICATIE= " << vect[i].aplicatie << " ORA= " << vect[i].ora
		<< " PRIORITATE= " << vect[i].prioritate << endl;
	for (int i = 0; i < nr; i++) {
		delete[] vect[i].mesaj;
		delete[] vect[i].aplicatie;
	}
	delete[] vect;

}