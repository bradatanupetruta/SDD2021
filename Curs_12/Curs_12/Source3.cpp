//Sortarea topologica

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

struct nod
{
	int info;
	nod* next;
};

void main()
{
	//vectorul de elemente de sortat
	int termen[20];
	//vector contor care retine numarul predecesorilor fiecarui element
	int nr_pred[20];
	//vector ce retine adresele listelor de succesori ai fiecarui element
	nod* lista_succ[20];

	int n, m, i, j, a, b;
	bool gata;

	nod* cap = NULL;
	int k1, k2;

	ifstream f("fisier3.txt");
	cout << "Sortare topologica\n";
	//cout << "\nDati numarul de termeni :";
	f >> n;
	for (i = 0; i < n; i++)
	{
		//cout << "Dati termenul " << i + 1 << " :";
		f >> termen[i];
		//elementele vectorilor se initializeaza cu 0, respectiv NULL, pentru ca nu s-a citit nici o pereche
		nr_pred[i] = 0;
		lista_succ[i] = NULL;
	}

	//cout << "\nDati numarul de relatii :";
	f >> m;
	for (i = 0; i < m; i++)
	{
		//cout << "Relatia numarul " << i << " (a<b) : ";
		//cout << "\na = ";
		f >> a;
		//cout << "b = ";
		f >> b;
		for (j = 0; j < n; j++)
		{
			if (termen[j] == a) 
				k1 = j;
			if (termen[j] == b) 
				k2 = j;
		}
		//se adauga k2 in lista de succesori ai lui k1
		cap = new nod;
		cap->info = k2;
		cap->next = lista_succ[k1];
		lista_succ[k1] = cap;
		//se incrementeaza nr. de predecesori ai lui k2
		nr_pred[k2] = nr_pred[k2] + 1;
	}
	f.close();

	for (i = 0; i < n; i++)
	{
		j = 0;
		gata = false;
		while ((j < n) && (!gata))
		{
			if (nr_pred[j] == 0)
			{
				cout << termen[j] << " ";
				gata = true;
				//pe pozitia j se pune -1 pt. a nu mai fi luat in considerare
				nr_pred[j] = -1;
				cap = lista_succ[j];
				while (cap != NULL)
				{
					//pentru toti succesorii se scade 1 din elementul corespunzator din vectorul contor
					//deoarece ulterior consideram ca acestia au un predecesor mai putin
					nr_pred[cap->info]--;
					cap = cap->next;
				}
			}
			else j++;
		}
	}
}
