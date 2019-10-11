#include "librairies.h"
#include "fonctions.h"
#include "menu.h"
#include "affichage_carte.h"


void affichage_txt(){
	FILE *fic;
	char l;
	printf("\33[1;1H");
	fic=fopen("Carte.txt", "r" );
	while((l=fgetc(fic))!=EOF){
		if(l=='x' || l=='w'){
			couleur("44");
			printf(" ");
			couleur("0");
		}
		else if(l=='a'){
			couleur("32"); 
			printf(" ");
			couleur("0");
		}
		else if(l=='y'){
			couleur("44");
			printf(" ");
			couleur("0");		
		} /*plantes pour jardin*/
		else if(l=='Z'){
			couleur("32");
			printf(" ");
			couleur("0");
		}
		else if(l=='X'){
			couleur("31");
			printf(" ");
			couleur("0");
		}
		else if(l=='Y'){
			couleur("33");
			printf(" ");
			couleur("0");
		}
		else if(l=='W'){
			couleur("36");
			printf(" ");
			couleur("0");
		}
		else if(l=='C'){
			couleur("31");
			printf(" ");
			couleur("0");
		} 
		else if(l=='V'){
			couleur("44");
			couleur("36");
			printf(" ");
			couleur("0");
		}
		else if(l=='B'){	
			printf(" ");
		}
		else if(l=='O'){	
			printf(" ");
		}
		else if(l=='U'){
			couleur("40");
			couleur("34");
			printf(" ");
			couleur("0");
		}
		else if(l=='z'){ /*feuilles rouges chateau*/
			couleur("31");
			printf(" ");
			couleur("0");
		}
		else if(l=='I'){
			couleur("40");
			printf("═");
			couleur("0");
		}
		else if(l=='R'){
			couleur("40");
			printf(" ");
			couleur("0");
		}
		else if(l=='Q'){
			printf(" ");
		}
		else if(l=='H'){
			printf(" ");
		}
		else if(l=='E'){
			couleur("40");
			printf(" "); 
			couleur("0");
		}
		else if(l=='J'){
			printf(" ");
		}
		else if(l=='S'){
			couleur("40");
			printf("/");
			couleur("0");
		}
		else if(l=='L'){
			couleur("40");
			printf("|");
			couleur("0");
		}
		else if(l=='K'){
			couleur("40");
			printf("─");
			couleur("0");
		}
		else if(l=='T'){
			couleur("40");
			printf("-");
			couleur("0");
		}
		else if(l=='P'){
			couleur("40");
			printf(":");
			couleur("0");
		}
		else if(l=='A'){
			couleur("32");
			printf(" ");
			couleur("0");
		}

		else
		printf("%c",l);
	}  
	fclose(fic);
	
	couleur("40");
	couleur("1");
	printf("\33[31;170HTOTAL 24H/7J\n");
	couleur("0");

	couleur("1");
	printf("\33[38;69HFOOD\n");
	couleur("0");

	couleur("1");
	printf("\33[34;27HESIEA\n");
	couleur("0");
	
}

