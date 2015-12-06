#include <iostream>
#include <cmath>
#include <string>
#include "biblioteka_vrijeme.cc"
#define POV(s,x,y,z) pow((s) * (s - a) * (s - b) * (s - c),0.5)

using namespace std;

namespace gb
{
   string Warning = "\nStranice koje ste unijeli ne cine trokut!\nPritisnite enter ako zelite ponovno unesti stranice, 0 za dalje: ";
   string Warning2 = "\nPolje je puno!\n";
   int numof = 0;
   int good = 0;
   float sum = 0;
}

class Triangle
{
   float s;
   cvrijeme time;
public:
   static int counter;
   string name;
   float a, b, c;

   int Status() {
	if (!gb::numof && cout << "\n0 - Polje nije alocirano") return 0;
	if (!counter && cout << "\n1 - Polje je prazno i alocirano na " << gb::numof << " elemenata\n") return 1;
	if (counter && cout << "\n2 - Polje je alocirano na " << gb::numof << " elemenata, a upisano je " << counter << endl) return 2;
   }

   void Unos() {
	time.pocetak();

	cout << "\nNaziv trokuta: ";
	cin.ignore();
	getline(cin, name);
	do {
		cout << "Unesi stranicu a: ";
		cin >> a;
		cout << "Unesi stranicu b: ";
		cin >> b;
		cout << "Unesi stranicu c: ";
		cin >> c;
		
		s = (a + b + c) / 2;

		cin.ignore();
		if (s <= a || s <= b || s <= c) cout << gb::Warning;
		if ((s <= a || s <= b || s <= c) && cin.get() != '\n') break;
	} while (s <= a || s <= b || s <= c);
	
	time.kraj();
	if ((s > a && s > b && s > c) && gb::good++) gb::sum += POV(s, a, b, c);
	cout << "\nTrenutni broj unesenih trokuta: " << counter << endl;
    }

    void Ispis() {
	cout << "\n\nNaziv: " << name << endl;
	cout << "Stranica a: " << a << "\nStranica b: " << b << "\nStranica c: " << c << endl;
	if (s > a && s > b && s > c) cout << "Povrsina: " << POV(s, a, b, c) << endl;
	else cout << "*Nije trokut" << endl;
        cout << "Vrijeme unosa: " << time.proteklo() / 1000;
    }
};

int Triangle::counter = 0;

int main() {
	short int c, i;
	Triangle* T = new Triangle;
	do {
	    puts("\n\n1. Dinamicka alokacija polja trokuta");
	    puts("2. Unos podataka o trokutima");
	    puts("3. Ispis podataka o svim unesenim trokutima");
	    puts("9. Izlaz");

	    cout << "\nIzbor: ";
	    cin >> c;

            switch (c) {
		case 1:
		    if (T->Status()) break;
			cout << "\nUnesi broj elemenata polja: ";
			cin >> gb::numof;
			T = new Triangle[gb::numof];
			break;

		case 2:
		    if (!T->Status()) break;
			if (Triangle::counter == gb::numof && cout << gb::Warning2) break;
			T[Triangle::counter++].Unos();
			break;

		case 3:
		    if (!T->Status()) break;
			i = 0;
			while (i < Triangle::counter) T[i++].Ispis();
			cout << "\n\nUkupna povrsina: " << gb::sum << endl;
			cout << "Broj unosa koji ne cine trokut: " << Triangle::counter - gb::good << endl;
			break;

		default:
			if (c != 9) puts("\nNepostojeci izbor!");
		}
	} while (c != 9);

	system("pause");
	return 0;
}