#include <iostream>
#include <Vector>
using namespace std;

template<class T>
T suma(T a, T b) {
	return a + b;
}

//relatie has a
template<class T>
class Colectie {
	T v[10];
	int nr = 0;

public:
	Colectie& operator+=(T _x) {
		this->v[nr++] = _x;
		return *this;
	}

	operator T() const{
		T total = 0;
		for (int i = 0; i < this->nr; i++)
			total += this->v[i];

		return total;
	}

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr elemente: " << c.nr;
		out << "\nElemente: ";
		for (int i = 0; i < c.nr; i++)
			out << c.v[i] << " ";

		return out;
	}
};

class Angajat {
	string nume = "";
	float salariu = 0;

public:
	Angajat() {};

	Angajat(float _salariu) {
		this->salariu = _salariu;
	}

	Angajat(string _nume, float _salariu) {
		this->nume = _nume;
		this->salariu = _salariu;
	}

	Angajat operator+(const Angajat& a) const {
		Angajat rez = *this;
		rez.nume += a.nume;
		rez.salariu += salariu;
		return rez;
	}

	Angajat& operator+=(const Angajat& a) const {
		Angajat rez = *this;
		rez = rez + a;
		return rez;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);
};

ostream& operator<<(ostream& out, const Angajat& a) {
	out << "\nNume: " << a.nume << "\nSalariu: " << a.salariu;
	return out;
}
int main() {
	//clase + functii template

	int rez = suma<int>(2, 6);
	cout << rez;

	Angajat a1("Gigel", 100), a2("Costel", 200);
	Angajat a3("Anonim", 0);
	a3 = suma<Angajat>(a1, a2);
	cout << a3;

	Colectie<int> Cint;
	Cint += 10;
	Cint += 20;
	
	Colectie<Angajat> Cangajat;
	Cangajat += a1;
	Cangajat += a2;
	cout << Cangajat;
	Angajat angRez;
	angRez = Cangajat;
	cout << angRez;

	//STL
	//faciliteaza lucrul cu structuri de date (vector, list, set, map)

	vector<int> vInt;
	vInt.push_back(10);
	vInt.push_back(20);
	vInt.push_back(30);

	for (int i = 0; i < vInt.size(); i++)
		cout << vInt[i] << " ";

	vector<int>::iterator it; //am declarat o variabila care retine membrul static iterator
	for (it = vInt.begin(); it != vInt.end(); it++) {
		cout << *it << " ";
	}
	//iteratorul din clasa vector este un pointer pentru fiecare element

	vector<int>::reverse_iterator rit;
	for (rit = vInt.rbegin(); rit != vInt.rend(); rit++) {
		cout << *rit << " ";
	}

	//de lucrat de utilizat vector intr-o clasa tip colectie
	//de folosit si celelalte stl uri, modelati in format de unicitate toti proprietarii de masini
	//fiecare proporietar unic are o lista unica de masini  sa avem unicitate proprietar dupa cnp, unicitate masini dupa codul de sasiu
	//exista posibilitatea ca 2 propr sa detina aceeasi masina sau nu?
	return 0;
}