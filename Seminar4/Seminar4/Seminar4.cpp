#include <iostream>
using namespace std;

class Student {
	string nume;  //e top stringul, totul se bazeaza pe alocarea dinamica
	int nrNote;
	int* note;
	double buget;

public:
	//constructor fara params
	Student() {
		cout << "\nApel constructor fara param";
		this->nume = "Anonim";  //poti cu sau fara this->
		this->nrNote = 0;
		this->note = nullptr;
		this->buget = 0;
	}

	//constructor cu un param
	Student(double _buget) {
		cout << "\nApel constructor cu un param";
		this->nume = "Anonim";  //poti cu sau fara this->
		this->nrNote = 0;
		this->note = nullptr;
		if (_buget >= 0)        //bagam si noi o validare
			this->buget = _buget;
		else
			this->buget = 0;
	}

	//constructor cu toti parametrii
	Student(const char* _nume, int _nrNote, int* _note, double _buget) {  //numele trebuie prin const deoarece trimitem in parametrii un sir const
		if (strlen(_nume) >= 3)
			this->nume = _nume;
		else
			this->nume = "Anonim";

		if (_nrNote > 0 && _note != nullptr) {
			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < nrNote; i++) 
				this->note[i] = _note[i];
		}
		else {
			this->nrNote = 0;
			this->note = nullptr; //tot timpul la validari unde avem if trebuie sa avem si else unde scriem exact ca la constructorul fara param
		}

		if (_buget >= 0)       
			this->buget = _buget;
		else
			this->buget = 0;
	}

	//get si set pentru note
	void setNote(int* _note, int _nrNote) {
		if(_note != nullptr &&_nrNote > 0)
		{
			delete[] this->note;
			this->note = nullptr;  //ca sa fim siguri ca o decuplam de fosta zona de memorie

			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < nrNote; i++)
				this->note[i] = _note[i];
		}
		else {
			//depinde de specificatii
		}
	}

	void setNota(int _nota, int _index) {
		if (_index >= 0 && _index <= this->nrNote)
			if (_nota >= 1 && _nota <= 10)
				this->note[_index] = _nota;
	}

	int* getNote() {
		//Tema
	}

	int getNota(int _index) {
		if (_index >= 0 && _index <= this->nrNote)
			return this->note[_index];
	}

	int getNrNote() {
		//Tema
	}

	//metode de afisare
	void afisare() const{        //acest const este goodpractice ca sa nu schimbam obiectul this din greseala
		cout << "\n==================";
		cout << "\nNume: " << this->nume;
		cout << "\nNr Note: " << this->nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < this->nrNote; i++)
			cout << this->note[i] << " ";
		cout << "\nBuget: " << this->buget;
		cout << "\n==================\n";
	}
};

int main()
{
	Student s;
	s.afisare();

	Student s2[5];  //constructorul e apelat de 5 ori ca e un vector de obiecte de tip studenti
	Student* ps;
	ps = new Student();
	Student s3();   //nu e apel de constructot fara parametrii, este o functie
	Student* p2[5];   //Vector de pointeri catre obiecte de tip student
	Student s4(2);    //se apeleaza constructorul cu un parametru
	Student s5 = 2; //pot apela asa constructor cu un singur param

	int note[]{ 10,7,4 };
	Student s6("Gigel", 3, note, 120);
	s6.afisare();

	return 0;
}