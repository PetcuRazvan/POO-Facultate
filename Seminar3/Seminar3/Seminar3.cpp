#include <iostream>
using namespace std;

class Student {
	//proprietati
	int codStudent;
	char nume[31];
	int nrNote;
	int* note;

public:
	//metode specifice
	//1. metode tip constructor
	//constructor default/fara param
	Student() {
		cout << "Apel constructor defaulf" << endl;
		codStudent = 0;
		strcpy(nume, "Ghostface");
		nrNote = 0;
		note = nullptr;
	}

	//metoder accesor (get si set)
	//se seteaza campurilor private
	void setCodStudent(int _codStudent) {      //asta cu _ e standardul in C
		//tre sa bagam validari, restrictii
		if (_codStudent > 0)
			this->codStudent = _codStudent;     //asta cu this nu e obligatoriu dar e niche
	}

	int getCodStudent()
	{
		return codStudent;
	}

	void setNume(const char* _nume)    // trebe const ca sa putem pune in parametrii siruri const, caci pointer de char poate varia
	{
		if (strlen(_nume) >= 1 && strlen(_nume) <= 30)
			strcpy(nume, _nume);
	}

	//const char* getNume() //tre sa punem const aici ca sa nu modificam ce e pe adresa asta din afara
	//{							dar totusi versiunea asta nu e corecta
	//	return nume;
	//}

	//tre sa faci asa
	char* getNume()
	{
		//se face o copie a numelui la o alta adresa ca sa putem proteja adresa originala

		char* copie;
		copie = new char[strlen(nume) + 1];
		strcpy(copie, nume);

		return copie;
	}
};

int main()
{
	//clasa + constructori(fara param + toti param)
	//get si set

	Student s;

	s.setCodStudent(67);
	cout << s.getCodStudent() << endl;

	s.setNume("Mirel");

	char* nume = s.getNume();
	cout << nume << endl;
	delete[] nume;
	/*s.codStudent = 100;
	strcpy(s.nume, "Gigel");
	s.nrNote = 3;
	s.note = new int[s.nrNote];

	s.note[0] = 10;
	s.note[1] = 6;
	s.note[2] = 3;*/   //asa faceam la struct

	return 0;
}