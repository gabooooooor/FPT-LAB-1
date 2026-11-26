#ifndef TORTEK_H_INCLUDED
#define TORTEK_H_INCLUDED
class Tortek {
private:
	int szamlalo;
	int nevezo;
public:
	Tortek(int szamlalo = 0, int nevezo = 1);
	Tortek(const Tortek&);

	void print() const;
	Tortek osszeadas(const Tortek& masik) const;
	Tortek kivonas(const Tortek& masik) const;
	Tortek szorzas(const Tortek& masik) const;
	Tortek osztas(const Tortek& masik) const;
	Tortek egyszerusites() const;
	Tortek forditott() const;
	bool egyenlo(const Tortek& masik) const;

	static int lnko(int a, int b);
};

#endif 