#include<iostream>
using namespace std;

//metode virtuale DONE
//metode virtuale pure: metoda virtuala care nu e definita
//clase abstracte: o clasa care contine cel putin o metoda virtuala pura, si nu putem sa instantiem obiecte abstracte
//interfete: o clasa abstracta care contine doar metode virtuale pure

//PRINCIPII:
//depend upon the abstract, do not depend on the concrete
//open-closed principle => many client specific interfaces are better then one general interface

class Payable {
public:
	virtual float calculSalariu() = 0; //metoda virtuala pura
};

class Angajat: public Payable {

protected:
	string nume = "Anonim";
	float salariuBaza = 0;

public:

	Angajat() {

	}

	Angajat(string _nume) {
		this->nume = _nume;
	}

	Angajat(string _nume, float _salariuBaza) {
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);


	virtual float calculSalariu() override{                          //adaugand "virtual" a crescut memoria cu un pointer catre tabela "virtual function pointer"
		//pp ca exista o regula complexa de calcul salariu		de adrese pt fiecare derivare diferita
		return this->salariuBaza;
	}

	~Angajat() {
	}
};

ostream& operator<<(ostream& out, const Angajat& a) {
	out << "\nNume: " << a.nume;
	out << "\nSalariu baza: " << a.salariuBaza;
	return out;
}

class Manager :public Angajat {
	int nrSubordonati = 0;

public:
	Manager(string _nume, float _salariuBaza, int _nrSubordonati):Angajat(_nume, _salariuBaza) {
		this->nrSubordonati = _nrSubordonati;
	}

	float calculSalariu() override{                               //este optional sa punem override sau nu dar daca punem override, ne obliga sa derivam metoda si ne ajuta in caz ca gresim
		//return this->salariuBaza + this->nrSubordonati * 100;
		return Angajat::calculSalariu() + this->nrSubordonati * 100;
	}

	friend ostream& operator<<(ostream& out, Manager& m);
};

ostream& operator<<(ostream& out, Manager& m) {
	out << (Angajat&)m;
	out << "\nNr subordonati: " << m.nrSubordonati;

	return out;
}

class Lucrator :public Angajat {
	int nrNoptiLucrate = 0;

public:
	Lucrator(string _nume, float _salariuBaza, int _nrNoptiLucrate) :Angajat(_nume, _salariuBaza) {
		this->nrNoptiLucrate = _nrNoptiLucrate;
	}

	float calculSalariu() override{
		return Angajat::calculSalariu() + this->nrNoptiLucrate * 50;
	}


	friend ostream& operator<<(ostream& out, Lucrator& l);
};

ostream& operator<<(ostream& out, Lucrator& l) {
	out << (Angajat&)l;
	out << "\nNr nopti lucrate: " << l.nrNoptiLucrate;

	return out;
}

int main() {
	//Angajat a1("Angajatul Gigel", 1000);
	Manager m1("Manager Gigel", 1000, 10);
	Lucrator l1("Lucrator Gigel", 1000, 5);

	//cout << "\nSalariu angajat: " << a1.calculSalariu();
	cout << "\nSalariu Manager: " << m1.calculSalariu();
	cout << "\nSalariu Lucrator: " << l1.calculSalariu();

	//Calculam fondul necesar de salariu    era mai tare daca adaugam o clasa companie in relatie has a
	float totalSalarii = 0;
	/*Angajat v[] = { a1, m1, l1 };

	for (int i = 0; i < 3; i++)
		totalSalarii += v[i].calculSalariu();
	cout << "\nTotal salarii folosinf vector de obiecte: " << totalSalarii;*/

	totalSalarii = 0;
	Angajat* vp[] = { &m1, &l1 };

	for (int i = 0; i < 3; i++)
		totalSalarii += vp[i]->calculSalariu();
	cout << "\nTotal salarii folosinf vector de pointeri: " << totalSalarii;

	//tema: de transformat vectorul de pointeri in clasa companie

	return 0;
}