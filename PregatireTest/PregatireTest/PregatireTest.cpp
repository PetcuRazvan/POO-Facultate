#include <iostream>
using namespace std;

class Chitara {
	string model;
	string producator;
	int nrFret;
	int nrCorzi;
	float* gauge;
	bool isElectric;

public:
	//Constructor fara param
	Chitara() {
		this->model = "no name";
		this->producator = "nobody";
		this->nrFret = 0;
		this->nrCorzi = 2;

		this->gauge = new float[2];
		this->gauge[0] = 0.09;
		this->gauge[1] = 0.1;

		this->isElectric = false;
	}

	//Constructor cu toti param
	Chitara(const char* _model, const char* _producator, int _nrFret, int _nrCorzi, float* _gauge, bool _isElectric) {
		if (strlen(_model) >= 3)
			this->model = _model;
		else
			this->model = "no name";

		if (strlen(_producator) >= 3)
			this->producator = _producator;
		else
			this->producator = "nobody";

		if (_nrFret >= 0)
			this->nrFret = _nrFret;
		else
			this->nrFret = 0;

		if (_nrCorzi >= 2 && _gauge != nullptr) {
			this->nrCorzi = _nrCorzi;
			this->gauge = new float[_nrCorzi];

			for (int i = 0; i < _nrCorzi; i++)
				this->gauge[i] = _gauge[i];
		}
		else {
			this->nrCorzi = 2;
			this->gauge = new float[2];
			this->gauge[0] = 0.09;
			this->gauge[1] = 0.1;
		}

		this->isElectric = _isElectric;
	}

	//constructor cu un param
	Chitara(const char* _model) {
		if (strlen(_model) >= 2)
			this->model = _model;
		else
			this->model = "no name";

		this->producator = "nobody";
		this->nrFret = 0;
		this->nrCorzi = 2;

		this->gauge = new float[2];
		this->gauge[0] = 0.09;
		this->gauge[1] = 0.1;

		this->isElectric = false;
	}

	//getere
	const string getModel() {
		return this->model;
	}

	const string getProducator() {
		return this->producator;
	}

	int getNrFret() {
		return this->nrFret;
	}

	int getNrCorzi() {
		return this->nrCorzi;
	}

	float* getGauge() {
		float* copie;
		copie = new float[this->nrCorzi];

		for (int i = 0; i <= this->nrCorzi; i++)
			copie[i] = this->gauge[i];

		return copie;
	}

	//setere
	void setModel(const char* _model) {
		if (strlen(_model) >= 3)
			this->model = _model;
		else
			this->model = "no name";
	}

	void setProducator(const char* _producator) {
		if (strlen(_producator) >= 3)
			this->producator = _producator;
		else
			this->producator = "nobody";
	}

	void setNrFret(int _nrFret) {
		if (_nrFret >= 0)
			this->nrFret = _nrFret;
		else
			this->nrFret = 0;
	}

	void setGauge(int _nrCorzi, float* _gauge) {
		if (_nrCorzi >= 2 && _gauge != nullptr) {
			delete[] this->gauge;
			this->nrCorzi = _nrCorzi;
			this->gauge = new float[_nrCorzi];

			for (int i = 0; i < _nrCorzi; i++)
				this->gauge[i] = _gauge[i];
		}
		else {

			this->gauge = new float[2];
			this->gauge[0] = 0.09;
			this->gauge[1] = 0.1;
		}
	}

	void setIsElectric(bool _isElectric) {
		this->isElectric = _isElectric;
	}

	//afisare
	void afisare() const{
		cout << "\n==================";
		cout << "\nModel: " << this->model;
		cout << "\nProducator: " << this->producator;
		cout << "\nNr freturi: " << this->nrFret;
		cout << "\nNr corzi: " << this->nrCorzi;
		cout << "\nGauge: ";
		for (int i = 0; i < this->nrCorzi; i++)
			cout << this->gauge[i] << " ";
		cout << "\nElectric: " << this->isElectric;
		cout << "\n==================";
	}

	~Chitara() {
		if (this->gauge != nullptr)
			delete[] this->gauge;

		cout << "\nfinish";
	}
};

int main()
{
	Chitara a;
	float gauge[]{ 0.09, 0.13,0.18, 0.22, 0.3, 0.34 };
	Chitara b("stratocaster", "Harley Benton", 22, 6, gauge, true );
	Chitara c("SG");
	a.afisare();
	b.afisare();
	c.afisare();
	return 0;
}