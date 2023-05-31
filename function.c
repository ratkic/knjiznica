#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

static int brojKnjiga = 0;               //5

void izbornik(const char izbor) {        //11
	//8
	int odabir = 0;                      //4, 1
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
		pretrazivanje(odabir);
		break;
	case 4:
		system("cls");
		ispisAutora();
		break;
	case 5:
		system("cls");
		ispisNaslova();
		break;
	case 6:
		system("cls");
		izbrisiKnjigu();
		break;
	case 7:
		system("cls");
		izbrisiDat();
		break;
	case 8:
		system("cls");
		izlaz();
		break;
	default:
		system("cls");
		printf("\033[1;37;31m\nKrivi unos! Pokusajte ponovno: \033[0m\n\n");
		return;
	}
}


int dodajKnjigu() {
	FILE* fp = NULL;
	KNJIGA* pKnjiga = NULL;                                 //9                                            
	pKnjiga = (KNJIGA*)malloc(sizeof(KNJIGA));              //14
	//int brojKnjiga;                                         
	if (pKnjiga == NULL) {                                  //15
		printf("\033[1;37;31m\nGreska pri alokaciji memorije.\n");
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
		int postoji = 0;                                    //4, 1
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
				printf("\033[1;37;31m\nGreska pri otvaranju datoteke.\n");
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

	free(pKnjiga);                                               //15
	pKnjiga = NULL;
	printf("\n\nUnesi bilo koji znak za povratak na izbornik:\n");
	getch();
	system("cls");

	return 0;
}


void ispisKnjiga() {
	//int brojKnjiga;
	int i;
	FILE* fp = NULL;
	KNJIGA* pKnjiga = NULL;                                           //9
	fp = fopen("knjiznica.bin", "rb");                                //16
	if (fp == NULL) {                                 
		perror("Error");                                              //19
		system("cls");
		exit(EXIT_FAILURE);
	}

	fread(&brojKnjiga, sizeof(int), 1, fp);
	if (brojKnjiga == 0) {
		printf("Repozitorij je prazan, probaj drugu opciju.\n");
		printf("\nUnesi bilo koji znak za povratak na izbornik:\n");
		getch();
		system("cls");
		return;
	}

	pKnjiga = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));
	if (pKnjiga == NULL) {
		printf("\033[1;37;31m\nGreska pri alokciji memorije.\n");
		return 1;
	}
	fread(pKnjiga, sizeof(KNJIGA), brojKnjiga, fp);

	printf("\033[1;35;47m");
	printf("U nasoj knjiznici mozete pronaci %d knjig%s.", brojKnjiga, brojKnjiga == 1 || brojKnjiga > 4 ? "a" : "e");
	printf("\033[0m");

	for (i = 0; i < brojKnjiga; i++) {
		printf("\033[1;35;47m\n\nNaslov: \033[0m %s\n", (pKnjiga + i)->naslov);
		printf("\033[1;35;47mAutor:\033[0m %s\n", (pKnjiga + i)->autor);
		printf("\033[1;35;47mVrsta:\033[0m %s\n", (pKnjiga + i)->vrsta);
		printf("\033[1;35;47mGodina izdanja:\033[0m %d\n", (pKnjiga + i)->godina);
		printf("\033[0m");
	}
	fclose(fp);
	free(pKnjiga);                                                    //15
	pKnjiga = NULL;                                                   //15
	printf("\n\nUnesi bilo koji znak za povratak na izbornik:\n");
	getch();
	system("cls");

	return;
}


