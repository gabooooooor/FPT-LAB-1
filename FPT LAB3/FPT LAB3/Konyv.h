#ifndef KONYV_H_INCLUDED
#define KONYV_H_INCLUDED

#include <string>

class Konyv {
private:
	std::string szerzo;
	std::string cim;
	std::string isbn;
	float ar;
	static unsigned peldanyok;
public:
	Konyv(const std::string& szerzo = "", const std::string& cim = "", const std::string& isbn = "", float ar = 0);
	Konyv(const Konyv&);
	~Konyv();

	// inline és const függvények
	inline std::string getSzerzo() const { return this->szerzo; }
	inline std::string getCim() const { return this->cim; }
	inline std::string getIsbn() const { return this->isbn; }
	inline float getAr() const { return this->ar; }
	inline void setSzerzo(const std::string& szerzo) { this->szerzo = szerzo; }
	inline void setCim(const std::string& cim) { this->cim = cim; }
	inline void setIsbn(const std::string& isbn) { this->isbn = isbn; }
	inline void setAr(float ar) { this->ar = ar; }

	static unsigned getPeldanyok();
	void kiirKonyv() const;
};

#endif
