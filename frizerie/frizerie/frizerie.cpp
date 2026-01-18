#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Serviciu {
public:
	virtual double calculPret() = 0;
};

class Tuns : public Serviciu {
	int durataMinute = 0;
	double tarifFrizer = 0;

public:
	Tuns(int _durataMinute, double _tarifFrizer) {
		this->durataMinute = _durataMinute;
		this->tarifFrizer = _tarifFrizer;
	}

	double calculPret() override {
		return this->durataMinute * this->tarifFrizer;
	}

	~Tuns() {
		cout << "\ns a dus tusul";
	}
};

class Frezat : public Serviciu {
	int grameGelUtilizat = 0;

public:
	Frezat(int _gramegelUtilizat) {
		this->grameGelUtilizat = _gramegelUtilizat;
	}

	double calculPret() override {
		return this->grameGelUtilizat * 0.5;
	}
};

class Barbierit : public Serviciu {
	int durataMinute = 0;
	double tarifFrizer = 0;
	int lameFolosite = 0;

public:
	Barbierit(int _durataMinute, double _tarifFrizer, int _lameFolosite) {
		this->durataMinute = _durataMinute;
		this->tarifFrizer = _tarifFrizer;
		this->lameFolosite = _lameFolosite;
	}

	double calculPret() override {
		return this->durataMinute * this->tarifFrizer + this->lameFolosite * 2;
	}

	~Barbierit() {
		cout << "\nS a dus barbieritul";
	}
};

enum class tipFrizerie {
	barberShop,
	hairStyle,
	Goku
};

class Frizerie {
	string denumire = "-";
	int numarFrizeri = 0;
	tipFrizerie tip = tipFrizerie::Goku;
	static int lungimeMinimaDenumire;
	vector<Serviciu*> servicii;

public:
	Frizerie() {}

	Frizerie(const char* _denumire, tipFrizerie _tip, int _nrFrizeri) {
		if (strlen(_denumire) >= Frizerie::lungimeMinimaDenumire)
			this->denumire = _denumire;

		if (_nrFrizeri >= 1)
			this->numarFrizeri = _nrFrizeri;

		this->tip = _tip;
	}

	Frizerie(Frizerie& f) {
		this->denumire = f.denumire;
		this->numarFrizeri = f.numarFrizeri;
		this->tip = f.tip;
	}

	void adaugareServiciu(Serviciu& s) {
		this->servicii.push_back(&s);
	}

	void operator+=(Serviciu& s) {
		this->servicii.push_back(&s);
	}

	void operator-=(Serviciu& s) {
		vector<Serviciu*>::iterator it;
		it = this->servicii.begin();

		while(it != this->servicii.end()) {
			if (*it == &s)
				it = this->servicii.erase(it);
			else
				it++;
		}
	}

	double pretTotal() {
		double pret = 0;
		vector<Serviciu*>::iterator it;

		for (it = this->servicii.begin(); it != this->servicii.end(); it++) {
			pret += (*it)->calculPret();
		}

		return pret;
	}

	static void setLungimeMinimaDenumire(int valoare) {
		if (valoare >= 1)
			Frizerie::lungimeMinimaDenumire = valoare;
	}

	void setDenumire(const char* _denumire) {
		if (strlen(_denumire) >= Frizerie::lungimeMinimaDenumire)
			this->denumire = _denumire;
	}

	string getDenumire() const{
		return this->denumire;
	}

	friend ostream& operator<<(ostream& out, Frizerie& f);

	friend istream& operator>>(istream& in, Frizerie& f);
};

ostream& operator<<(ostream& out, Frizerie& f) {
	out << "\nDenumire: " << f.denumire;
	out << "\nNumar Frizeri: " << f.numarFrizeri;
	out << "\nTip Frizerie: ";

	switch (f.tip) {
	case tipFrizerie::Goku:
		out << "Goku";
		break;
	case tipFrizerie::barberShop:
		out << "Barber shop";
		break;
	case tipFrizerie::hairStyle:
		out << "Hair style";
		break;
	}
	
	return out;
}

istream& operator>>(istream& in, Frizerie& f) {
	cout << "\nDenumire: ";
	getline(in, f.denumire);
	
	cout << "Tip(0: barber shop, 1: hair style): ";
	int _tip;
	in >> _tip;
	switch (_tip) {
	case 0:
		f.tip = tipFrizerie::barberShop;
		break;
	case 1:
		f.tip = tipFrizerie::hairStyle;
		break;
	default:
		f.tip = tipFrizerie::Goku;
		break;
	}

	cout << "Numar frizeri: ";
	in >> f.numarFrizeri;

	return in;
}


int Frizerie::lungimeMinimaDenumire = 4;

int main() {
	Frizerie f1;
	Frizerie f2("la Mihai", tipFrizerie::barberShop, 3);
	Frizerie f3 = f2;

	Frizerie::setLungimeMinimaDenumire(5);
	f3.setDenumire("El Saloon");

	/*cout << f3;
	cout << f1;*/

	//cin >> f1;

	Tuns t1(30, 1.2);
	Barbierit b1(20, 1, 2);

	f2 += t1;
	f2 += b1;

	cout << f2.pretTotal();

	f2 -= b1;
	cout << f2.pretTotal();


	return 0;
}