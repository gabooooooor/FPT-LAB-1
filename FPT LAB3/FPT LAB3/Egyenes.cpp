#include "Egyenes.h"
#include "Pont.h"

Egyenes::Egyenes(float m, float n) : m(m), n(n) {}
Egyenes::Egyenes(const Egyenes& e) : m(e.m), n(e.n) {}
Egyenes::~Egyenes() {}
float Egyenes::getM() const { return m; }
float Egyenes::getN() const { return n; }

bool Egyenes::rajtaVan(const Pont& p) const {
	return m * p.x + n == p.y;
}