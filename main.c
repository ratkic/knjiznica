#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

int main() {
	int izbor = 0;
	
	//8
	do{

		printf("\033[1;3;37;45m               KNJIZNICA                      \n");
		printf("\033[0m");
		printf("----------------------------------------------\n");
		printf("\033[1;35;47m");
		printf("                                              \n");
		printf("            1) Dodaj knjigu                   \n");
		printf("            2) Ispisi knjige                  \n");
		printf("            3) Pretrazivanje                  \n");
		printf("            4) Sortiraj knjige po autoru      \n");
		printf("            5) Sortiraj knjige po naslovu     \n");
		printf("            6) Izbrisi knjigu                 \n");
		printf("            7) Izbrisi datoteku               \n");
		printf("            8) Izlaz                          \n");
		printf("                                              \n");
		printf("\033[0m");
		printf("----------------------------------------------\n");
		
		printf("\n\nUnesi broj: ");
		scanf("%d", &izbor);

		izbornik(izbor);


	} while (izbor != 9);
	

	return 0;
}