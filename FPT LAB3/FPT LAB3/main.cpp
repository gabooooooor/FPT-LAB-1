#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include "Konyv.h"
#include "Pont.h"
#include "SZLL.h"
#include "Film.h"
#include "Komplex.h"


using namespace std;

Pont sulypont(const vector<Pont>& t) {
	float sx = 0, sy = 0;
	for (const Pont& p : t) { sx += p.getX(); sy += p.getY(); }
	return Pont(sx / t.size(), sy / t.size());
}

// levágja a sor végéről a '\r' karaktert (Windowsos fájloknál lehet)
void tisztit(string& s) {
	if (!s.empty() && s.back() == '\r') s.pop_back();
}

// egy könyvet olvas be a megadott streamből (billentyűzet vagy fájl)
Konyv* beolvasKonyv(istream& in) {
	string szerzo, cim, isbn;
	float ar;
	getline(in, szerzo);
	getline(in, cim);
	getline(in, isbn);
	in >> ar;
	in.ignore(1000, '\n');
	tisztit(szerzo);
	tisztit(cim);
	tisztit(isbn);
	return new Konyv(szerzo, cim, isbn, ar);
}

// rendezés (növekvő), a nagyobb/kisebb döntést a barát összehasonlító függvény adja
void rendezBevetel(Film* filmek[], unsigned n) {
	for (unsigned i = 0; i < n - 1; i++)
		for (unsigned j = 0; j < n - i - 1; j++)
			if (kevesebbBevetel(*filmek[j + 1], *filmek[j])) {
				Film* seged = filmek[j];
				filmek[j] = filmek[j + 1];
				filmek[j + 1] = seged;
			}
}

void rendezSzineszSzam(Film* filmek[], unsigned n) {
	for (unsigned i = 0; i < n - 1; i++)
		for (unsigned j = 0; j < n - i - 1; j++)
			if (kevesebbSzinesz(*filmek[j + 1], *filmek[j])) {
				Film* seged = filmek[j];
				filmek[j] = filmek[j + 1];
				filmek[j + 1] = seged;
			}
}

void kiirFilmek(Film* filmek[], unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		filmek[i]->kiirFilm();
		cout << endl;
	}
}

