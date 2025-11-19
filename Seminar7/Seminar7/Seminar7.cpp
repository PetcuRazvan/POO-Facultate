#include <iostream>
using namespace std;

//home2: sa se implementeze clasa masina care detine nr inmatriculare si are un constructor care primeste un nr preferential
//constant este serie sasiu, are si campul nr inmatriculare

class Abonat {
	const int id; //se genereaza nu se primeste ca param
	string detinator = "Anonim";
	int nrContacte = 0;
	string* contacte = nullptr;
	static int generatorId;  //folosit pt a genera automat id-ul, primul id este 101

public:

	//constructor fara param
	Abonat(): id(++generatorId) {}   //id este const deci trebuie initializat in lista de initializare

	Abonat(const char* _detinator, int _nrContacte, string* _contacte) : id(++ Abonat::generatorId) {
		if (strlen(_detinator) >= 3)
			this->detinator = _detinator;

		if (_nrContacte > 0 && _contacte != nullptr) {
			this->nrContacte = _nrContacte;

			this->contacte = new string[_nrContacte];

			for (int i = 0; i < _nrContacte; i++)
				this->contacte[i] = _contacte[i];
		}
	}

	Abonat(const Abonat& abonat): id(++ Abonat::generatorId) {
		this->detinator = abonat.detinator;
		this->nrContacte = abonat.nrContacte;

		if (abonat.contacte != nullptr) {
			this->contacte = new string[abonat.nrContacte];
			for (int i = 0; i < abonat.nrContacte; i++)
				this->contacte[i] = abonat.contacte[i];
		}
	}

	//suprascriere operator =
	Abonat& operator=(const Abonat& abonat) {
		if (this != &abonat) {
			delete[] this->contacte;
			this->contacte = nullptr;

			this->detinator = abonat.detinator;
			this->nrContacte = abonat.nrContacte;

			if (abonat.contacte != nullptr) {
				this->contacte = new string[abonat.nrContacte];
				for (int i = 0; i < abonat.nrContacte; i++)
					this->contacte[i] = abonat.contacte[i];
			}
			else {
				this->nrContacte = 0;
				this->contacte = nullptr;
			}
		}
		return *this;
	}

	bool operator==(string _x) const {
		for (int i = 0; i < this->nrContacte; i++)
			if (this->contacte[i] == _x)
				return true;

		return false;
	}

	//home1: sa se implementeze o modalitate de generare de id uri dupa o regula
	//exemplu1:  id este numar prim mai mare ca 100
	//exemplu2: id este dintr-o lista predefinita


	void afisare() const {
		cout << "\n===========================";
		cout << "\nId: " << this->id;
		cout << "\nDetinator: " << this->detinator;
		cout << "\nNr contacte: " << this->nrContacte;
		cout << "\nContacte: ";
		for (int i = 0; i < this->nrContacte; i++)
			cout << this->contacte[i] << "; ";
		cout << "\n===========================";
	}

	~Abonat() {
		delete[] this->contacte;
		this->contacte = nullptr;
	}
};

int Abonat::generatorId = 100; //initializam membru static

int main() {
	Abonat a1;
	a1.afisare();

	string numere[]{ "0759116012", "0751283029" };
	Abonat a2("Ion", 2, numere);
	a2.afisare();

	Abonat* pa;
	pa = new Abonat;
	delete pa;    //apel destructor

	Abonat a3 = a2;
	a3.afisare();

	a2 = a1;
	a2.afisare();

	if (a3 == "0759116012")
		cout << "\nGigel este in lista de contacte pt a3";
	else
		cout << "\nGigel nu este contact a lui a3";

	return 0;
}