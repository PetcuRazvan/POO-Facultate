#include<iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <map>
#include <iterator> //pentru niste iteratoti smecheri
#include <algorithm>

using namespace std;

class suma_el {
	double s;

public:
	suma_el() : s(0) {}
	void operator()(double element) { s += element; }
	operator double() { return s; }
};

void afisare(int element) { cout << "\n" << element; }
bool sens(int a, int b) { return a < b; }

void main()
{
	int i;
	ostream_iterator<double> osit(cout, "\n");
	vector<int> vi;
	vector<int>::iterator it;
	vector<int>::reverse_iterator rit;
	
	vi.push_back(100); vi.push_back(50); vi.push_back(74);
	//for (rit = vi.rbegin(); rit != vi.rend(); rit++) cout << *rit << endl;
	//for (i = 0; i < vi.size(); i++)cout << vi[i] << endl;
	//for (auto el : vi)cout << el << endl;
	//for (it = vi.begin(); it != vi.end(); it++) cout << *it << endl;

	//sort(vi.begin(), vi.end(), sens);
	int sum = 0;
	for_each(vi.begin(), vi.end(), [&sum](int element) { sum += element; }); //functie lambda
	cout << sum;

	cout << endl;
	list<double>  ld;
	list<double>::iterator lit;
	ld.push_back(4.7); ld.push_back(2.76); ld.push_back(67.11);
	ld.push_front(100);
	suma_el obs;
	double sumallist = for_each(ld.begin(), ld.end(), obs); 
	cout << "\nSuma elementelor listei: " << sumallist;

	for (lit = ld.begin(); lit != ld.end(); lit++) osit = *lit;
	cout << endl;
	stack<int, list<int>> s;
	s.push(40); s.push(25); s.push(54);
	cout << s.top() << endl;
	s.pop(); s.pop(); s.pop();
	cout << (s.empty() ? "Stiva vida!!" : to_string(s.top()));

	//map declarare + inserare
	map<int, string> mp;
	map<int, string>::iterator mpit;
	mp.insert({ 300, "Vasile" });
	mp.insert(pair<int, string>(200, "SILvia"));
	pair<int, string> eln(250, "Gigi");
	mp.insert(eln);

	//parcurgere
	for (auto el : mp) cout << "\n" << el.first << " " << el.second; //sunt ordonate crescator dupa cheie
	pair<int, string> elnou(350, "Elena");
	//mp.insert(elnou); //returneaza o pereche <iterator la perechea adaugata sau perechea care exista deja, boolean daca s a adaugat sau nu>
	if (mp.insert(elnou).second == false) cout << "\nElement deja exista";

	for (mpit = mp.begin(); mpit != mp.end(); mpit++) {
		cout << "\n" << mpit->first << " " << mpit->second;
	}

	mpit = mp.find(750);
	if (mpit == mp.end()) cout << "\nNu l a gasit";
	else cout << "\nNumele: " << mpit->second;
}