#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace Mine {

	template<class T>
	class Vector {
		T* elemente = nullptr;
		int dimensiune = 0;
		const int id;
		static int contor;

	public:
		static const int idStart;

		Vector() : id(Vector::idStart + contor++) {
			this->elemente = new T[1];
			this->elemente[0] = 0;
			this->dimensiune = 1;
		}

		Vector(int _dimensiune, T* _elemente) : id(Vector::idStart + contor++) {
			if (_dimensiune > 0) {
				this->elemente = new T[_dimensiune];

				for (int i = 0; i < _dimensiune; i++)
					this->elemente[i] = _elemente[i];

				this->dimensiune = _dimensiune;
			}
		}

		void setElemente(T valoare) {
			for (int i = 0; i < this->dimensiune; i++)
				this->elemente[i] = valoare;
		}

		Vector& operator=(Vector& v) {
			if (this != &v) {
				this->elemente = nullptr;
				this->elemente = new T[v.dimensiune];

				for (int i = 0; i < v.dimensiune; i++)
					this->elemente[i] = v.elemente[i];

				this->dimensiune = v.dimensiune;

				return *this;
			}
		}

		operator int() const {
			return this->dimensiune;
		}

		T& operator[](int index) {
			if (index >= 0 && index < this->dimensiune)
				return this->elemente[index];
		}

		friend ostream& operator<<(ostream& out, Vector<T>& v) {
			out << "\n" << v.id << ": ";
			out << "[" << v.elemente[0];
			for (int i = 1; i < v.dimensiune; i++)
				out << ", " << v.elemente[i];
			out << "]";

			return out;
		}

		~Vector() {
			delete[] this->elemente;
		}

		void serializare(const char* numeFisier) {
			ofstream fisier(numeFisier, ios::binary);

			if (fisier.is_open()) {
				fisier.write((char*)&this->dimensiune, sizeof(int));
				fisier.write((char*)this->elemente, this->dimensiune * sizeof(T));

				fisier.close();
			}
			else
				cout << "\nEroare la deschidere fisier";
		}

		void deserializare(const char* numeFisier) {
			ifstream fisier(numeFisier, ios::binary);

			if (fisier.is_open()) {
				fisier.read((char*)&this->dimensiune, sizeof(int));

				if (this->elemente != nullptr)
					delete[] this->elemente;

				this->elemente = new T[this->dimensiune];
				fisier.read((char*)this->elemente, this->dimensiune * sizeof(T));
			}
			else
				cout << "\nFisierul nu s-a deschis";
		}
	};

	template<class T>
	int Vector<T>::contor = 0;

	template<class T>
	const int Vector<T>::idStart = 100;

	template<class T>
	class Matrice {
		Vector<T>** vectori = nullptr;
		int nrRanduri = 0;

	public:
		Matrice(int _nrRanduri, Vector<T>* _vectori) {
			this->vectori = new Vector<T>*[_nrRanduri];

			for (int i = 0; i < _nrRanduri; i++)
				this->vectori[i] = &_vectori[i];

			this->nrRanduri = _nrRanduri;
		}

		void addLine(Vector<T>& v) {
			Vector<T>** temp = new Vector<T>*[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++)
				temp[i] = this->vectori[i];

			delete[] this->vectori;
			this->vectori = nullptr;
			this->vectori = new Vector<T>*[this->nrRanduri + 1];
			for (int i = 0; i < this->nrRanduri; i++)
				this->vectori[i] = temp[i];
			this->vectori[this->nrRanduri] = &v;
			this->nrRanduri++;

			delete[] temp;
		}

		friend ostream& operator<<(ostream& out, Matrice& m) {
			for (int i = 0; i < m.nrRanduri; i++)
				out << *m.vectori[i];

			return out;
		}

		~Matrice() {
			delete[] this->vectori;
		}
	};
}


int main() {
	Mine::Vector<int> v1;
	Mine::Vector<int> v2(3, new int[3] {1, 2, 3});
	Mine::Vector<int> v3(5, new int[5] {1, 5, 7, 3, 8});

	Mine::Matrice<int> m1(2, new Mine::Vector<int>[2] {v1, v2});
	m1.addLine(v3);
	//cout << m1;

	v3.serializare("vectori.bin");
	Mine::Vector<int> v4;
	v2.deserializare("vectori.bin");
	cout << v2;

	return 0;
}