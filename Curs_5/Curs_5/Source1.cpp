#include <stdio.h>
#include <malloc.h>
#include <iostream>
using namespace std;

//definire structura matrice rara, reprezentata prin vectori
struct MatriceRara
{
	int* val;
	int* lin;
	int* col;
	int m;
	int n;
	int nrnenule;
};

//functie pentru citirea unei matrice de la tastatura
int** citiremat(int& nrlin, int& nrcol)
{
	printf("Nr. de linii=");
	scanf("%d", &nrlin);
	printf("Nr. de coloane=");
	scanf("%d", &nrcol);

	int** a = new int* [nrlin];
	for (int i = 0; i < nrlin; i++) 
		a[i] = new int[nrcol];

	for (int i = 0; i < nrlin; i++)
		for (int j = 0; j < nrcol; j++)
		{
			printf("matr[%d][%d]=", i, j);
			scanf("%d", &a[i][j]);
		}
	return a;
}

//procedura pentru afisarea unei matrice
void afisare(int** a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++) 
			printf("%d ", a[i][j]);
	}
}

//functie pentru a verifica daca o matrice este rara
int rara(int** a, int nrlin, int nrcol)
{
	float s = 0;
	for (int i = 0; i < nrlin; i++)
		for (int j = 0; j < nrcol; j++) 
			if (a[i][j] != 0) 
				s++;
	if (s / (float)(nrlin * nrcol) < 0.3) 
		return s;
	else 
		return 0;
}

//functia pentru transformarea unei matrice complete in matrice rara reprezentata prin 3 vectori
MatriceRara transformare(int** a, int nrlin, int nrcol)
{
	MatriceRara b;
	b.m = b.n = b.nrnenule = 0;
	b.col = b.lin = b.val = NULL;
	int k = 0, temp;
	if (temp = rara(a, nrlin, nrcol))
	{
		b.val = (int*)malloc(temp * sizeof(int));
		b.col = (int*)malloc(temp * sizeof(int));
		b.lin = (int*)malloc(temp * sizeof(int));
		b.m = nrlin;
		b.n = nrcol;
		b.nrnenule = rara(a, nrlin, nrcol);
		for (int i = 0; i < nrlin; i++)
			for (int j = 0; j < nrcol; j++)
			{
				if (a[i][j])
				{
					b.val[k] = a[i][j];
					b.lin[k] = i;
					b.col[k] = j;
					k++;
				}
			}
	}
	else printf("\nMatricea nu este rara!");
	return b;
}

//procedura pentru afisarea unei matrice rare
void afisareRara(MatriceRara mat)
{
	printf("\n");
	for (int i = 0; i < mat.nrnenule; i++)
		printf("%d (%d,%d) ", mat.val[i], mat.lin[i], mat.col[i]);
}

//functie pentru extragerea elementului de pe linia i si col j a matricei rare
int extrag(MatriceRara a, int i, int j)
{
	for (int k = 0; k < a.nrnenule; k++)
		if ((a.lin[k] == i) && (a.col[k] == j)) 
			return a.val[k];
	return 0;
}

//procedura pentru calculul transpusei unei matrici stocate ca matrice rara
void transp(MatriceRara a)
{
	int aux;
	for (int i = 0; i < a.nrnenule; i++)
	{
		aux = a.col[i];
		a.col[i] = a.lin[i];
		a.lin[i] = aux;
	}
	for (int i = 0; i < a.nrnenule - 1; i++)
		for (int j = i + 1; j < a.nrnenule; j++)
		{
			if ((a.lin[i] > a.lin[j]) && (a.col[i] > a.col[j]))
			{
				aux = a.col[i];
				a.col[i] = a.col[j];
				a.col[j] = aux;
				aux = a.lin[i];
				a.lin[i] = a.lin[j];
				a.lin[j] = aux;
				aux = a.val[i];
				a.val[i] = a.val[j];
				a.val[j] = aux;
			}
		}
	aux = a.m;
	a.m = a.n;
	a.n = aux;
}

//dezalocare matrice
void dezaloc_matrice(int** a, int nrlin, int nrcol)
{
	for (int i = 0; i < nrlin; i++) 
		delete[] a[i];
	delete[] a;
}

//dezalocare vectori
void dezaloc_vectori(MatriceRara mat)
{
	free(mat.lin);
	free(mat.col);
	free(mat.val);
}

void main()
{
	int** mat1;
	int m, n;

	mat1 = citiremat(m, n);
	afisare(mat1, m, n);

	MatriceRara a;
	a = transformare(mat1, m, n);
	cout << "\nMatricea rara:" << endl;
	afisareRara(a);

	MatriceRara c = a;
	cout << "\nMatricea rara transpusa:" << endl;
	transp(c);
	afisareRara(c);

	//dezalocari
	dezaloc_matrice(mat1, m, n);
	dezaloc_vectori(a);
}