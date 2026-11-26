#ifndef EGYENES_H_INCLUDED
#define EGYENES_H_INCLUDED

class Pont;

class Egyenes {
private:
	float m, n;
public:
	Egyenes(float m = 1, float n = 0);
	Egyenes(const Egyenes& e);
	~Egyenes();

	float getM() const;
	float getN() const;
	bool rajtaVan(const Pont& p) const;
};

#endif