int main() {
	SetConsoleOutputCP(CP_UTF8);

	//1
	//int n;
	//cout << "Hany pont? ";
	//cin >> n;

	//vector<Pont> t;
	//for (int i = 0; i < n; i++) {
	//	float x, y;
	//	cin >> x >> y;
	//	t.push_back(Pont(x, y));
	//}

	//cout << "Egyenesen: " << Pont::getEgyenesen() << endl;
	//cout << "Pozitiv felsik: " << Pont::getPozitiv() << endl;
	//cout << "Negativ felsik: " << Pont::getNegativ() << endl;

	//if (n >= 2) cout << "Tavolsag t[0]-t[1]: " << tavolsag(t[0], t[1]) << endl;

	//if (n > 0) {
	//	Pont s = sulypont(t);
	//	cout << "Sulypont: " << s.getX() << ", " << s.getY() << endl;
	//}

	//Egyenes e;   // y = x
	//cout << "t[0] rajta van y=x-en: " << e.rajtaVan(t[0]) << endl;

	//2
	//SZLL l;
	//l.beszurElejere(2);
	//l.beszurVegere(5);
	//l.beszurPoziciora(9, 1);    // 2 9 5
	//l.kiir();
	//SZLL m(l);                  // melymasolat
	//l.torolErtek(9);
	//l.torolUtolso();
	//l.kiir();                   // 2
	//m.kiir();                   // 2 9 5, nem valtozott

	//3
	//int valasz;
	//unsigned n;
	//ifstream f;
	//istream* in = &cin;

	//cout << "Beolvasás: 1 - billentyűzetről, 2 - fájlból (konyvek.txt): ";
	//cin >> valasz;
	//cin.ignore(1000, '\n');

	//if (valasz == 2) {
	//	f.open("konyvek.txt");
	//	if (!f) {
	//		cout << "Nem sikerült megnyitni a fájlt!" << endl;
	//		return 1;
	//	}
	//	in = &f;
	//	*in >> n;
	//	in->ignore(1000, '\n');
	//}
	//else {
	//	cout << "Hány könyv legyen? ";
	//	cin >> n;
	//	cin.ignore(1000, '\n');
	//}

	//Konyv** tomb = new Konyv * [n];
	//for (unsigned i = 0; i < n; i++) {
	//	if (valasz != 2)
	//		cout << i + 1 << ". könyv (szerző, cím, ISBN, ár - mind külön sorban):" << endl;
	//	tomb[i] = beolvasKonyv(*in);
	//}

	//string keresett;
	//cout << "Add meg a szerzőt: ";
	//getline(cin, keresett);

	//cout << endl << keresett << " által írt könyvek:" << endl;
	//bool talalt = false;
	//for (unsigned i = 0; i < n; i++) {
	//	if (tomb[i]->getSzerzo() == keresett) {
	//		tomb[i]->kiirKonyv();
	//		cout << endl;
	//		talalt = true;
	//	}
	//}
	//if (!talalt) cout << "Nincs ilyen szerző a tömbben." << endl;

	//cout << "A Konyv osztály példányainak száma: " << Konyv::getPeldanyok() << endl;

	//for (unsigned i = 0; i < n; i++)
	//	delete tomb[i];
	//delete[] tomb;

	//cout << "Törlés után: " << Konyv::getPeldanyok() << endl;
	//return 0;

	//4
	//Szinesz sz1("Leonardo DiCaprio", 50, "USA");
	//Szinesz sz2("Kate Winslet", 51, "UK");
	//Szinesz sz3("Tom Hanks", 68, "USA");
	//Szinesz sz4("Brad Pitt", 62, "USA");

	//const unsigned N = 3;
	//Film* filmek[N];
	//filmek[0] = new Film("Titanic", 1997, 2200);
	//filmek[1] = new Film("Revolutionary Road", 2008, 90);
	//filmek[2] = new Film("Inception", 2010, 830);

	//filmek[0]->ujSzinesz(sz1);
	//filmek[0]->ujSzinesz(sz2);
	//filmek[0]->ujSzinesz(sz3);

	//filmek[1]->ujSzinesz(sz1);
	//filmek[1]->ujSzinesz(sz2);

	//filmek[2]->ujSzinesz(sz1);
	//filmek[2]->ujSzinesz(sz4);
	//filmek[2]->ujSzinesz(sz3);
	//filmek[2]->ujSzinesz(Szinesz("Marion Cotillard", 49, "Franciaország"));

	//cout << "=== Filmek ===" << endl;
	//kiirFilmek(filmek, N);

	//cout << "=== Törlés: Tom Hanks a Titanicból ===" << endl;
	//filmek[0]->torolSzinesz("Tom Hanks");
	//filmek[0]->torolSzinesz("Nincs Ilyen");   // hiba: nincs ilyen színész
	//filmek[0]->kiirFilm();
	//cout << endl;

	//cout << "=== Rendezés bevétel szerint ===" << endl;
	//rendezBevetel(filmek, N);
	//kiirFilmek(filmek, N);

	//cout << "=== Rendezés a színészek száma szerint ===" << endl;
	//rendezSzineszSzam(filmek, N);
	//kiirFilmek(filmek, N);

	//cout << "=== Közös színészek ===" << endl;
	//kozosSzineszek(*filmek[0], *filmek[2]);
	//cout << endl;

	//cout << "A Szinesz osztály példányainak száma: " << Szinesz::getPeldanyok() << endl;

	//for (unsigned i = 0; i < N; i++)
	//	delete filmek[i];

	//cout << "A filmek törlése után: " << Szinesz::getPeldanyok() << endl;
	//return 0;

	//5
	Komplex a;          // 0 + 0i
	Komplex b(3, 4);    // 3 + 4i
	Komplex c(1, -2);   // 1 - 2i
	Komplex d(b);       // másolat
	a.print(); b.print(); c.print(); d.print();
	cout << endl;
	
	b.osszeadas(c).print();   // 4 + 2i
	b.kivonas(c).print();     // 2 + 6i
	b.szorzas(c).print();     // 11 - 2i
	b.osztas(c).print();      // -1 + 2i
	b.osztas(a).print();      // hiba: 0-val osztás
	cout << endl;
	
	cout << b.egyenlo(d) << endl;   // 1
	cout << b.egyenlo(c) << endl;   // 0
	cout << endl;
	
	// a :: kell, mert a std::modulus-szal ütközne
	cout << "|b| = " << ::modulus(b) << endl;   // 5
	cout << "b konjugáltja: ";
	konjugalt(b).print();                       // 3 - 4i
	
	return 0;
}