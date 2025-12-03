//RPG
#include <iostream>
using namespace std;

class Character {

protected:
	string name = "npc";
	int hp = 100;
	int dmg = 20;

public:
	Character() {}

	Character(const char* _name) {
		if (strlen(_name) >= 3)
			this->name = _name;
	}

	Character(const char* _name, int _hp, int _dmg) {
		if (strlen(_name) >= 3)
			this->name = _name;

		if (hp >= 100)
			this->hp = _hp;

		if (dmg >= 20)
			this->dmg = _dmg;
	}

	Character(const Character& c) {
		this->name = c.name;
		this->hp = c.hp;
		this->dmg = c.dmg;
	}

	virtual void takeDamage(int dmg) {
		this->hp -= dmg;

		if (this->hp <= 0)
			cout << "\n" << this->name << " died bravely in battle!";
	}

	virtual void attack(Character& target) {
		target.takeDamage(this->dmg);
	}

	Character& operator=(Character c) {
		if (this != &c) {
			this->name = c.name;
			this->hp = c.hp;
			this->dmg = c.dmg;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Character& c);
	friend istream& operator>>(istream& in, Character& c);

	~Character() {
		cout << "\n" << this->name << " just got burried";
	}
};

ostream& operator<<(ostream& out, const Character& c) {
	out << "\nName: " << c.name;
	out << "\nhp: " << c.hp;
	out << "\ndmg: " << c.dmg;

	return out;
}

istream& operator>>(istream& in, Character& c) {
	do {
		cout << "\nName: ";
		in >> c.name;
	} while (c.name.length() < 3);

	do {
		cout << "Health points: ";
		in >> c.hp;
	} while (c.hp < 100);

	do{
		cout << "Damage: ";
		in >> c.dmg;
	} while (c.dmg < 20);

	return in;
}

class Wizard : public Character {
	int mana = 80;

public:
	Wizard() {}

	Wizard(const char* _name): Character(_name) {}

	Wizard(const char* _name, int _hp, int _dmg, int _mana) : Character(_name, _hp, _dmg) {
		if (_mana >= 80)
			this->mana = _mana;
	}

	Wizard(const Wizard& w) : Character(w) {
		this->mana = w.mana;
	}

	void attack(Character& c) override {
		if (this->mana >= 10) {
			Character::attack(c);
			this->mana -= 10;
		}
		else
			cout << "\nNot enough Mana!";
	}

	friend ostream& operator<<(ostream& out, const Wizard& w);
	friend istream& operator>>(istream& in, Wizard& w);

	~Wizard() {
		cout << "\n" << this->name << " the wizard just got burried";
	}
};

ostream& operator<<(ostream& out, const Wizard& w) {
	cout << (Character&)w; //pun & ca sa nu se mai construiasca un Character
	out << "\nMana: " << w.mana;

	return out;
}

istream& operator>>(istream& in, Wizard& w) {
	cin >> (Character&)w;

	do{
		cout << "Mana: ";
		in >> w.mana;
	} while (w.mana < 80);

	return in;
}

class Knight : public Character {
	int armour = 25;
	string general = "no one";

public:
	Knight() {}

	Knight(const char* _name): Character(_name) {}

	Knight(const char* _name, int _hp, int _dmg, int _armour) : Character(_name, _hp, _dmg) {
		if (_armour <= 50)
			this->armour = _armour;
	}

	Knight(const Knight& k) : Character(k) {
		this->armour = armour;
	}

	string getName() const {
		return this->name;
	}

	void setGeneral(string generalName) {
		this->general = generalName;
	}

	void takeDamage(int dmg) override {
		int aux = dmg;
		dmg -= this->armour;
		this->armour -= dmg;

		if (this->armour < 0)
			this->armour = 0;

		if (dmg > 0)
			this->hp -= dmg;
	}

	friend ostream& operator<<(ostream& out, const Knight& k);
	friend istream& operator>>(istream& in, Knight& k);

	~Knight() {
		cout << "\n" << this->name << " the knight just got burried";
	}
};

ostream& operator<<(ostream& out, const Knight& k) {
	cout << (Character&)k;
	out << "\nArmour: " << k.armour;
	out << "\nGeneral: " << k.general;

	return out;
}

istream& operator>>(istream& in, Knight& k) {
	cin >> (Character&)k;
	do {
		cout << "Armour: ";
		in >> k.armour;
	} while (k.armour < 0 || k.armour > 50);

	return in;
}

class General : public Character {
	Knight** soldiers = nullptr;
	int armySize = 0;

public:
	General() {}

	General(const char* _name) : Character(_name) {}

	General(const char* _name, int _hp, int _dmg) : Character(_name, _hp, _dmg) {}

	void addSoldierToArmy(Knight* k) {
		Knight** aux = new Knight*[this->armySize];
		for (int i = 0; i < this->armySize; i++) {
			aux[i] = this->soldiers[i];
		}
		delete[] this->soldiers;
		this->soldiers = nullptr;

		this->soldiers = new Knight * [this->armySize + 1];
		for (int i = 0; i < this->armySize; i++)
			this->soldiers[i] = aux[i];
		this->soldiers[this->armySize] = k;
		k->setGeneral(this->name);

		delete[] aux;

		this->armySize++;
	}

	friend ostream& operator<<(ostream& out, const General& g);

	~General() {
		cout << "\n" << this->name << " the general just got burried";
	}
};

ostream& operator<<(ostream& out, const General& g) {
	cout << (Character&)g;
	out << "\nSoldiers: ";
	for (int i = 0; i < g.armySize; i++)
		out << g.soldiers[i]->getName() << " ";

	return out;
}


int main() {

	//Wizard w("Merlin", 150, 50, 100);
	Knight k("Lancelot", 200, 60, 40);

	/*cout << w;
	cout << k;*/

	General g("Greg", 150, 30);
	g.addSoldierToArmy(&k);

	cout << g;

	return 0;
}