#include <iostream>
#include <map>
using namespace std;

class IdNeunicError : public logic_error {
public:
	IdNeunicError(const char* mesaj) : logic_error(mesaj) {}
};

class Produs {
protected:
	const string idUnic;
	string nume = "nimic";
	double pret;

	static string* coduri;
	static int nrCoduri;

	map<string, int> stocPeMarimi;

public:
	Produs(const char* _idUnic, const char* _nume, double _pret, map<string, int>& _stocPemarimi) : idUnic(_idUnic) {
		try {
			bool unic = true;
			if (Produs::coduri != nullptr)
				for (int i = 0; i < Produs::nrCoduri; ++i)
					if (Produs::coduri[i] == _idUnic)
						throw IdNeunicError("Id deja existent");
		}
		catch (const IdNeunicError& err){
			cerr << err.what();
		}

		if (strlen(_nume) >= 4)
			this->nume = _nume;

		if (_pret >= 5)
			this->pret = _pret;

		this->stocPeMarimi = _stocPemarimi;

		if (Produs::coduri == nullptr) {
			Produs::coduri = new string  [1];
			Produs::coduri[0] = _idUnic;

			Produs::nrCoduri++;
		}
		else {
			string* temp = new string[Produs::nrCoduri + 1];
			for (int i = 0; i < Produs::nrCoduri; i++)
				temp[i] = Produs::coduri[i];
			temp[Produs::nrCoduri] = _idUnic;

			delete[] Produs::coduri;
			Produs::coduri = new string[++Produs::nrCoduri];
			
			for (int i = 0; i < Produs::nrCoduri; i++)
				Produs::coduri[i] = temp[i];

			delete[] temp;
		}
	}

	virtual string getCategorie() = 0;

	virtual double getPretFinal() {
		return this->pret;
	}
};

string* Produs::coduri = nullptr;
int Produs::nrCoduri = 0;

class Tricou : public Produs {
	string producator = "nimeni";

public:
	Tricou(const char* _idUnic, const char* _nume, double _pret, map<string, int> _stocPemarimi, const char* producator) : Produs(_idUnic, _nume, _pret, _stocPemarimi) {
		if (strlen(producator) >= 3)
			this->producator = producator;
	}

	string getCategorie() override {
		return "pantaloni";
	}

	double getPretFinal() override {
		
		int stoc = 0;
		for (auto pereche : this->stocPeMarimi)
			stoc += pereche.second;

		if (stoc > 100)
			return this->pret * 0.9;
		return this->pret;
	}
};

class Pantaloni: public Produs {
	string culoare = "cacaniu";

public:
	Pantaloni(const char* _idUnic, const char* _nume, double _pret, map<string, int>& _stocPemarimi, const char* _culoare) : Produs(_idUnic, _nume, _pret, _stocPemarimi) {
		if (strlen(_culoare) >= 3)
			this->culoare = _culoare;
	}

	string getCategorie() override {
		return "pantaloni";
	}
};

class Jacheta :public Produs {
public:
	Jacheta(const char* _idUnic, const char* _nume, double _pret, map<string, int>& _stocPemarimi) : Produs(_idUnic, _nume, _pret, _stocPemarimi) {}

	string getCategorie() override {
		return "jacheta";
	}

	double getPretFinal() {
		if (this->pret > 1200)
			return this->pret * 1.15;
		return this->pret;
	}
};

int main() {
	Tricou t1("TR1", "tricoubengos", 60, { {"S", 50}, {"M" , 100}, {"L" , 80}, {"XL" , 20} }, "H&M");
	Tricou t2("TR2", "tricouobraznic", 90, { {"S", 50}, {"M" , 100}, {"L" , 80}, {"XL" , 20} }, "H&M");

	

	return 0;
}