//21
void pretrazivanje(const int odabir) {                                //11
	KNJIGA* pKnjiga = NULL;
	FILE* fp = NULL;
	char pretraziNaslov[50], pretraziAutora[50], pretraziVrstu[30];   //12
	int pretraziGodinu;
	int brojKnjiga, flag = 0;

	//system("cls");
	
	fp = fopen("knjiznica.bin", "rb");                                   //16
	if (fp == NULL) {                                                    //19
		perror("Error");
		system("cls");
		exit(EXIT_FAILURE);
	}

	fread(&brojKnjiga, sizeof(int), 1, fp);
	pKnjiga = (KNJIGA*) malloc(sizeof(KNJIGA));                      //13
	if (pKnjiga == NULL) {
		printf("\033[1;37;31m\nGreska pri alokaciji memorije.\n");
		return 1;
	}

	system("cls");
	printf("\nOdaberi opciju pretrazivanja: \n");
	printf("1. Pretrazivanje po naslovu\n");
	printf("2. Pretrazivanje po autoru\n");
	printf("3. Pretrazivanje po vrsti\n");
	printf("4. Pretrazivanje po godini\n");
	printf("5. Povratak u glavni izbornik\n");

	//odabir = getch();
	scanf("%d", &odabir);
	// inicijalizacija polja knjiga koje æe se ispisati
	KNJIGA* knjige = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));     //13
	if (knjige == NULL) {
		printf("\033[1;37;31m\nGreska pri alokaciji memorije.\n");
		return;
	}
	int brojPronadenihKnjiga = 0;                                      //4, 1

	switch (odabir) {
	case 1:
		system("cls");
		printf("Odabrali ste opciju 1.\n");
		printf("Unesite naslov knjige koju trazite: \n");
		scanf(" %49[^\n]", pretraziNaslov);


		for (int i = 0; i < brojKnjiga; i++) {
			fread(pKnjiga, sizeof(KNJIGA), 1, fp);
			if (strcmp(pKnjiga->naslov, pretraziNaslov) == 0) {
				// ako je naslov knjige jednak traženom naslovu, dodaj knjigu u polje knjiga koje æe se ispisati
				*(knjige + brojPronadenihKnjiga) = *pKnjiga;
				brojPronadenihKnjiga++;
			}
		}

		if (brojPronadenihKnjiga > 0) {
			// ispis svih knjiga koje su pronaðene
			printf("\nPronadeno je %d knjiga autora %s:\n", brojPronadenihKnjiga, pretraziNaslov);
			for (int i = 0; i < brojPronadenihKnjiga; i++) {
				printf("\033[1;35;47m\nNaslov:\033[0m \033[1;35m %s \033[0m", (knjige + i)->naslov);
				printf("\033[1;35;47m\nAutor:\033[0m %s", (knjige + i)->autor);
				printf("\033[1;35;47m\nVrsta:\033[0m %s", (knjige + i)->vrsta);
				printf("\033[1;35;47m\nGodina:\033[0m %d\n", (knjige + i)->godina);
			}
			flag = 1;
		}
		break;
	case 2:
		system("cls");
		printf("Odabrali ste opciju 2.\n");
		printf("Unesite ime autora knjige koju trazite: \n");
		scanf(" %49[^\n]", pretraziAutora);


		for (int i = 0; i < brojKnjiga; i++) {
			fread(pKnjiga, sizeof(KNJIGA), 1, fp);
			if (strcmp(pKnjiga->autor, pretraziAutora) == 0) {
				*(knjige + brojPronadenihKnjiga) = *pKnjiga;
				brojPronadenihKnjiga++;
			}
		}

		if (brojPronadenihKnjiga > 0) {
			printf("\nPronadeno je %d knjiga autora %s:\n", brojPronadenihKnjiga, pretraziAutora);
			for (int i = 0; i < brojPronadenihKnjiga; i++) {
				printf("\033[1;35;47m\nNaslov:\033[0m %s", (knjige + i)->naslov);
				printf("\033[1;35;47m\nAutor:\033[0m \033[1;35m %s \033[0m", (knjige + i)->autor);
				printf("\033[1;35;47m\nVrsta:\033[0m %s", (knjige + i)->vrsta);
				printf("\033[1;35;47m\nGodina:\033[0m %d\n", (knjige + i)->godina);
			}
			flag = 1;
		}
		break;
	case 3:
		system("cls");
		printf("Odabrali ste opciju 3.\n");
		printf("Unesite vrstu knjige koju trazite: \n");
		scanf(" %29[^\n]", pretraziVrstu);

		for (int i = 0; i < brojKnjiga; i++) {
			fread(pKnjiga, sizeof(KNJIGA), 1, fp);
			if (strcmp(pKnjiga->vrsta, pretraziVrstu) == 0) {
				*(knjige + brojPronadenihKnjiga) = *pKnjiga;
				brojPronadenihKnjiga++;
			}
		}

		if (brojPronadenihKnjiga > 0) {
			printf("\nPronadeno je %d knjiga vrste %s:\n", brojPronadenihKnjiga, pretraziVrstu);
			for (int i = 0; i < brojPronadenihKnjiga; i++) {
				printf("\033[1;35;47m\nNaslov:\033[0m %s", (knjige + i)->naslov);
				printf("\033[1;35;47m\nAutor:\033[0m %s", (knjige + i)->autor);
				printf("\033[1;35;47m\nVrsta:\033[0m \033[1;35m %s \033[0m", (knjige + i)->vrsta);
				printf("\033[1;35;47m\nGodina:\033[0m %d\n", (knjige + i)->godina);
			}
			flag = 1;
		}
		break;
	case 4:
		system("cls");
		printf("Odabrali ste opciju 4.\n");
		printf("Unesite godinu knjige koju trazite: \n");
		scanf("%d", &pretraziGodinu);

		for (int i = 0; i < brojKnjiga; i++) {
			fread(pKnjiga, sizeof(KNJIGA), 1, fp);
			if (pKnjiga->godina == pretraziGodinu) {
				*(knjige + brojPronadenihKnjiga) = *pKnjiga;
				brojPronadenihKnjiga++;
			}
		}

		if (brojPronadenihKnjiga > 0) {
			printf("\nPronadeno je %d knjiga godine izdanja %d:\n", brojPronadenihKnjiga, pretraziGodinu);
			for (int i = 0; i < brojPronadenihKnjiga; i++) {
				printf("\033[1;35;47m\nNaslov:\033[0m %s", (knjige + i)->naslov);
				printf("\033[1;35;47m\nAutor:\033[0m %s", (knjige + i)->autor);
				printf("\033[1;35;47m\nVrsta:\033[0m %s", (knjige + i)->vrsta);
				printf("\033[1;35;47m\nGodina:\033[0m \033[1;35m %d \033[0m\n", (knjige + i)->godina);
			}
			flag = 1;
		}
		break;
	case 5:
		system("cls");
		return;
		break;
	default:
		system("cls");
		printf("\033[1;37;31m\nKrivi unos!\033[0m\n\n");
		return;
		break;
	}
	if (flag == 0) {
		printf("\nKnjiga nije dostupna\n");
	}

	free(knjige);                                                         //15   
	knjige = NULL;                                                        //15

	fclose(fp);
	free(pKnjiga);                                                        //15
	pKnjiga = NULL;                                                       //15
	printf("\n\nUnesi bilo koji znak za povratak na izbornik:\n");
	getch();
	system("cls");

	return;
}


