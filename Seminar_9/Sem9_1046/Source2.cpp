#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

//arbori
struct produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

struct nodArb {
	int BF;
	produs inf;
	nodArb* stanga;
	nodArb* dreapta;
};
//pas 1 - creare nod
nodArb* creareNod(nodArb* stanga, nodArb* dreapta, produs p) {

	nodArb* nou = new nodArb;

	nou->inf.cod = p.cod;
	nou->inf.denumire = new char[strlen(p.denumire) + 1];
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->dreapta = stanga;
	nou->stanga = dreapta;

	return nou;
}
//pas 2 - inserarea pe pozitia corespunzatoare
//nodArb* inserare(produs p, nodArb* rad) {
//
//	nodArb* aux = rad; //ma ajuta sa explorez toata nodurile mai intai pozitionandu-se pe rad si apoi trecand de la nod la nod
//	if (rad == NULL) {
//		aux = creareNod(NULL, NULL, p);
//		return aux; //returneaza un singur nod
//	}
//	else {
//		//caut pozitia unde vreau sa inserez
//		while (true) {
//			if (p.cod < aux->inf.cod) {
//				//verif daca exista fiu in stanga
//				if (aux->stanga) {
//					aux = aux->stanga;
//				}
//				else {
//					aux->stanga = creareNod(NULL, NULL, p);
//					return rad; 
//				}
//			}
//			else if (p.cod > aux->inf.cod) {
//				//verif daca exista fiu in dreapta
//				if (aux->dreapta) {
//					aux = aux->dreapta;
//				}
//				else {
//					aux->dreapta = creareNod(NULL, NULL, p);
//					return rad; 
//				}
//			}
//			else {
//				return rad; //cheie duplicata
//			}
//		}
//	}
//}

nodArb* inserare(produs p, nodArb* rad)
{
	if (rad != NULL)
	{
		if (p.cod < rad->inf.cod)
		{
			rad->stanga = inserare(p, rad->stanga);
			return rad;
		}
		else
			if (p.cod > rad->inf.cod)
			{
				rad->dreapta = inserare(p, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(NULL, NULL, p);
}

//preordine
void traversare_preordine(nodArb* rad) {
	if (rad) {
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate << " , BF="<<rad->BF;
		traversare_preordine(rad->stanga);
		traversare_preordine(rad->dreapta);
	}
}

//practic le sorteaza
void traversare_inordine(nodArb* rad) {
	if (rad) {
		traversare_inordine(rad->stanga);
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate << " , BF=" << rad->BF;
		traversare_inordine(rad->dreapta);
	}
}

void traversare_postordine(nodArb* rad) {
	if (rad) {
		traversare_postordine(rad->stanga);
		traversare_postordine(rad->dreapta);
		cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
			" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate << " , BF=" << rad->BF;
	}
}

void dezalocare(nodArb* rad) {

	if (rad) {
		//salvez copiii pt a nu ii pierde
		nodArb* stang = rad->stanga;
		nodArb* drep = rad->dreapta;

		delete[] rad->inf.denumire;
		delete rad;

		dezalocare(stang);
		dezalocare(drep);
	}
}

//fct de cautare
nodArb* cautare(nodArb* rad, int cheie) {
	if (rad) {
		if (rad->inf.cod == cheie) {
			return rad;
		}
		else {
			if (rad->inf.cod > cheie) {
				return cautare(rad->stanga, cheie);
			}
			else
				return cautare(rad->dreapta, cheie);

		}
	}
	return NULL;
}

//determinam numarul de niveluri ale arborelui
int maxim(int a, int b) {

	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}

int nr_niveluri(nodArb* rad) {
	if (rad) {

		int st = nr_niveluri(rad->stanga);
		int dr = nr_niveluri(rad->dreapta);
		return 1 + maxim(st, dr);

		//return 1 + maxim(nr_niveluri(rad->stanga), nr_niveluri(rad->dreapta));
	}
	else {
		return 0;
	}
}

//fct ce det elem din arb care au pret > de un prag
void detElem(nodArb* rad, produs* vect, int* nr, float prag) {
	if (rad) {
		if (rad->inf.pret > prag) {
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].denumire = new char[strlen(rad->inf.denumire) + 1];
			strcpy(vect[*nr].denumire, rad->inf.denumire);
			vect[*nr].pret = rad->inf.pret;
			vect[*nr].cantitate = rad->inf.cantitate;
			(*nr)++;
		}
		detElem(rad->stanga, vect, nr, prag);
		detElem(rad->dreapta, vect, nr, prag);
	}
}

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (aux->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta != NULL)
				temp = temp->dreapta;
			temp->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	delete[] aux->inf.denumire;
	delete aux;
	return rad;
}

nodArb* stergeNod(nodArb* rad, int cod)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.cod == cod)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			nodArb* aux = rad;
			while (true)
			{
				if (cod < aux->inf.cod)
					if (aux->stanga == NULL)
						break;
					else
						if (aux->stanga->inf.cod == cod)
							aux->stanga = stergeRad(aux->stanga);
						else
							aux = aux->stanga;
				else
					if (cod > aux->inf.cod)
						if (aux->dreapta == NULL)
							break;
						else
							if (aux->dreapta->inf.cod == cod)
								aux->dreapta = stergeRad(aux->dreapta);
							else
								aux = aux->dreapta;
			}
			return rad;
		}
}

nodArb* stergeNodRecursiv(nodArb* rad, int cod) {
	if (rad == NULL)
		return NULL;
	else {
		if (rad->inf.cod == cod) {
			rad = stergeRad(rad);
		}
		else {
			nodArb* aux = rad;
			if (cod < aux->inf.cod)
				aux->stanga = stergeNodRecursiv(aux->stanga, cod);
			else
				if (cod > aux->inf.cod)
					aux->dreapta = stergeNodRecursiv(aux->dreapta, cod);
		}
	}
	return rad;
}

