#include <iostream>
using namespace std;

class salariat {
	int marca;
	char *nume;
	int ol;
	int os;

	static int genm;

public:
	//constructor implicit
	salariat() :marca(genm), ol(0), os(0)
	{
		genm++;
		nume = new char[6];
		strcpy(nume, "Zorro");
	}

	//constructor explicit
	salariat(const char* fnume, int fol, int fos) : marca(genm), ol(fol), os(fos)
	{
		genm++;
		nume = new char[strlen(fnume) + 1];
		strcpy(nume, fnume);
	}

	friend ostream& operator<<(ostream& os, salariat& s)
	{
		os << s.marca << " " << s.nume << " " << s.ol << " " << s.os << endl;
		return os;
	}

	/*void Afisare()
	{
		cout << marca << " " << nume << " " << ol << " " << os << endl;
	}*/

	int get_marca() { return marca; }

	static int Marca_urmator_sal() { return genm; }

	~salariat() { cout << "Destructor!!!" << endl; }

	salariat& operator=(const salariat& obs)   //supradefinirea ooperatorului "="
	{
		delete[] nume;
		nume = new char[strlen(obs.nume) + 1];
		strcpy(nume, obs.nume);
		ol = obs.ol;
		os = obs.os;

		return *this;
	}
};

int salariat::genm = 100;

int main()
{
	cout << salariat::Marca_urmator_sal()<<endl;
	salariat s1, s2("Mirel", 12, 15),s3, * ps;

	cout << s1 << s2 << s3;

	//s1 = s2; profu zicea ca nu merge dar mie mi merge si fara sa suprascriu operatorul

	//s1.Afisare();
	//s2.Afisare();
	////aici s au terminat duratele de viata pt s1 si s2 deci vedem mesajul destructor
	//s1 = s3 = s2;
	//s1.Afisare();
	//s2.Afisare();
	//s3.Afisare();

	ps = new salariat("Gigi", 50, 12.5);
	//ps->Afisare();
	cout << salariat::Marca_urmator_sal()<<endl;
	//salariatul alocat dinamic trebuie dezalocat manual :(
	delete ps;

	return 0;
}