//20
void sortirajAutora(KNJIGA * pKnjiga, const int brojKnjiga) {
	int j, i;
	KNJIGA* temp = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));                  //14

	for (i = 0; i < brojKnjiga; i++) {
		for (j = i + 1; j < brojKnjiga; j++) {
			if (strcmp((pKnjiga + i)->autor, (pKnjiga + j)->autor) > 0) {

				strcpy(temp, (pKnjiga + i)->autor);
				strcpy((pKnjiga + i)->autor, (pKnjiga + j)->autor);
				strcpy((pKnjiga + j)->autor, temp);

				strcpy(temp, (pKnjiga + i)->naslov);
				strcpy((pKnjiga + i)->naslov, (pKnjiga + j)->naslov);
				strcpy((pKnjiga + j)->naslov, temp);

				strcpy(temp, (pKnjiga + i)->vrsta);
				strcpy((pKnjiga + i)->vrsta, (pKnjiga + j)->vrsta);
				strcpy((pKnjiga + j)->vrsta, temp);

				temp->godina = (pKnjiga + i)->godina;
				(pKnjiga + i)->godina = (pKnjiga + j)->godina;
				(pKnjiga + j)->godina = temp->godina;
			}


		}
	}

	free(temp);                                                //15
	temp = NULL;

	return;

}

void ispisAutora() {
	int brojKnjiga, i;
	FILE* fp = NULL;
	KNJIGA* pKnjiga = NULL;
	fp = fopen("knjiznica.bin", "rb");                                //16
	if (fp == NULL) {
		perror("Error");                                              //19
		system("cls");
		exit(EXIT_FAILURE);
	}

	fread(&brojKnjiga, sizeof(int), 1, fp);
	if (brojKnjiga == 0) {
		printf("Repozitorij je prazan, probaj drugu opciju.\n");
		getch();
		system("cls");
		return;
	}

	pKnjiga = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));
	if (pKnjiga == NULL) {
		printf("\033[1;37;31m\nGreska pri alokciji memorije.\n");
		return 1;
	}
	fread(pKnjiga, sizeof(KNJIGA), brojKnjiga, fp);

	sortirajAutora(pKnjiga, brojKnjiga);

	// ispis sortiranog niza
	printf("\nSortirani niz:\n");
	for (i = 0; i < brojKnjiga; i++) {
		printf("\n%d. %s - \033[1;35m %s \033[0m - %s - %d\n", i + 1, (pKnjiga + i)->naslov, (pKnjiga + i)->autor, (pKnjiga + i)->vrsta, (pKnjiga + i)->godina);
	}
	fclose(fp);                                                              //16
	free(pKnjiga);
	pKnjiga = NULL;                                                          //15
	printf("\n\nUnesi bilo koji znak za povratak na izbornik:\n");
	getch();
	system("cls");

	return;
}



