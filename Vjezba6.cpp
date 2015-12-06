/* Lopac Antonio
   42813/14-R
   Vjezba 6 */
#include <iostream>
#include <fstream>
#include <string>
#include "biblioteka_vrijeme_i_binarno_pretrazivanje.cc"
#define n "\n" 

typedef unsigned int var;
using namespace std;


namespace gbv
{
	char Fname[] = "roba_Lopac_Antonio.bin";
	char Ind[] = "roba_indeks.bin";
	tindeks Indeks;
	double Stime;
	float Sprice;
}

class App
{
public:
	var Code;
	char Name[50];
	float Pr;
	var Qt;
	double Et;

	int Fptr(char* name, int i = 0, char c = 0)
	{
		ifstream F(name, ios::binary);
		if (!F) return -1;
		while (F.get(c)) ++i;
		return i;
	}

	var Status(char* name)
	{
		switch (Fptr(name))
		{
		case -1:
			puts(n "0 - Datoteka nije kreirana"n);
			return 0;
		case 0:
			puts(n "1 - Datoteka je prazna"n);
			return 1;

		default:
			printf(n "2 - Datoteka sadrzi %i zapis/a"n, Fptr(name) / sizeof(App));
			return 2;
		}
	}

	void Handle();
	void Search();
	void Print();
};


int main()
{
	var c;
	App app;

	do
	{
		puts(n "1. Rucni unos podataka o robi u indeksiranu datoteku");
		puts("2. Pretrazivanje indeksirane datoteke prema sifri robe");
		puts("3. Ispis sadrzaja maticne datoteke u redoslijedu sifre robe");
		puts("9. Izlaz iz programa" n);

		cout << "Izbor: ";
		cin >> c;

		if (c == 1) app.Handle();
		else if (c == 2) app.Search();
		else if (c == 3) app.Print();
		else if (c != 9) puts(n"Nepostojeci izbor!"n);
	}
	while (c != 9);

	getchar();
	return 0;
}

void App::Handle()
{
	try
	{
		if (!Status(gbv::Fname)) throw 0;
		char pn;

		cout << n "Zelite li raditi s postojecima ili kreirati nove datoteke? (p/n): ";
		cin >> pn;

		if (pn != 'P' && pn != 'p') throw 0;

		vrijeme_pocetak();
		cout << n "Sifra: ";
		cin >> Code;
		cout << "Naziv: ";
		cin.ignore();
		unos(Name);
		cout << "Cijena: ";
		cin >> Pr;
		cout << "Kolicina: ";
		cin >> Qt;
		vrijeme_kraj();
		Et = vrijeme_proteklo() / 1000;

		ofstream F(gbv::Fname, ios::app | ios::binary);
		ofstream I(gbv::Ind, ios::app | ios::binary);
		F.write((char *)this, sizeof(App));
		F.close();

		gbv::Indeks.kljuc = Code;
		gbv::Indeks.adresa = Fptr(gbv::Fname) - sizeof(App);
		I.write((char*)&gbv::Indeks, sizeof(tindeks));
		I.close();
		preslozi_indeks(gbv::Ind, gbv::Indeks);

		ifstream i(gbv::Ind, ios::binary);
		while (i.read((char*)&gbv::Indeks, sizeof(gbv::Indeks))) cout << n "Sifra: " << gbv::Indeks.kljuc << n "Pozicija u maticnoj: " << gbv::Indeks.adresa << n ;
		i.close();
	}
	catch (int e)
	{
		ofstream F(gbv::Fname, ios::trunc | ios::binary);
		ofstream I(gbv::Ind, ios::trunc | ios::binary);
		cout << "Nove datoteke kreirane!" << n ;
		F.close();
		I.close();
	}
}

void App::Search()
{
	if (!Status(gbv::Fname)) return;
	var code;
	cout << n "Unesite sifra za pretragu: ";
	cin >> code;
	var Adresa = pretrazivanje_zapisa(gbv::Ind, code);
	cout << n "Velicina indeksne datoteke u bajtima: " << Fptr(gbv::Ind) << n ;

	if (Adresa == -1 && cout << "Zapis nije pronadjen!"n) return;

	cout << n "Pronaden je sljedeci zapis: " << n ;
	cout << "Sifra: " << code << n "Adresa: " << Adresa << n ;
	ifstream F(gbv::Fname, ios::binary);
	F.seekg(Adresa);
	F.read((char *)this, sizeof(App));
	cout << "Naziv: " << Name << n "Cijena: " << Pr << n ;
	cout << "Kolicina: " << Qt << n "Vrijeme unosa : " << Et << n ;
	F.close();
}

void App::Print()
{
	char name[50];
	cout << "Unesite naziv maticne datoteke: ";
	cin.ignore();
	cin.getline(name, 50);

	if (!Status(name)) return;

	ifstream I(gbv::Ind, ios::binary);
	ifstream F(name, ios::binary);
	
	gbv::Stime = 0;
	gbv::Sprice = 0;

	while (I.read((char*)&gbv::Indeks, sizeof(tindeks)) && !I.eof())
	{
		F.seekg(gbv::Indeks.adresa);
		F.read((char*)this, sizeof(App));
		cout << n "Sifra: " << Code << n "Naziv: " << Name << n "Cijena: " << Pr << n ;
		cout << "Kolicina: " << Qt << n "Vrijeme unosa : " << Et << n << n ;
		gbv::Stime += Et;
		gbv::Sprice += (Qt * Pr);
	}
	cout << n "Ukupno vrijeme unosa: " << gbv::Stime << n "Ukupna vrijednost: " << gbv::Sprice << n ;
	I.close();
	F.close();
}