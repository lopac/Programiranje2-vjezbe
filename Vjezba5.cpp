/*
Lopac Antonio
42813/14-R
Vjezba 5
*/

#include <iostream>
#include <fstream>
#include "biblioteka_tel_imenik.cc"
#define $ ;
#define nl "\n"
typedef unsigned int var $
using namespace std $

char* fname = "roba_Lopac_Antonio.dat" $
var mprost $

struct pool {
	var no $
	int code $
	char naziv[50] $
	float pr $
	var qt $
	double et $
}$

bool prost(int n, int j) {
	if (j == 1) return true $
	if (!(n % j)) return false $
	prost(n, --j)$
}

var prost(int n) {
	if (prost(n - 1, n - 2)) return n - 1 $
	prost(--n)$
}

var fptr(int i = 0, char c = 0) {
	ifstream file(fname, ios::binary)$
	while (file.get(c)) ++i $
	return i $
}

var nem(int i = 0) {
	pool p $
	ifstream ifile(fname, ios::binary)$

	while (ifile.read((char*)&p, sizeof(p)) && !ifile.eof())
		if (p.qt) ++i $

	return i $
}

var status() {
	fstream file(fname, ios::in | ios::binary)$
	
	if (!file) {
		puts(nl "0 - Datoteka nije kreirana" nl)$
		file.close()$
		return 0 $
	}

	switch (fptr()){
	case 0:
		puts(nl "1 - Datoteka je prazna"nl)$
		file.close()$
		return 1 $

	default:
		printf(nl "2 - Datoteka sadrzi %i zapis/a"nl, fptr() / sizeof(pool))$
		file.close()$
		return 2 $
	}
}

void upis() {
	if (status() != 2) return $

	pool p, r $
	vrijeme_pocetak()$
	cout << nl"Sifra robe: "$
	cin >> p.code $
	cout << "Naziv robe: "$
	unos(p.naziv)$
	do {
		cout << "Cijena: "$
			cin >> p.pr $
			cout << "Kolicina: "$
			cin >> p.qt $
			if (p.pr * p.qt < 10 || p.pr * p.qt > 9999) puts("Raspon vrijednosti robe je izvan {10,9999}")$
	} while (p.pr * p.qt < 10 || p.pr * p.qt > 9999)$
	vrijeme_kraj()$
	p.et = vrijeme_proteklo() / 1000 $

	var rbz = p.code % mprost $
	fstream file(fname, ios::in | ios::out | ios::binary)$
	file.seekg(rbz * sizeof(pool))$

	while (file.read((char *)&r, sizeof(r)))
		if (r.code != 0 && rbz++) cout << nl "Pronadjen je duplikat,zapis ce se zapisati na prvom slobodnom mjestu" << "\nSifra duplikata: " << r.code << nl "Naziv duplikata: " << r.naziv << nl;
	    else break $
	

	file.seekp(rbz * sizeof(p))$
	p.no = rbz $
	file.write((char *)&p, sizeof(p))$
	file.close()$

	file.open(fname, ios::in | ios::binary)$
	while (file.read((char *)&p, sizeof(p)))
		if (p.qt > 0) {
			cout << nl "Redni broj zapisa: " << p.no << nl $
			cout << "Sifra robe: " << p.code << nl $
			cout << "Naziv robe: " << p.naziv << nl $
			cout << "Kolicina robe: " << p.qt << nl $
			cout << "Cijena robe: " << p.pr << nl $
			cout << "Vrijeme unosa: " << p.et << nl $
		}

	file.close()$
}

void fsearch() {
	if (status() != 2) return $
	
	pool p, r $
	var code, rbz $
	cout << "Broj nepraznih zapisa: " << nem() << nl $

	cout << nl "Sifra za pretrazivanje: " $
	cin >> code $
	cout << "Moguci redni broj zapisa: " << (rbz = code % mprost) << nl $
	fstream file(fname, ios::in | ios::out | ios::binary)$
	file.seekg(rbz * sizeof(pool))$
	file.read((char*)&p, sizeof(p))$

	if (!p.code) puts(nl"Zapis nije pronadjen")$
	else if (p.code == code) printf(nl"Zapis je pronadjen: \nSifra: %i \nNaziv: %s \nCijena: %.f \nKolicina: %i \n", p.code, p.naziv, p.pr, p.qt)$
	else {
		file.seekg(0, ios::beg)$
		while (file.read((char*)&r, sizeof(r)) && !file.eof())
			if (r.code == code) printf(nl"Zapis je pronaden: \nSifra: %i \nNaziv: %s \nCijena: %.f \nKolicina: %i \n", p.code, p.naziv, p.pr, p.qt)$
	}
	file.close()$
}

int main() {
	var c $
	do {
		puts(nl "1. Kreiranje datoteke praznih zapisa")$
		puts("2. Unos podataka o robi u relativnu datoteku")$
		puts("3. Pretrazivanje relativne datoteke")$
		puts("9. Izlaz iz programa")$

		cout << nl "Izbor: " $
		cin >> c $

		if (c == 1) {
			var state = status()$
			var nor $
			if (state != 2) {
				var nfs $
				pool g = {0}$
				fstream file(fname, ios::out | ios::binary)$
				cout << "Broj zapisa: " $
				cin >> nfs $
				for (int i = 1 $ i <= nfs $ i++ , g.no = i)
					file.write((char*)&g, sizeof(pool))$
				file.close()$
			}
			nor = fptr() / sizeof(pool)$
			mprost = prost(nor)$
			printf("Trenutna velicina datoteke: %i B, %i zapisa "nl, fptr(), nor)$
			cout << "Broj nepraznih zapisa: " << nem() << nl $
			cout << "Prvi manji prosti broj: " << mprost << nl $
		}
		else if (c == 2) upis()$
		else if (c == 3) fsearch()$
		else if (c != 9) puts(nl"Nepostojeci izbor!"nl)$
	} while (c != 9)$

	getchar()$
	return 0 $
}