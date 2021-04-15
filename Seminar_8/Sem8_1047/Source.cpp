#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct carte {
	int cod;
	char* editura;
	float pret;
	int an_publicare;
};

struct NodArb
{
	carte inf;
	NodArb* st, * dr;
};

NodArb* creareNod(carte c, NodArb* st, NodArb* dr)
{
	NodArb* nou = new NodArb;
	nou->inf.cod = c.cod;
	nou->inf.editura = new char[strlen(c.editura) + 1];
	strcpy(nou->inf.editura, c.editura);
	nou->inf.pret = c.pret;
	nou->inf.an_publicare = c.an_publicare;
	nou->st = st;
	nou->dr = dr;

	return nou;
}

NodArb* inserareNod(carte c, NodArb* rad)
{
	if (rad != nullptr)
	{
		if (c.cod < rad->inf.cod)
		{
			rad->st = inserareNod(c, rad->st);
			return rad;
		}
		else
			if (c.cod > rad->inf.cod)
			{
				rad->dr = inserareNod(c, rad->dr);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(c, nullptr, nullptr);
}

//NodArb* inserareNod(carte c, NodArb* rad) {
//	NodArb* temp = rad;
//	if (rad == nullptr) {
//		temp = creareNod(c, nullptr, nullptr);
//		return temp;
//	}
//	else {
//		while (true) {
//			if (c.cod < temp->inf.cod)
//			{
//				if (temp->st != nullptr) 
//					temp = temp->st;
//				else
//				{
//					temp->st = creareNod(c, nullptr, nullptr);
//					return rad;
//				}
//			}
//			else
//			{
//				if (c.cod > temp->inf.cod)
//				{
//					if (temp->dr != nullptr) 
//						temp = temp->dr;
//					else
//					{
//						temp->dr = creareNod(c, nullptr, nullptr);
//						return rad;
//					}
//				}
//				else
//				{
//					return rad;
//				}
//			}
//		}
//
//	}
//}

void traversarePreordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		cout << "PREORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;
		traversarePreordine(rad->st);
		traversarePreordine(rad->dr);
	}
}

void traversareInordine(NodArb* rad)
{
	if (rad != nullptr)
	{

		traversareInordine(rad->st);
		cout << "INORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;
		traversareInordine(rad->dr);
	}
}

void traversarePostordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		traversarePostordine(rad->st);
		traversarePostordine(rad->dr);
		cout << "POSTORD=> Cod= " << rad->inf.cod << ", Editura: " << rad->inf.editura << ", Pret: " << rad->inf.pret << ", An publicatie: " << rad->inf.an_publicare << endl;
	}
}

void determinareCarti(NodArb* rad, int an, carte* vect, int* nr)
{
	if (rad != nullptr)
	{
		if (rad->inf.an_publicare > an)
		{
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].editura = new char[strlen(rad->inf.editura) + 1];
			strcpy(vect[*nr].editura, rad->inf.editura);
			vect[*nr].pret = rad->inf.pret;
			vect[*nr].an_publicare = rad->inf.an_publicare;
			(*nr)++;
		}
		determinareCarti(rad->st, an, vect, nr);
		determinareCarti(rad->dr, an, vect, nr);
	}
}

void dezalocare(NodArb* rad)
{
	if (rad != nullptr)
	{
		NodArb* st = rad->st;
		NodArb* dr = rad->dr;
		delete[] rad->inf.editura;
		delete rad;

		dezalocare(st);
		dezalocare(dr);
	}
}

void dezalocareVector(carte* vect, int n) {
	for (int i = 0; i < n; i++) {
		delete[] vect[i].editura;
	}
	delete vect;
}

NodArb* stergeRad(NodArb* rad)
{
	NodArb* aux = rad;
	if (aux->st != nullptr)
	{
		rad = aux->st;
		if (aux->dr != nullptr)
		{
			NodArb* temp = aux->st;
			while (temp->dr != nullptr)
				temp = temp->dr;
			temp->dr = aux->dr;
		}
	}
	else
		if (aux->dr != nullptr)
			rad = aux->dr;
		else
			rad = nullptr;
	delete[] aux->inf.editura;
	delete aux;
	return rad;
}

NodArb* stergeNod(NodArb* rad, int cod)
{
	if (rad == nullptr)
		return nullptr;
	else
		if (rad->inf.cod == cod)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			NodArb* aux = rad;
			while (true)
			{
				if (cod < aux->inf.cod)
					if (aux->st == nullptr)
						break;
					else
						if (aux->st->inf.cod == cod)
							aux->st = stergeRad(aux->st);
						else
							aux = aux->st;
				else
					if (cod > aux->inf.cod)
						if (aux->dr == nullptr)
							break;
						else
							if (aux->dr->inf.cod == cod)
								aux->dr = stergeRad(aux->dr);
							else
								aux = aux->dr;
			}
			return rad;
		}
}

