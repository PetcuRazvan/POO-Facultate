#include <iostream>
using namespace std;

class Entity {
public:
	virtual void attack() = 0;
};

class Personaj : public Entity{
protected:
	string denumire = "secret";
	int nrLovituri = 0;
	int* damage = nullptr;

public:
	Personaj() {}

	Personaj(const char* _denumire, int _nrLovituri, int* _damage) {
		if (strlen(_denumire) >= 4)
			this->denumire = _denumire;

		if (_nrLovituri > 1 && _damage != nullptr) {
			this->damage = new int[_nrLovituri];
			for (int i = 0; i < _nrLovituri; i++)
				this->damage[i] = _damage[i];

			this->nrLovituri = _nrLovituri;
		}
	}

	Personaj(Personaj& p) {
		this->denumire = p.denumire;
		
		this->damage = new int[p.nrLovituri];
		for (int i = 0; i < p.nrLovituri; i++)
			this->damage[i] = p.damage[i];

		this->nrLovituri = p.nrLovituri;
	}

	void setLovituri(int _nrLovituri, int* _damage) {
		if (this->damage != nullptr)
			delete[] this->damage;

		this->damage = new int[_nrLovituri];
		for (int i = 0; i < _nrLovituri; i++)
			this->damage[i] = _damage[i];

		this->nrLovituri = _nrLovituri;
	}

	void attack() override {
		cout << "\nAtaca de " << this->nrLovituri << " ori";
		for (int i = 0; i < this->nrLovituri; i++)
			cout << " " << this->damage[i];
	}

	void operator+=(int valoare) {
		for (int i = 0; i < this->nrLovituri; i++)
			this->damage[i] += valoare;
	}

	void operator-=(int valoare) {
		for (int i = 0; i < this->nrLovituri; i++)
			this->damage[i] -= valoare;
	}

	bool operator>=(Personaj& p) {
		int damagetotal1 = 0;
		for (int i = 0; i < this->nrLovituri; i++)
			damagetotal1 += this->damage[i];

		int damagetotal2 = 0;
		for (int i = 0; i < p.nrLovituri; i++)
			damagetotal2 += p.damage[i];

		return damagetotal1 >= damagetotal2;
	}
};

class NPC : public Personaj {
	string zona;

public:
	NPC(const char* _denumire, int _nrLovituri, int* _damage, const char* _zona) : Personaj(_denumire, _nrLovituri, _damage) {
		if (strlen(_zona) >= 4)
			this->zona = _zona;
	}
};

template<class T>
T functieTemplateMedie(T a, T b) {
	return (a + b) / 2;
}

int main() {
	Personaj p1;
	Personaj p2("Batman", 3, new int[3] {1, 2, 3});
	Personaj p3(p2);

	p2.setLovituri(2, new int[2] {5, 5});

	NPC n1("Blashkowitz", 4, new int[4] {1, 2, 3, 4}, "U-boat");

	p2.attack();
	n1.attack();

	cout << "\n" << functieTemplateMedie<double>(6.7, 3.4);

	return 0;
}