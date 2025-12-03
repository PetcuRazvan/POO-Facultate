#include<iostream>
using namespace std;

//citire si afisare de enum folosind ostream si istream

class Angajat {

protected:
	string nume = "Anonim";
	float salariuBaza = 0;

public:
	Angajat() {
		cout << "\nApel constructor fara param Angajat";
	}

	Angajat(string _nume, float _salariuBaza) {
		cout << "\nApel constructor cu param Angajat";
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		cout << "\nApel constructor copiere Angajat";
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		cout << "\nApel operator= Angajat";
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);

	float calculSalariu() {
		return this->salariuBaza;
	}

	bool operator==(const Angajat& a)const {
		return this->nume == a.nume;
	}

	~Angajat() {
		cout << "\nApel destructor Angajat";
	}

	friend istream& operator>>(istream& in, Angajat& a);
};

ostream& operator<<(ostream& out, const Angajat& a) {
	out << "\nNume: " << a.nume;
	out << "\nSalariu baza: " << a.salariuBaza;
	return out;
}

istream& operator>>(istream& in, Angajat& a) {
	in >> a.nume >> a.salariuBaza;
	return in;
}


//relatie de tipul is a
//relatie de tipul derivare/mostenire

//clasa parinte/baza -> Angajat
//clasa copil/derivata -> Manager
class Manager: public Angajat {   //implicit este private => toata zona protected devine accesibila pt clasa Manager
	int nrSubordonati = 0;

public:
	Manager() {
		cout << "\nConstruire fara param manager";
	}

	Manager(string _nume, float _salariuBaza, int _nrSubordonati): Angajat(_nume, _salariuBaza) {
		cout << "\nConstruire cu toti param manager";
		this->nrSubordonati = _nrSubordonati;
	}

	Manager(const Manager& m): Angajat(m) {//conceptul de upcast a transformat managerul in angajat
		cout << "\nApel constructor de copiere Manager";
		this->nrSubordonati = m.nrSubordonati;
	}

	Manager(Angajat a, int _nrSubordonati): Angajat(a) {
		cout << "\napel constructor cu param2";
		this->nrSubordonati = _nrSubordonati;
	}

	Manager& operator=(const Manager& m) {
		cout << "\nApel operator = in clasa manager";
		if (this != &m) {
			this->Angajat::operator=(m);
			this->nrSubordonati = m.nrSubordonati;
		}
		return *this;
	}

	~Manager() {
		cout << "\nApel destructor Manager";
	}

	bool operator==(Manager& m) const{
		return this->nrSubordonati == m.nrSubordonati && (Angajat)*this == (Angajat)m;
	}

	friend ostream& operator<<(ostream& out, const Manager& M);
};

ostream& operator<<(ostream& out, const Manager& m) {
	out << (Angajat)m; //upcast explicit si apeleaza constructor de copiere
	out << "\nNr subordonati: " << m.nrSubordonati;
	return out;
}

int main() {

	Manager m1;
	Manager m2("Gigel", 1200, 3);
	Manager m3(m2);
	Manager m4(Angajat("Costel", 3000), 6);
	m1 = m4;
	cout << m1;

	if (m1 == m2)
		cout << "\nObj de tip manager au acelasi nume si nr subordonati";
	else
		cout << "\nBafta";

	//TEMA MANAGER HAS A ANGAJATI
	return 0;
}