//sa se numere cate produse au costul achizitie peste 10 (valoarea)
void detNrElemVal(nodArb* rad, float prag, int* nr) {
	if (rad) {
		if (rad->inf.pret * rad->inf.cantitate > prag) {
			(*nr)++;
		}
		detNrElemVal(rad->stanga, prag, nr);
		detNrElemVal(rad->dreapta, prag, nr);
	}
}

void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = nr_niveluri(rad->dreapta) - nr_niveluri(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	cout << endl << "Rotatie dreapta" << endl;
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	cout << endl << "Rotatie stanga" << endl;
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	cout << endl << "Rotatie dreapta-stanga" << endl;
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	cout << endl << "Rotatie stanga-dreapta" << endl;
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	if (rad->BF <= -2 && rad->stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && rad->dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && rad->dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && rad->stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

void traversareNivel(nodArb* rad, int nivelRad, int nivel)
{
	if (rad != nullptr && nivel <= nivelRad)
	{
		if (nivelRad - nr_niveluri(rad) == nivel)
		{
			cout << "\ncod: " << rad->inf.cod << " ,denumire: " << rad->inf.denumire <<
				" ,pret: " << rad->inf.pret << " ,cantitate: " << rad->inf.cantitate << " , BF= " << rad->BF;
		}
		traversareNivel(rad->stanga, nivelRad, nivel);
		traversareNivel(rad->dreapta, nivelRad, nivel);
	}
}

void traversarePeNivele(nodArb* rad)
{
	if (rad != nullptr)
	{
		for (int i = 0; i < nr_niveluri(rad); i++)
		{
			cout << endl << "Nivelul " << i + 1;
			traversareNivel(rad, nr_niveluri(rad), i);
		}
	}
}

void drum(nodArb* rad, int cheie, bool& gasit)
{
	if (rad) {
		if (rad->inf.cod == cheie) {
			gasit = true;
		}
		else {
			if (rad->inf.cod > cheie) {
				drum(rad->stanga, cheie, gasit);
			}
			else
				drum(rad->dreapta, cheie, gasit);
		}
	}
	if (gasit == true)
		cout << rad->inf.cod << " <-";
}

void main() {

	nodArb* rad = NULL;

	int nrProduse;
	char buffer[20];
	produs p;

	ifstream fis;
	fis.open("fisier.txt");
	fis >> nrProduse;

	for (int i = 0; i < nrProduse; i++) {

		fis >> p.cod;
		fis >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);
		fis >> p.pret;
		fis >> p.cantitate;

		rad = inserare(p, rad);

		rad = reechilibrare(rad);

		delete[] p.denumire;
	}
	fis.close();

	cout << "-------preordine-----";
	traversare_preordine(rad);

	cout << "\n-------inordine-----";
	traversare_inordine(rad);

	cout << "\n-------postordine-----";
	traversare_postordine(rad);

	/*cout << "\n-------cautare-----";
	nodArb* gasit = NULL;
	gasit = cautare(rad, 6);
	if (gasit) {
		cout << "\ncod: " << gasit->inf.cod << " ,denumire: " << gasit->inf.denumire <<
			" ,pret: " << gasit->inf.pret << " ,cantitate: " << gasit->inf.cantitate;
	}
	else {
		cout << "\nnodul nu exista!\n";
	}*/

	cout << "\n-------nr niveluri arbore = inaltime arbore-----";
	cout << nr_niveluri(rad);
	cout << "\n-------nr niveluri subarbore stang -----";
	cout << nr_niveluri(rad->stanga);
	cout << "\n-------nr niveluri subarbore drept -----";
	cout << nr_niveluri(rad->dreapta);

	/*cout << "\n\n";
	int gradEchilibru = nr_niveluri(rad->dreapta) - nr_niveluri(rad->stanga);
	if (gradEchilibru <= 1 && gradEchilibru >=-1) {
		cout << "\narbore echilibrat, grad echilibru: " << gradEchilibru;
	}
	else {
		cout << "\nnu este echilibrat\n";
	}*/

	//rad = stergeRad(rad);
	rad = stergeNod(rad, 3);
	rad = reechilibrare(rad);
	traversare_preordine(rad);
	cout << "\n-------nr niveluri arbore = inaltime arbore-----";
	cout << nr_niveluri(rad);
	cout << "\n-------nr niveluri subarbore stang -----";
	cout << nr_niveluri(rad->stanga);
	cout << "\n-------nr niveluri subarbore drept -----";
	cout << nr_niveluri(rad->dreapta);

	bool gasit = false;
	drum(rad, 8, gasit);

	/*cout << "\n\n";
	gradEchilibru = nr_niveluri(rad->dreapta) - nr_niveluri(rad->stanga);
	if (gradEchilibru <= 1 && gradEchilibru >= -1) {
		cout << "\narbore echilibrat, grad echilibru: " << gradEchilibru;
	}
	else {
		cout << "\nnu este echilibrat\n";
	}*/

	/*cout << "\n\n----det---:\n";
	produs* v = new produs[nrProduse];
	int dim = 0;
	detElem(rad, v, &dim, 5);
	for (int i = 0; i < dim; i++) {
		cout << "\ncod: " << v[i].cod << " ,denumire: " << v[i].denumire <<
			" ,pret: " << v[i].pret << " ,cantitate: " << v[i].cantitate;
	}
	for (int i = 0; i < dim; i++) {
		delete[] v[i].denumire;
	}
	delete[] v;*/

	dezalocare(rad);
}