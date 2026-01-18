#include<iostream>
using namespace std;

class Produs {
	const int id = 0;
	string denumire = "nimic";
	int stoc = 0;
	float pret = 0;

public:

	Produs(int _id, const char* _denumire, float _pret, int _stoc) :id(_id) {
		if (strlen(_denumire) >= 2)
			this->denumire = _denumire;

		if (_stoc > 0)
			this->stoc = _stoc;

		if (_pret > 0)
			this->pret = _pret;
	}

	Produs(const Produs& p, int _id) :id(_id) {
		this->denumire = p.denumire;
		this->stoc = p.stoc;
		this->pret = p.pret;
	}

	string getDenumire() {
		return this->denumire;
	}

	int getStoc() {
		return this->stoc;
	}

	float getPret() {
		return this->pret;
	}

	void setStoc(int _stoc) {
		if (_stoc > 0)
			this->stoc = _stoc;
	}

	friend  ostream& operator<<(ostream& out, const Produs& p);

	Produs& operator=(const Produs& p) {
		if (this != &p) {
			this->denumire = p.denumire;
			this->stoc = p.stoc;
			this->pret = p.pret;
		}

		return *this;
	}

	Produs operator+(int suma) {
		Produs aux(*this, this->id);
		aux.pret += 10;

		return aux;
	}

	Produs& operator+=(int suma) {
		this->pret += suma;

		return *this;
	}

	bool operator==(const Produs& p) const{
		if (this->id == p.id && this->denumire == p.denumire)
			return true;

		return false;
	}

	~Produs() {
		cout << "\nS-a dus produsul";
	}
};

ostream& operator<<(ostream& out, const Produs& p) {
	out << "\nId: " << p.id;
	out << "\nDenumire: " << p.denumire;
	out << "\nStoc: " << p.stoc;
	out << "\nPret: " << p.pret;
	return out;
}

class Magazin {
	Produs** produse = nullptr;
	int nrProduse = 0;

public:
	Magazin() {}

	Magazin(Magazin& m) {
		this->nrProduse = m.nrProduse;

		this->produse = new Produs * [m.nrProduse];
		for (int i = 0; i < m.nrProduse; i++)
			this->produse[i] = m.produse[i];
	}

	void addProdus(Produs& p) {
		Produs** aux;
		aux = new Produs * [this->nrProduse + 1];
		for (int i = 0; i < this->nrProduse; i++)
			aux[i] = this->produse[i];
		aux[this->nrProduse] = &p;

		delete[] this->produse;
		this->produse = nullptr;

		this->nrProduse++;

		this->produse = new Produs * [this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
			this->produse[i] = aux[i];

		delete[] aux;

		cout << p;
	}

	float operator-(int suma) {
		float venit = 0;

		for (int i = 0; i < this->nrProduse; i++) {
			int cantitateVanduta = this->produse[i]->getStoc() / 10;

			venit += cantitateVanduta * this->produse[i]->getPret();
		}

		return venit;
	}

	Magazin operator++(int) {
		Magazin vechi(*this);

		for (int i = 0; i < this->nrProduse; i++)
			this->produse[i]->setStoc(this->produse[i]->getStoc() + 1);

		return vechi;
	}

	Magazin& operator++() {
		for (int i = 0; i < this->nrProduse; i++)
			this->produse[i]->setStoc(this->produse[i]->getStoc() + 1);

		return *this;
	}

	~Magazin() {
		delete[] this->produse;
		this->produse = nullptr;
	}
};

enum class tipAngajat {
	Junior,
	Senior,
	Manager
};

class Angajat {
	tipAngajat tip = tipAngajat::Junior;
	const int cod = 0;
	string nume = "anonim";
	float salariu = 3000;

public:
	Angajat(int _cod, const char* _nume, float _salariu) : cod(_cod) {
		if (strlen(_nume) >= 3)
			this->nume = _nume;

		if (_salariu > 3000)
			this->salariu = _salariu;
	}
	
	Angajat(Angajat& a) : cod(a.cod) {
		this->nume = a.nume;
		this->salariu = a.salariu;
	}

	Angajat(int _cod): cod(_cod) {}

	int getCod() {
		return this->cod;
	}

	string getNume() {
		return this->nume;
	}

