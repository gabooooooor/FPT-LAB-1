#include <iostream>
#include "Bank.h"
using namespace std;

Bank::Bank(const string& bankKod) :
	bankKod(bankKod), kliensekSzama(0) {
}

Bank::Bank(const Bank& param) :
	bankKod(param.bankKod), kliensekSzama(param.kliensekSzama) {
	for (unsigned i = 0; i < kliensekSzama; i++)
		this->kliensek[i] = param.kliensek[i];
}

string Bank::getBankKod() const {
	return this->bankKod;
}

unsigned Bank::getKliensekSzama() const {
	return this->kliensekSzama;
}

void Bank::setBankKod(const string& bankKod) {
	this->bankKod = bankKod;
}

void Bank::ujKliens(const Kliens& kliens) {
	if (this->kliensekSzama < MAX_KLIENSEK)
	{
		this->kliensek[this->kliensekSzama++] = kliens;
	}
	else cout << "A bank már elérte a maximális kliensszámot!" << endl;
}

void Bank::kiirBank() const {
	cout << "Bank kód: " << this->bankKod << endl;
	cout << "Kliensek száma: " << this->kliensekSzama << endl;
	for (unsigned i = 0; i < kliensekSzama; i++) {
		cout << "Kliens #" << i + 1 << ":" << endl;
		this->kliensek[i].kiirKliens();
	}
}