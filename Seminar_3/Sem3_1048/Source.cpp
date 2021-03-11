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

struct nodStiva
{
	notificare inf;
	nodStiva* next;
};

nodStiva* push(nodStiva* varf, notificare notif)
{
	nodStiva* nou = new nodStiva;
	nou->inf.mesaj = new char[strlen(notif.mesaj) + 1];
	strcpy_s(nou->inf.mesaj, strlen(notif.mesaj) + 1, notif.mesaj);
	nou->inf.aplicatie = new char[strlen(notif.aplicatie) + 1];
	strcpy_s(nou->inf.aplicatie, strlen(notif.aplicatie) + 1, notif.aplicatie);
	nou->inf.ora = notif.ora;
	nou->inf.prioritate = notif.prioritate;
	nou->next = nullptr;
	if (varf == nullptr)
	{
		varf = nou;
	}
	else
	{
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf, notificare* notif)
{
	if (*varf == nullptr)
	{
		return -1;
	}
	else
	{
		(*notif).mesaj = new char[strlen((*varf)->inf.mesaj) + 1];
		strcpy_s((*notif).mesaj, strlen((*varf)->inf.mesaj) + 1, (*varf)->inf.mesaj);
		(*notif).aplicatie = new char[strlen((*varf)->inf.aplicatie) + 1];
		strcpy_s((*notif).aplicatie, strlen((*varf)->inf.aplicatie) + 1, (*varf)->inf.aplicatie);
		(*notif).ora = (*varf)->inf.ora;
		(*notif).prioritate = (*varf)->inf.prioritate;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		delete[] aux->inf.mesaj;
		delete[] aux->inf.aplicatie;
		delete aux;
		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		cout << "Aplicatie: " << temp->inf.aplicatie << "\nMesaj: " << temp->inf.mesaj << "\nOra: " << temp->inf.ora << "\nPrioritate: " << temp->inf.prioritate;
		cout << endl;
		temp = temp->next;
	}
}

void main()
{
	int n;
	notificare notif;
	nodStiva* varf = nullptr;
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
		varf = push(varf, notif);
		delete[] notif.aplicatie;
		delete[] notif.mesaj;
	}
	traversare(varf);
	notificare notif2;
	while (pop(&varf, &notif2) == 0)
	{
		delete[] notif2.aplicatie;
		delete[] notif2.mesaj;
	}
}
