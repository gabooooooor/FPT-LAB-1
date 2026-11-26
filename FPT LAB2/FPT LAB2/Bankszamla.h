#ifndef BANKSZAMLA_H_INCLUDED
#define BANKSZAMLA_H_INCLUDED

#include <string>
#include "Muveletek.h"

class Bankszamla : public Muveletek {
private:
	std::string szamlaSzam;
	float osszeg;
	std::string penznem;
public:
	Bankszamla(const std::string& szamlaSzam = "", float osszeg = 0, const std::string& penznem = "RON");
	Bankszamla(const Bankszamla&);

	std::string getSzamlaSzam() const;
	std::string getPenznem() const;
	void setSzamlaSzam(const std::string& szamlaSzam);
	void setOsszeg(float osszeg);
	void setPenznem(const std::string& penznem);

	float getOsszeg() const override;
	float getKamat() const override;
	void letet(float osszeg) override;
	void kivet(float osszeg) override;

	void transzfer(Bankszamla& hova, float osszeg);
	void kiirSzamla() const;
};

#endif