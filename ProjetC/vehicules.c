#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "pietons.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"

void AFF_LISTE(Liste_V liste_v){
	VOITURE* tmp = liste_v;
	while(tmp != NULL)
	{
		printf("%d \n",tmp->posx);
		tmp = tmp->NXT;
	}
}

int empty(Liste_V liste_v){
	if(liste_v == NULL) return 1;
	else return 0;
}

VOITURE* INIT_V(char **MAT){
	VOITURE* V = malloc(sizeof(VOITURE));
	int r = rand()%5; /*marque et vitesse*/
	int p = rand()%8; /*position de départ*/

	switch(r){ /*initialisation de la marque et de la vitesse MAX*/
		case 0 : strcpy(V->marque, "Ferrari"); V->vitesse=2; break;
		case 1 : strcpy(V->marque, "Bugatti"); V->vitesse=2; break;
		case 2 : strcpy(V->marque, "Mini");    V->vitesse=1; break;
		case 3 : strcpy(V->marque, "Transit"); V->vitesse=1; break;
		case 4 : strcpy(V->marque, "Renault"); V->vitesse=1; break;
		default : break;
	}

	switch(p){ /*initialisation des positions de départ*/
		case 0 : if(MAT[6][0] != 'V') {
					V->posx = 1;   V->posy = 7; V->depart='o';  /*Haut gauche*/
				 }
				 else p=1;
				 break;
		case 1 : if(MAT[0][78] != 'V' && MAT[1][78] != 'V') {
					V->posx = 79;  V->posy = 1; V->depart='n';  /*Haut centre*/
				 }
				 else {V->posx = 159; V->posy = 53;V->depart='s';}
				 break;
		case 2 : if(MAT[4][203] != 'V') {
					V->posx = 203; V->posy = 5; V->depart='e';  /*Haut droit*/
				 }break;
		case 3 : if(MAT[27][0] != 'V') {
					V->posx = 1;   V->posy = 28;V->depart='o';  /*Milieu gauche*/
				 }
				 else {V->posx = 203; V->posy = 5; V->depart='e';}
				 break;
		case 4 : if(MAT[25][203] != 'V') {
					V->posx = 203; V->posy = 26;V->depart='e';  /*Milieu droite*/
				 }
				 else {V->posx = 204; V->posy = 5; V->depart='e';}
				 break;
		case 5 : if(MAT[52][82] != 'V') {
					V->posx = 83;  V->posy = 53;V->depart='s';  /*Bas gauche*/
				 }break;
		case 6 : if(MAT[52][129] != 'V') {
					V->posx = 130; V->posy = 53;V->depart='s';  /*Bas centre*/
				 }break;
		case 7 : if(MAT[52][158] != 'V') {
					V->posx = 159; V->posy = 53;V->depart='s';  /*Bas droite*/
				 }break;
		default : break;
	}

	/*on indique qu'il y a une voiture à cet endroit (anti collisions)*/
	//V->tempo=MAT[V->posy-1][V->posx-1]; //on sauvegarde le caractère sur lequel la voiture est, pour ensuite pouvoir le remettre
	V->attente = 0;
	V->tempo=' '; /*rien*/
	MAT[V->posy-1][V->posx-1]='V'; /*on met un V à l'endroit ou il y a une voiture*/

/////////////////	Ravitaillement
	p=rand()%2;
	if(p%2==0){
		V->ravitaillement='y'; /*besoins de ravitaillement*/
	}
	else V->ravitaillement='n'; /*pas besoins de ravitaillement*/
/////////////////

	V->lc='n'; /*last carrefour "none"*/
	V->lm='n'; /*last move "none"*/
	V->etat='a'; /*etat actif*/

return V;
}

Liste_V INSERTION_V(Liste_V liste_v, char **MAT){ //en tete
	/* Création du nouvel élément */
	VOITURE *new = malloc(sizeof(*new));
	new = INIT_V(MAT);
	/* On assigne l'adresse de l'element suivant au nouveau */
	new->NXT = liste_v;

	return new;
}

int content(Liste_V liste_v){
	VOITURE *tmp = liste_v;
	int nb=0;
	while(tmp != NULL){
		nb += 1;
		tmp = tmp->NXT;
	}
return nb;
}


