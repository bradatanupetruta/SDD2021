#include <stdio.h>
#include <iostream>
using namespace std;

struct produs
{
	int *cod;
	char* den;
	float pret;
	float cant;
};

void citireVector(produs* p, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		cout << "Cod=";
		p[i].cod = new int[1];
		cin >> *(p[i].cod);
		cout << "Denumire=";
		cin >> buffer;
		p[i].den = new char[strlen(buffer) + 1];
		strcpy(p[i].den, buffer);
		cout << "Pret=";
		cin >> p[i].pret;
		cout << "Cantitate=";
		cin >> p[i].cant;
	}
}

void afisareVector(produs* p, int n)
{
	for (int i = 0; i < n; i++)
		cout << "Cod=" << *(p[i].cod) << ", Denumire=" << p[i].den << ", Pret=" << p[i].pret << ", Cantitate=" << p[i].cant << endl;
}

void dezalocareVector(produs* p, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] p[i].cod;
		delete[] p[i].den;
	}
	delete[] p;
}

void citire4Vectori(int *cod, char **den, float *pret, float *cant, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		cout << "Cod=";
		cin >> cod[i];
		cout << "Denumire=";
		cin >> buffer;
		den[i] = new char[strlen(buffer) + 1];
		strcpy(den[i], buffer);
		cout << "Pret=";
		cin >> pret[i];
		cout << "Cantitate=";
		cin >> cant[i];
	}
}

void afisare4Vectori(int* cod, char** den, float* pret, float* cant, int n)
{
	for (int i = 0; i < n; i++)
		cout << "Cod=" << cod[i] << ", Denumire=" << den[i] << ", Pret=" << pret[i] << ", Cantitate=" << cant[i] << endl;
}

void dezalocare4Vectori(int* cod, char** den, float* pret, float* cant, int n)
{
	delete[] cod;
	for (int i = 0; i < n; i++)
		delete[] den[i];
	delete[] den;
	delete[] pret;
	delete[] cant;
}

void citireMatrice(float** mat, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
		{
			cout << "mat[" << i << "][" << j << "]=";
			cin >> mat[i][j];
		}
}

void afisareMatrice(float** mat, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

void dezalocareMatrice(float** mat, int n)
{
	for (int i = 0; i < n; i++)
		delete[] mat[i];
	delete[] mat;
}

void main()
{
	int n;
	cout << "Nr. produse=";
	cin >> n;
	/*produs* p = new produs[n];

	citireVector(p, n);
	afisareVector(p, n);
	dezalocareVector(p, n);*/

	/*int* coduri = new int[n];
	char** denumiri = new char* [n];
	float* preturi = new float[n];
	float* cantitati = new float[n];
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, n);*/

	float** mat = new float* [n];
	for (int i = 0; i < n; i++)
		mat[i] = new float[3];

	citireMatrice(mat, n);
	afisareMatrice(mat, n);
	dezalocareMatrice(mat, n);
}