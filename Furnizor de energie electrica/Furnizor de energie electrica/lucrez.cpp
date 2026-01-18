#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Motocicleta {
	string producator = "anonim";
	int nrDrumuri = 0;
	int* distante = nullptr;

public:
	static char tipPermis;

	Motocicleta() {};

	Motocicleta(const char* _producator, int _nrDrumuri, int* _distante) {
		if (strlen(_producator) >= 4)
			this->producator = _producator;

		if (_nrDrumuri >= 1 && _distante != nullptr) {
			this->nrDrumuri = _nrDrumuri;

			this->distante = new int[this->nrDrumuri];
			for (int i = 0; i < this->nrDrumuri; i++)
				this->distante[i] = _distante[i];
		}
	}

	Motocicleta(Motocicleta& m) {
		this->producator = m.producator;
		this->nrDrumuri = m.nrDrumuri;

		this->distante = new int[this->nrDrumuri];
		for (int i = 0; i < this->nrDrumuri; i++)
			this->distante[i] = m.distante[i];
	}

	void setProducator(const char* _producator) {
		if (strlen(_producator) >= 4)
			this->producator = _producator;
	}

	void adaugareDistanta(int _distanta) {
		if (_distanta > 0)
			for (int i = 0; i < this->nrDrumuri; i++)
				this->distante[i] += _distanta;
	}

	void adaugareDistanta(int _distanta, int index) {
		if (_distanta > 0 && index >= 0 && index < this->nrDrumuri)
			this->distante[index] += _distanta;
	}

	~Motocicleta() {
		cout << "\nAccident";
	}

	void serializare(const char* numeFisier) {
		ofstream f(numeFisier, ios::binary);
		
		if (f.is_open()) {
			int lungime = this->producator.length() + 1;

			f.write((char*)&lungime, sizeof(int));
			f.write(this->producator.c_str(), lungime);

			f.write((char*)&this->nrDrumuri, sizeof(int));

			f.write((char*)this->distante, this->nrDrumuri * sizeof(int));
		}
		else
			cout << "\nEroare la deschiderea fissierului";
	}

	void deserializare(const char* numeFisier) {
		ifstream f(numeFisier, ios::binary);

		if (f.is_open()) {
			int lungime;
			f.read((char*)&lungime, sizeof(int));
			char* temp = new char[lungime];
			f.read(temp, lungime);
			this->producator = temp;
			delete[] temp;

			f.read((char*)&this->nrDrumuri, sizeof(int));

			if (this->distante != nullptr)
				delete[] this->distante;
			this->distante = new int[this->nrDrumuri];
			f.read((char*)this->distante, this->nrDrumuri * sizeof(int));
		}
		else
			cout << "\nEroare la deschiderea fissierului";
	}

	friend ostream& operator<<(ostream& out, Motocicleta& m);
};

ostream& operator<<(ostream& out, Motocicleta& m) {
	out << "\nProducator: " << m.producator;
	out << "\nNumar drumuri: " << m.nrDrumuri;
	out << "\nDistante: ";
	for (int i = 0; i < m.nrDrumuri; i++)
		out << m.distante[i] << ", ";

	return out;
}

char Motocicleta::tipPermis = 'A';

int main() {
	Motocicleta m1;
	Motocicleta m2("Suzuki", 3, new int[3] {100, 150, 90});
	Motocicleta m3 = m2;

	Motocicleta::tipPermis = 'B';

	m2.setProducator("Yamaha");
	m2.serializare("motociclete.bin");
	m1.deserializare("motociclete.bin");

	cout << m1;

	return 0;
}