//20
void sortirajNaslov(KNJIGA* pKnjiga, const int brojKnjiga) {                    //11
	int j, i;
	KNJIGA* temp = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));

	for (i = 0; i < brojKnjiga; i++) {
		for (j = i + 1; j < brojKnjiga; j++) {
			if (strcmp((pKnjiga + i)->naslov, (pKnjiga + j)->naslov) > 0) {

				strcpy(temp, (pKnjiga + i)->naslov);
				strcpy((pKnjiga + i)->naslov, (pKnjiga + j)->naslov);
				strcpy((pKnjiga + j)->naslov, temp);

				strcpy(temp, (pKnjiga + i)->autor);
				strcpy((pKnjiga + i)->autor, (pKnjiga + j)->autor);
				strcpy((pKnjiga + j)->autor, temp);

				strcpy(temp, (pKnjiga + i)->vrsta);
				strcpy((pKnjiga + i)->vrsta, (pKnjiga + j)->vrsta);
				strcpy((pKnjiga + j)->vrsta, temp);

				temp->godina = (pKnjiga + i)->godina;
				(pKnjiga + i)->godina = (pKnjiga + j)->godina;
				(pKnjiga + j)->godina = temp->godina;

			}


		}
	}

	free(temp);                                           //15
	temp = NULL;

	return;
}



void ispisNaslova() {
	int brojKnjiga, i;
	FILE* fp = NULL;
	KNJIGA* pKnjiga = NULL;
	fp = fopen("knjiznica.bin", "rb");
	if (fp == NULL) {
		perror("Error");                                              //19
		system("cls");
		exit(EXIT_FAILURE);
	}

	fread(&brojKnjiga, sizeof(int), 1, fp);
	if (brojKnjiga == 0) {
		printf("Repozitorij je prazan, probaj drugu opciju.\n");
		getch();
		system("cls");
		return;
	}

	pKnjiga = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));
	if (pKnjiga == NULL) {
		printf("\033[1;37;31m\nGreska pri alokciji memorije.\n");
		return 1;
	}
	fread(pKnjiga, sizeof(KNJIGA), brojKnjiga, fp);

	sortirajNaslov(pKnjiga, brojKnjiga);

	// ispis sortiranog niza
	printf("\nSortirani niz:\n");
	for (i = 0; i < brojKnjiga; i++) {
		printf("\n%d. \033[1;35m %s \033[0m - %s - %s - %d\n", i + 1, (pKnjiga + i)->naslov, (pKnjiga + i)->autor, (pKnjiga + i)->vrsta, (pKnjiga + i)->godina);
	}
	fclose(fp);
	free(pKnjiga);
	pKnjiga = NULL;                                                  //15
	printf("\n\nUnesi bilo koji znak za povratak na izbornik:\n");
	getch();
	system("cls");

	return;
}



void izbrisiKnjigu() {
	KNJIGA* pKnjiga = NULL;
	int index, flag = 0;
	char str[30];
	FILE* fp = fopen("knjiznica.bin", "rb");
	if (fp == NULL) {
		perror("Error");                                              //19
		system("cls");
		exit(EXIT_FAILURE);
	}
	else {
		fread(&brojKnjiga, sizeof(int), 1, fp);
		pKnjiga = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));
		if (pKnjiga == NULL) {
			printf("\033[1;37;31m\nGreska pri alokciji memorije.\n");
			return 1;
		}
		else {
			fread(pKnjiga, sizeof(KNJIGA), brojKnjiga, fp);
			fclose(fp);
			system("cls");
			printf("Unesite naziv knjige koju zelite obrisati: \n");
			scanf(" %29[^\n]", str);
			for (int i = 0; i < brojKnjiga; i++) {
				if (strcmp((pKnjiga + i)->naslov, str) == 0) {
					index = i;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				printf("\nKnjiga nije dostupna!\n");
			}
			else {
				fclose(fp);
				fp = fopen("knjiznica.bin", "wb");                      //16
				if (fp == NULL) {
					perror("Error");                                    //19
					system("cls");
					exit(EXIT_FAILURE);
				}
				else {
					brojKnjiga--;
					fwrite(&brojKnjiga, sizeof(int), 1, fp);
					for (int i = 0; i < brojKnjiga + 1; i++) {
						if (i == index) {
							continue;
						}
						else {
							fwrite((pKnjiga + i), sizeof(KNJIGA), 1, fp);
						}
					}
					printf("\nKnjiga je obrisana!\n");
					fclose(fp);
					free(pKnjiga);
				}
			}
		}
	}
}


