#include <iostream>
#include <windows.h>
#include "Tortek.h"
#include "Bank.h"

using namespace std;
int main() {
	SetConsoleOutputCP(CP_UTF8);
	//Tortek a;          // 0/1
	//Tortek b(5);       // 5/1
	//Tortek c(3, 4);    // 3/4
	//Tortek d(c);       // másolat
	//a.print(); b.print(); c.print(); d.print();
	//
	//Tortek e = c.osszeadas(b);
	//e.print();
	//c.kivonas(b).print();    // 3/4 - 5/1 = -17/4
	//c.szorzas(b).print();    // 15/4
	//c.osztas(b).print();     // 3/20

	//cout << Tortek::lnko(12, 18) << endl;   // 6

	//Tortek(6, 8).egyszerusites().print();    // 3/4
	//Tortek(3, -4).egyszerusites().print();   // -3/4
	//Tortek(0, 5).egyszerusites().print();    // 0/1
	//Tortek(-6, -8).egyszerusites().print();  // 3/4

	//cout << Tortek(3, 4).egyenlo(Tortek(6, 8)) << endl;   // 1
	//cout << Tortek(3, 4).egyenlo(Tortek(3, 5)) << endl;   // 0
	//Tortek(3, 4).forditott().print();                     // 4/3

	Bankszamla s1("RO01", 1000, "RON");   // 1. kliens RON szamla
	Bankszamla s2("EU01", 300, "EUR");    // 1. kliens EUR szamla
	Bankszamla s3("RO02", 200, "RON");    // 2. kliens 1. RON szamla
	Bankszamla s4("RO03", 700, "RON");    // 2. kliens 2. RON szamla

	// letet, kivet
	s1.letet(500);        // 1500
	s1.kivet(200);        // 1300
	s3.kivet(1000);       // hiba: nincs fedezet
	s2.letet(50);         // 350

	// transzfer
	s1.transzfer(s3, 300);    // s1: 1000, s3: 500
	s1.transzfer(s2, 100);    // hiba: EUR szamla, csak RON-RON lehet
	s4.transzfer(s3, 5000);   // hiba: nincs fedezet
	s4.transzfer(s3, 200);    // s4: 500, s3: 700

	// copy-konstruktor kiprobalasa
	Bankszamla s1masolat(s1);
	cout << "s1 masolat: " << s1masolat.getSzamlaSzam() << ", " << s1masolat.getOsszeg() << endl;

	// get / set
	s2.setPenznem("EUR");
	cout << "s2 penzneme: " << s2.getPenznem() << ", kamata: " << s2.getKamat() << "%" << endl;
	cout << endl;

	// Kliensek
	Kliens k1("Kovacs", "Janos", "Targu Mures, Str. Libertatii 1");
	k1.ujKonto(s1);
	k1.ujKonto(s2);

	Kliens k2("Nagy", "Anna", "Cluj-Napoca, Str. Memorandumului 5");
	k2.ujKonto(s3);
	k2.ujKonto(s4);

	// Bank
	Bank bank("BTRLRO22");
	bank.ujKliens(k1);
	bank.ujKliens(k2);

	// A mainben csak a kiirBank-ot hivjuk
	bank.kiirBank();

	return 0;
}
