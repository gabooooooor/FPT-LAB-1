#include <iostream>

#include "Kliens.h"

using namespace std;

Kliens::Kliens(const string& vnev, const string& knev, const string& cim) :
	vnev(vnev), knev(knev), cim(cim), kontokSzama(0) {
}

Kliens::Kliens(const Kliens& param) :
	vnev(param.vnev), knev(param.knev), cim(param.cim), kontokSzama(param.kontokSzama) {
	for (unsigned i = 0; i < kontokSzama; i++)
		this->kontok[i] = param.kontok[i];
}

string Kliens::getVnev() const {
	return this->vnev;
}

string Kliens::getKnev() const {
	return this->knev;
}

string Kliens::getCim() const {
	return this->cim;
}

void Kliens::setVnev(const string& vnev) {
	this->vnev = vnev;
}

void Kliens::setKnev(const string& knev) {
	this->knev = knev;
}

void Kliens::setCim(const string& cim) {
	this->cim = cim;
}

unsigned Kliens::getKontokSzama() const {
	return this->kontokSzama;
}

void Kliens::ujKonto(const Bankszamla& szamla) {
	if (this->kontokSzama < MAX_KONTOK)
	{
		this->kontok[this->kontokSzama++] = szamla;
	}
	else cout << "A kliens már elérte a maximális számlaszámot!" << endl;
}

void Kliens::kiirKliens() const {
		cout << "Vezetéknév: " << this->vnev << endl;
	cout << "Keresztnév: " << this->knev << endl;
	cout << "Cím: " << this->cim << endl;
	cout << "Számlák száma: " << this->kontokSzama << endl;
	for (unsigned i = 0; i < kontokSzama; i++) {
		cout << "Számla #" << i + 1 << ":" << endl;
		this->kontok[i].kiirSzamla();
	}
}