//Lopac Antonio 42813 vjezba 7
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "biblioteka_vrijeme.cc"

typedef unsigned int var;
using namespace std;

namespace gb {
	char* fname = "autori_Lopac_Antonio.dat";
	int D, M, Y;
}

class App {
protected:
	var id;
	char name[100];
	char date[10];
	float et;
public:
	App* next;

	var Fptr(int i = 0, char c = 0) {
		ifstream F(gb::fname, ios::binary);
		if (!F) return -1;
		while (F.get(c)) ++i;
		return i;
	}

	var Status() {
		switch (Fptr()) {
		case -1:
			puts("\n0 - Datoteka nije kreirana\n");
			return 0;
		case 0:
			puts("\n1 - Datoteka je prazna\n");
			return 1;
		default:
			printf("\n2 - Datoteka sadrzi %i zapis/a \n", Fptr() / sizeof(App));
			return 2;
		}
	}

	void In();
	void Gen();
	void ToList(App* list);
};

int main() {
	var c;
	App app;
	srand(time(0));
	App* list = new App;
	list->next = NULL;
	do {
		puts("\n\n1. Rucni unos/ispis svih zapisa");
		puts("2. Generiranje zapisa datoteke");
		puts("3. Kopiranje sadrzaja datoteke u odgovarajucu vl/ispis vl");
		puts("9. Izlaz iz programa\n");

		cout << "Izbor: ";
		cin >> c;

		if (c == 1) app.In();
		else if (c == 2) app.Gen();
		else if (c == 3) app.ToList(list);
		else if (c != 9) puts("\nNepostojeci izbor!\n");
	} while (c != 9);

	getchar();
	return 0;
}

void App::In() {
	try {
		if (!Status()) throw 0;

		cout << "\nEnter za postojece, ostalo za nove datoteke: ";
		cin.ignore();
		if (cin.get() != '\n') throw 0;

		vrijeme_pocetak();

		do cout << "\n\nSifra: ";
		while (cin >> id && ((id < 1000 || id > 9999) && cout << "Neispravan unos!"));

		cout << "Prezime i ime: ";
		unos(name);

		do cout << "Dan (dd): ";
		while (cin >> gb::D && ((gb::D < 1 || gb::D > 31) && cout << "Neispravan unos!"));

		do cout << "Mjesec (mm): ";
		while (cin >> gb::M && ((gb::M < 1 || gb::M > 12) && cout << "Neispravan unos!"));

		do cout << "Godina (gggg): ";
		while (cin >> gb::Y && ((gb::Y < 2000 || gb::Y > 2020) && cout << "Neispravan unos!\n"));

		vrijeme_kraj();
		et = vrijeme_proteklo() / 1000;

		sprintf(date, "%d.%d.%d.", gb::D, gb::M, gb::Y);

		ofstream F(gb::fname, ios::app | ios::binary);
		F.write((char *)this, sizeof(App));
		F.close();

		ifstream f(gb::fname, ios::binary);
		while (f.read((char*)this, sizeof(App))) cout << "\n\nSifra: " << id << "\nPrezime i ime: " << name << "\nDatum upisa: " << date << "\nVrijeme unosa:" << et;
		f.close();
		cout << "\nBroj zapisa u datoteci: " << Fptr() / sizeof(App) << endl;
	}
	catch (int ex) {
		ofstream F(gb::fname, ios::trunc | ios::binary);
		cout << "Datoteka kreirana!" << endl;
		F.close();
	}
}

void App::Gen() {
	if (!Status()) return;
	var n;
	cout << "\nBroj zapisa za generiranje: ";
	cin >> n;

	ofstream F(gb::fname, ios::app | ios::binary);
	for (int i = 0; i < n; i++) {
		vrijeme_pocetak();
		id = rand() % 8999 + 1000;
		sprintf(name, "autor_%i", id);
		sprintf(date, "%d.%d.%d.", rand() % 30 + 1, rand() % 11 + 1, rand() % 20 + 2000);
		vrijeme_kraj();
		et = vrijeme_proteklo();
		F.write((char*)this, sizeof(App));
	}
	puts("Zapisi generirani!");
	F.close();
}

void App::ToList(App* list) {
	if (Status() != 2) return;

	App* e = list->next;
	bool flag = false;
	cout << "Enter ako zelite ucitati sadrzaj datoteke u VL, ostalo za ispis: ";
	cin.ignore();
	if (cin.get() != '\n' && (flag = true)) while (e && cout << "\n\nSifra: " << e->id << "\nPrezime i ime: " << e->name << "\nDatum: " << e->date << "\nVrijeme unosa: " << e->et << endl) e = e->next;
	if (flag) return;

	while (list->next) {
		e = list->next;
		list->next = e->next;
		delete e;
	}
	puts("\nLista dealocirana!");

	ifstream f(gb::fname, ios::binary);
	while (f.read((char*)this, sizeof(App))) {
		App *node = new App;
		node->id = id;
		strcpy(node->name, name);
		strcpy(node->date, date);
		node->et = et;
		node->next = list->next;
		list->next = node;
	}
	puts("Datoteka prepisana u listu!");
	f.close();
}