#include <iostream>

#include "Konyv.h"

using namespace std;

unsigned Konyv::peldanyok = 0;

Konyv::Konyv(const string& szerzo, const string& cim, const string& isbn, float ar) :
	szerzo(szerzo), cim(cim), isbn(isbn), ar(ar) {
	peldanyok++;
}

Konyv::Konyv(const Konyv& param) :
	szerzo(param.szerzo), cim(param.cim), isbn(param.isbn), ar(param.ar) {
	peldanyok++;
}

Konyv::~Konyv() {
	peldanyok--;
}

unsigned Konyv::getPeldanyok() {
	return peldanyok;
}

void Konyv::kiirKonyv() const {
	cout << "Szerző: " << this->szerzo << endl;
	cout << "Cím: " << this->cim << endl;
	cout << "ISBN: " << this->isbn << endl;
	cout << "Ár: " << this->ar << endl;
}
