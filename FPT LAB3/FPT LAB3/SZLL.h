#ifndef SZLL_H_INCLUDED
#define SZLL_H_INCLUDED

#include "Csomopont.h"

class SZLL {
private:
	Csomopont* fej;
	int meret;
public:
	SZLL();
	SZLL(const SZLL& l);
	~SZLL();

	void beszurElejere(int ertek);
	void beszurVegere(int ertek);
	void beszurPoziciora(int ertek, int poz);   // poz: 0-tol

	void torolElso();
	void torolUtolso();
	void torolErtek(int ertek);                 // az elso elofordulast

	bool keres(int ertek) const;
	int getMeret() const;
	void kiir() const;
};

#endif