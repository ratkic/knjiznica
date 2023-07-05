#ifndef HEADER_H
#define HEADER_H


//10
typedef struct knjiga{
	char naslov[50];
	char autor[50];
	char vrsta[30];
	int godina;
}KNJIGA;


void izbornik(const char);
int dodajKnjigu();
void ispisKnjiga();
void pretrazivanje(const int);
void sortirajAutora(KNJIGA*, const int);
void ispisAutora();
void sortirajNaslov(KNJIGA*, const int);
void ispisNaslova();
void izbrisiKnjigu();
void izbrisiDat();
void izlaz();


#endif