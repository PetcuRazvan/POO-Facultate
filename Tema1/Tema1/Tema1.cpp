#include<stdio.h>
#include<malloc.h>

int* alocareVector(int n) {
	int* v;
	v = (int*)malloc(n * sizeof(int));
	return v;
}

void initializareVector(int* v, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("V[%d] = ", i);
		scanf("%d", v + i);
	}
}

void afisareVector(int* v, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

void inlocuireValoriImpare(int* v, int n)
{
	printf("Inlocuim valorile impare cu 0\n");
	for (int i = 0; i < n; i++)
		if (v[i] % 2)
			v[i] = 0;
}

void eliminareValoriPare(int* v, int* n)
{
	printf("Eliminam valorile pare\n");
	for (int i = 0; i < (*n); i++)
		if (v[i] % 2 == 0)
		{
			for (int j = i; j < (*n) - 1; j++)
				v[j] = v[j + 1];
			(*n)--;
			i--;
		}
}

void dublareValoriPare(int** v, int* n)
{
	
	int nrPare = 0;
	int j = 0;

	for (int i = 0; i < *(n); i++)
		if ((*v)[i] % 2 == 0)
			nrPare++;

	int* u;
	u = alocareVector((*n) + nrPare);

	for (int i = 0; i < (*n); i++)  
	{
		u[j++] = (*v)[i];
		if ((*v)[i] % 2 == 0)
			u[j++] = (*v)[i];
	}
	free(*v);  
	*v = u;   
	*n = (*n) + nrPare; 
}

void exercitiu() {
	int* vector;
	int lungime;
	int varianta;
	bool iesire = false;

	printf("Lungimea vectorului: ");
	scanf("%d", &lungime);
	vector = alocareVector(lungime);
	initializareVector(vector, lungime);
	afisareVector(vector, lungime);

	printf("================================\n");
	printf("1.Inlocuire valori impare cu 0.\n");
	printf("2.Eliminare valori pare.\n");
	printf("3.Dublarea valorilor pare.\n");
	printf("4.EXIT\n");

	while(true)
	{
		printf("\nIntroduceti varianta: ");
		scanf("%d", &varianta);
		printf("\n");

		switch (varianta) {
		case 1: inlocuireValoriImpare(vector, lungime);
			afisareVector(vector, lungime);
			break;
		case 2: eliminareValoriPare(vector, &lungime);
			afisareVector(vector, lungime);
			break;
		case 3:printf("Dublam valorile pare\n");
			dublareValoriPare(&vector, &lungime);
			afisareVector(vector, lungime);
			break;
		case 4: iesire = true;
		default:
			break;
		}

		if (iesire)
			break;
	}

	free(vector);
}

int main()
{
	exercitiu();

	return 0;
}