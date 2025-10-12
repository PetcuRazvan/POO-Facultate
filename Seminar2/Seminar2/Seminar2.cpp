#include <iostream>
using namespace std;

void EliminareValoareMinima(int*& vector, int& lungime)  //e mai smecher C++
{
	int min = vector[0];
	int lungimeNoua;
	int* aux;
	int j = 0;
	int nr = 1;

	for (int i = 1; i < lungime; i++)
	{
		if (vector[i] == min)
			nr++;
		if (vector[i] < min)
		{
			min = vector[i];
			nr = 1;
		}
	}
		
	lungimeNoua = lungime - nr;
	aux = new int[lungimeNoua];
	
	for (int i = 0; i < lungime; i++)
		if (vector[i] != min)
			aux[j++] = vector[i];
	
	delete[] vector;  //asa eliberam
	vector = aux;

	lungime = lungimeNoua;
}

void dublareUltimaAparitie(int*& vector, int& lungime)
{
	int* aux;
	aux = new int[lungime + 1];

	
	for (int i = 0; i < lungime; i++)
	{
		aux[i] = vector[i];
	}
	aux[lungime] = vector[lungime - 1];

	delete[] vector;
	vector = aux;

	lungime++;
}

int main()
{
	int* v;
	int n;
	cin >> n;
	//v = (int*)malloc(n * sizeof(int));  //limbaj C
	v = new int[n];  //limbaj C++   alocare dinamica vector
	/*int* p;
	p = new int(n);*/  //aloca zona de memorie pentru un int pe care il initializeaza cu n
	
	for (int i = 0; i < n; i++)
		cin >> v[i];
	cout << endl;

	cout << "Vector initiat: ";
	for (int i = 0; i < n; i++)
		cout << v[i] <<" ";
	cout << endl;

	//Exercitiul 1: functia care elimina valoarea minima dintr-un vector indiferent de numarul de aparitii;
	dublareUltimaAparitie(v, n);
	cout << "Vector modificat: ";
	for (int i = 0; i < n; i++)
		cout << v[i] <<" ";
	cout << endl;

	//Exercitiul 2: Functia care dubleaza aparitia ultimului element din vector

	delete[] v;

	cout << "Joaca pe for" << endl;
	int i = 0;
	for (; i < n; )
	{
		cout << i << " ";
		i++;
	}
	return 0;
}