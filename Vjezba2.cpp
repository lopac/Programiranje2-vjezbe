/* Lopac Antonio
   42813/14-R
   vjezba 2 */
#include <iostream>
#include <unistd.h>
#include "biblioteka_vrijeme.cc"
#define SIZE 100

using namespace std;

typedef unsigned int var;

struct tauthor
{
  var author_code;
  char name[SIZE];
  char book_title[SIZE];
  float time;
  tauthor *sljedeci;
};

void unos(tauthor* list)
{
  if(!list)
  {
   puts("\n\tGlava vezane liste nije alocirana, alocirajte glavu vezane liste! (Mogucnost 0.)");
   sleep(1);
  }

  else
  {
    var temp;
    char temp2[SIZE];
    char temp3[SIZE];
    bool boolean;

    tauthor *novi,*zadnji,*pretraga;
    zadnji = list;
    pretraga = list -> sljedeci;

    while (zadnji -> sljedeci)
      zadnji = zadnji -> sljedeci;

    novi = new tauthor;
    zadnji -> sljedeci = novi;
    novi -> sljedeci = NULL;
    vrijeme_pocetak();

    do
    {
      boolean = false;
      cout << "Unesite sifru autora: ";
      cin >> temp;
      cout << "Unesite prezime i ime autora: ";
      unos(temp2);
      cout << "Unesite naslov rada: ";
      unos(temp3);

      while(pretraga)
      {
        if(temp == pretraga -> author_code)
        {
          puts("\nAutor s unesenom sifrom vec postoji!");
          boolean = true;
          break;
        }
        pretraga = pretraga -> sljedeci;
      }

      if(temp < 1000 || temp > 9999) puts("\nSifra autora mora biti u rasponu (1000 - 9999)\n");
    }
    while(boolean || temp < 1000 || temp > 9999);

    vrijeme_kraj();
    novi -> author_code = temp;
    strcpy(novi -> name,temp3);
    strcpy(novi -> book_title,temp2);
    novi -> time = vrijeme_proteklo() / 1000;
    printf("\nProteklo vrijeme je %.2f sekundi/a\n",novi -> time);
  }
}

void ispis(tauthor* list)
{

  if(!list)
  {
   puts("\n\tGlava vezane liste nije alocirana, alocirajte glavu vezane liste! (Mogucnost 0.)");
   sleep(1);
  }

  else
  {
    var counter = 0;
    float average;

    tauthor* tekuci = list -> sljedeci;
    while(tekuci) { tekuci = tekuci -> sljedeci; counter++; }
    printf("Upisano je %i zapis/a\n",counter);

    tauthor* tekucina = list -> sljedeci;
    puts("\nSadrzaj vezane liste: ");
    while(tekucina)
    {
      printf("\tSifra autora: %i\n",tekucina -> author_code);
      printf("\tPrezime i ime: %s\n",tekucina -> name);
      printf("\tNaslov rada: %s\n\n",tekucina -> book_title);
      printf("\tVrijeme unosa: %.2f\n\n",tekucina -> time);
      average += tekucina -> time;
      tekucina = tekucina -> sljedeci;
    }
    printf("Prosjecno vrijeme unosa: %.2f sekundi\n",average/counter);
  }
}

int main(){

  var izbor;
  tauthor* list = NULL;

  do
  {


      puts("\n------------Vjezba 2---------------");
      puts("\n0. Alokacija glave vezane liste");
      puts("1. Unos novog elementa vezane liste studenata");
      puts("2. Ispis sadrzaja cijele vezane liste");
      puts("9. Izlaz iz programa\n");

      cout << "Izbor: ";
      cin >> izbor;

      switch (izbor)
      {
        case 0:
          if(!list)
          {
          list = new tauthor;
          list->sljedeci = NULL;
          cout << "\n\tGlava liste alocirana." << endl;
          sleep(1);
          }

          else {puts("\n\tGlava liste je VEC alocirana!");  sleep(1);}

        break;

        case 1:
           unos(list);
        break;

        case 2:
          ispis(list);
        break;

        default: if(izbor != 9) {puts("\nNepostojeci izbor!\n"); sleep(1);}
        break;
      }

  }
  while(izbor != 9);

  system("pause");
  return 0;
}