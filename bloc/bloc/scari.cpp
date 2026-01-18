#include <iostream>
using namespace std;

class Scara {
	string adresa = "nicaieri";
	int nrApartamente = 0;
	int nrLocatari = 0;
	string* locatari = nullptr;
	const int id;
	static int nextId;

public:
	Scara() : id(Scara::nextId++) {}

	Scara(const char* _adresa, int _nrApartamente, int _nrLocatari, string* _locatari) : id(Scara::nextId++) {
		if (strlen(_adresa) >= 4)
			this->adresa = _adresa;

		if (_nrApartamente > 0)
			this->nrApartamente = _nrApartamente;

		if (_nrLocatari > 0 && _locatari != nullptr) {
			this->nrLocatari = _nrLocatari;

			this->locatari = new string[this->nrLocatari];
			for (int i = 0; i < this->nrLocatari; i++)
				this->locatari[i] = _locatari[i];
		}
	}

	string& operator[](int index) {
		if (index >= 0 && index < this->nrLocatari)
			return this->locatari[index];
	}

	float getProductivitate() {
		float prod = 0;
		prod += this->nrLocatari * 200;
		prod += this->nrApartamente * 3000;

		return prod;
	}

	friend ostream& operator<<(ostream& out, Scara& s);
};

ostream& operator<<(ostream& out, Scara& s) {
	out << "\nId: " << s.id;
	out << "\nAdresa: " << s.adresa;
	out << "\nNumar apartamente: " << s.nrApartamente;
	out << "\nLocatari: ";
	for (int i = 0; i < s.nrLocatari; i++)
		out << s.locatari[i] << ", ";

	return out;
}

int Scara::nextId = 0;

class Bloc {
	int nrScari = 0;
	Scara** scari = nullptr;

public:
	Bloc(int _nrScari, Scara** _scari) {
		if(_nrScari > 0 && _scari != nullptr) {
			this->nrScari = _nrScari;

			this->scari = new Scara * [this->nrScari];
			for (int i = 0; i < this->nrScari; ++i)
				this->scari[i] = _scari[i];
		}
	}

	Bloc& operator+=(Scara& s) {
		Scara** temp = new Scara * [this->nrScari + 1];
		for (int i = 0; i < this->nrScari; ++i)
			temp[i] = this->scari[i];
		temp[this->nrScari];

		delete[] this->scari;
		this->scari = temp;

		return *this;
	}

	float getProdMax() {
		int max = this->scari[0]->getProductivitate();

		for (int i = 1; i < this->nrScari; ++i)
			if (this->scari[i]->getProductivitate() > max)
				max = this->scari[i]->getProductivitate();

		return max;
	}

	float getProdMin() {
		int min = this->scari[0]->getProductivitate();

		for (int i = 1; i < this->nrScari; ++i)
			if (this->scari[i]->getProductivitate() < min)
				min = this->scari[i]->getProductivitate();

		return min;
	}

	float getProdTotal() {
		float prod = 0;
		for (int i = 0; i < this->nrScari; i++)
			prod += this->scari[i]->getProductivitate();

		return prod;
	}
};

int main() {
	Scara s1;
	Scara s2("Buzaului", 4, 3, new string[3]{ "andrei", "botezatu", "marius" });
	Scara s3("Vidin", 2, 5, new string[5]{ "andrei", "botezatu", "marius", "alin", "alex"});

	cout << s3;

	Bloc b1(3, new Scara * [3] {&s1, & s2, & s3});

	cout << "\n" << b1.getProdMax();
	cout << "\n" << b1.getProdMin();
	cout << "\n" << b1.getProdTotal();

	return 0;
}