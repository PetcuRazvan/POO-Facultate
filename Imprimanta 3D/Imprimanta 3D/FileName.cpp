#include <iostream>
#include <string>
using namespace std;

enum class Divizie {
	INFANTERIE,
	BOMBARDIER,
	INFIRMIER,
	LUNETIST
};

class Soldat {
protected:
	string nume = "JMOOOORT";
	Divizie divizia = Divizie::INFANTERIE;
	const string id;
	static int contor;

	static string nextId(Divizie _divizia) {
		switch (_divizia) {
		case Divizie::INFANTERIE:
			return "INF" + to_string(Soldat::contor++);
			break;
		case Divizie::BOMBARDIER:
			return "BOM" + to_string(Soldat::contor++);
			break;
		case Divizie::INFIRMIER:
			return "INR" + to_string(Soldat::contor++);
			break;
		case Divizie::LUNETIST:
			return "LUN" + to_string(Soldat::contor++);
			break;
		}
	}


public:
	
	Soldat(const char* _nume, Divizie _divizie) : id(Soldat::nextId(_divizie)){
		if (strlen(_nume) >= 3)
			this->nume = _nume;
	}

	Soldat(Soldat& s) :id(Soldat::nextId(s.divizia)) {
		this->nume = s.nume;
		this->divizia = s.divizia;
	}

	Soldat& operator=(Soldat& s) {
		if (this != &s) {
			this->nume = s.nume;
			this->divizia = s.divizia;
		}

		return *this;
	}

	string getId() {
		return this->id;
	}
};

int Soldat::contor = 0;

class Comandant :public Soldat {
	int nrSoldati = 0;
	Soldat** soldati = nullptr;

public:
	Comandant(const char* _nume, Divizie _divizie, int _nrSoldati, Soldat* _soldati) :Soldat(_nume, _divizie) {
		this->nrSoldati = _nrSoldati;
		this->soldati = new Soldat * [this->nrSoldati];

		for (int i = 0; i < this->nrSoldati; ++i)
			this->soldati[i] = &_soldati[i];
	}

	Soldat& operator[](int index) {
		if (index >= 0 && index < this->nrSoldati)
			return *this->soldati[index];
	}

	Comandant& operator-=(Soldat& s) {
		bool isIn = false;
		for (int i = 0; i < this->nrSoldati; ++i)
			if (this->soldati[i] = &s)
				isIn = true;

		if (isIn) {
			Soldat** aux = new Soldat * [this->nrSoldati - 1];
			for (int i = 0; i < this->nrSoldati; ++i)
				if (this->soldati[i] != &s)
					aux[i] = this->soldati[i];

			delete[] this->soldati;
			this->soldati = new Soldat * [--this->nrSoldati];
			this->soldati = aux;

			cout << "\nS a scos";
		}
		return *this;
	}

	~Comandant() {
		delete[] this->soldati;
	}
};

int main() {
	Soldat s1("Bogdan", Divizie::BOMBARDIER);
	Soldat s2("Mircea", Divizie::LUNETIST);

	Comandant c1("Rares", Divizie::INFANTERIE, 2, new Soldat[2]{ s1, s2 });
	//cout << c1.getId();

	Soldat s3 = c1[1];
	//cout << s3.getId();
	c1 -= s1;

	return 0;
}