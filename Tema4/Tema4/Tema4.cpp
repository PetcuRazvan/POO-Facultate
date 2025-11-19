#include <iostream>
#include <regex>

using namespace std;

class Angajat {
	const int id;
	string nume = "Anonim";
	string departament = "neangajat";
	int salariu = 0;
	static int generatorId;

	void nextPrim() {
		while (true) {
			Angajat::generatorId++;
			int nr = 0;
			for (int i = 2; i * i <= Angajat::generatorId; i++) 
				if (Angajat::generatorId % i == 0)
					nr++;
			if (nr == 0)
				break;
		}
	}

public:

	//constructor fara param
	Angajat(): id(Angajat::generatorId) {
		this->nextPrim();
	}

	//constructor cu un singur param
	Angajat(const char* _nume) : id(Angajat::generatorId) {
		this->nextPrim();

		if (strlen(_nume) >= 3)
			this->nume = _nume;
	}

	//constructor cu toti param
	Angajat(const char* _nume, const char* _departament, int _salariu) : id(Angajat::generatorId) {
		this->nextPrim();

		if (strlen(_nume) >= 3)
			this->nume = _nume;

		if (strlen(_departament) >= 2)
			this->departament = _departament;

		if (_salariu > 0)
			this->salariu = _salariu;
	}

	void afisare() const {
		cout << "\n===================";
		cout << "\nId: " << this->id;
		cout << "\nNume: " << this->nume;
		cout << "\nDepartament: " << this->departament;
		cout << "\nSalariu: " << this->salariu;
		cout << "\n===================";
	}

	Angajat& operator=(Angajat& angajat) {
		if (this != &angajat) {
			this->nume = angajat.nume;
			this->departament = angajat.departament;
			this->salariu = angajat.salariu;
		}

		return *this;
	}
};
int Angajat::generatorId = 101;

class Masina {
	const int serieSasiu;
	string motor = "da-i din vasle";
	float kilometraj = 0;
	string producator = "nimeni";
	string model = "niciunul";
	string numarInmatriculare = "Nada ne suno";

	static int generatorSasiu;
	static int n;
	static string* numereInmatriculare;

	bool isNrValid(const char* numarInmatriculare) {
		regex b(R"(B [0-9]{2,3} [A-Z]{3})");

		return regex_match(numarInmatriculare, b);
	}

	bool isNrUnique(const char* numarInmatriculare) {
		string aux = numarInmatriculare;

		for (int i = 0; i < Masina::n; i++)
			if (aux == Masina::numereInmatriculare[i])
				return false;

		return true;
	}

	void addNumber(const char* numarInmatriculare) {
		string* aux = new string[Masina::n + 1];

		for (int i = 0; i < Masina::n; i++)
			aux[i] = Masina::numereInmatriculare[i];
		aux[Masina::n] = numarInmatriculare;

		Masina::n++;
		delete[] Masina::numereInmatriculare;
		Masina::numereInmatriculare = nullptr;
		Masina::numereInmatriculare = new string[n];

		for (int i = 0; i < Masina::n; i++)
			Masina::numereInmatriculare[i] = aux[i];

		delete[] aux;
	}

public:

	//constructor fara param
	Masina(): serieSasiu(++Masina::generatorSasiu) {}

	//constructor cu 2 parami
	Masina(const char* _producator, const char* _model): serieSasiu(++Masina::generatorSasiu) {
		if (strlen(_producator) >= 2)
			this->producator = _producator;

		if (strlen(_model) >= 2)
			this->model = _model;
	}

	//constructor cu toti param
	Masina(const char* _producator, const char* _model, const char* _motor, float _kilometraj) : serieSasiu(++Masina::generatorSasiu) {
		if (strlen(_producator) >= 2)
			this->producator = _producator;

		if (strlen(_model) >= 2)
			this->model = _model;

		if (strlen(_motor) >= 2)
			this->motor = _motor;

		if (_kilometraj > 0)
			this->kilometraj = _kilometraj;
	}

	void setNumarInmatriculare(const char* _numarInmatriculare) {
		if (this->isNrValid(_numarInmatriculare) && this->isNrUnique(_numarInmatriculare)) {
			this->numarInmatriculare = _numarInmatriculare;
			this->addNumber(_numarInmatriculare);
		}
	}

	void afisare() const {
		cout << "\n===================";
		cout << "\nSerie sasiu: " << this->serieSasiu;
		cout << "\nNumar de inmatriculare: " << this->numarInmatriculare;
		cout << "\nProducator: " << this->producator;
		cout << "\nModel: " << this->model;
		cout << "\nMotor: " << this->motor;
		cout << "\nKilometraj: " << this->kilometraj;
		cout << "\n===================";
	}
};
int Masina::generatorSasiu = 0;
int Masina::n = 0;
string* Masina::numereInmatriculare = nullptr;

int main() {
	{
		Angajat a1;
		Angajat a2("Petrica");
		Angajat a3("Iustin", "IT", 9000);

		a1.afisare();

		a2 = a1;

		a2.afisare();
		a3.afisare();
	}

	{
		Masina m1;
		Masina m2("BMW", "X6");
		Masina m3("Wolksvagen", "Golf 6", "V8", 657468.67);

		m1.afisare();

		m2.setNumarInmatriculare("B 101 VIG");
		m2.afisare();

		m3.setNumarInmatriculare("B 101 VIG");
		m3.afisare();
	}

	return 0;
}