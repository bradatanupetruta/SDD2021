#include<iostream>
#include<fstream>
using namespace std;

struct Angajat {
	int cod;
	char* nume;
	float salariu;
};

struct nodARB {
	Angajat info;
	nodARB* stanga, * dreapta;
};

nodARB* crearenod(Angajat a, nodARB* st, nodARB* dr) {
	nodARB* nou = new nodARB;
	nou->info.cod = a.cod;
	nou->info.nume = new char[strlen(a.nume) + 1];
	strcpy_s(nou->info.nume, strlen(a.nume) + 1, a.nume);
	nou->info.salariu = a.salariu;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodARB* inserarenod(Angajat a, nodARB* radacina) {
	nodARB* temp = radacina;
	if (radacina == nullptr) {
		temp = crearenod(a, nullptr, nullptr);
		return temp;
	}
	else {
		while (true)
		{
			if (a.cod < temp->info.cod) {
				if (temp->stanga != nullptr) {
					temp = temp->stanga;
				}
				else {
					temp->stanga = crearenod(a, nullptr, nullptr);
					return radacina;
				}
			}
			else if (a.cod > temp->info.cod) {
				if (temp->dreapta != nullptr) {
					temp = temp->dreapta;
				}
				else {
					temp->dreapta
						= crearenod(a, nullptr, nullptr);
					return radacina;
				}
			}
			else
			{
				return radacina;
			}
		}
	}
}

void traversarePreordine(nodARB* radacina) {
	if (radacina != nullptr) {
		cout << "codul " << radacina->info.cod << " nume : " << radacina->info.nume << " salariul: " << radacina->info.salariu << endl;
		traversarePreordine(radacina->stanga);
		traversarePreordine(radacina->dreapta);
	}
}

void traversareInOrdine(nodARB* radacina) {
	if (radacina != nullptr) {
		traversareInOrdine(radacina->stanga);
		cout << "codul " << radacina->info.cod << " nume : " << radacina->info.nume << " salariul: " << radacina->info.salariu << endl;
		traversareInOrdine(radacina->dreapta);
	}
}

void traversarePostOrdine(nodARB* radacina) {
	if (radacina != nullptr) {
		traversarePostOrdine(radacina->stanga);
		traversarePostOrdine(radacina->dreapta);
		cout << "codul " << radacina->info.cod << " nume : " << radacina->info.nume << " salariul: " << radacina->info.salariu << endl;
	}
}

void dezalocarePre(nodARB* radacina) {
	if (radacina != nullptr) {
		nodARB* st = radacina->stanga;
		nodARB* dr = radacina->dreapta;
		delete[] radacina->info.nume;
		delete radacina;
		dezalocarePre(st);
		dezalocarePre(dr);
	}
}
//sa se determine angajatii ai caror sal e mai mare de 1850
void asalariuMaiMareDe1850(nodARB* rad, nodARB** temp) {

	if (rad != nullptr) {
		if (rad->info.salariu > 1850) {

			*temp = inserarenod(rad->info, *temp);
		}
		asalariuMaiMareDe1850(rad->stanga, temp);
		asalariuMaiMareDe1850(rad->dreapta, temp);
	}
}

void AngajatiCuSalDat(nodARB* rad, Angajat* vect, int* nr, int prag) {
	if (rad != nullptr) {

		if (rad->info.salariu > prag) {
			vect[*nr] = rad->info;
			(*nr)++;
		}
		AngajatiCuSalDat(rad->stanga, vect, nr, prag);
		AngajatiCuSalDat(rad->dreapta, vect, nr, prag);
	}
}

void main() {
	int n;
	char buffer[20];
	nodARB* rd = nullptr;
	Angajat a;
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> a.cod;
		f >> buffer;
		a.nume = new char[strlen(buffer) + 1];
		strcpy_s(a.nume, strlen(buffer) + 1, buffer);
		f >> a.salariu;
		rd = inserarenod(a, rd);;
		delete[] a.nume;
	}
	f.close();
	cout << "\n";
	traversareInOrdine(rd);
	cout << "\n";
	traversarePostOrdine(rd);
	cout << "\n";
	traversarePreordine(rd);

	cout << "\n";
	nodARB* temp = nullptr;
	asalariuMaiMareDe1850(rd, &temp);
	cout << endl << "angajati cu sal mai mare: " << endl;
	traversarePreordine(temp);
	dezalocarePre(temp);

	cout << "\n";

	Angajat* vect = new Angajat[n];
	int nr = 0;
	AngajatiCuSalDat(rd, vect, &nr, 1850);
	cout << "Angajatul cu sal dat: ";
	for (int i = 0; i < nr; i++) {

		cout << "codul " << vect[i].cod << " nume : " << vect[i].nume << " salariul: " << vect[i].salariu << endl;
	}
	delete[] vect;

	dezalocarePre(rd);
}