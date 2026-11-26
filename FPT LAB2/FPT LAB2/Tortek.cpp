#include <iostream>
#include <cstdlib>
#include "Tortek.h"

using namespace std;

Tortek::Tortek(int szamlalo, int nevezo) :
	szamlalo(szamlalo), nevezo(nevezo) {
	if (this->nevezo == 0) {
		cout << "0-val nem lehet osztani!" << endl;
		this->szamlalo = 0;
		this->nevezo = 1;
	}
}

Tortek::Tortek(const Tortek& param) :
	szamlalo(param.szamlalo), nevezo(param.nevezo) {
}

void Tortek::print() const {
	cout << this->szamlalo << "/" << this->nevezo << endl;
}

Tortek Tortek::osszeadas(const Tortek& masik) const {
	return (Tortek((this->szamlalo * masik.nevezo + this->nevezo * masik.szamlalo), (this->nevezo * masik.nevezo)));
}

Tortek Tortek::kivonas(const Tortek& masik) const {
	return Tortek((this->szamlalo * masik.nevezo - this->nevezo * masik.szamlalo), (this->nevezo * masik.nevezo));
}

Tortek Tortek::szorzas(const Tortek& masik) const {
	return Tortek((this->szamlalo * masik.szamlalo), (this->nevezo * masik.nevezo));
}

Tortek Tortek::osztas(const Tortek& masik) const {
	if (masik.szamlalo == 0) {
		cout << "0 - val nem lehet osztani" << endl;
		return Tortek(0, 1);
	}
	return Tortek((this->szamlalo * masik.nevezo), (this->nevezo * masik.szamlalo));
}

int Tortek::lnko(int a, int b) {
	if (b == 0) return abs(a);
	return lnko(b, abs(a % b));
}

Tortek Tortek::egyszerusites() const {
	int koz = lnko(this->szamlalo, this->nevezo);
	int ujnevezo = this->nevezo / koz;
	int ujszamlalo = this->szamlalo / koz;
	if (ujnevezo < 0) {
		ujszamlalo *= -1;
		ujnevezo *= -1;
	}
	return Tortek(ujszamlalo, ujnevezo);
}

Tortek Tortek::forditott() const {
	if (this->szamlalo == 0)
	{
		cout << "0-val nem lehet osztani!" << endl;
		return Tortek(0, 1);
	}
	return Tortek(this->nevezo, this->szamlalo);
}

bool Tortek::egyenlo(const Tortek& masik) const {
	Tortek t1 = this->egyszerusites();
	Tortek t2 = masik.egyszerusites();
	return (t1.szamlalo * t2.nevezo == t1.nevezo * t2.szamlalo);
}