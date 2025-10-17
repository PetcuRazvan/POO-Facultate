#include <iostream>
#include <cstring>
using namespace std;

char* initializareSir()
{
	char* sirAux;
	char* sir;
	int lungime;

	sirAux = new char[50];
	cin.get(sirAux, 50);
	cin.get();

	lungime = strlen(sirAux);

	sir = new char[lungime+1];
	strcpy(sir, sirAux);

	delete[] sirAux;
	return sir;
}

char** initializareVectorNume(int nrNume)
{
	char** vector = new char* [nrNume];

	for (int i = 0; i < nrNume; i++)
	{
		if (i == 0)
			cout << "Primul Nume: ";
		else
			cout << "Cel de al " << i + 1 << "-lea nume: ";
		
		vector[i] = initializareSir();
	}
	return vector;
}

void dezalocareVectorNume(char** vector, int randuri)
{
	for (int i = 0; i < randuri; i++)
		delete[] vector[i];
	
	delete[] vector;
}

int numararePrenume(char** vector, int nrNume, char* prenume)
{
	int nr = 0;

	bool gasit;
	char* cuvant;
	for (int i = 0; i < nrNume; i++)
	{
		gasit = false;

		cuvant = strtok(vector[i], " -");
		while (cuvant != NULL)
		{
			if (strcmp(cuvant, prenume) == 0)
				gasit = true;

			cuvant = strtok(NULL, " -");
		}
		if (gasit)
			nr++;
	}
	return nr;
}

void exercitiuSir()
{
	char** vectorNume;
	int nrNume;

	cout << "Numarul numelor: ";
	cin >> nrNume;
	cin.get();

	vectorNume = initializareVectorNume(nrNume);

	char* prenume;
	cout << endl << "Prenumele: ";
	prenume = initializareSir();

	int nr = numararePrenume(vectorNume, nrNume, prenume);

	cout << "Prenumele "<<prenume<<" a fost gasit de "<<nr<<" ori";
	
	delete[] prenume;
	dezalocareVectorNume(vectorNume, nrNume);
}

void afisareVector(int* vector, int lungime)
{
	if (lungime == 0)
		cout << endl << "Vectorul este gol";
	else
	{
		cout << endl << "Afisare vector:" << endl;
		for (int i = 0; i < lungime; i++)
			cout << vector[i] << " ";
	}
}

int* initializareVector(int lungime)
{
	int* vector;
	vector = new int[lungime];

	for (int i = 0; i < lungime; i++)
	{
		cout << "V[" << i << "] = ";
		cin >> vector[i];
	}

	return vector;
}

void stergerePrimeleNumere(int*& vector, int &lungime, int k)
{
	int* vectorAux;

	if (lungime <= k)
	{
		delete[] vector;
		vector = new int[0];
		lungime = 0;
	}
	else
	{
		vectorAux = new int[lungime - k];

		for (int i = k, j = 0; i < lungime; i++, j++)
			vectorAux[j] = vector[i];

		delete[] vector;
		vector = new int[lungime - k];

		for (int i = 0; i < lungime - k; i++)
			vector[i] = vectorAux[i];

		lungime = lungime - k;
		delete[] vectorAux;
	}
}

void dublarePrimeleNumere(int*& vector, int& lungime, int k)
{
	if (lungime <= k)
		k = lungime;

	int* vectorAux;
	vectorAux = new int[lungime + k];

	for (int i = 0, j = 0; i < lungime; i++, j++)
	{
		if (i < k)
		{
			vectorAux[j++] = vector[i];
			vectorAux[j] = vector[i];
		}
		else
		{
			vectorAux[j] = vector[i];
		}
	}

	lungime = lungime + k;
	delete[] vector;
	vector = new int[lungime];

	for (int i = 0; i < lungime; i++)
		vector[i] = vectorAux[i];

	delete[] vectorAux;
}

void exercitiuVector()
{
	int* vector;
	int lungime;

	cout << endl << "Lungimea Vectorului: ";
	cin >> lungime;

	vector = initializareVector(lungime);
	cout << endl;

	cout << "1.Sterge primele k numere." << endl;
	cout << "2.Dubleaza primele k numere." << endl;

	int optiune;
	int ok = 1;
	while(ok)
	{
		ok = 0;
		cout << endl << "Introduceti optiunea: ";

		cin >> optiune;

		int k;
		switch (optiune)
		{
		case 1:
			cout << "k = ";
			cin >> k;
			stergerePrimeleNumere(vector, lungime, k);
			afisareVector(vector, lungime);
			break;
		case 2:
			cout << "k = ";
			cin >> k;
			dublarePrimeleNumere(vector, lungime, k);
			afisareVector(vector, lungime);
			break;
		default:
			cout << "Nu exista aceasta optiune.";
			ok = 1;
		}
	}
}

void tema()
{
	

	cout << "1.Exercitiu vector." << endl;
	cout << "2.Exercitiu sir de caractere." << endl;

	int optiune;
	int ok = 1;
	while(ok)
	{
		ok = 0;

		cout << endl << "Introduceti optiunea: ";
		cin >> optiune;

		switch (optiune)
		{
		case 1:
			exercitiuVector();
			break;
		case 2:
			exercitiuSir();
			break;
		default:
			cout << "Nu exista aceasta optiune";
			ok = 1;
			break;
		}
	}
}

int main()
{
	tema();

	return 0;
}