	float getSalariu() {
		return this->salariu;
	}

	void setNume(const char* _nume) {
		if (strlen(_nume) >= 3)
			this->nume = _nume;
	}

	void setSalariu(float _salariu) {
		if (_salariu > 3000)
			this->salariu = _salariu;
	}

	Angajat& operator++() {
		this->salariu *= 1.1;

		return *this;
	}

	Angajat& operator-(int suma) {
		if (this->salariu - suma < 0)
			this->salariu = 0;
		else
			this->salariu -= suma;

		return *this;
	}

	Angajat& operator=(const Angajat& a) {
		if (this != &a) {
			this->nume = a.nume;
			this->salariu = a.salariu;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);
	friend istream& operator>>(istream& in, Angajat& a);

	~Angajat() {
		cout << "\n" << this->nume << " a fost concediat";
	}
};

ostream& operator<<(ostream& out, const Angajat& a) {
	out << "\nCod: " << a.cod;
	out << "\nNume: " << a.nume;
	out << "\nSalariu: " << a.salariu;

	return out;
}

istream& operator>>(istream& in, Angajat& a) {
	do {
		cout << "\nNume: ";
		in >> a.nume;
	} while (a.nume.length() < 3);

	do {
		cout << "Salariu: ";
		in >> a.salariu;
	} while (a.salariu < 3000);

	return in;
}


class Companie {
	string nume = "Falit";
	int nrAngajati = 0;
	Angajat** angajati = nullptr;

public:
	Companie(const char* _nume, int _nrAngajati, Angajat** _angajati) {
		if (strlen(_nume) > 1)
			this->nume = _nume;

		if (_nrAngajati > 0 && _angajati != nullptr) {
			this->nrAngajati = _nrAngajati;

			this->angajati = new Angajat * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->angajati[i] = _angajati[i];
		}
	}

	Companie(Companie& c) {
		this->nume = c.nume;
		this->nrAngajati = c.nrAngajati;

		delete[] this->angajati;
		this->angajati = nullptr;

		this->angajati = new Angajat * [this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
			this->angajati[i] = c.angajati[i];
	}

	Companie() {}

	Companie& operator!() {
		for (int i = 0; i < this->nrAngajati; i++) {
			this->angajati[i]->setNume("anonim");
			this->angajati[i]->setSalariu(3000);
		}

		return *this;
	}

	Angajat& operator[](int i) const{
		return *(this->angajati[i]);
	}

	operator char* () {
		char* rez = new char[this->nume.length() + 1];
		strcpy(rez, this->nume.data());

		return rez;
	}

	explicit operator int() {
		return this->nrAngajati;
	}

	friend ostream& operator<<(ostream& out, const Companie& c);

	Companie operator+(const Companie& c) {
		Companie aux;

		aux.nume = this->nume + " si " + c.nume;
		aux.nrAngajati = this->nrAngajati + c.nrAngajati;

		int k = 0;
		aux.angajati = new Angajat * [aux.nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
			aux.angajati[k++] = this->angajati[i];
		for (int i = 0; i < c.nrAngajati; i++)
			aux.angajati[k++] = c.angajati[i];

		return aux;
	}

	~Companie() {
		delete[] this->angajati;
	}
};

ostream& operator<<(ostream& out, const Companie& c) {
	out << "\nNume: " << c.nume;
	out << "\nAngajati: ";
	for (int i = 0; i < c.nrAngajati; i++)
		out << c.angajati[i]->getNume() << " ";

	return out;
}


int main() {
	Angajat a1(120, "Popescu", 12000), a2(121, "Anghelescu", 6000), a3(122, "Loredana", 9000), a4(123, "Popa", 3000);
	++a1;

	/*Angajat a5(69);
	cin >> a5;
	cout << a5;*/


	Angajat** angajati;
	angajati = new Angajat * [2];
	angajati[0] = &a1;
	angajati[1] = &a2;

	Companie c1("Profi", 2, angajati);
	//cout << c1;

	angajati[0] = &a3;
	angajati[1] = &a4;

	Companie c2("Mega", 2, angajati);
	//cout << c2;

	//cout << (c1 + c2);

	cout << c1[0];
	cout << c2[1];

	return 0;
}