void izbrisiDat() {
	char izbor[3];                                             //12
	int var;
	char imeDat[] = "knjiznica.bin";                           //12

	printf("Zelite li obrisati cijelu knjiznicu? (da/ne)\n");
	while (1) {
		scanf(" %2s", izbor);
		if (strcmp(izbor, "da") == 0) {
			printf("\nIzlazak iz programa...");
			var = remove(imeDat);                               //18
			if (var == 0) {
				printf("Uspjesno obrisana datoteka.\n");
				system("cls");
				return;
			}
			else {
				printf("Brisanje nije uspjelo.\n\n");
				return;
			}
		}
		else if (strcmp(izbor, "ne") == 0) {
			system("cls");
			return;
		}
		else {
			printf("\033[1;37;31m\nPogresan unos, molimo unesite 'da' ili 'ne': \033[0m\n");
		}
	}
}



void izlaz() {
	char odabir[3];                                                //12
	printf("Zelite li izaci iz programa? (da/ne)\n");
	while (1) {
		scanf(" %2s", odabir);
		if (strcmp(odabir, "da") == 0) {
			printf("\nIzlazak iz programa...");
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(odabir, "ne") == 0) {
			system("cls");
			return;
		}
		else {
			printf("\033[1;37;31m\nPogresan unos, molimo unesite 'da' ili 'ne': \033[0m\n");
		}
	}
}



