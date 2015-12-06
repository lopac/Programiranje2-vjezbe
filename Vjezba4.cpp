/*Lopac Antonio
 42813/14-R
 Vjezba 4 */
#include <iostream>
#include <fstream>
#include "biblioteka_vrijeme.cc"
#define n "\n"
typedef unsigned short int var;
using namespace std;

/*2*/struct pool
{
	int code;
	char name[50];
	float price;
	double etime;
	var qt;
};/*2*/

/*2*/var file_ptr(char* fname, int i = 0, char c = 0)
{
	ifstream ifile(fname, ios::binary);
	while (ifile.get(c)) ++i;
	return i;
}

/*2*/bool fsearch(char* fname, int code)
{
	pool p;
	ifstream ifile(fname, ios::binary);

	while (ifile.read((char*)&p, sizeof(p)) && !ifile.eof())
		if (p.code == code) return true;

	return false;
}

/*2*/void fprint(fstream& ifile, char* fname, bool boolean = false)
{
	/*2*/pool p;
	/*3*/float sum = 0, avg = 0;

	/*3*/if (file_ptr(fname)) cout << n "Sadrzaj datoteke: " << file_ptr(fname) / sizeof(p) << " zapis/a." << n;

	/*2*/while (ifile.read((char*)&p, sizeof(p)) && !ifile.eof())
	{
		//2cout << n "Sifra robe: " << p.code << n;
		//2cout << "Naziv robe: " << p.name << n;
		//2cout << "Cijena: " << p.price << n;
		//2cout << "Kolicina: " << p.qt << n;
		//2cout << "Vrijeme unosa: " << p.etime << " s" << n;
		/*3*/if (boolean)
		{
			cout << "Vrijednost robe: " << p.qt * p.price << " kn."n;
			sum += p.qt * p.price;
			avg += p.etime;
		}
	}
	/*3*/if (boolean)
	{
		cout << n "Ukupna vrijednost robe: " << sum;
		cout << n "Prosjecno vrijeme unosenja: " << avg / (file_ptr(fname) / sizeof(p)) << n;
	}
	/*2*/ifile.close();
}

/*2*/void input()
{
	char* fname = "roba_Ime_Prezime.dat";
	fstream ifile(fname, ios::in | ios::binary);

	if (ifile)
	{
		pool p;
		fprint(ifile, fname);

		ofstream file("roba_Ime_Prezime.dat", ios::app | ios::binary);

		vrijeme_pocetak();
		do
		{


/*2*/			again: cout << n "Sifra robe: "; cin >> p.code;
				
/*2*/			if (fsearch(fname, p.code))
			{
					//2if (file_ptr(fname)) cout << n "Broj zapisa: " << file_ptr(fname) / sizeof(p) << " zapis/a." << n;
					//2puts(n "Sifra vec postoji,unesite ponovno!");
					//2goto again;
			}

		
			  cout << "Naziv robe: ";
			  unos(p.name);
			  cout << "Cijena: ";
			  cin >> p.price;
			  cout << "Kolicina: ";
			  cin >> p.qt;


			/*2*/if (p.price * p.qt < 10 || p.price * p.qt > 1000) cout << n "Umnozak cijene i kolicine nije u rasponu {10,1000}" << n;
		}while (p.price * p.qt < 10 || p.price * p.qt > 1000);
		  vrijeme_kraj();
		  p.etime = vrijeme_proteklo() / 1000;

		  file.write((char*)&p, 80);
		  file.close();
	}

	  else cout << n "Datoteka ne postoji!\nKreirajte datoteku!";
}

/*3*/void ispis()
{
	char fname[50];
	cout << n "Unesite naziv datoteke: ";
	unos(fname);
	fstream file(fname, ios::in | ios::binary);

	if (file.is_open()) fprint(file, fname, 1);

	if (!file_ptr(fname))
	{
		file.close();
		cout << n"Datoteka je prazna ili ne postoji!" << n;
	}
}

/*1*/ int main()
{
         var ch = 0;

	while (ch != 9)
	{
		puts(n "_______________________________________________");
		puts("0. Kreiranje datoteke");
		puts("1. Unos podataka o robi u datoteku");
		puts("2. Ispis sadrzaja datoteke roba");
		puts("9. Izlaz iz programa");
		puts("_______________________________________________");

		cout << "Izbor: ";
		cin >> ch;

		if (ch == 0)
		{
			char yn;
			fstream file("roba_Ime_Prezime.dat", ios::in | ios::binary);

			if (file.is_open())
			{
				cout << n "Datoteka vec postoji, zelite li ju izbrisati i kreirati novu? (d/n): ";
				cin.ignore();
				yn = cin.get();

				if (yn == 'd')
				{
					file.close();
					file.open("roba_Ime_Prezime.dat", ios::out | ios::binary);
				}
				else file.close();
			}
			else file.open("roba_Ime_Prezime.dat", ios::out | ios::binary);
		}
	/*2*/	else if (ch == 1) input();
	/*3*/	else if (ch == 2) ispis();
	/*1*/	else if (ch != 9) puts(n "Nepostojeci izbor!");
	}


   /*1*/	system("pause");
   /*1*/	return 0;
}