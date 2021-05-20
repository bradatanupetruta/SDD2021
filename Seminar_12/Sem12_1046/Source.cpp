#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<malloc.h>

struct localitate
{
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
	localitate info;
	nodlp* next;
};

nodlp* inserareLP(nodlp* cap, localitate s)
{
	nodlp* nou = (nodlp*)malloc(sizeof(nodlp));
	nou->info.id = s.id;
	nou->info.denumire = (char*)malloc((strlen(s.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, s.denumire);

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

nodlp* cautareDupaDenumire(nodlp* cap, char *den)
{
	nodlp* temp = cap;
	while (temp && strcmp(temp->info.denumire, den)!=0)
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

//pt parcurgere in adancime
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

//parcurgere in adancime
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

//parcurgere in latime
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

void main()
{
	nodlp* graf = NULL;
	int nrNoduri;
	FILE* f = fopen("fisier.txt", "r");
	//printf("Nr de noduri: ");
	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		//id-ul va fi i-ul, numele citit de la tastatura
		localitate s;
		s.id = i;
		char buffer[20];
		//printf("Denumire localitate: ");
		fscanf(f,"%s", &buffer);
		s.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.denumire, buffer);
		graf = inserareLP(graf, s);
	}

	//inserare arce(vecinii pt fiecare nod)
	int nrArce = 0;
	//printf("Nr de arce: ");
	fscanf(f,"%d", &nrArce);

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
	//afisare
	traversareLP(graf);
	//parcurgere in adancime
	printf("\nParcurgere in adancime de la nodul 1:\n");
	parcurgereAdancime(graf, 0);

	printf("\nParcurgere in latime de la nodul 1:\n");
	parcurgereInLatime(graf, 0);

	char den[20];
	printf("Denumire localitate: ");
	scanf("%s", &den);
	nodlp* nodCurent = cautareDupaDenumire(graf, den);
	printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.denumire);

	dezalocareLP(graf);
}