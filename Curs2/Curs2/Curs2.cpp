#include <iostream>
using namespace std;

class salariat {
	int marca;
	char nume[20];
	int ol;
	int os;

public:
	//constructor implicit
	salariat() : marca(0), ol(0), os(0)
	{
		strcpy(nume, "Zorro");
	}

	//constructor explicit
	salariat(int fmarca, const char* fnume, int fol, int fos) : marca(fmarca), ol(fol), os(fos)
	{
		strcpy(nume, fnume);
	}

	void Afisare()
	{
		cout << marca << " " << nume << " " << ol << " " << os << endl;
	}

	~salariat() { cout << "Destructor!!!"<<endl; }
};

int main()
{
	salariat s1, s2(150, "Mirel", 12, 15), *ps;

	s1.Afisare();
	s2.Afisare();
	//aici s au terminat duratele de viata pt s1 si s2 deci vedem mesajul destructor

	ps = new salariat(150, "Gigi", 50, 12.5);
	ps->Afisare();
	//salariatul alocat dinamic trebuie dezalocat manual :(
	delete ps;

	return 0;
}