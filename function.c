#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

/*
void izbornik(int izbor) {
	switch (izbor) {
	case 1:
		system("cls");
		dodajKnjigu();
		break;
	case 2:
		system("cls");
		ispisKnjiga();
		break;
	case 3:
		system("cls");
		pretraziNaslov();
		break;
	case 4:
		system("cls");
		pretraziAutora();
		break;
	case 5:
		system("cls");
		sortirajNaslov();
		break;
	case 6:
		system("cls");
		sortirajAutora();
		break;
	case 7:
		system("cls");
		izbrisiKnjigu();
		break;
	case 8:
		system("cls");
		izbrisiDat();
		break;
	case 9:
		system("cls");
		izlaz();
		break;
	default:
		printf("Krivi unos!");
	}
}*/


int dodajKnjigu() {
	FILE* fp = NULL;
	KNJIGA* pKnjiga = NULL;                                 //9
	pKnjiga = (KNJIGA*)malloc(sizeof(KNJIGA));              //14
	int brojKnjiga;                                         //4
	if (pKnjiga == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return 1;
	}

	printf("Unesite naslov knjige: ");
	scanf(" %49[^\n]", pKnjiga->naslov);
	printf("Unesite ime autora: ");
	scanf(" %49[^\n]", pKnjiga->autor);
	printf("Unesite vrstu knjige: ");
	scanf(" %29[^\n]", pKnjiga->vrsta);
	printf("Unesite godinu izdanja knjige: ");
	scanf("%d", &pKnjiga->godina);

	fp = fopen("knjiznica.bin", "rb");                      //16
	if (fp == NULL) {
		fp = fopen("knjiznica.bin", "wb");
		brojKnjiga = 1;
		fwrite(&brojKnjiga, sizeof(int), 1, fp);
		fwrite(pKnjiga, sizeof(KNJIGA), 1, fp);
		fclose(fp);                                         //16
	}
	else {
		fread(&brojKnjiga, sizeof(int), 1, fp);
		KNJIGA knjiga;
		int postoji = 0;                         
		for (int i = 0; i < brojKnjiga; i++) {
			fread(&knjiga, sizeof(KNJIGA), 1, fp);
			if (strcmp(knjiga.naslov, pKnjiga->naslov) == 0) {
				printf("Knjiga sa istim imenom vec postoji u knjiznici.\n");
				postoji = 1;
				break;
			}
		}
		if (!postoji) {
			fclose(fp);
			fp = fopen("knjiznica.bin", "rb+");
			if (ferror(fp)) {                                    //19
				printf("Greska pri otvaranju datoteke.\n");
				return 1;
			}
			brojKnjiga++;
			fseek(fp, 0, SEEK_SET);                              //17
			fwrite(&brojKnjiga, sizeof(int), 1, fp);
			fseek(fp, 0, SEEK_END);                              //17
			fwrite(pKnjiga, sizeof(KNJIGA), 1, fp);
			fclose(fp);
			printf("Uspjesno dodana nova knjiga.\n");
		}
	}

	free(pKnjiga);  //15

	return 0;
}



