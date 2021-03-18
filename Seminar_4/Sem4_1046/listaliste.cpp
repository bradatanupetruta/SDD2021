#include <iostream>
#include <fstream>
using namespace std;

struct produs
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodLS {
	produs inf;
	nodLS* next;
};

struct nodLP {
	nodLS* inf;
	nodLP* next;
};

nodLS* inserareLS(nodLS* cap, produs p)
{
	nodLS* nou = new nodLS;
	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(p.denumire) + 1, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;
	nou->next = nullptr;
	if (cap == nullptr)
		cap = nou;
	else
	{
		nodLS* temp = cap;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;

}

nodLP* inserareLP(nodLP* capLP, nodLS* capLS)
{
	nodLP* nou = new nodLP;
	nou->inf = capLS;
	nou->next = nullptr;
	if (capLP == nullptr)
		capLP = nou;
	else
	{
		nodLP* temp = capLP;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = nou;
	}
	return capLP;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != nullptr)
	{
		cout << "Produsul cu codul: " << temp->inf.cod << ", denumire: " << temp->inf.denumire << ", pret:" << temp->inf.pret << ", cantitate:" << temp->inf.cantitate << endl;
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp != nullptr)
	{
		cout << "Sublista:" << endl;
		traversareLS(temp->inf);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->inf.denumire;
		delete temp;
		temp = temp2;
	}
}

void dezalocareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		delete temp;
		temp = temp2;
	}

}
//functie care sa afiseze suma tuturor produselor din lista
float pretTotal(nodLP* cap)
{
	float pr = 0;
	nodLP* temp = cap;
	while (temp != nullptr)
	{

		nodLS* tempLS = temp->inf;
		while (tempLS != nullptr)
		{
			pr += tempLS->inf.pret * tempLS->inf.cantitate;
			tempLS = tempLS->next;
		}
		temp = temp->next;
	}
	return pr;
}
int main()
{
	int n;
	ifstream fis("fisier.txt");
	fis >> n;
	produs p;
	char buffer[20];
	nodLP* capLP = nullptr;
	nodLS* capLS1 = nullptr, * capLS2 = nullptr;
	for (int i = 0; i < n; i++)
	{
		fis >> p.cod;
		fis >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);
		fis >> p.pret;
		fis >> p.cantitate;
		if (p.pret < 10)
			capLS1 = inserareLS(capLS1, p);
		else
			capLS2 = inserareLS(capLS2, p);
		delete[] p.denumire;
	}
	fis.close();
	capLP = inserareLP(capLP, capLS1);
	capLP = inserareLP(capLP, capLS2);
	traversareLP(capLP);
	cout << endl << "valoarea totala:" << pretTotal(capLP);
	dezalocareLP(capLP);

	return 0;
}