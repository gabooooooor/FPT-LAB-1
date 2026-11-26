#include <iostream>
#include "SZLL.h"
using namespace std;

SZLL::SZLL() : fej(nullptr), meret(0) {}

SZLL::SZLL(const SZLL& l) : fej(nullptr), meret(0) {
	for (Csomopont* p = l.fej; p != nullptr; p = p->kovetkezo)
		beszurVegere(p->info);     // melymasolat
}

SZLL::~SZLL() {
	while (fej != nullptr) torolElso();
}

void SZLL::beszurElejere(int ertek) {
	fej = new Csomopont(ertek, fej);
	meret++;
}

void SZLL::beszurVegere(int ertek) {
	Csomopont* uj = new Csomopont(ertek);
	if (fej == nullptr) fej = uj;
	else {
		Csomopont* p = fej;
		while (p->kovetkezo != nullptr) p = p->kovetkezo;
		p->kovetkezo = uj;
	}
	meret++;
}

void SZLL::beszurPoziciora(int ertek, int poz) {
	if (poz <= 0 || fej == nullptr) { beszurElejere(ertek); return; }
	Csomopont* p = fej;
	for (int i = 0; i < poz - 1 && p->kovetkezo != nullptr; i++)
		p = p->kovetkezo;
	p->kovetkezo = new Csomopont(ertek, p->kovetkezo);
	meret++;
}

void SZLL::torolElso() {
	if (fej == nullptr) { cout << "Ures lista!" << endl; return; }
	Csomopont* t = fej;
	fej = fej->kovetkezo;
	delete t;
	meret--;
}

void SZLL::torolUtolso() {
	if (fej == nullptr) { cout << "Ures lista!" << endl; return; }
	if (fej->kovetkezo == nullptr) { torolElso(); return; }
	Csomopont* p = fej;
	while (p->kovetkezo->kovetkezo != nullptr) p = p->kovetkezo;
	delete p->kovetkezo;
	p->kovetkezo = nullptr;
	meret--;
}

void SZLL::torolErtek(int ertek) {
	if (fej == nullptr) return;
	if (fej->info == ertek) { torolElso(); return; }
	Csomopont* p = fej;
	while (p->kovetkezo != nullptr && p->kovetkezo->info != ertek) p = p->kovetkezo;
	if (p->kovetkezo == nullptr) { cout << "Nincs ilyen elem!" << endl; return; }
	Csomopont* t = p->kovetkezo;
	p->kovetkezo = t->kovetkezo;
	delete t;
	meret--;
}

bool SZLL::keres(int ertek) const {
	for (Csomopont* p = fej; p != nullptr; p = p->kovetkezo)
		if (p->info == ertek) return true;
	return false;
}

int SZLL::getMeret() const { return meret; }

void SZLL::kiir() const {
	for (Csomopont* p = fej; p != nullptr; p = p->kovetkezo)
		cout << p->info << " -> ";
	cout << "NULL" << endl;
}