#include <iostream>

#include "Bankszamla.h"

using namespace std;

Bankszamla::Bankszamla(const string& szamlaSzam, float osszeg,const string& penznem) :
	szamlaSzam(szamlaSzam), osszeg(osszeg), penznem(penznem) {

}

Bankszamla::Bankszamla(const Bankszamla& param) :
	szamlaSzam(param.szamlaSzam), osszeg(param.osszeg), penznem(param.penznem) {

}

float Bankszamla::getKamat() const {
	if (this->penznem == "RON" && this->osszeg < 500) return 0.3f;
	else if (this->penznem == "RON" && this->osszeg >= 500) return 0.8f;
	else if (this->penznem == "EUR") return 0.1f;
	else return 0.0f;
}

float Bankszamla::getOsszeg() const {
	return this->osszeg + this->osszeg * getKamat() / 100.f;
}

string Bankszamla::getSzamlaSzam() const {
	return this->szamlaSzam;
}

string Bankszamla::getPenznem() const {
	return this->penznem;
}

void Bankszamla::setSzamlaSzam(const string& szamlaSzam) {
	this->szamlaSzam = szamlaSzam;
}

void Bankszamla::setOsszeg(float osszeg) {
	this->osszeg = osszeg;
}

void Bankszamla::setPenznem(const string& penznem) {
	this->penznem = penznem;
}

void Bankszamla::letet(float osszeg) {
	this->osszeg += osszeg;
}

void Bankszamla::kivet(float osszeg) {
	if (this->osszeg < osszeg) {
		cout << "Nincs elegendő pénz a számlán!" << endl;
		return;
	}
	this->osszeg -= osszeg;
}

void Bankszamla::transzfer(Bankszamla& hova, float osszeg) {
	if (this->penznem == "RON" && hova.penznem == "RON") {
		if(this->osszeg < osszeg) {
			cout << "Nincs elegendő pénz a számlán!" << endl;
			return;
		}
		this->osszeg -= osszeg;
		hova.osszeg += osszeg;
	}
	else cout << "Transzfer csak RON számlák között lehetséges!" << endl;
}

void Bankszamla::kiirSzamla() const {
	cout << "Számlaszám: " << this->getSzamlaSzam() << endl;
	cout << "Pénznem: " << this->getPenznem() << endl;
	cout << "Összeg: " << this->osszeg << endl;
	cout << "Kamat: " << this->getKamat() << "%" << endl;
	cout<< "Végösszeg: " << this->getOsszeg() << endl;
}