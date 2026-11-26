#ifndef KOMPLEX_H_INCLUDED
#define KOMPLEX_H_INCLUDED

class Komplex {
private:
	double re;
	double im;
public:
	Komplex(double re = 0, double im = 0);
	Komplex(const Komplex&);
	~Komplex();

	double getRe() const;
	double getIm() const;
	void setRe(double re);
	void setIm(double im);

	void print() const;
	Komplex osszeadas(const Komplex& masik) const;
	Komplex kivonas(const Komplex& masik) const;
	Komplex szorzas(const Komplex& masik) const;
	Komplex osztas(const Komplex& masik) const;
	bool egyenlo(const Komplex& masik) const;

	// barát függvények
	friend double modulus(const Komplex&);
	friend Komplex konjugalt(const Komplex&);
};

double modulus(const Komplex&);
Komplex konjugalt(const Komplex&);

#endif
