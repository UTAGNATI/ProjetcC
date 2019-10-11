#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "pietons.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"

void AFF_LISTE_P(Liste_P liste_p){
	PIETON* tmp = liste_p;
	while(tmp != NULL)
	{
		printf("%d \n",tmp->posx);
		tmp = tmp->NXT;
	}
}

int empty_P(Liste_P liste_p){
	if(liste_p == NULL) return 1;
	else return 0;
}


PIETON* INIT_P(char **MAT) {
	PIETON* P = malloc(sizeof(PIETON));
	int r = rand()%10; //choix de position de départ
	
	switch(r) {
		case 0: P->posx=203; P->posy=25; P->depart='e';
		break;
		case 1: P->posx=203; P->posy=29; P->depart='e';
		break;
		case 2: P->posx=203; P->posy=4;  P->depart='e';
		break;
		case 3: P->posx=203; P->posy=16; P->depart='e';
		break;
		case 4: P->posx=1; P->posy=25;   P->depart='o';
		break;
		case 5: P->posx=1; P->posy=29;   P->depart='o';
		break;
		case 6: P->posx=1; P->posy=4;    P->depart='o';
		break;
		case 7: P->posx=1; P->posy=16;   P->depart='o';
		break;
		case 8: P->posx=95; P->posy=53;   P->depart='s';
		break;
		case 9: P->posx=113; P->posy=53;   P->depart='s';
		break;
		default : break;
	}

	P->lm='n';
	P->tempo=' ';
	P->etat='a'; /*etat actif*/
	
return P;
}

Liste_P INSERTION_P(Liste_P liste_p, char **MAT){ //en tete
	/* Création du nouvel élément */
	PIETON *new = malloc(sizeof(*new));
	new = INIT_P(MAT);
	/* On assigne l'adresse de l'element suivant au nouveau */
	new->NXT = liste_p;

	return new;
}

int content_P(Liste_P liste_p){
	PIETON *tmp = liste_p;
	int nb=0;
	while(tmp != NULL){
		nb += 1;
		tmp = tmp->NXT;
	}
return nb;
}


void SUPPRESSION_P(Liste_P liste_p){
	PIETON *tmp = liste_p;
	PIETON *find = NULL;
	PIETON *replace = NULL;
	while(tmp != NULL)
	{
		if(tmp->etat == 'i'){
			find=tmp;
			replace=tmp->NXT;
			tmp=tmp->NXT;
		}
		else tmp = tmp->NXT;
	}
	tmp=liste_p;
	if(find != NULL){
		while(tmp->NXT != find){tmp=tmp->NXT;}
		tmp->NXT=replace; /*L'elt qui pointait sur l'elt inactif pointe maintenant sur le suivant*/
		free(find);
	}
}

void continu(Liste_P liste_p, PIETON *tmp) {
	if(tmp->lm == 'h')
		tmp->posy -= 1;
	else if(tmp->lm == 'b')
		tmp->posy += 1;
	else if(tmp->lm == 'g')
		tmp->posx -= 1;
	else if(tmp->lm == 'd')
		tmp->posx += 1;
}

void sortie_carrefour_pieton(PIETON *tmp, char direction) {
	if(direction == 'd')
		tmp->posx += 1;
	else if(direction == 'g')
		tmp->posx -= 1;
	else if(direction == 'h')
		tmp->posy -= 1;
	else if(direction == 'b')
		tmp->posy += 1;
	tmp->lm = direction;
}

