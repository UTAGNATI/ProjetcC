#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"


TRAIN* INIT_TRAIN(int posx, int posy, int nb, char direction){
	TRAIN* T = malloc(sizeof(TRAIN));
	T->posx=posx;
	T->posy=posy;
	T->direction = direction;
	T->nb = nb;
	T->etat = 'a';
	T->attente = 0;
	return T;
}

Liste_T INSERTION_T(Liste_T liste_t, int posx, int nb, int posy, char direction){
	/* Création du nouvel élément */
	TRAIN *new = malloc(sizeof(*new));
	new = INIT_TRAIN(posx, posy, nb, direction);
	/* On assigne l'adresse de l'element suivant au nouveau */
	new->NXT = liste_t;

	return new;
} 

Liste_T Creation_tram(){
	Liste_T liste_t = NULL;

	liste_t = INSERTION_T(liste_t, 1, 1, 12, 'e');
	liste_t = INSERTION_T(liste_t, 1, 204, 10, 'o');


	return liste_t;
}

void deplacement_tram(Liste_T liste_t, TRAIN *tmp, char **MAT, char **MAT_V) {
	while(tmp != NULL) {
		//Met une barrière lors du passage du tramway
		if(tmp->posx > 70 && tmp->posx < 92 && tmp->direction == 'e') {
			MAT_V[7][78]='V';
			MAT_V[14][82]='V';
			couleur("40");
			printf("\33[8;78H-------\n");
			printf("\33[14;78H-------\n");
			couleur("0");
		}
		else if(tmp->posx > 70 && tmp->posx < 92 && tmp->direction == 'o') {
			MAT_V[7][78]='V';
			MAT_V[14][82]='V';
			couleur("40");
			printf("\33[8;78H-------\n");
			printf("\33[14;78H-------\n");
			couleur("0");
		}
		else if ((tmp->direction == 'e' && (tmp->posx <= 70 || tmp->posx >= 92)) || (tmp->direction == 'o' && (tmp->posx <= 70 || tmp->posx >= 92))) {
			MAT_V[7][78]=' ';
			MAT_V[14][82]=' ';
			couleur("40");
			printf("\33[8;78H   |   \n");
			printf("\33[14;78H   |   \n");
			couleur("0");
		}

		if(MAT[tmp->posy-1][tmp->posx-1] == 'T' && tmp->attente < 50){ //si le tram est à un arret et qu'il n'a pas assez attendu, alors il continu d'attendre
			tmp->etat = 's';
		}
		else {
			tmp->attente = 0;
			tmp->etat = 'a'; //sinon, repart
		}
		if((tmp->posy != 10 || tmp->posx != -20) && (tmp->posy != 12 || tmp->posx != 220)) {
			if(tmp->etat == 'a'){    //bouge si actif
				if(tmp->direction == 'o' && MAT_V[tmp->posy-1][tmp->posx-2] != 'V' && MAT_V[tmp->posy-1][tmp->posx-2] != 'T') { /*Gauche*/
					tmp->posx -= 1;
				}
				else if(tmp->direction == 'e' && MAT_V[tmp->posy-1][tmp->posx+1] != 'V' && MAT_V[tmp->posy-1][tmp->posx+1] != 'T') { /*Droite*/
					tmp->posx += 1;
				}	
				tmp=tmp->NXT;
			}
			else if(tmp->etat == 's'){ //ne bouge pas si tu es à l'arret de tram
				tmp->attente += 1;
				tmp=tmp->NXT;
			}
		}	
		else 
		{
			if(tmp->direction == 'e')
				tmp->posx = 1;
			else if(tmp->direction == 'o')
				tmp->posx = 203;

			tmp=tmp->NXT;
		}
	}
}
