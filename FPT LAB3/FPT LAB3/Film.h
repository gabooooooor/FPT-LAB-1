#ifndef FILM_H_INCLUDED
#define FILM_H_INCLUDED

#include <string>
#include "Szinesz.h"

class Film {
private:
	std::string cim;
	unsigned ev;
	float bevetel;
	static const unsigned MAX_SZINESZEK = 20;
	Szinesz* szineszek[MAX_SZINESZEK];   // a színészek listája (a lista végére lehet adni)
	unsigned szineszekSzama;
public:
	Film(const std::string& cim = "", unsigned ev = 0, float bevetel = 0);
	Film(const Film&);
	~Film();
	Film& operator=(const Film&);

	std::string getCim() const;
	unsigned getEv() const;
	float getBevetel() const;
	unsigned getSzineszekSzama() const;
	void setCim(const std::string& cim);
	void setEv(unsigned ev);
	void setBevetel(float bevetel);

	void ujSzinesz(const Szinesz&);              // a lista végére ad
	bool torolSzinesz(const std::string& nev);   // törlés név alapján
	void kiirFilm() const;

	// barát függvények
	friend bool kevesebbBevetel(const Film&, const Film&);
	friend bool kevesebbSzinesz(const Film&, const Film&);
	friend void kozosSzineszek(const Film&, const Film&);
};

bool kevesebbBevetel(const Film&, const Film&);
bool kevesebbSzinesz(const Film&, const Film&);
void kozosSzineszek(const Film&, const Film&);

#endif
