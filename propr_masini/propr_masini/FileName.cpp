#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class SerieSasiuNeoriginalError : public runtime_error {
public:
	SerieSasiuNeoriginalError(const char* mesaj) : runtime_error(mesaj) {}
};

class CnpNeoriginalError : public runtime_error {
public:
	CnpNeoriginalError(const char* mesaj) : runtime_error(mesaj) {}
};

class Masina {
	string model = "";
	string motor = "";
	int nrLocuri = 0;
	const string serieSasiu;
	static vector<Masina*> vectorMasini;
	bool valid = true;

	void scrieString(ofstream& fisier, string& str) {
		int lungime = str.length() + 1;

		fisier.write((char*)&lungime, sizeof(int));
		fisier.write(str.c_str(), lungime);
	}

	void citireString(ifstream& fisier, string& str) {
		int lungime;
		fisier.read((char*)&lungime, sizeof(int));

		char* buffer = new char[lungime];
		fisier.read(buffer, lungime);
		str = buffer;
		delete[] buffer;
	}

public:
	Masina(const char* _model, const char* _motor, int _nrLocuri, const char* _serieSasiu): serieSasiu(_serieSasiu) {
		try
		{
			vector<Masina*>::iterator masina;
			for (masina = Masina::vectorMasini.begin(); masina != Masina::vectorMasini.end(); masina++)
				if (_serieSasiu == (*masina)->getSerieSasiu())
				{
					this->valid = false;
					throw SerieSasiuNeoriginalError("Serie sasiu deja folosita");
				}
			if (this->valid) {
				if (strlen(_model) >= 3)
					this->model = _model;

				if (strlen(_motor) >= 2)
					this->motor = _motor;

				if (_nrLocuri >= 2 && _nrLocuri <= 10)
					this->nrLocuri = _nrLocuri;

				Masina::vectorMasini.push_back(this);
			}
		}
		catch (const SerieSasiuNeoriginalError& err) {
			cerr << err.what();
		}
	}

	string getSerieSasiu() const{
		return this->serieSasiu;
	}

	bool getValid() {
		return this->valid;
	}

	friend ostream& operator<<(ostream& out, Masina& m);

	~Masina() {
		cout << "\nAccident";
	}

	

	void serializare(const char* numeFisier) {
		ofstream fisier(numeFisier, ios::binary);

		if (fisier.is_open()) {
			this->scrieString(fisier, this->model);
			this->scrieString(fisier, this->motor);
			fisier.write((char*)&this->nrLocuri, sizeof(int));
			fisier.write((char*)&this->valid, sizeof(bool));

			fisier.close();
		}
		else
			cout << "\nEroare la deschiderea fisierului";
	}

	void deserializare(const char* numeFisier) {
		ifstream fisier(numeFisier, ios::binary);

		if (fisier.is_open()) {
			this->citireString(fisier, this->model);
			this->citireString(fisier, this->motor);
			fisier.read((char*)&this->nrLocuri, sizeof(int));
			fisier.read((char*)&this->valid, sizeof(bool));

			fisier.close();
		}
		else
			cout << "\nEroare la deschiderea fisierului";
	}
};

ostream& operator<<(ostream& out, Masina& m) {
	out << "\nModel: " << m.model;
	out << "\nMotor: " << m.motor;
	out << "\nNr locuri: " << m.nrLocuri;
	out << "\nSerie de sasiu: " << m.serieSasiu;

	return out;
}


vector<Masina*> Masina::vectorMasini;

class Proprietar {
	string nume;
	const string cnp;
	static vector<Proprietar*> vectorProprietari;
	bool valid = true;

	void scrieString(ofstream& fisier, string& str) {
		int lungime = str.length() + 1;

		fisier.write((char*)&lungime, sizeof(int));
		fisier.write(str.c_str(), lungime);
	}

