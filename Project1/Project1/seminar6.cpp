#include<iostream>
using namespace std;

//atribut constant + atribut static

class Student {
	string nume;
	int nrNote;
	int* note;
	double buget;
	static double taxaRestanta;

public:
	Student() {
		cout << "\nApel constructor fara param";
		this->nume = "Anonim";
		this->nrNote = 0;
		this->note = nullptr;
		this->buget = 0;
	}

	Student(double _buget) {
		cout << "\nApel constructor cu 1 param";
		this->nume = "Anonim";
		this->nrNote = 0;
		this->note = nullptr;
		if (_buget > 0) {
			this->buget = _buget;
		}
		else {
			this->buget = 0;
		}
	}

	Student(const char* _nume, int _nrNote,
		int* _note, double _buget) {
		cout << "\nApel constructor cu toti param";
		if (strlen(_nume) >= 3) {
			this->nume = _nume;
		}
		else {
			this->nume = "Anonim";
		}
		if (_nrNote > 0 && _note != nullptr) {
			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++) {
				this->note[i] = _note[i];
			}
		}
		else {
			this->nrNote = 0;
			this->note = nullptr;
		}
		if (_buget > 0) {
			this->buget = _buget;
		}
		else {
			this->buget = 0;
		}
	}

	Student(const Student& s) {
		cout << "\nApel constructor de copiere";
		if (s.nume.length() >= 3)
			this->nume = s.nume;
		else
			this->nume = "Anonim";

		if (s.nrNote > 0 && s.note != nullptr) {
			this->nrNote = s.nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++) {
				this->note[i] = s.note[i];
			}
		}
		else {
			this->nrNote = 0;
			this->note = nullptr;
		}

		this->buget = s.buget;
	}

	void setNote(int* _note, int _nrNote) {
		if (_note != nullptr && _nrNote > 0) {
			delete[] this->note;
			this->note = nullptr;
			this->nrNote = 0;

			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++) {
				this->note[i] = _note[i];
			}
		}
		else {

		}
	}

	Student& operator=(const Student& s) {    //FORMA FINALA SUPRASCRIERE OPERATOR =
		//obj this deja exista
		//destructor + constructor de copiere

		cout << "\nApel operator =";

		if(this != &s)
		{
			if (this->note != nullptr) {
				delete[] this->note;
				this->note = nullptr;
			}

			if (s.nume.length() >= 3)
				this->nume = s.nume;
			else
				this->nume = "Anonim";

			if (s.nrNote > 0 && s.note != nullptr) {
				this->nrNote = s.nrNote;
				this->note = new int[this->nrNote];
				for (int i = 0; i < this->nrNote; i++) {
					this->note[i] = s.note[i];
				}
			}
			else {
				this->nrNote = 0;
				this->note = nullptr;
			}

			this->buget = s.buget;
		}

		return *this;
	}

	void setNota(int _nota, int _index) {
		if (_index >= 0 && _index < this->nrNote) {
			if (_nota >= 1 && _nota <= 10) {
				this->note[_index] = _nota;
			}
		}
	}

	int getNota(int _index) {
		if (_index >= 0 && _index < this->nrNote) {
			return this->note[_index];
		}
	}

	int getNrNote() {
		return this->nrNote;
	}

	void afisare() const {
		cout << "\n-------------";
		cout << "\nNume: " << this->nume;
		cout << "\nNr note: " << this->nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < this->nrNote; i++) {
			cout << this->note[i] << " ";
		}
		cout << "\nBuget: " << this->buget;
		cout << "\n-------------";
	}

	~Student() {
		cout << "\nApel destructor" << " " << this->nume;
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}

	static double getTaxaRestanta() {
		return Student::taxaRestanta;  //sau doar taxaRestanta dar e mai clar cu Student::
	}

	static void setTaxaRestanta(double _taxa) {
		if (_taxa > 0) 
			Student::taxaRestanta = _taxa;
		else
			Student::taxaRestanta = 100;
	}
};

double Student::taxaRestanta = 100;     //initializare atribut static

//Student f1(Student s) {
//	return s;
//}
//
//Student& f2(Student s[10], int n) {
//	return s[0];
//}
//
//Student f3(Student s) {
//	Student aux;
//	return aux;
//}
//
//Student& f4() {
//	Student aux;
//	return aux;
//}

Student functie() {
	return Student();
}

int main() {
	cout << "\n-------------atribut static-----------";
	cout << "\nTaxa restanta: " << Student::getTaxaRestanta();
	Student::setTaxaRestanta(150);

	int note[]{ 10,7,4 };
	int note2[]{ 9,9,9,9 };
	Student s1("Gigel", 3, note, 120);
	Student s4("Costel", 4, note2, 999);
	Student s2;
	s1.afisare();

	/*Student s2 = s1;
	Student s3(s1);
	s2.afisare();

	Student* ps = new Student();
	delete ps;*/

	//op =
	s2 = s4 = s1;//apel in cascada
	
	s2.afisare();

	s1 = s1;//auto-asignare
	s1.afisare();

	//copy elision
	cout << "\n------------1------------";
	Student s5 = functie();
	cout << "\n-------------2-----------";
	s5 = functie();
	

	//reguli supraincarcare operatori
	//Pas1  identificare tip operanzi
	//Pas2  daca I operand este de tipul clasei atunci supraincarcarea se 
	// poaterealiza printr-o metoda a clasei. iar I operand este inghitit de this
	//daca I operand nu este de tipul clasei atunci OBLIGATORIU se supraincarca prin functie globala
	//Pas4  ce returneaza operatorul
	//Pas 4  ce modifica this? sau alti operanzi?

	return 0;
}