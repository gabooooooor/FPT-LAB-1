#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include <string>
#include "Kliens.h"

class Bank {
private:
	std::string bankKod;
	unsigned kliensekSzama;
	static const unsigned MAX_KLIENSEK = 20;
	Kliens kliensek[MAX_KLIENSEK];
public:
	Bank(const std::string& bankKod = "");
	Bank(const Bank&);

	std::string getBankKod() const;
	unsigned getKliensekSzama() const;
	void setBankKod(const std::string& bankKod);

	void ujKliens(const Kliens&);
	void kiirBank() const;
};

#endif