void affichage_txt_danger(){
	FILE *fic;
	char l;
	printf("\33[1;1H");
	fic=fopen("Carte_danger.txt", "r" );
	while((l=fgetc(fic))!=EOF){
		if(l=='x' || l=='w'){
			couleur("44");
			printf(" ");
			couleur("0");
		}
		else if(l=='a'){
			couleur("32");//🌿
			printf(" ");
			couleur("0");
		}
		else if(l=='y'){
			couleur("44");
			printf(" ");
			couleur("0");		
		} /*plantes pour jardin*/
		else if(l=='Z'){
			couleur("32");
			printf(" ");//🎋
			couleur("0");
		}
		else if(l=='X'){
			couleur("31");
			printf(" ");
			couleur("0");
		}
		else if(l=='Y'){
			couleur("33");
			printf(" ");//🕊🏍🚲🚗🚘🚑🚚🚍🚒🐕🏗💀🚴🐿⛴🚉🚝🚈🚢🐦🚶⛽🏪🚕🚖🚊🚜🚙🚔🚓🚋🚌 
			couleur("0");
		}
		else if(l=='W'){
			couleur("36");
			printf(" ");
			couleur("0");
		}
		else if(l=='C'){
			couleur("31");
			printf(" ");
			couleur("0");
		} 
		else if(l=='V'){
			couleur("44");
			couleur("36");
			printf(" ");
			couleur("0");
		}
		else if(l=='B'){	
			printf(" ");
		}
		else if(l=='O'){	
			printf(" ");
		}
		else if(l=='U'){
			couleur("40");
			couleur("34");
			printf("🅿");
			couleur("0");
		}
		else if(l=='z'){ /*feuilles rouges chateau*/
			couleur("31");
			printf(" ");
			couleur("0");
		}
		else if(l=='I'){
			couleur("40");
			printf("═");
			couleur("0");
		}
		else if(l=='R'){
			couleur("40");
			printf(" ");
			couleur("0");
		}
		else if(l=='Q'){
			printf(" ");
		}
		else if(l=='H'){
			printf(" ");
		}
		else if(l=='E'){
			couleur("40");
			printf(" "); 
			couleur("0");
		}
		else if(l=='J'){
			printf(" ");
		}
		else if(l=='S'){
			couleur("40");
			printf("/");
			couleur("0");
		}
		else if(l=='L'){
			couleur("40");
			printf("|");
			couleur("0");
		}
		else if(l=='K'){
			couleur("40");
			printf("─");
			couleur("0");
		}
		else if(l=='T'){
			couleur("40");
			printf("-");
			couleur("0");
		}
		else if(l=='P'){
			couleur("40");
			printf(":");
			couleur("0");
		}
		else if(l=='A'){
			couleur("32");
			printf("🌴");
			couleur("0");
		}

		//affichage du stade
		else if(l=='h'){
			couleur("42");
			printf(" ");
			couleur("0");
		}
		else if(l=='g'){
			couleur("42");
			printf("_");
			couleur("0");
		}
		else if(l=='i'){
			couleur("42");
			printf("/");
			couleur("0");
		}
		else if(l=='t'){
			couleur("42");
			printf("-");
			couleur("0");
		}
		else if(l=='j'){
			couleur("42");
			printf("|");
			couleur("0");
		}
		else if(l=='l'){
			couleur("42");
			printf("'");
			couleur("0");
		}
		else if(l=='`'){
			couleur("42");
			printf("`");
			couleur("0");
		}
		else if(l=='.'){
			couleur("42");
			printf(".");
			couleur("0");
		}
		else if(l==','){
			couleur("42");
			printf(",");
			couleur("0");
		}
		else if(l=='('){
			couleur("42");
			printf("(");
			couleur("0");
		}
		else if(l==':'){
			couleur("42");
			printf(":");
			couleur("0");
		}
		

		else
		printf("%c",l);
	}  
	fclose(fic);
	
	couleur("40");
	couleur("1");
	printf("\33[31;170HTOTAL 24H/7J\n");
	couleur("0");

	couleur("31");
	couleur("48;5;21"); 
	couleur("1");
	printf("\33[31;30HPSG\n");
	couleur("0");

	couleur("38;5;14");
	couleur("48;5;15"); 
	couleur("1");
	printf("\33[31;49HOM\n");
	couleur("0");

	printf("\33[31;38H3 - 0\n");
	
}


void AFFICHAGE_PERM(int NB_L,int NB_C, char **MAT){
	int nbl,nbc;
	for(nbl=0;nbl<NB_L;nbl++){
		for(nbc=0;nbc<NB_C;nbc++){
			if(*(*(MAT+nbl)+nbc)=='P') {
				couleur("40");
				printf("\33[%d;%dH:\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='T') {
				couleur("40");
				printf("\33[%d;%dH-\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='K'){
				couleur("40");
				printf("\33[%d;%dH─\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='S'){
				couleur("40");
				printf("\33[%d;%dH/\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='I'){
				couleur("40");
				printf("\33[%d;%dH═\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='L'){
				couleur("40");
				printf("\33[%d;%dH|\n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='R'){
				couleur("40");
				printf("\33[%d;%dH \n",nbl+1,nbc+1);
				couleur("0");
			}
			else if(*(*(MAT+nbl)+nbc)=='N'){
				printf("\33[%d;%dH \n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='t'){
				printf("\33[%d;%dH╦\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='e'){
				printf("\33[%d;%dH╩\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='x'){
				printf("\33[%d;%dH╝\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='w'){
				printf("\33[%d;%dH╚\n",nbl+1,nbc+1);
			}

			else if(*(*(MAT+nbl)+nbc)=='l'){
				printf("\33[%d;%dH╗\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='r'){
				printf("\33[%d;%dH╔\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='j') {
				printf("\33[%d;%dH┌\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='i') {
				printf("\33[%d;%dH─\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='k') {
				printf("\33[%d;%dH┐\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='M') {
				printf("\33[%d;%dH│\n",nbl+1,nbc+1);
			}
			else if(*(*(MAT+nbl)+nbc)=='U') {
				couleur("48;5;0");
				couleur("38;5;33");
				printf("\33[%d;%dH🅿\n",nbl+1,nbc+1);
				couleur("0");
			}
			//printf("\33[54;1H\n");
		}
	}
}


/* permet un affichage alterné en fonction de la variable c pour donner une impression de mouvement de l'eau */
void animation_eau(int c){
	if(c%2==0) {
		if(c%3==0){
			
		}
		else if(c%3==1) {

		}
		else if(c%3==2) {

		}
	}
	else if(c%2==1) {
		if(c%3==0){

		}
		else if(c%3==1) {

		}
		else if(c%3==2) {
			
		}
	}
}


