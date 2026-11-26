#ifndef MUVELETEK_H_INCLUDED
#define MUVELETEK_H_INCLUDED

class Muveletek {
public:
	virtual float getOsszeg() const = 0;
	virtual float getKamat() const = 0;
	virtual void letet(float osszeg) = 0;
	virtual void kivet(float osszeg) = 0;
	virtual ~Muveletek() {};
};

#endif // !defined(MUVELETEK_H_INCLUDED)