	void citireString(ifstream& fisier, string& str) {
		int lungime;
		fisier.read((char*)&lungime, sizeof(int));

		char* buffer = new char[lungime];
		fisier.read(buffer, lungime);
		str = buffer;

		delete[] buffer;
	}

public:
	Proprietar(const char* _nume, const char* _cnp) : cnp(_cnp) {
		try
		{
			vector<Proprietar*>::iterator proprietar;
			for (proprietar = Proprietar::vectorProprietari.begin(); proprietar != Proprietar::vectorProprietari.end(); proprietar++)
				if (_cnp == (*proprietar)->getCnp())
				{
					this->valid = false;
					throw CnpNeoriginalError("Cnp deja folosit");
				}

			if (this->valid) {
				if (strlen(_nume) >= 2)
					this->nume = _nume;

				Proprietar::vectorProprietari.push_back(this);
			}
		}
		catch (const CnpNeoriginalError& err) {
			cerr << err.what();
		}
	}

	string getCnp() {
		return this->cnp;
	}

	bool getValid() {
		return this->valid;
	}

	friend ostream& operator<<(ostream& out, Proprietar& s);

	~Proprietar() {
		cout << "\nA murit";
	}

	void serializare(const char* numeFisier) {
		ofstream fisier(numeFisier, ios::binary);

		if (fisier.is_open()) {
			scrieString(fisier, this->nume);
			fisier.write((char*)&this->valid, sizeof(bool));

			fisier.close();
		}
		else
			cout << "\nEroare la deschiderea fisierului";
	}

	void deserializare(const char* numeFisier) {
		ifstream fisier(numeFisier, ios::binary);

		if (fisier.is_open()) {
			citireString(fisier, this->nume);
			fisier.read((char*)&this->valid, sizeof(bool));

			fisier.close();
		}
		else
			cout << "\nEroare la deschiderea fisierului";
	}
};

ostream& operator<<(ostream& out, Proprietar& s) {
	out << "\nNume: " << s.nume;
	out << "\nCnp: " << s.cnp;

	return out;
}


vector<Proprietar*> Proprietar::vectorProprietari;

class DRPCIV {
	static map<Proprietar*, vector<Masina*>> mapProprietariMasini;

public:
	static void inregistrareMasina(Proprietar& s, Masina& m) {
		if(s.getValid() && m.getValid()){
			if (DRPCIV::mapProprietariMasini.count(&s))
				DRPCIV::mapProprietariMasini[&s].push_back(&m);

			else {
				vector<Masina*> masini;
				masini.push_back(&m);
				DRPCIV::mapProprietariMasini[&s] = masini;
			}
		}
	}

	static void afisareMasiniDupaProprietar(Proprietar& s) {
		vector<Masina*> masini = DRPCIV::mapProprietariMasini.at(&s);

		vector<Masina*>::iterator masina;
		for (masina = masini.begin(); masina != masini.end(); masina++)
			cout << **masina;
	}

	static void afisareProprietariDupaMasina(Masina& m) {
		vector<Proprietar*> vectorProprietari;

		for (const auto& pereche : DRPCIV::mapProprietariMasini) {
			Proprietar* proprietar = pereche.first;
			vector<Masina*> vectorMasini = pereche.second;

			vector<Masina*>::iterator masina;
			for (masina = vectorMasini.begin(); masina != vectorMasini.end(); masina++)
				if (m.getSerieSasiu() == (*masina)->getSerieSasiu())
					vectorProprietari.push_back(proprietar);
		}

		vector<Proprietar*>::iterator proprietar;
		for (proprietar = vectorProprietari.begin(); proprietar != vectorProprietari.end(); proprietar++)
			cout << **proprietar;
	}
};

map<Proprietar*, vector<Masina*>> DRPCIV::mapProprietariMasini;

int main() {
	Masina m1("BMW", "V6", 4, "6767");
	Masina m2("Fiat", "X16", 4, "6969");

	Proprietar s1("Marius", "5050808090058");
	Proprietar s2("Marian", "5050808090059");

	DRPCIV::inregistrareMasina(s1, m1);
	DRPCIV::inregistrareMasina(s1, m2);
	DRPCIV::inregistrareMasina(s2, m2);

	//DRPCIV::afisareProprietariDupaMasina(m2);

	s1.serializare("propr.bin");
	s2.deserializare("propr.bin");
	cout << s2;

	return 0;
}