#ifndef CSOMOPONT_H_INCLUDED
#define CSOMOPONT_H_INCLUDED

class Csomopont {
private:
	int info;
	Csomopont* kovetkezo;
public:
	Csomopont(int info = 0, Csomopont* kovetkezo = nullptr) : info(info), kovetkezo(kovetkezo) {}
	friend class SZLL;    // az SZLL elerheti az info-t es a kovetkezot
};

#endif