void SUPPRESSION_V(Liste_V liste_v){
	VOITURE *tmp = liste_v;
	VOITURE *find = NULL;
	VOITURE *replace = NULL;
	while(tmp != NULL)
	{
		if(tmp->etat == 'i'){
			find=tmp;
			replace=tmp->NXT;
			tmp=tmp->NXT;
		}
		else tmp = tmp->NXT;
	}
	tmp=liste_v;
	if(find != NULL){
		while(tmp->NXT != find){tmp=tmp->NXT;}
		tmp->NXT=replace; /*L'elt qui pointait sur l'elt inactif pointe maintenant sur le suivant*/
		free(find);
	}
}

void sortie_carrefour(char **MAT_V, VOITURE *tmp, char direction) {
	MAT_V[tmp->posy-1][tmp->posx-1]=tmp->tempo;
	if(direction == 'd')
		tmp->posx += 1;
	else if(direction == 'g')
		tmp->posx -= 1;
	else if(direction == 'h')
		tmp->posy -= 1;
	else if(direction == 'b')
		tmp->posy += 1;
	tmp->tempo=MAT_V[tmp->posy-1][tmp->posx-1];
	MAT_V[tmp->posy-1][tmp->posx-1]='V';
	tmp->lc = tmp->lm;
	tmp->lm = direction;
}

