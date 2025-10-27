#include <iostream>
#include <memory>

class Dinosaur {
	std::string nume;
	int nr;
	std::unique_ptr<int[]>vector;

public:
	Dinosaur() {
		this->nume = "fosila";
		this->nr = 0;
		this->vector = nullptr;
	}

	Dinosaur(const std::string& _nume, int _nr, const int* _vector) {
		if (_nume.length() >= 3)
			this->nume = _nume;
		else
			this->nume = "fosila";

		if (_nr > 0) {
			this->nr = _nr;

			this->vector = std::make_unique<int[]>(_nr);
			for (int i = 0; i < _nr; i++)
				this->vector[i] = _vector[i];
		}
		else {
			this->nr = 0;
			this->vector = nullptr;
		}
	}

	void afisare() const {
		std::cout << "================" << std::endl;
		std::cout << "Nume: " << this->nume << std::endl;
		std::cout << "Numar: " << this->nr << std::endl;
		std::cout << "vector: ";
		for (int i = 0; i < this->nr; i++)
			std::cout << this->vector[i] << " ";
		std::cout << std::endl;
		std::cout << "================" << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& outStream, Dinosaur& dinosaur) {
		outStream << "================" << std::endl;
		outStream << "Nume: " << dinosaur.nume << std::endl;
		outStream << "Numar: " << dinosaur.nr << std::endl;
		outStream << "vector: ";
		for (int i = 0; i < dinosaur.nr; i++)
			std::cout << dinosaur.vector[i] << " ";
		outStream << std::endl;
		outStream << "================" << std::endl;

		return outStream;
	}

	Dinosaur& operator=(const Dinosaur& dinosaur) {
		this->nume = dinosaur.nume;
		this->nr = dinosaur.nr;
		this->vector = std::make_unique<int[]>(dinosaur.nr);
		for (int i = 0; i < dinosaur.nr; i++)
			this->vector[i] = dinosaur.vector[i];

		return *this;
	}

	~Dinosaur() { std::cout << "Asteroid!!!" << std::endl; }
};

int main() {

	std::unique_ptr<Dinosaur>unPtr1 = std::make_unique<Dinosaur>();

	int vector[]{ 1,4,5,6 };
	std::unique_ptr<Dinosaur>unPtr2 = std::make_unique<Dinosaur>("Spinosaur", 4, vector);
	
	/*(*unPtr1).afisare();
	(*unPtr2).afisare();*/
	(*unPtr1) = (*unPtr2);
	std::cout << *unPtr1;

	return 0;
}