void carrefour_pietons(Liste_P liste_p, PIETON *tmp, char **MAT) {
	int cpt=0; /*compteur de directions d'un carrefour*/
	int choice;
	/*droite*/
	if(MAT[tmp->posy-1][tmp->posx]=='p' && tmp->lm != 'g')
		cpt += 1;
	if(MAT[tmp->posy-1][tmp->posx]=='D' && tmp->lm == 'd')
		cpt += 1;
	if(MAT[tmp->posy-1][tmp->posx]=='H' && tmp->lm == 'h')
		cpt +=1;

    /*gauche*/
	if(MAT[tmp->posy-1][tmp->posx-2]=='p' && tmp->lm != 'd')
		cpt += 2;
	if(MAT[tmp->posy-1][tmp->posx-2]=='G' && tmp->lm == 'g')
		cpt += 2;

    /*bas*/
	if(MAT[tmp->posy][tmp->posx-1]=='p' && tmp->lm != 'h')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='E' && tmp->lm != 'h')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='G' && tmp->lm == 'b')
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='B' && (tmp->lm == 'b' || tmp->lm == 'd' || tmp->lm == 'g'))
		cpt += 4;

    /*haut*/
	if(MAT[tmp->posy-2][tmp->posx-1]=='p' && tmp->lm != 'b')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='H' && (tmp->lm == 'h' || tmp->lm == 'g'))
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='E' && tmp->lm != 'b')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='D' && (tmp->lm == 'h' || tmp->lm == 'd'))
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='G' && (tmp->lm == 'h' || tmp->lm == 'g'))
		cpt += 8;

	switch(cpt){
	case 1:
		sortie_carrefour_pieton(tmp, 'd');
	break;
	case 2: sortie_carrefour_pieton(tmp, 'g');
	break;
	case 3: if((choice=rand()%2)==1) {
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%2==0) {
			sortie_carrefour_pieton(tmp, 'd');
		}
	break;
	case 4: sortie_carrefour_pieton(tmp, 'b');
	break;
	case 5: if((choice=rand()%2)==1){
			sortie_carrefour_pieton(tmp, 'd');
		}
		else if(choice%2==0){
			sortie_carrefour_pieton(tmp, 'b');
		}
	break;
	case 6: if((choice=rand()%2)==1){
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%2==0){
			sortie_carrefour_pieton(tmp, 'b');
		}
	break;
	case 7: if((choice=rand()%3)==1){
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour_pieton(tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour_pieton(tmp, 'b');
		}
	break;
	case 8: sortie_carrefour_pieton(tmp, 'h');
	break;
	case 9: if((choice=rand()%2)==1){
			sortie_carrefour_pieton(tmp, 'd');
		}
		else if(choice%2==0){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	case 10: if((choice=rand()%2)==1){
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%2==0){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	case 11: if((choice=rand()%3)==1){
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour_pieton(tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	case 12: if((choice=rand()%2)==1){
			sortie_carrefour_pieton(tmp, 'b');
		}
		else if(choice%2==2){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	case 13: if((choice=rand()%3)==1){
			sortie_carrefour_pieton(tmp, 'b');
		}
		else if(choice%3==2){
			sortie_carrefour_pieton(tmp, 'd');
		}
		else if(choice%3==0){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	case 14: if((choice=rand()%3)==1){
			sortie_carrefour_pieton(tmp, 'g');
		}
		else if(choice%3==2){
			sortie_carrefour_pieton(tmp, 'b');
		}
		else if(choice%3==0){
			sortie_carrefour_pieton(tmp, 'h');
		}
	break;
	default : break;
	}
}


void deplacement_pietons(Liste_P liste_p, PIETON *tmp, char **MAT, char **MAT_P) {
	while(tmp != NULL) {
		if(Bords_Pietons_S && Bords_Pietons_N && Bords_Pietons_D && Bords_Pietons_G) {
			if(MAT[tmp->posy-1][tmp->posx-1]=='m') {
				if(tmp->etat == 'a') {
					tmp->etat = 'o';
				}
				else if(tmp->etat == 'o') {
					tmp->etat = 'a';
				}
			}
			
			if(tmp->depart == 's' && tmp->lm == 'n'){      //haut
				tmp->posy -= 1;
				tmp->lm = 'h';
			}
			else if(tmp->depart == 'n' && tmp->lm == 'n'){ //bas
				tmp->posy += 1;
				tmp->lm = 'b';
			}
			else if(tmp->depart == 'e' && tmp->lm == 'n'){ //gauche
				tmp->posx -= 1;
				tmp->lm = 'g';
			}
			else if(tmp->depart == 'o' && tmp->lm == 'n'){ //droite
				tmp->posx += 1;
				tmp->lm = 'd';
			}

//////////////////////////////////////////////////////////////////////////
			else if(tmp->posy==16 && tmp->lm == 'd') {
				tmp->posx += 1;
				tmp->lm = 'd'; 
			}
			else if(tmp->posy==16 && tmp->lm == 'g') {
				tmp->posx -= 1;
				tmp->lm = 'g';
			}
///////////////////////////////////////////////////////////////////////////

			else if(MAT[tmp->posy-1][tmp->posx-1]=='c') {
				continu(liste_p,tmp);
			}

			else if(MAT[tmp->posy-1][tmp->posx-1]=='f') {
				carrefour_pietons(liste_p,tmp, MAT);
			}

			
			else if(PDOK && tmp->lm != 'g'){ /*droite*/
				tmp->posx += 1;
				tmp->lm = 'd'; 
			}
			else if(PGOK && tmp->lm != 'd'){ /*gauche*/
				tmp->posx -= 1;
				tmp->lm = 'g';
			}
			else if(PBOK && tmp->lm != 'h'){ /*bas*/
				tmp->posy += 1;
				tmp->lm = 'b';
			}
			else if(PHOK && tmp->lm != 'b'){ /*haut*/
				tmp->posy -= 1;
				tmp->lm = 'h';
			}
			else {}

			tmp=tmp->NXT;
		}
		else {
			tmp->etat = 'i';
			MAT_P[tmp->posy-1][tmp->posx-1]=tmp->tempo;
			tmp=tmp->NXT;
		}

	}
}