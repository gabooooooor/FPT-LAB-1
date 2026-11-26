#ifndef KLIENS_H_INCLUDED
#define KLIENS_H_INCLUDED

#include <string>
#include "Bankszamla.h"

class Kliens {
private:
	std::string vnev;
	std::string knev;
	std::string cim;
	static const unsigned MAX_KONTOK = 10;
	Bankszamla kontok[MAX_KONTOK];
	unsigned kontokSzama;
public:
	Kliens(const std::string& vnev = "", const std::string& knev = "", const std::string& cim = "");
	Kliens(const Kliens&);

	std::string getVnev() const;
	std::string getKnev() const;
	std::string getCim() const;
	void setVnev(const std::string& vnev);
	void setKnev(const std::string& knev);
	void setCim(const std::string& cim);

	unsigned getKontokSzama() const;

	void ujKonto(const Bankszamla&);
	void kiirKliens() const;
};

#endif