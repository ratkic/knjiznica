#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

int main() {
	int opcija;

	do{

		printf("\033[1;37;45m               KNJIZNICA                      \n");
		printf("\033[0m");
		printf("----------------------------------------------\n");
		//printf("\033[1;35m");
		printf("\033[1;35;47m");
		printf("                                              \n");
		printf("            1) Dodaj knjigu                   \n");
		printf("            2) Ispisi knjige                  \n");
		printf("            3) Pretrazi knjige                \n");
		printf("            4) Pretrazi autora                \n");
		printf("            5) Sortiraj knjige po naslovu     \n");
		printf("            6) Sortiraj knjige po autoru      \n");
		printf("            7) Izbrisi knjigu                 \n");
		printf("            8) Izbrisi datoteku               \n");
		printf("            9) Izlaz                          \n");
		printf("                                              \n");
		printf("\033[0m");
		printf("----------------------------------------------\n");
		
		printf("\n\nUnesi broj: ");
		scanf("%d", &opcija);


		izbornik(opcija);


	} while (opcija != 9);
	
	//dodajKnjigu();
	return 0;
}