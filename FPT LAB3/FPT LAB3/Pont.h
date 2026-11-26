#ifndef PONT_H_INCLUDED
#define PONT_H_INCLUDED

#include "Egyenes.h"

class Pont {
private:
	float x, y;
	static Egyenes egyenes;
	static int egyenesenSzam, pozitivSzam, negativSzam;
	void szamol(int d);
public:
	Pont(float x = 0, float y = 0);
	Pont(const Pont& p);
	~Pont();

	float getX() const;
	float getY() const;

	static int getEgyenesen();
	static int getPozitiv();
	static int getNegativ();

	friend float tavolsag(const Pont& a, const Pont& b);
	friend class Egyenes;
};

// a friend deklaracio az osztalyon belul nem eleg a hivashoz, ezert kell ide is:
float tavolsag(const Pont& a, const Pont& b);

#endif