/*
void pretrazivanje(int kriterij) {
	FILE* fp = fopen("knjiznica.bin", "rb");
	if (fp == NULL) {
		printf("\nGreska.\n");
		return;
	}

	int brojKnjiga;
	fread(&brojKnjiga, sizeof(int), 1, fp);

	KNJIGA* knjige = (KNJIGA*)malloc(brojKnjiga * sizeof(KNJIGA));
	if (knjige == NULL) {
		printf("Greska.\n");
		fclose(fp);
		return;
	}

	fread(knjige, sizeof(KNJIGA), brojKnjiga, fp);
	fclose(fp);

	system("cls");
	printf("1. Pretrazivanje po imenu\n");
	printf("2. Pretrazivanje po autoru\n");
	printf("3. Pretrazivanje po vrsti\n");
	printf("4. Pretrazivanje po godini\n");
	printf("5. Povratak u glavni izbornik\n");
	//kriterij = getch();
	scanf("%d", &kriterij);
	// Izvršavanje pretrage
	switch (kriterij) {
	case 1:
	{
		char kljucNaslov[50];
		printf("Unesite naslov trazene knjige: ");
		scanf(" %49[^\n]", kljucNaslov);

		qsort(knjige, brojKnjiga, sizeof(KNJIGA), usporediNaslov);

		KNJIGA* trazeniNaslov;
		trazeniNaslov = bsearch(kljucNaslov, knjige, brojKnjiga, sizeof(KNJIGA), usporediNaslov);

		if (trazeniNaslov != NULL) {
			printf("\033[1;35;47m\nNaslov:\033[0m \033[1;35m %s \033[0m", trazeniNaslov->naslov);
			printf("\033[1;35;47m\nAutor:\033[0m %s", trazeniNaslov->autor);
			printf("\033[1;35;47m\nVrsta:\033[0m %s", trazeniNaslov->vrsta);
			printf("\033[1;35;47m\nGodina:\033[0m %d\n", trazeniNaslov->godina);
		}
		else {
			printf("\nNisam nasao trazenu knjigu.\n");
		}
		free(knjige);
		break;
	}
	case 2:
	{
		char kljucAutor[50];
		printf("Unesite ime autora trazene knjige: ");
		scanf(" %49[^\n]", kljucAutor);

		// Sortiranje knjiga prema autoru
		qsort(knjige, brojKnjiga, sizeof(KNJIGA), usporediAutor);

		KNJIGA *trazeniAutor;
		trazeniAutor = bsearch(kljucAutor, knjige, brojKnjiga, sizeof(KNJIGA), usporediAutor);

		if (trazeniAutor != NULL) {
			printf("\033[1;35;47m\nNaslov:\033[0m %s", trazeniAutor->naslov);
			printf("\033[1;35;47m\nAutor:\033[0m \033[1;35m %s \033[0m", trazeniAutor->autor);
			printf("\033[1;35;47m\nVrsta:\033[0m %s", trazeniAutor->vrsta);
			printf("\033[1;35;47m\nGodina:\033[0m %d\n", trazeniAutor->godina);
		}
		else {
			printf("\nNisam nasao trazenu knjigu.\n");
		}
		free(knjige);
		break;
	}
	case 3:
	{
		char kljucVrsta[30];
		printf("Unesite vrstu trazene knjige: ");
		scanf(" %29[^\n]", kljucVrsta);

		// Sortiranje knjiga prema vrsti
		qsort(knjige, brojKnjiga, sizeof(KNJIGA), usporediVrstu);

		KNJIGA *trazenaVrsta;
		trazenaVrsta = bsearch(kljucVrsta, knjige, brojKnjiga, sizeof(KNJIGA), usporediVrstu);

		if (trazenaVrsta != NULL) {
			printf("\033[1;35;47m\nNaslov:\033[0m %s", trazenaVrsta->naslov);
			printf("\033[1;35;47m\nAutor:\033[0m %s", trazenaVrsta->autor);
			printf("\033[1;35;47m\nVrsta:\033[0m \033[1;35m %s \033[0m", trazenaVrsta->vrsta);
			printf("\033[1;35;47m\nGodina:\033[0m %d\n", trazenaVrsta->godina);
		}
		else {
			printf("\nNisam nasao trazenu knjigu.\n");
		}
		free(knjige);
		break;
	}
	case 4:
	{
		int trazenaGodina;
		printf("Unesite godinu izdanja trazene knjige: ");
		scanf("%d", &trazenaGodina);

		// Sortiranje knjiga prema godini izdanja
		qsort(knjige, brojKnjiga, sizeof(KNJIGA), usporediGodinu);

		KNJIGA kljuc = { .godina = trazenaGodina };
		KNJIGA* rezultat = bsearch(&kljuc, knjige, brojKnjiga, sizeof(KNJIGA), usporediGodinu);

		if (rezultat != NULL) {
			printf("\033[1;35;47m\nNaslov:\033[0m %s", rezultat->naslov);
			printf("\033[1;35;47m\nAutor:\033[0m %s", rezultat->autor);
			printf("\033[1;35;47m\nVrsta:\033[0m %s", rezultat->vrsta);
			printf("\033[1;35;47m\nGodina:\033[0m \033[1;35m %d \033[0m\n", rezultat->godina);
		}
		else {
			printf("\nNisam nasao trazenu knjigu.\n");
		}
		free(knjige);
		break;
	}
	case 5:
		free(knjige);
		system("cls");
		return;
		break;
	default:
		system("cls");
		printf("\nKrivi unos, molim pokusajte ponovno.\n\n");
		free(knjige);
		break;
	}
}

int usporediNaslov(const void* a, const void* b) {
	const KNJIGA* knjigaA = (const KNJIGA*)a;
	const KNJIGA* knjigaB = (const KNJIGA*)b;
	return strcmp(knjigaA->naslov, knjigaB->naslov);
}

int usporediAutor(const void* a, const void* b) {
	const KNJIGA* knjigaA = (const KNJIGA*)a;
	const KNJIGA* knjigaB = (const KNJIGA*)b;
	return strcmp(knjigaA->autor, knjigaB->autor);
}

int usporediVrstu(const void* a, const void* b) {
	const KNJIGA* knjigaA = (const KNJIGA*)a;
	const KNJIGA* knjigaB = (const KNJIGA*)b;
	return strcmp(knjigaA->vrsta, knjigaB->vrsta);
}

int usporediGodinu(const void* a, const void* b) {
	const KNJIGA* knjigaA = (const KNJIGA*)a;
	const KNJIGA* knjigaB = (const KNJIGA*)b;
	return knjigaA->godina - knjigaB->godina;
}
*/
