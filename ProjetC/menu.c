#include "librairies.h"
#include "fonctions.h"
#include "menu.h"
#include "affichage_carte.h"

void mode_fluide(){
int c=0;
	printf("\033[2J"); /*clear screen*/
	affichage_txt();
	coordination(&c);	
	printf("\33[54;0H");
}

void mode_danger(){
	printf("Le mode danger n'existe pas encore!! \n");
}



void menu(){
	int entree;

	printf("\033[2J"); /*clear screen*/
	FILE *fic;
	char l;
	printf("\33[0;0H");
	fic=fopen("menu.txt", "r" );
	while((l=fgetc(fic))!=EOF){
		printf("%c",l);
	}

	scanf("%d",&entree);	
	switch(entree){
		case 1 : mode_fluide();break;
		case 2 : mode_danger();break;
		//case 3 : printf("%c \n", key_pressed());break;
		default : printf("Ce mode n'existe pas \n");
	}
}


