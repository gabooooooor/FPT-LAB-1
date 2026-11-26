#include <cmath>
#include "Pont.h"

Egyenes Pont::egyenes(2, 1);
int Pont::egyenesenSzam = 0;
int Pont::pozitivSzam = 0;
int Pont::negativSzam = 0;

void Pont::szamol(int d) {
	float k = egyenes.getM() * x + egyenes.getN() - y;
	if (k == 0) egyenesenSzam += d;
	else if (k > 0) pozitivSzam += d;
	else negativSzam += d;
}

Pont::Pont(float x, float y) : x(x), y(y) {
	szamol(1);
}
Pont::Pont(const Pont& p) : x(p.x), y(p.y) {
	szamol(1);
}
Pont::~Pont() { szamol(-1); }

float Pont::getX() const { return x; }
float Pont::getY() const { return y; }
int Pont::getEgyenesen() { return egyenesenSzam; }
int Pont::getPozitiv() { return pozitivSzam; }
int Pont::getNegativ() { return negativSzam; }

float tavolsag(const Pont& a, const Pont& b) {
	float dx = a.x - b.x, dy = a.y - b.y;
	return std::sqrt(dx * dx + dy * dy);
}