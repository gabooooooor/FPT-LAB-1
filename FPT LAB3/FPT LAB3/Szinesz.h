#ifndef SZINESZ_H_INCLUDED
#define SZINESZ_H_INCLUDED

#include <string>

class Szinesz {
private:
	std::string nev;
	unsigned kor;
	std::string orszag;
	static unsigned peldanyok;
public:
	Szinesz(const std::string& nev = "", unsigned kor = 0, const std::string& orszag = "");
	Szinesz(const Szinesz&);
	~Szinesz();

	std::string getNev() const;
	unsigned getKor() const;
	std::string getOrszag() const;
	void setNev(const std::string& nev);
	void setKor(unsigned kor);
	void setOrszag(const std::string& orszag);

	static unsigned getPeldanyok();
	void kiirSzinesz() const;
};

#endif
