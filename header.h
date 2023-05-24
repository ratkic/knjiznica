#ifndef HEADER_H
#define HEADER_H


//10
typedef struct knjiga{
	char naslov[50];
	char autor[50];
	char vrsta[30];
	int godina; //ili char
}KNJIGA;


void izbornik(const char);
int dodajKnjigu();
void ispisKnjiga();
void pretrazivanje(int);
/*
int usporediNaslov(const void*, const void*);
int usporediAutor(const void*, const void*);
int usporediVrstu(const void*, const void*);
int usporediGodinu(const void*, const void*);
*/
/*
void sortirajNaslov();
void sortirajAutora();
void izbrisiKnjigu();
void izbrisiDat();
*/
void izlaz();


#endif