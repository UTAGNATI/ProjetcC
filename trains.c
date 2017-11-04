#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"


TRAIN* INIT_TRAIN(int posx, int posy, char direction){
	TRAIN* T = malloc(sizeof(TRAIN));
	T->posx=posx;
	T->posy=posy;
	T->direction = direction;
	T->etat = 'a';
	T->attente = 0;
}

Liste_T INSERTION_T(Liste_T liste_t, int posx, int posy, char direction){
	/* Création du nouvel élément */
	TRAIN *new = malloc(sizeof(*new));
	new = INIT_TRAIN(posx, posy, direction);
	/* On assigne l'adresse de l'element suivant au nouveau */
	new->NXT = liste_t;

	return new;
} 

Liste_T Creation_tram(){
	Liste_T liste_t = NULL;
	liste_t = INSERTION_T(liste_t, 1, 12, 'e');
	liste_t = INSERTION_T(liste_t, 204, 10, 'o');
	return liste_t;
}

void deplacement_tram(Liste_T liste_t, TRAIN *tmp, char **MAT) {
	while(tmp != NULL) {
		if(MAT[tmp->posy-1][tmp->posx-1] == 'T' && tmp->attente < 50){ //si tu es à un arret de tram est que tu n'as pas assez attend, alors continu d'attendre
			tmp->etat = 's';
		}
		else {
			tmp->attente = 0;
			tmp->etat = 'a'; //sinon, repars
		}
		
		if((tmp->posy != 10 || tmp->posx != -20) && (tmp->posy != 12 || tmp->posx != 220)) {
			if(tmp->etat == 'a'){    //bouge si actif
				if(tmp->direction == 'o') { /*Gauche*/
					tmp->posx -= 1;
				}
				else if(tmp->direction == 'e') { /*Droite*/
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
				tmp->posx = 204;
			tmp=tmp->NXT;
		}
	}
}
