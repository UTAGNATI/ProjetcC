#include "librairies.h"
#include "fonctions.h"
#include "menu.h"
#include "affichage_carte.h"
#include "launchers.h"

void mode_fluide() {
	printf("\033[2J"); /*clear screen*/
	affichage_txt();
	launcher_fluide();
	printf("\33[54;1H");
}

void mode_danger() {
	printf("\033[2J"); /*clear screen*/
	affichage_txt_danger();
	launcher_danger();
	printf("\33[54;1H");
}

void affichage_menu() {
    //printf("\033[2J"); /*clear screen*/
	FILE *fic;
	char l;
	printf("\33[1;1H");
	fic=fopen("menu.txt", "r" );
	while((l=fgetc(fic))!=EOF){
		if(l==' ') {
			couleur("48;5;16");
			printf(" ");
			couleur("0");
		}
		else if(l=='	') {
			couleur("48;5;16");
			printf("	");
			couleur("0");
		}
		else if(l=='m') {
			couleur("48;5;27");
			printf("█");
			couleur("0");
		}
		else if(l=='n') {
			couleur("48;5;27");
			printf("█");
			couleur("0");
		}
		else if(l=='u') {
			couleur("48;5;27");
			printf("█");
			couleur("0");
		}

		else if(l=='4') {
			couleur("48;5;27");
			printf("╔");
			couleur("0");
		}
		else if(l=='7') {
			couleur("48;5;27");
			printf("║");
			couleur("0");
		}
		else if(l=='8') {
			couleur("48;5;27");
			printf("═");
			couleur("0");
		}

		else if(l=='1') {
			couleur("48;5;27");
			printf("╚");
			couleur("0");
		}
		else if(l=='2') {
			couleur("48;5;27");
			printf("╝");
			couleur("0");
		}
		else if(l=='5') {
			couleur("48;5;27");
			printf("╗");
			couleur("0");
		}

		else if(l=='X') {
			couleur("48;5;16");
			printf("1");
			couleur("0");
		}
		else {
			couleur("48;5;16");
			printf("%c",l);
			couleur("0");
		}

		
	}
}

void deplacement_curseur(char entree) {
        CURSEUR curseur ;
	curseur.posx = 61;
	curseur.posy = 19;
	system("play -q musique.mp3 repeat 10 &"); //lance le fond musical
	printf("\33[1;1H\n");
	affichage_menu();
	while(entree != 'q') {
	        couleur("31");
	        couleur("48;5;16");
	        printf("\33[%d;%dH=>w \n",curseur.posy, curseur.posx);
	        printf("\33[54;1H\n");
	        couleur("0");
	        
	        entree = key_pressed();
                if(entree == 'z') {
                	printf("\33[1;1H\n");
	        		affichage_menu();
                    if(curseur.posy > 19) {
                    	couleur("48;5;16");
                        printf("\33[%d;%dH   \n",curseur.posy, curseur.posx);
                        couleur("0");
                        curseur.posy -= 9;
                    }
                }
                else if(entree == 's') {
                	printf("\33[1;1H\n");
	        		affichage_menu();
                    if(curseur.posy < 28) {
                    	couleur("48;5;16");
                        printf("\33[%d;%dH   \n",curseur.posy, curseur.posx);
                        couleur("0");
                        curseur.posy += 9;
                    }
                }
                else if(entree == ' ' && curseur.posy == 19) {
                	//system("killall play"); //permet de stopper le son à la fermeture du pregramme
                    mode_fluide();
                    printf("\033[2J"); /*clear screen*/
                    affichage_menu();
		    //system("play -q musique.mp3 repeat 10 &"); //lance le fond musical
                }
                else if(entree == ' ' && curseur.posy == 28) {
                	//system("killall play"); //permet de stopper le son à la fermeture du pregramme
                    mode_danger();
                    printf("\033[2J"); /*clear screen*/
                    affichage_menu();
 		    //system("play -q musique.mp3 repeat 10 &"); //lance le fond musical
                }
        }
}

void menu() {
	char entree = 'n';
	
	affichage_menu();
	
	deplacement_curseur(entree);

	//system("killall play"); //permet de stopper le son à la fermeture du pregramme
}


