#include <iostream>
#include <fstream>
using namespace std;

struct departament
{
	int cod;
	char* denumire;
	int nrAngajati;
};

struct nodArb
{
	int BF;
	departament inf;
	nodArb* stanga, * dreapta;
};

nodArb* creareNod(departament d, nodArb* st, nodArb* dr)
{
	nodArb* nou = new nodArb;
	nou->inf.cod = d.cod;
	nou->inf.denumire = new char[strlen(d.denumire) + 1];
	strcpy_s(nou->inf.denumire, strlen(d.denumire) + 1, d.denumire);
	nou->inf.nrAngajati = d.nrAngajati;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(departament d, nodArb* rad)
{
	if (rad != nullptr)
	{
		if (d.cod < rad->inf.cod)
		{
			rad->stanga = inserareNod(d, rad->stanga);
			return rad;
		}
		else
			if (d.cod > rad->inf.cod)
			{
				rad->dreapta = inserareNod(d, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(d, nullptr, nullptr);
}

/*nodArb* inserareNod(departament d, nodArb* rad)
{
	nodArb* temp = rad;
	if (rad == nullptr)
	{
		temp = creareNod(d, nullptr, nullptr);
		return temp;
	}
	else
	{
		while (true)
		{
			if (d.cod < temp->inf.cod) {
				if (temp->stanga != nullptr) {
					temp = temp->stanga;
				}
				else {
					temp->stanga = creareNod(d, nullptr, nullptr);
					return rad;
				}
			}
			else if (d.cod > temp->inf.cod) {
				if (temp->dreapta != nullptr) {
					temp = temp->dreapta;
				}
				else {
					temp->dreapta = creareNod(d, nullptr, nullptr);
					return rad;
				}
			}
			else {
				return rad;
			}
		}
	}
}*/

void traversarePreordine(nodArb* rad) {
	if (rad != nullptr) {
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " 
			<< rad->inf.nrAngajati <<" BF = "<<rad->BF<< endl;
		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);
	}
}

void traversareInordine(nodArb* rad) {
	if (rad != nullptr) {
		traversareInordine(rad->stanga);
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " 
			<< rad->inf.nrAngajati << " BF = " << rad->BF << endl;
		traversareInordine(rad->dreapta);
	}
}

void traversarePostordine(nodArb* rad) {
	if (rad != nullptr) {
		traversarePostordine(rad->stanga);
		traversarePostordine(rad->dreapta);
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " 
			<< rad->inf.nrAngajati << " BF = " << rad->BF << endl;
	}
}

void dezalocare(nodArb* rad) {
	if (rad != nullptr) {
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		delete[]rad->inf.denumire;
		delete rad;
		dezalocare(st);
		dezalocare(dr);
	}
}

nodArb* cautare(nodArb* rad, int cod) {
	if (rad != nullptr) {
		if (cod == rad->inf.cod) {
			return rad;
		}
		else {
			if (cod < rad->inf.cod) {
				return cautare(rad->stanga, cod);
			}
			else {
				return cautare(rad->dreapta, cod);
			}
		}
	}
	else {
		return nullptr;
	}
}

void departCuAngPestePrag(nodArb* rad, nodArb** rad2, int prag)
{
	if (rad != nullptr)
	{
		if (rad->inf.nrAngajati > prag)
			*rad2 = inserareNod(rad->inf, *rad2);
		departCuAngPestePrag(rad->stanga, rad2, prag);
		departCuAngPestePrag(rad->dreapta, rad2, prag);
	}
}

void departCuAngPestePragVector(nodArb* rad, departament* vect, int* nr, int prag)
{
	if (rad != nullptr)
	{
		if (rad->inf.nrAngajati > prag)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		departCuAngPestePragVector(rad->stanga, vect, nr, prag);
		departCuAngPestePragVector(rad->dreapta, vect, nr, prag);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int nrNiveluri(nodArb* rad)
{
	if (rad != nullptr)
	{
		int nrNivSt = nrNiveluri(rad->stanga);
		int nrNivDr = nrNiveluri(rad->dreapta);
		return 1 + maxim(nrNivSt, nrNivDr);
	}
	else
		return 0;
}

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (aux->stanga != nullptr)
	{
		rad = aux->stanga;
		if (aux->dreapta != nullptr)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta != nullptr)
				temp = temp->dreapta;
			temp->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != nullptr)
			rad = aux->dreapta;
		else
			rad = nullptr;
	delete[] aux->inf.denumire;
	delete aux;
	return rad;
}

//nodArb* stergeNod(nodArb* rad, int cod)
//{
//	if (rad == nullptr)
//		return nullptr;
//	else
//		if (rad->inf.cod == cod)
//		{
//			rad = stergeRad(rad);
//			return rad;
//		}
//		else
//		{
//			nodArb* aux = rad;
//			while (true)
//			{
//				if (cod < aux->inf.cod)
//					if (aux->stanga == nullptr)
//						break;
//					else
//						if (aux->stanga->inf.cod == cod)
//							aux->stanga = stergeRad(aux->stanga);
//						else
//							aux = aux->stanga;
//				else
//					if (cod > aux->inf.cod)
//						if (aux->dreapta == nullptr)
//							break;
//						else
//							if (aux->dreapta->inf.cod == cod)
//								aux->dreapta = stergeRad(aux->dreapta);
//							else
//								aux = aux->dreapta;
//			}
//			return rad;
//		}
//}

nodArb* stergeNod(nodArb* rad, int cod)
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
			if (cod < rad->inf.cod)
			{
				rad->stanga = stergeNod(rad->stanga, cod);
				return rad;
			}
			else
				if (cod > rad->inf.cod)
				{
					rad->dreapta = stergeNod(rad->dreapta, cod);
					return rad;
				}
}

void numarareAngajati(nodArb* rad, int prag, int* nr)
{
	if (rad != nullptr)
	{
		if (rad->inf.nrAngajati >= prag)
			(*nr)++;
		numarareAngajati(rad->stanga, prag, nr);
		numarareAngajati(rad->dreapta, prag, nr);
	}
}

void departamenteFrunza(nodArb* rad, departament* vect, int* nr)
{
	if (rad != nullptr)
	{
		if (rad->stanga == nullptr && rad->dreapta == nullptr)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		departamenteFrunza(rad->stanga, vect, nr);
		departamenteFrunza(rad->dreapta, vect, nr);
	}
}

nodArb* stergeDepartDenumire(nodArb* rad, char* denumire)
{
	if (rad != nullptr)
	{
		if (strcmp(rad->inf.denumire, denumire) == 0)
		{
			rad = stergeNod(rad, rad->inf.cod);
			return rad;
		}
		else
		{
			rad->stanga = stergeDepartDenumire(rad->stanga, denumire);
			rad->dreapta = stergeDepartDenumire(rad->dreapta, denumire);
			return rad;
		}
	}
	else
		return nullptr;
}

void calculBF(nodArb* rad)
{
	if (rad != nullptr)
	{
		rad->BF = nrNiveluri(rad->dreapta) - nrNiveluri(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	cout << endl << "Rotatie dreapta!" << endl;
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	cout << endl << "Rotatie stanga!" << endl;
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	cout << endl << "Rotatie dreapta-stanga!" << endl;
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
	cout << endl << "Rotatie stanga-dreapta!" << endl;
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

void afisareNivel(nodArb* rad, int nivel) {
	if (rad == nullptr)
		return;
	if (nivel == 1) {
		cout << "Cod: " << rad->inf.cod << " Denumire: " << rad->inf.denumire << " Nr angajati: " << rad->inf.nrAngajati << " BF - " << rad->BF << endl;
	}

	else if (nivel > 1) {
		afisareNivel(rad->stanga, nivel - 1);
		afisareNivel(rad->dreapta, nivel - 1);
	}
}

void afisareNiveluri(nodArb* rad) {
	int inaltime = nrNiveluri(rad);
	for (int i = 1; i <= inaltime; i++) {
		cout << i << endl;
		afisareNivel(rad, i);
		cout << endl;
	}
}

void main() {
	int n;
	departament d;
	char buffer[20];
	nodArb* rad = nullptr;
	ifstream f("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> d.cod;
		f >> buffer;
		d.denumire = new char[strlen(buffer) + 1];
		strcpy_s(d.denumire, strlen(buffer) + 1, buffer);
		f >> d.nrAngajati;
		rad = inserareNod(d, rad);

		rad = reechilibrare(rad);

		delete[]d.denumire;
	}
	f.close();
	traversareInordine(rad);
	cout << endl;
	traversarePreordine(rad);
	cout << endl;
	traversarePostordine(rad);
	cout << endl;
	//nodArb* cautat = cautare(rad, 7);
	//if (cautat != nullptr) {
	//	cout << "Cod: " << cautat->inf.cod << " Denumire: " << cautat->inf.denumire << " Nr angajati: " << cautat->inf.nrAngajati << endl;
	//}

	//cout << endl;

	//cout << "Inaltime arbore: " << nrNiveluri(rad) << endl;

	////rad = stergeRad(rad);
	rad = stergeNod(rad, 3);
	rad = reechilibrare(rad);
	//char denumire[20];
	//cout << "Denumire de sters: ";
	//cin >> denumire;
	//rad = stergeDepartDenumire(rad, denumire);
	traversarePreordine(rad);

	cout << "Inaltime arbore: " << nrNiveluri(rad) << endl;
	cout << "Inaltime subarbore stang: " << nrNiveluri(rad->stanga) << endl;
	cout << "Inaltime subarbore drept: " << nrNiveluri(rad->dreapta) << endl;

	/*int gradEchilibru = nrNiveluri(rad->dreapta) - nrNiveluri(rad->stanga);
	if (gradEchilibru >= -1 && gradEchilibru <= 1)
		cout << "Arbore echilibrat, grad echilibru: " << gradEchilibru << endl;
	else
		cout << "Arbore neechilibrat" << endl;*/

	/*nodArb* rad2 = nullptr;
	departCuAngPestePrag(rad, &rad2, 10);
	traversareInordine(rad2);
	dezalocare(rad2);

	cout << endl;

	departament* vect = new departament[n];
	int nr = 0;
	departCuAngPestePragVector(rad, vect, &nr, 10);
	for(int i=0;i<nr;i++)
		cout << "Cod: " << vect[i].cod << " Denumire: " << vect[i].denumire << " Nr angajati: " << vect[i].nrAngajati << endl;
	delete[] vect;*/

	dezalocare(rad);
}