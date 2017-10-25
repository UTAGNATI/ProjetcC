#include "librairies.h"
#include "fonctions.h"
#include "menu.h"
#include "affichage_carte.h"


void affichage_txt(){
	int i;
	FILE *fic;
	char l;
	printf("\33[0;0H");
	fic=fopen("Carte.txt", "r" );
	while((l=fgetc(fic))!=EOF){
		if(l=='x' || l=='w'){
			couleur("44");
			printf(" ");
			couleur("0");
		}
		else if(l=='a'){
			couleur("32");//🌿
			printf("🌿");
			couleur("0");
		}
		else if(l=='y'){
			couleur("44");
			printf("╬");
			couleur("0");		
		} /*plantes pour jardin*/
		else if(l=='Z'){
			couleur("32");
			printf("💐");//🎋
			couleur("0");
		}
		else if(l=='X'){
			couleur("31");
			printf("💐");
			couleur("0");
		}
		else if(l=='Y'){
			couleur("33");
			printf("🌻");//🕊🏍🚲🚗🚘🚑🚚🚍🚒🐕🏗💀🚴🐿⛴🚉🚝🚈🚢🐦🚶⛽🏪🚕🚖🚊🚜🚙🚔🚓🚋🚌   feu 🚦
			couleur("0");
		}
		else if(l=='W'){
			couleur("36");
			printf("🌻");
			couleur("0");
		}
		else if(l=='C'){
			couleur("37");
			printf("🌻");
			couleur("0");
		} /*feuilles rouges chateau*/
		else if(l=='z'){
			couleur("31");
			printf("🍁");
			couleur("0");
		}
		else if(l=='R'){
			couleur("40");
			printf(" ");
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
		else if(l==':'){
			couleur("40");
			printf(":");
			couleur("0");
		}
		else if(l=='>'){
			couleur("40");
			printf(">");
			couleur("0");
		}
		else if(l=='<'){
			couleur("40");
			printf("<");
			couleur("0");
		}

		else
		printf("%c",l);
	}  
	fclose(fic);

        couleur("32");
	for(i=0;i<205;i++){
		if(i==75)
			i=88;
		if(i%2==1)
			printf("\33[15;%dH🌴",i);
	}
	couleur("0");
}

void deplacement_tram(int j){
  	printf("\33[12;%dH🚋🚋🚋🚋🚋🚋🚋\n",(j%210));        //affichage du tram ouest vers est
	printf("\33[10;%dH🚋🚋🚋🚋🚋🚋🚋\n",175-(j%210));    //affichage du tram est vers ouest
}

void effacement_tram(int j){
	printf("\33[10;%dH             \n",175-(j%210)); //effacement du tram est vers ouest
	printf("\33[12;%dH             \n",j%210);	  //effacement du tram ouest vers est 

}

/* permet un affichage alterné en fonction de la variable c pour donner une impression de mouvement de l'eau */
void animation_eau(int c){
	int i,j; //correspond à la ligne et i correspond à la colonne
	for(j=0;j<36;j++){
		couleur("44");
		if(j<6){//ici on s'occupe de la grosse partie horizontale
				printf("\33[%d;0H                                                                          ",j+18);
				printf("\33[%d;88H                                                                                                                     ",j+18);
			if(c%4==0){ //c fait alterner les lignes
				for(i=0;i<204;i++){
					if(i==74){
						i=87;
					}			
					else if(i%4==0){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
					}
				}
			}
			else if(c%4==2){
				for(i=0;i<204;i++){
					if(i==74){
						i=87;
					}
					else if(i%4==0){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i);
						}
					}
				}
			}
		}
		else if(j>=3 && j<14){//ici la partie verticale du haut
			printf("\33[%d;135H                \n",j+18);
			if(c%4==0){
				for(i=135;i<151;i++){
					if(i%4==1){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i-1);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
					}					
				}
			}
			else if(c%4==2){
				for(i=135;i<151;i++){
					if(i%4==1){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i-1);
						}
					}
				}
			}
		}
		else if(j>=21){//ici la partie verticale du bas
			printf("\33[%d;135H                \n",j+18);
			if(c%4==0){
				for(i=135;i<151;i++){
					if(i%4==1){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i-1);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
					}					
				}
			}
			else if(c%4==2){
				for(i=135;i<151;i++){
					if(i%4==1){
						if(j%2==0){
							printf("\33[%d;%dH♒️\n",j+18,i+1);
						}
						else if(j%2==1){
							printf("\33[%d;%dH♒️\n",j+18,i-1);
						}
					}
				}
			}
		}
		couleur("0");	
	}
}


/*il faut gérer la condition d'arret*/
void coordination(int *c){
	int k;
	affichage_txt();
	deplacement_tram(c);
	animation_eau(c);
	//wait(8);
	//effacement_tram(&c);
	c+=1;
}
