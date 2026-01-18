#include <iostream>
using namespace std;

class Dosar {
	string companie = "niciuna";
	int nrActe = 0;
	string* listaActe = nullptr;
	float salariu = 0;

public:
	static int nrDosare;

	Dosar() {
		Dosar::nrDosare++;
	}

	Dosar(const char* _companie, int _nrActe, string* _listaActe, float _salariu) {
		if (strlen(_companie) >= 4)
			this->companie = _companie;

		if (_nrActe > 0 && _listaActe != nullptr) {
			this->nrActe = _nrActe;

			this->listaActe = new string[this->nrActe];
			for (int i = 0; i < this->nrActe; i++)
				this->listaActe[i] = _listaActe[i];
		}

		if (_salariu >= 3000)
			this->salariu = _salariu;

		Dosar::nrDosare++;
	}

	Dosar(const Dosar& d) {
		this->companie = d.companie;
		this->nrActe = d.nrActe;
		this->listaActe = new string[this->nrActe];
		for (int i = 0; i < this->nrActe; i++)
			this->listaActe[i] = d.listaActe[i];
		this->salariu = d.salariu;

		Dosar::nrDosare++;
	}

	float getSalariu() {
		return this->salariu;
	}

	void setSalariu(float _salariu) {

		if (_salariu >= 3000)
			this->salariu = _salariu;
	}

	~Dosar() {
		delete[] this->listaActe;

		Dosar::nrDosare--;
	}
};

int Dosar::nrDosare = 0;

int main() {
	Dosar d;

	Dosar d1("IBM", 3, new string[3]{ "CV", "CI" }, 7000);

	return 0;
}