NodArb* stergereNod_recursiv(int cod, NodArb* rad)
{
	if (rad != nullptr)
	{
		if (cod < rad->inf.cod)
		{
			rad->st = stergereNod_recursiv(cod, rad->st);
		}
		else
			if (cod > rad->inf.cod)
			{
				rad->dr = stergereNod_recursiv(cod, rad->dr);
			}
			else rad = stergeRad(rad);
		return rad;
	}
	else return nullptr;
}


int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int nrNiveluri(NodArb* rad)
{
	if (rad != nullptr)
	{
		int stanga = nrNiveluri(rad->st);
		int dreapta = nrNiveluri(rad->dr);
		return 1 + maxim(stanga, dreapta);
	}
	else
		return 0;
}

//cate carti au pretul > 30
void cartiPeste30(NodArb* rad, int* nr)
{
	if (rad != nullptr) {
		if (rad->inf.pret > 30) {
			(*nr)++;
		}
		cartiPeste30(rad->st, nr);
		cartiPeste30(rad->dr, nr);
	}
}


//cartile din nodurile frunza salvate in vector
void frunze(NodArb* rad, carte* vect, int* nr)
{
	if (rad != nullptr)
	{
		if (rad->dr == nullptr && rad->st == nullptr)
		{
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].editura = new char[strlen(rad->inf.editura) + 1];
			strcpy(vect[*nr].editura, rad->inf.editura);
			vect[*nr].pret = rad->inf.pret;
			vect[*nr].an_publicare = rad->inf.an_publicare;
			(*nr)++;
		}
		frunze(rad->st, vect, nr);
		frunze(rad->dr, vect, nr);
	}
}

//sterge cartea de la o anumita editura
NodArb* stergeEditura(NodArb* rad, char* editura)
{
	if (rad != nullptr)
	{
		if (strcmp(rad->inf.editura, editura) == 0)
		{
			rad = stergeNod(rad, rad->inf.cod);
			return rad;
		}
		else
		{
			rad->st = stergeEditura(rad->st, editura);
			rad->dr = stergeEditura(rad->dr, editura);
			return rad;
		}
	}
	else
		return nullptr;
}

void main()
{
	int n;
	char buffer[20];
	NodArb* rad = nullptr;
	carte c;
	ifstream f;
	f.open("fisier.txt");
	f >> n;

	for (int i = 0; i < n; i++)
	{
		f >> c.cod;
		f >> buffer;
		c.editura = new char[strlen(buffer) + 1];
		strcpy(c.editura, buffer);
		f >> c.pret;
		f >> c.an_publicare;
		rad = inserareNod(c, rad);

		delete[] c.editura;
	}
	f.close();

	traversarePreordine(rad);
	cout << endl;
	traversareInordine(rad);
	cout << endl;
	traversarePostordine(rad);

	//cout << endl << "==========Cartile publicate dupa 2018==========";
	//carte* vectorCarti = new carte[n];
	//n = 0;
	//determinareCarti(rad, 2018, vectorCarti, &n);
	//for (int i = 0; i < n; i++)
	//{
	//	cout << "\nCod= " << vectorCarti[i].cod << ", Editura: " << vectorCarti[i].editura << ", Pret: " << vectorCarti[i].pret << ", An publicare: " << vectorCarti[i].an_publicare << endl;
	//}

	////dezaloc vect
	//dezalocareVector(vectorCarti, n);

	rad = stergeRad(rad);
	//rad = stergeNod(rad, 3);
	cout << endl;
	traversarePreordine(rad);
	
	char editura[20];
	cin >> editura;
	rad = stergeEditura(rad, editura);
	cout << "Stergere editura: " << endl;
	traversarePreordine(rad);

	cout << "Inaltime arbore: " << nrNiveluri(rad) << endl;
	cout << "Inaltime subarbore stang: " << nrNiveluri(rad->st) << endl;
	cout << "Inaltime subarbore drept: " << nrNiveluri(rad->dr) << endl;
	int gradEchilibru = nrNiveluri(rad->dr) - nrNiveluri(rad->st);
	if (gradEchilibru >= -1 && gradEchilibru <= 1)
		cout << "Arbore echilibrat, grad echilibru: " << gradEchilibru << endl;
	else
		cout << "Arbore neechilibrat" << endl;

	dezalocare(rad);
}
