#ifndef HEADER_H
#define HEADER_H

//10
typedef struct knjiga {
	char naslov[50];
	char autor[50];
	char vrsta[30];
	int godina; //ili char
}KNJIGA;

//void izbornik(int izbor);
int dodajKnjigu();
/*
void ispisKnjiga();
void pretraziNaslov();
void pretraziAutora();
void sortirajNaslov();
void sortirajAutora();
void izbrisiKnjigu();
void izbrisiDat();
void izlaz();
*/

#endif