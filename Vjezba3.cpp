/* Lopac Antonio 
42813/14-R
Vjezba 3*/
#include <iostream>
#include <cstring>
#include "biblioteka_vrijeme.cc"

#define SIZE 100


using namespace std;

/*1*/typedef unsigned int var;

/*1*/struct tstore
{
	var num;
	var qt;
	char name[SIZE];
	float price;
	double time;
	tstore *l, *d, *p, *s;
};

/*2*/var countlist(tstore* l)
{
	var counter = 0;
	tstore* count = l->s;

	while (count)
	{
		count = count->s;
		counter++;
	}

	return counter;
}

/*3*/void treeremove(tstore* node)
{
	if (node->l) treeremove(node->l);
	if (node->d) treeremove(node->d);

	delete node;
}

/*3*/void treeprint(tstore* tree, bool asc)
{
	static tstore* root = tree;
	if (!tree) return;

	if (asc) treeprint(tree->l, true);
	else treeprint(tree->d, false);

	if (tree != root)
	{
		cout << "\nRedni broj robe: " << tree->num << endl;
		cout << "Naziv robe: " << tree->name << endl;
		cout << "Cijena: " << tree->price << endl;
		cout << "Kolicina: " << tree->qt << endl;
		cout << "Vrijeme unosa: " << tree->time << "s." << endl << endl;
	}

	if (asc) treeprint(tree->d, true);
	else treeprint(tree->l, false);
}


/*2*/void unos(tstore* list, bool end)
{
	/*2*/if (list)
	{
		var cnum, cqt;
		char cname[SIZE];
		float cprice;

		tstore* n = new tstore;
		tstore* z = list;
		tstore* s = list->s;

		if (end)
		{
			cout << "\nTrenutni broj elemenata: " << countlist(list) << endl << endl;

			while (z->s) z = z->s;

			n->p = z;
			n->s = NULL;
			z->s = n;
		}

		if (!end && list->s)
		{
			n->p = list;
			n->s = s;
			list->s = n;
			s->p = n;
		}

		if (!list->s)
		{
			puts("\nLista je prazna,te se ne moze dodati element na pocetak!");
			return;
		}

		vrijeme_pocetak();
		do
		{
			system("Color 1A");
			cout << "Redni broj robe: ";
			cin >> cnum;
			cout << "Naziv robe: ";
			unos(cname);
			cout << "Cijena: ";
			cin >> cprice;
			cout << "Kolicina: ";
			cin >> cqt;
			if (cqt * cprice > 1000) puts("\nRacun je veci od 1000!");
		}
		while (cqt * cprice > 1000);
		vrijeme_kraj();

		n->num = cnum;
		strcpy(n->name, cname);
		n->price = cprice;
		n->qt = cqt;
		n->time = vrijeme_proteklo() / 1000;

		if (end) cout << "Trenutni broj elemenata: " << countlist(list) << endl;

		cout << "\nProteklo vrijeme unosa: " << n->time << "s" << endl;

		if (!end)
		{
			tstore* t = list->s;
			while (t->s) t = t->s;

			while (t != list)
			{
				cout << "\nRedni broj robe: " << t->num << endl;
				cout << "Naziv robe: " << t->name << endl;
				cout << "Vrijednost: " << t->price * t->qt << endl;
				cout << "Vrijeme unosa: " << t->time << "s." << endl << endl;
				t = t->p;
			}

		}
		cin.ignore();
		cin.get();
	}


	/*2*/else puts("\nGlava dvostruko vezane liste nije alocirana!");
};

/*3*/void bst(tstore* t, tstore* & l)
{
	/*3*/if (!l || !t)
	{
		puts("\nKorijen stabla i vezana lista nisu alocirani!");
		return;
	}

	/*3*/if (!l->s)
	{
		puts("\nU vezanoj listi nema elemenata!");
		return;
	}

	/*3*/if (t->l || t->d)
	{
		puts("\nStablo vec postoji!\nDealociranje starog stabla i alokacija novog...");
		treeremove(t);

		t = new tstore;
		t->l = NULL;
		t->d = NULL;
	}

	/*3*/var pivot = 0, counter = 0;
	tstore* lt = new tstore;
	tstore* tt = new tstore;

	lt = l;


	/*3*/while (lt->s)
	{ 
		lt = lt->s;
		++counter;
		pivot += lt->num;
	}

	pivot /= counter;
	t->num = pivot; 
	lt = l;

	/*3*/while (lt->s)
	{
		tstore* n = new tstore;
		lt = lt->s;
		n->l = NULL;
		n->d = NULL;
		n->num = lt->num;
		strcpy(n->name, lt->name);
		n->price = lt->price;
		n->qt = lt->qt;
		n->time = lt->time;
		tt = t;
		while (tt)
		{
			if (n->num > tt->num)
			{
				if (!tt->d)
				{
					tt->d = n;
					break;
				}
				tt = tt->d;
			}
			else
			{
				if (!tt->l)
				{
					tt->l = n;
					break;
				}
				tt = tt->l;
			}
		}
	}

	
	/*3*/
	cout << "Ispis stabla uzlazno ili silazno(u/s): ";
	cin.ignore();
	char print = cin.get();

	if (print == 'u') treeprint(t, true);
	else treeprint(t, false);
}

/*1*/int main()
{
	/*1*/var choice;
	/*1*/tstore* list = NULL;
	/*1*/tstore* tree = NULL;
	do
	{
		system("Color 6E");
		/*1*/puts("\nIzbornik - Vjezba 03");
		/*1*/puts("0. Alokacija vezane liste i korijena binarnog stabla");
		/*1*/puts("1. Dodavanje elementa na kraj dvostruko vezane liste");
		/*1*/puts("2. Dodavanje elementa na pocetak dvostruko vezane liste");
		/*1*/puts("3. Binarno stablo (kreiranje i ispis)");
		/*1*/puts("9. Izlaz\n");

		/*1*/cout << "Izbor: ";
		/*1*/cin >> choice;

		switch (choice)
		{
		/*1*/case 0:
			/*1*/if (list && tree) puts("\nGlava vezane liste i korijena binarnog stabla su VEC alocirane!");

			/*1*/else
			{
				list = new tstore;
				tree = new tstore;
				list->s = NULL;
				list->p = NULL;
				tree->l = NULL;
				tree->d = NULL;
				puts("\nGlava vezane liste i korijena binarnog stabla su upravo alocirani!");
			}
			break;

		/*2*/case 1:
			/*2*/unos(list, 1);
			/*2*/break;

		/*2*/case 2:
			/*2*/unos(list, 0);
			/*2*/break;

		/*3*/case 3:
			/*3*/bst(tree, list);
			break;

		/*1*/default: if (choice != 9) cout << "\nNepostojeci izbor! " << endl;
		}
	}
	while (choice != 9);

	getchar();
	return 0;
}