void carrefour(VOITURE* tmp, char **MAT, char **MAT_V){
	int cpt=0; /*compteur de directionsd'un carrefour*/
	int choice;
	/*On compte le nombre de direction possible*/

    /*droite*/
	if(MAT[tmp->posy-1][tmp->posx]=='r' && tmp->lm != 'g' && tmp->lc != 'g' && MAT_V[tmp->posy-1][tmp->posx] != 'V')
		cpt += 1;
	if(MAT[tmp->posy-1][tmp->posx]=='D' && tmp->lm == 'd' && tmp->lc != 'g' && MAT_V[tmp->posy-1][tmp->posx] != 'V')
		cpt += 1;
	if(MAT[tmp->posy-1][tmp->posx]=='R' && tmp->ravitaillement == 'y' && tmp->lm != 'g' && tmp->lc != 'g' && MAT_V[tmp->posy-1][tmp->posx] != 'V')
		cpt = 1;

    /*gauche*/
	if(MAT[tmp->posy-1][tmp->posx-2]=='r' && tmp->lm != 'd' && tmp->lc != 'd' && MAT_V[tmp->posy-1][tmp->posx-2] != 'V')
		cpt += 2;
	if(MAT[tmp->posy-1][tmp->posx-2]=='G' && tmp->lm == 'g' && tmp->lc != 'd' && MAT_V[tmp->posy-1][tmp->posx-2] != 'V')
		cpt += 2;

    /*bas*/
	if(MAT[tmp->posy][tmp->posx-1]=='r' && tmp->lm != 'h' && tmp->lc != 'h' && MAT_V[tmp->posy][tmp->posx-1] != 'V')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='E' && tmp->lm != 'h' && MAT_V[tmp->posy][tmp->posx-1] != 'V')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='G' && tmp->lm == 'b' && tmp->lc != 'h' && MAT_V[tmp->posy][tmp->posx-1] != 'V')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='B' && (tmp->lm == 'b' || tmp->lm == 'd' || tmp->lm == 'g') && tmp->lc != 'h' && MAT_V[tmp->posy][tmp->posx-1] != 'V')
		cpt += 4;

    /*haut*/
	if(MAT[tmp->posy-2][tmp->posx-1]=='r' && tmp->lm != 'b' && tmp->lc != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='H' && (tmp->lm == 'h' || tmp->lm == 'g') && tmp->lc != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='E' && tmp->lm != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='D' && (tmp->lm == 'h' || tmp->lm == 'd') && tmp->lc != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='G' && (tmp->lm == 'h' || tmp->lm == 'g') && tmp->lc != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V')
		cpt += 8;

	/*on choisit la direction à prendre en fonction du carrefour*/

	switch(cpt){
	case 1:
		sortie_carrefour(MAT_V, tmp, 'd');
	break;
	case 2: sortie_carrefour(MAT_V, tmp, 'g');
	break;
	case 4: sortie_carrefour(MAT_V, tmp, 'b');
	break;
	case 5: if((choice=rand()%2)==1){
			sortie_carrefour(MAT_V, tmp, 'd');
		}
		else if(choice%2==0){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
	break;
	case 6: if((choice=rand()%2)==1){
			sortie_carrefour(MAT_V, tmp, 'g');
		}
		else if(choice%2==0){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
	break;
	case 7: if((choice=rand()%3)==1){
			sortie_carrefour(MAT_V, tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour(MAT_V, tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
	break;
	case 8: sortie_carrefour(MAT_V, tmp, 'h');
	break;
	case 9: if((choice=rand()%2)==1){
			sortie_carrefour(MAT_V, tmp, 'd');
		}
		else if(choice%2==0){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	case 10: if((choice=rand()%2)==1){
			sortie_carrefour(MAT_V, tmp, 'g');
		}
		else if(choice%2==0){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	case 11: if((choice=rand()%3)==1){
			sortie_carrefour(MAT_V, tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour(MAT_V, tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	case 12: if((choice=rand()%2)==1){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
		else if(choice%2==2){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	case 13: if((choice=rand()%3)==1){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
		else if(choice%3==2){
			sortie_carrefour(MAT_V, tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	case 14: if((choice=rand()%3)==1){
			sortie_carrefour(MAT_V, tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour(MAT_V, tmp, 'b');
		}
		else if(choice%3==0){
			sortie_carrefour(MAT_V, tmp, 'h');
		}
	break;
	default : break;//printf("booom et le compteur vaut %d \n",cpt);
	}
}

void deplacement_sens(char **MAT_V, VOITURE *tmp, char direction) {

	MAT_V[tmp->posy-1][tmp->posx-1]=tmp->tempo; //on remet le caractère supprimé par V avant de déplacer la voiture

	if(direction == 'h')
		tmp->posy -= 1;								//on deplace la voiture vers le haut
	else if(direction == 'b')
		tmp->posy += 1;								//on deplace la voiture vers le bas
	else if(direction == 'g')
		tmp->posx -= 1;								//on deplace la voiture vers la gauche
	else if(direction == 'd')
		tmp->posx += 1;								//on deplace la voiture vers la droite

	tmp->tempo=MAT_V[tmp->posy-1][tmp->posx-1]; //on sauvegarde le caractère sur lequel la voiture est, pour ensuite pouvoir le remettre
	MAT_V[tmp->posy-1][tmp->posx-1]='V';        //on signale une voiture à sa position
	tmp->lm = direction;						//on sauvegarde la dernière direction empreintée
}


void deplacement_voiture(Liste_V liste_v, VOITURE *tmp, char **MAT, char **MAT_V) {
	while(tmp != NULL){

		if((tmp->posx != 155 || tmp->posy != 53) && (tmp->posx != 79 || tmp->posy != 53) && (tmp->posx != 126 || tmp->posy != 53) && (tmp->posx != 1 || tmp->posy != 26) && (tmp->posx != 203 || tmp->posy != 28) && (tmp->posx != 83 || tmp->posy != 1) && (tmp->posx != 203 || tmp->posy != 7) && (tmp->posx != 1 || tmp->posy != 5))
		{
			if(tmp-> depart == 's' && tmp->lm == 'n' && MAT_V[tmp->posy-2][tmp->posx-1] != 'V'){
				deplacement_sens(MAT_V, tmp, 'h');
			}
			else if(tmp->depart == 'n' && tmp->lm == 'n' && MAT_V[tmp->posy][tmp->posx-1] != 'V'){
				deplacement_sens(MAT_V, tmp, 'b');
			}
			else if(tmp->depart == 'e' && tmp->lm == 'n' && MAT_V[tmp->posy-1][tmp->posx-2] != 'V'){
				deplacement_sens(MAT_V, tmp, 'g');
			}
			else if(tmp->depart == 'o' && tmp->lm == 'n' && MAT_V[tmp->posy-1][tmp->posx] != 'V'){
				deplacement_sens(MAT_V, tmp, 'd');
			}
////////////////////////////////
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'c') { /*lorsqu'on arrive à un carrefour*/
				carrefour(tmp, MAT, MAT_V); //test de la fonction carrefour
			}
////////////////////////////////
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'l' && tmp->ravitaillement == 'y') {
				if(MAT_V[tmp->posy-3][tmp->posx+1] != 'V') {
					deplacement_sens(MAT_V, tmp, 'h');
				}
				else if (MAT_V[tmp->posy+1][tmp->posx+1] != 'V') {
					deplacement_sens(MAT_V, tmp, 'b');
				}
				else {
					deplacement_sens(MAT_V, tmp, 'd');
				} 
			}
////////////////////////////////
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'e' && tmp->attente < 30) { //met l'etat à ravitaillement
				tmp->etat = 'r';
				ravitaillement(liste_v, tmp, MAT, MAT_V);
			}
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'e') { //remet l'etat à actif
				tmp->etat = 'a';
				tmp->attente = 0;
				tmp->ravitaillement = 'n';
				MAT_V[tmp->posy-1][tmp->posx-1] = ' ';
				couleur("40");
				printf("\33[%d;%dH   \n",tmp->posy, tmp->posx);
				couleur("0");
				tmp->posx +=1;
			}
////////////////////////////////
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'x' && rand()%5==0) {
					tmp->etat = 'x';
			}
			else if(tmp->etat == 'x' && tmp->attente < 30) {
				panne(liste_v, tmp, MAT, MAT_V);

			}
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'x') { //remet l'etat à actif
				tmp->etat = 'a';
				tmp->attente = 0;
				MAT_V[tmp->posy-1][tmp->posx-1] = ' ';
				couleur("40");
				printf("\33[%d;%dH  \n",tmp->posy, tmp->posx);
				couleur("0");
				deplacement_sens(MAT_V, tmp, tmp->lm);
			}
////////////////////////////////
			else if(DOK && tmp->lm != 'g' && MAT_V[tmp->posy-1][tmp->posx] == ' ' && MAT_V[tmp->posy-1][tmp->posx+1] != 'V'){ /*droite*/
				deplacement_sens(MAT_V, tmp, 'd');
			}
			else if(GOK && tmp->lm != 'd' && MAT_V[tmp->posy-1][tmp->posx-2] == ' ' && MAT_V[tmp->posy-1][tmp->posx-3] != 'V'){ /*gauche*/
				deplacement_sens(MAT_V, tmp, 'g');
			}
			else if(BOK && tmp->lm != 'h' && MAT_V[tmp->posy][tmp->posx-1] == ' '){ /*bas*/
				deplacement_sens(MAT_V, tmp, 'b');
			}
			else if(HOK && tmp->lm != 'b' && MAT_V[tmp->posy-2][tmp->posx-1] == ' '){ /*haut*/
				deplacement_sens(MAT_V, tmp, 'h');
			}

			tmp=tmp->NXT; /*passe à l'élément suivant de la liste*/
		}
		else
		{
			tmp->etat = 'i'; /*état inactif*/
			MAT_V[tmp->posy-1][tmp->posx-1]=tmp->tempo;
			tmp=tmp->NXT; /*passe à l'élément suivant de la liste*/
		}
		
	}
}



void ravitaillement(Liste_V liste_v, VOITURE *tmp, char **MAT, char **MAT_V) {
	tmp->attente += 1;
	couleur("40");
	if(strcmp(tmp->marque,"Renault")==0){
		printf("\33[%d;%dHP\n", tmp->posy, tmp->posx+2);
		couleur("38;5;118");
		printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Mini")==0){
		printf("\33[%d;%dHP\n", tmp->posy, tmp->posx+2);
		couleur("38;5;33");
		printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Ferrari")==0){
		printf("\33[%d;%dHP\n", tmp->posy, tmp->posx+2);
		couleur("38;5;196");
		printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Transit")==0){
		printf("\33[%d;%dHP\n", tmp->posy, tmp->posx+2);
		couleur("38;5;202");
		printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else {
		printf("\33[%d;%dH🚶\n", tmp->posy, tmp->posx+2);
		couleur("38;5;226");
		printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
		couleur("0");		
	}
}

void panne(Liste_V liste_v, VOITURE *tmp, char **MAT, char **MAT_V) {
	tmp->attente +=1;
	couleur("40");
	if(tmp->attente%2 == 0) {
		if(strcmp(tmp->marque,"Renault")==0){
		couleur("38;5;118");
		printf("\33[%d;%dHv\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Mini")==0){
		couleur("38;5;33");
		printf("\33[%d;%dHv\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Ferrari")==0){
		couleur("38;5;196");
		printf("\33[%d;%dHv\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else if(strcmp(tmp->marque,"Transit")==0){
		couleur("38;5;202");
		printf("\33[%d;%dHv\n", tmp->posy, tmp->posx);
		couleur("0");
	}
	else {
		couleur("38;5;226");
		printf("\33[%d;%dHv\n", tmp->posy, tmp->posx);
		couleur("0");		
	}
	}
	else if(tmp->attente%2 == 1) {
		printf("\33[%d;%dHc\n", tmp->posy, tmp->posx);
	}
}
