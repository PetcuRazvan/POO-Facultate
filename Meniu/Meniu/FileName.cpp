#include <iostream>
using namespace std;

enum class Tip {
	VEGAN,
	VEGETARIAN,
	RAW_VEGAN,
	NORMAL_LA_CAP
};

class Mancare {
	float pret = 0;
	string denumire = "cacaniu";
	float greutate = 0;
	string* ingrediente = nullptr;
	int nrIngrediente = 0;
	Tip tip = Tip::NORMAL_LA_CAP;

public:
	Mancare(float _pret, const char* _denumire, float _greutate, int _nrIngrediente, string* _ingrediente, Tip _tip) {
		if (_pret > 0)
			this->pret = _pret;

		if (strlen(_denumire) >= 3)
			this->denumire = _denumire;

		if (_greutate > 0)
			this->greutate = _greutate;

		if (_nrIngrediente > 0 && _ingrediente != nullptr) {
			this->ingrediente = new string[_nrIngrediente];

			for (int i = 0; i < _nrIngrediente; ++i)
				this->ingrediente[i] = _ingrediente[i];

			this->nrIngrediente = _nrIngrediente;
		}

		this->tip = _tip;
	}

	Mancare(Mancare& m) {
		this->pret = m.pret;
		this->denumire = m.denumire;
		this->greutate = m.greutate;
		this->nrIngrediente = m.nrIngrediente;

		this->ingrediente = new string[m.nrIngrediente];
		for (int i = 0; i < m.nrIngrediente; i++)
			this->ingrediente[i] = m.ingrediente[i];

		this->tip = m.tip;
	}

	string* getToateIngredientele() {
		string* aux = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			aux[i] = this->ingrediente[i];

		return aux;
	}

	float getPret() {
		return this->pret;
	}

	Mancare& operator++() {
		this->pret++;

		return *this;
	}

	Mancare& operator++(int) {
		Mancare m = *this;
		this->pret++;

		return m;
	}

	~Mancare() {
		delete[] this->ingrediente;
	}
};

class Meniu {
	int nrMancaruri = 0;
	Mancare** mancaruri = nullptr;

public:
	Meniu(int _nrMancaruri, Mancare* _mancaruri) {
		if (_nrMancaruri > 0 && _mancaruri != nullptr) {
			this->nrMancaruri = _nrMancaruri;

			this->mancaruri = new Mancare * [_nrMancaruri];
			for (int i = 0; i < _nrMancaruri; ++i)
				this->mancaruri[i] = &(_mancaruri[i]);
		}
	}

	Meniu& operator+=(Mancare& m) {
		Mancare** temp = new Mancare * [this->nrMancaruri + 1];
		for (int i = 0; i < this->nrMancaruri; ++i)
			temp[i] = this->mancaruri[i];
		temp[this->nrMancaruri] = &m;

		delete[] this->mancaruri;
		this->mancaruri = new Mancare * [this->nrMancaruri++];
		this->mancaruri = temp;

		return *this;
	}

	float getCostTotal() {
		float suma = 0;
		for (int i = 0; i < this->nrMancaruri; i++)
			suma += this->mancaruri[i]->getPret();

		return suma;
	}

	~Meniu() {
		delete[] this->mancaruri;
	}
};

int main() {
	Mancare m1(60, "Mici", 0.5, 2, new string[2]{ "porc", "vita" }, Tip::NORMAL_LA_CAP);

	Meniu men1(1, new Mancare[1]{ m1 });

	men1 += m1;

	string* ingrediente = m1.getToateIngredientele();
	for (int i = 0; i < sizeof(ingrediente)/4; i++)
		cout << ingrediente[i];

	++m1;
	m1++;
	cout << men1.getCostTotal();

	return 0;
}