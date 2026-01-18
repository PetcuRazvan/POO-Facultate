#include <iostream>
using namespace std;

class Animal {
protected:
	string nume = "Jane Doe";
	int varsta = 0;

public:
	Animal(const char* _nume, int _varsta) {
		if (strlen(_nume) >= 3)
			this->nume = _nume;

		if (_varsta > 0)
			this->varsta = _varsta;
	}

	virtual float getCostTratament(int zileTratament) = 0;

	friend ostream& operator<<(ostream& out, Animal& a);
};

ostream& operator<<(ostream& out, Animal& a) {
	out << "\nAnimal";

	return out;
}

class Caine : public Animal {
	float greutate = 0;
	bool rasaPericuloasa = false;

public:
	Caine(const char* _nume, int _varsta, int _greutate, bool _rasaPericuloasa) : Animal(_nume, _varsta) {
		if (_greutate > 0)
			this->greutate = _greutate;

		this->rasaPericuloasa = _rasaPericuloasa;
	}

	float getCostTratament(int zileTratament) override {
		float cost = zileTratament * 150.5;

		if (this->rasaPericuloasa)
			cost *= 2;

		return cost;
	}

	friend ostream& operator<<(ostream& out, Caine& c);
};

ostream& operator<<(ostream& out, Caine& c) {
	out << "\nNume: " << c.nume;
	out << "\nVarsta: " << c.varsta;
	out << "\nGreutate: " << c.greutate;
	out << "\nRasa periculoasa: " << c.rasaPericuloasa;

	return out;
}


class Hamster : public Animal {
	bool necesitaAnestezie = false;

public:
	Hamster(const char* _nume, int _varsta, bool _necesitaAnestezie) : Animal(_nume, _varsta) {
		this->necesitaAnestezie = _necesitaAnestezie;
	}

	float getCostTratament(int zileTratament) override {
		float cost = zileTratament * 60;

		if (this->necesitaAnestezie)
			cost += 50;

		return cost;
	}

	friend ostream& operator<<(ostream& out, Hamster& h);
};

ostream& operator<<(ostream& out, Hamster& h) {
	out << "\nNume: " << h.nume;
	out << "\nVarsta: " << h.varsta;
	out << "\nNecesita anesteie: " << h.necesitaAnestezie;

	return out;
}

class Cabinet {
	Animal** animale = nullptr;
	int nrAnimale = 0;
	string adresa = "nicaieri";

public:
	static float taxaUrgenta;

	Cabinet() {}

	Cabinet(const char* _adresa, int _nrAnimale, Animal** _animale) {
		if (strlen(_adresa) >= 4)
			this->adresa = _adresa;

		this->animale = new Animal * [_nrAnimale];

		for (int i = 0; i < _nrAnimale; i++)
			this->animale[i] = _animale[i];

		this->nrAnimale = _nrAnimale;
	}

	void operator+=(Animal& a) {
		Animal** temp = new Animal * [this->nrAnimale];
		for (int i = 0; i < this->nrAnimale; i++)
			temp[i] = this->animale[i];

		delete[] this->animale;
		this->animale = nullptr;

		this->animale = new Animal * [this->nrAnimale + 1];
		for (int i = 0; i < this->nrAnimale; i++)
			this->animale[i] = temp[i];

		this->animale[this->nrAnimale] = &a;

		this->nrAnimale++;

		delete[] temp;
	}

	friend ostream& operator<<(ostream& out, Cabinet& c);
};

ostream& operator<<(ostream& out, Cabinet& c) {
	for (int i = 0; i < c.nrAnimale; i++)
		out << *c.animale[i];

	return out;
}


float Cabinet::taxaUrgenta = 1000;

int main() {
	Caine c1("Dorel", 2, 3, false);
	Caine c2("Lupu", 3, 5, true);

	Hamster h1("Risotto", 1, true);

	Cabinet cab1("coltu strazii", 3, new Animal*[3]{ &c1, &c2, &h1 });

	cout << cab1;

	return 0;
}