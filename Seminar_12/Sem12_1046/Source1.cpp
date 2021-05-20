#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string>
#include<malloc.h>
using namespace std;


struct Localitate {
	int id;
	char* denumire;

};

struct nodlp;

struct nodls
{
	nodls* next;
	nodlp* info;
};

struct nodlp
{
	nodls* vecini;//lista de vecini
	Localitate info;
	nodlp* next;
};

nodlp* inserareLP(nodlp* cap, Localitate l)
{
	nodlp* nou = (nodlp*)malloc(sizeof(nodlp));
	nou->info.id = l.id;
	nou->info.denumire = (char*)malloc((strlen(l.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, l.denumire);

	nou->vecini = NULL;
	nou->next = NULL;

	if (cap)
	{
		nodlp* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

nodls* inserareLS(nodls* cap, nodlp* info)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = info;
	nou->next = NULL;
	if (cap)
	{
		nodls* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

nodlp* cautareDupaId(nodlp* cap, int id)
{
	nodlp* temp = cap;
	while (temp && temp->info.id != id)
	{
		temp = temp->next;
	}
	return temp;
}

void inserareArcInGraf(nodlp* graf, int idStart, int idStop)
{
	if (graf)
	{
		nodlp* nodStart = cautareDupaId(graf, idStart);
		nodlp* nodStop = cautareDupaId(graf, idStop);
		if (nodStart && nodStop)
		{
			nodStart->vecini = inserareLS(nodStart->vecini, nodStop);//daca este orientat
			nodStop->vecini = inserareLS(nodStop->vecini, nodStart);
		}
	}
}

void traversareLS(nodls* cap)
{
	nodls* temp = cap;
	while (temp)
	{
		printf("    %d.%s\n", temp->info->info.id + 1, temp->info->info.denumire);
		temp = temp->next;
	}
}

void traversareLP(nodlp* cap)
{
	nodlp* temp = cap;
	while (temp)
	{
		printf("%d.%s are urmatorii vecini: \n", temp->info.id + 1, temp->info.denumire);
		traversareLS(temp->vecini);
		temp = temp->next;
	}
}


struct NodStiva
{
	int id;
	NodStiva* next;
};

NodStiva* push(NodStiva* varf, int id)
{
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->next = NULL;
	nou->id = id;
	if (varf == NULL)
		return nou;
	else
	{
		nou->next = varf;
		varf = nou;
		return varf;
	}
}

int pop(NodStiva*& varf)
{
	if (varf)
	{
		int id = varf->id;
		NodStiva* temp = varf;
		varf = varf->next;
		free(temp);
		return id;
	}
	else
	{
		return -1;
	}
}

int calculareNumarNoduri(nodlp* graf)
{
	int contor = 0;
	nodlp* temp = graf;
	while (temp)
	{
		contor++;
		temp = temp->next;
	}
	return contor;
}


void parcurgereAdancime(nodlp* graf, int idNodStart)
{
	if (graf)
	{
		NodStiva* stiva = NULL;
		int nrNoduri = calculareNumarNoduri(graf);
		int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitate[i] = 0;
		}

		stiva = push(stiva, idNodStart);
		vizitate[idNodStart] = 1;

		while (stiva)
		{
			int idNodCurent = pop(stiva);

			nodlp* nodCurent = cautareDupaId(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.denumire);

			nodls* temp = nodCurent->vecini;
			while (temp)
			{
				if (vizitate[temp->info->info.id] == 0)
				{
					stiva = push(stiva, temp->info->info.id);
					vizitate[temp->info->info.id] = 1;
				}
				temp = temp->next;
			}
		}
	}
}

void dezalocareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		nodls* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodlp* cap) {
	nodlp* temp = cap;
	while (temp) {
		nodlp* temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters %s", temp->info.denumire);
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
	}
}

struct nodCoada {
	int id;
	nodCoada* next;
};

nodCoada* inserareCoada(nodCoada* cap, int id) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->id = id;
	nou->next = NULL;
	if (cap) {
		nodCoada* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

int extragereDinCoada(nodCoada*& cap) {
	if (cap) {
		int rezultat = cap->id;
		nodCoada* aux = cap;
		cap = cap->next;
		free(aux);
		return rezultat;
	}
	else {
		return -1;
	}
}

void parcurgereInLatime(nodlp* graf, int idStart) {
	if (graf) {
		nodCoada* coada = NULL;
		int nrNoduri = calculareNumarNoduri(graf);
		int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++) {
			vizitate[i] = 0;
		}

		coada = inserareCoada(coada, idStart);
		vizitate[idStart] = 1;

		while (coada) {
			int idNodCurent = extragereDinCoada(coada);
			nodlp* nodCurent = cautareDupaId(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.denumire);
			nodls* p = nodCurent->vecini;

			while (p) {
				if (vizitate[p->info->info.id] == 0) {
					vizitate[p->info->info.id] = 1;
					coada = inserareCoada(coada, p->info->info.id);
				}
				p = p->next;
			}

		}
	}
}

struct nodAbc {
	Localitate info;
	nodAbc* stanga;
	nodAbc* dreapta;
};

nodAbc* creare(Localitate s, nodAbc* st, nodAbc* dr)
{
	nodAbc* nou = (nodAbc*)malloc(sizeof(nodAbc));
	nou->info.id = s.id;
	nou->info.denumire = (char*)malloc((strlen(s.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, s.denumire);

	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodAbc* inserare_arb(Localitate s, nodAbc* rad)
{
	nodAbc* aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true)
		{
			if (s.id < aux->info.id)
				if (aux->stanga != NULL)
					aux = aux->stanga;
				else
				{
					aux->stanga = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.id > aux->info.id)
					if (aux->dreapta != NULL)
						aux = aux->dreapta;
					else
					{
						aux->dreapta = creare(s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
}

void inordine(nodAbc* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod=%d, denumire=%s", rad->info.id, rad->info.denumire);
		inordine(rad->dreapta);
	}
}

void dezalocare(nodAbc* rad)
{
	if (rad != NULL)
	{
		nodAbc* st = rad->stanga;
		nodAbc* dr = rad->dreapta;
		free(rad->info.denumire);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void conversie(nodlp* graf, nodAbc** rad) {
	nodlp* temp = graf;
	while (temp) {
		*rad = inserare_arb(temp->info, *rad);
		temp = temp->next;
	}
}

nodlp* cautareDupaNume(nodlp* cap, const char* den)
{
	nodlp* temp = cap;
	while (temp && strcmp(temp->info.denumire, den) != 0)
	{
		temp = temp->next;
	}
	return temp;
}

void main()
{
	nodlp* graf = NULL;

	FILE* f = fopen("fisier.txt", "r");

	int nrNoduri;
	//printf("Nr de noduri: ");

	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		//id-ul va fi i-ul, numele citit de la tastatura
		Localitate s;
		s.id = i;
		char buffer[20];
		//	printf("Denumire localitate: ");
		fscanf(f, "%s", &buffer);
		s.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.denumire, buffer);
		graf = inserareLP(graf, s);
	}

	//inserare arce(vecinii pt fiecare nod)
	int nrArce = 0;
	//printf("Nr de arce: ");
	fscanf(f, "%d", &nrArce);

	for (int i = 0; i < nrArce; i++)
	{
		int idStart;
		//printf("Id-ul nodului de start: ");
		fscanf(f, "%d", &idStart);
		int idStop;
		//printf("Id-ul nodului de stop: ");
		fscanf(f, "%d", &idStop);
		inserareArcInGraf(graf, idStart, idStop);
	}
	fclose(f);

	traversareLP(graf);

	printf("\n\n++++++++++++++");
	nodlp* cauta = cautareDupaNume(graf, "Timisoara");
	if (cauta) {
		printf("nodul gasit este: %s", cauta->info.denumire);
	}
	else {
		printf("nu exista nodul.");
	}


	printf("\n\n===== conversie arbore =======");
	nodAbc* rad = NULL;
	conversie(graf, &rad);
	inordine(rad);
	dezalocare(rad);

	printf("\nParcurgere in adancime de la nodul 1:\n");
	parcurgereAdancime(graf, 0);

	printf("\nParcurgere in latime de la nodul 1:\n");
	parcurgereInLatime(graf, 0);

	dezalocareLP(graf);
}
