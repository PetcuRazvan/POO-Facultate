#include<iostream>
using namespace std;

class Student {
	const int id;
	string nume;
	int nrNote = 0;
	int* note = nullptr;
	static int notaTrecere;

public:
	Student(int _id) :id(_id) {
	}

	Student(int _id, string _nume, int _nrNote, int* _note) :id(_id) {
		this->nume = _nume;
		if (_nrNote > 0 && _note != nullptr) {
			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
		}
	}

	Student(const Student& s) :id(s.id) {
		this->nume = s.nume;
		if (s.nrNote > 0 && s.note != nullptr) {
			this->nrNote = s.nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = s.note[i];
		}
	}

	Student& operator=(const Student& s) {
		if (this != &s) {
			//destructor
			if (this->note != nullptr) {
				delete[] this->note;
				this->note = nullptr;
				this->nrNote = 0;
			}
			//constructor copiere
			this->nume = s.nume;
			if (s.nrNote > 0 && s.note != nullptr) {
				this->nrNote = s.nrNote;
				this->note = new int[this->nrNote];
				for (int i = 0; i < this->nrNote; i++)
					this->note[i] = s.note[i];
			}
		}
		return *this;
	}

	~Student() {
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
			this->nrNote = 0;
		}
	}

	//operator functie
	Student operator()() const{
		Student rez = *this;
		delete[] rez.note;
		rez.note = nullptr;
		rez.nrNote = 0;

		return rez;
	}

	//operatorul cast pe int
	explicit operator int() { //ca sa fie apelat doar daca il apelam explicit
		return this->nrNote;
	}

	//operatorul cast pentru char
	operator char* () {
		char* rez = new char[this->nume.length() + 1];
		strcpy(rez, this->nume.data());

		return rez;
	}

	//operator+
	Student operator+(const Student& s) const{
		Student rez = *this;
		if (rez.note != nullptr) {
			delete[] rez.note;
			rez.note = nullptr;
			rez.nrNote = 0;
		}

		if (rez.nrNote + s.nrNote > 0) {
			rez.nrNote = this->nrNote + s.nrNote;
			rez.note = new int[rez.nrNote];
			int k = 0;
			for (int i = 0; i < this->nrNote; i++)
				rez.note[k++] = this->note[i];
			for (int i = 0; i < s.nrNote; i++)
				rez.note[k++] = s.note[i];
		}
		return rez;
	}

	//forma pre-fixata
	Student& operator--() {   //aici putem prin referinta dar dincolo nu putem, pentru ca copia e pe stiva
		for (int i = 0; i < this->nrNote; i++)
			if (this->note[i] > 1)
				this->note[i]--;
		return *this;  //returnam obiectul de dupa modificare
	}

	//forma post-fixata
	Student operator--(int) {  //trebuie sa punem int ca sa faca diferenta dintre pre si post
		Student copie = *this;
		for (int i = 0; i < this->nrNote; i++)
			if (this->note[i] > 1)
				this->note[i]--;
		return copie;  //returnez obiectul de dinainte
	}

	friend ostream& operator<<(ostream& out, const Student& s);  //trebuie sa ne imprietenim cu clasa aici
	friend istream& operator>>(istream& in, Student& s);
};

int Student::notaTrecere = 5;

//TO DO HOME: V1(SA CERETI REINTRODUCEREA VALORILOR DE TIP NRnOTE SI NOTE PANA SUNT VALIDE)
             //V2(SA APELATI OOPERATORUL += CARE ADAUGA CATE O NOTA DE FIECARE DATA)
//OPERATORUL += VA ARUNCA O EXCEPTIE CARE TREBUIE AICI TRATATA
istream& operator>>(istream& in, Student& s) {  //fara const ca eu tre sa modific
	//obj s deja exista deci tre sa l dezalocam
	if (s.note != nullptr) {
		delete[] s.note;
		s.note = nullptr;
		s.nrNote = 0;
	}

	cout << "\nIntroduceti Numele: ";
	in >> s.nume;
	cout << "Introduceti numarul de note: ";
	in >> s.nrNote;
	if (s.nrNote < 0) {
		s.nrNote = 0;
		s.note = nullptr;
	}
	else {
		s.note = new int[s.nrNote];
		cout << "Introduceti note: ";
		for (int i = 0; i < s.nrNote; i++)
			in >> s.note[i];
	}
	return in;
}

ostream& operator<<(ostream& out, const Student& s) {
	out << "\nId: " << s.id;
	out << "\nNume: " << s.nume;
	out << "\nNumar note: " << s.nrNote;
	out << "\nNote: ";
	for (int i = 0; i < s.nrNote; i++)
		out << s.note[i] << " ";
	return out;
}

int main() {
	int note[] = { 10,6,8,4,1,9 };
	Student s1(12, "Gigel", 6, note);
	cout << s1;

	cout << "\n---------------------- operator >> -----------------";
	Student s2(13);
	//cin >> s2;

	cout << "\n---------------------- operator --(pre) ------------";
	//scade fiecare nota cu 1
	s2 = s1--;
	cout << s2;

	cout << "\n---------------------- operator ++ -----------------";
	//obj + int => returneaza un obiect nou plecand de la primul operand la care adauga o noua nota
	//TEMAAA: INT + OBJ => acelasi context dar sa facem comutativitatea
	Student s3(1);
	s3 = s2 + s1;//returneaza un obiect plecand de la s2 si coompletand cu notele de la s1
	cout << s3;

	cout << "\n---------------------- operator cast/conversie ----------------";
	//fun weirdo
	char* nume = s2;//extrage char* din nume
	cout << endl<< nume;
	delete[] nume;
	//double notaMedie = s2;//returneaza media tuturor notelor

	if ((int)s1 != 10) {
		cout << "\nStudentul nu are 10 note";
	}
	else
		cout << "\nInvers";

	cout << "\n---------------------- operator functie ----------------";
	//s3 = s3(1, 4);//returneaza un nou student doar cu notele dintre indexsii 1, 4
	//s3 = s2(3);//returneaza un student cu primele 3 note
	Student* v[5];
	int n = 5;
	//bool gasit = s2(v, n); //returneaza true daca exista s2 in vectorul primit
	s3 = s2();//returneaza un student din care am golit notele
	cout << s3;

	//TEMA: S3 += 10 ADAUGA O NOTA LA FINAL + ARUNCAT EXCEPTION SI TRATARE IN MAIN
	//!!!!!! SE POATE ARUNCA SI UN POINTER DE EXCEPTION throw new exception DECI TREBUIE SA DEZALOCAM CAND IL TRATAM

	return 0;
}