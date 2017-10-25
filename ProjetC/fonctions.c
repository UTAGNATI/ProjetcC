#include "librairies.h"
#include "fonctions.h"
#include "menu.h"
#include "affichage_carte.h"

//PERMET D'ALLOUER DE L'ESPACE MÉMOIRE À UNE MATRICE DE DIMENSION NB_L PAR NB_C
int **INIT_MAT(int nb_lignes, int nb_colonnes){
	int i;
	int **mat = malloc(nb_lignes*sizeof(int*));
	for(i=0;i<nb_lignes;i++){
		*(mat+i) = malloc(nb_colonnes*sizeof(int)); 
	}
return mat;
}

char **INIT_MAT_C(int nb_lignes, int nb_colonnes){
	int i;
	char **mat = malloc(nb_lignes*sizeof(char*));
	for(i=0;i<nb_lignes;i++){
		*(mat+i) = malloc(nb_colonnes*sizeof(char)); 
	}
return mat;
}

//PERMET DE LIBERER L'ESPACE MÉMOIRE UTILISÉ PAR LA MATRICE UNE FOIS QU'ON NE S'EN SERT PLUS
void LIB_MAT(int nb_lignes, int **mat){
	int i;
	for(i=0;i<nb_lignes;i++){
		free(*(mat+i));
	}
	free(mat);
}

void LIB_MAT_C(int nb_lignes, char **mat){
	int i;
	for(i=0;i<nb_lignes;i++){
		free(*(mat+i));
	}
	free(mat);
}

//PERMET DE CHARGER UNE MATRICE DE DIMENSION NB_L PAR NB_C
void CHARGEMENT_MAT(int nb_lignes, int nb_colonnes, int **mat){
	int nbl,nbc;
	for(nbl=0;nbl<nb_lignes;nbl++){
		for(nbc=0;nbc<nb_colonnes;nbc++){
			scanf("%d",&mat[nbl][nbc]);
		}
	}
}

void CHARGEMENT_MAP(int nb_lignes, int nb_colonnes, char **mat){
	int nbl,nbc;	
	FILE* fic = NULL;
	fic=fopen("map.txt", "r");
	for(nbl=0;nbl<nb_lignes;nbl++){
		
			fgets(mat[nbl], nb_colonnes, fic);

	}
	fclose(fic);
}

//PERMET D'AFFICHER UNE MATRICE DE DIMENSION NB_L PAR NB_C
void AFFICHAGE_MAT(int NB_L,int NB_C, int **MAT){
	int nbl,nbc;
	for(nbl=0;nbl<NB_L;nbl++){
		for(nbc=0;nbc<NB_C;nbc++){
			printf("%d ",*(*(MAT+nbl)+nbc));
		}
	printf("\n");
	}
}

void AFFICHAGE_MAT_C(int NB_L,int NB_C, char **MAT){
	int nbl,nbc;
	for(nbl=0;nbl<NB_L;nbl++){
		for(nbc=0;nbc<NB_C;nbc++){
			printf("%c",*(*(MAT+nbl)+nbc));
		}
	//printf("\n");
	}
}

//FONCTIONS DE VISUALISATION DE LA ROUTE ENREGISTRÉE EN MÉMOIRE
void AFFICHAGE_ROUTE(int NB_L,int NB_C, int **MAT){
	int nbl,nbc;
	for(nbl=0;nbl<NB_L;nbl++){
		for(nbc=0;nbc<NB_C;nbc++){
			if(*(*(MAT+nbl)+nbc)==0)
				printf(" ");
			if(*(*(MAT+nbl)+nbc)==1)
				printf("1");
			if(*(*(MAT+nbl)+nbc)==2)
				printf("2");
			if(*(*(MAT+nbl)+nbc)==3)
				printf("3");
		}
	printf("\n");
	}
}

void AFF_LISTE(Liste_V liste_v){
	VOITURE* tmp = liste_v;
	while(tmp != NULL)
	{
		printf("%d \n",tmp->posx);
		tmp = tmp->NXT;
	}
}


/*
//FONCTION DE DEPLACEMENT DE VÉHICULE
void DEPLACEMENT_VOITURE(int **mat, VOITURE *V, char direc){
	switch(direc){
		case 'E': V->posx +=1;break;
		case 'O': V->posx -=1;break;
		case 'N': V->posy +=1;break;
		case 'S': V->posy -=1;break;
		default : ;break;
	}
}
*/

/*
//FONCTION INITIALISATION DE LA LISTE DE VEHICULES
Liste_V INITIALISATION_V(){
	Liste_V *liste_v = malloc(sizeof(*liste));
	VOITURE *voiture = malloc(sizeof(*voiture));

	voiture->nombre = 0;
	voiture->NXT = NULL;
	liste->premier = voiture;

	return liste_v;
}
*/

/*Fonction de delai*/
void wait(int wtime){
	//wtime en centième de seconde
	int i;
	for(i=0;i<wtime*10000000;i++){
		//ne rien faire
	}
}


int empty(Liste_V liste_v){
	if(liste_v == NULL) return 1;
	else return 0;
}

VOITURE* INIT_V(){
	VOITURE* V = malloc(sizeof(VOITURE));
	int r = rand()%5; /*marque et vitesse*/
	int p = rand()%8; /*position de départ*/
	switch(r){ /*initialisation de la marque et de la vitesse MAX*/
		case 0 : strcpy(V->marque, "Ferrari"); V->vitesse=2; break;
		case 1 : strcpy(V->marque, "Bugatti"); V->vitesse=2; break;
		case 2 : strcpy(V->marque, "Mini"); V->vitesse=1; break;
		case 3 : strcpy(V->marque, "Transit"); V->vitesse=1; break;
		case 4 : strcpy(V->marque, "Renault"); V->vitesse=1; break;
		default : break;
	}
	switch(p){ /*initialisation des positions de départ*/
		case 0 : V->posx = 1;   V->posy = 7; V->depart='o'; break; /*Haut gauche*/
		case 1 : V->posx = 79;  V->posy = 1; V->depart='n'; break; /*Haut centre*/
		case 2 : V->posx = 205; V->posy = 5; V->depart='e'; break; /*Haut droit*/
		case 3 : V->posx = 1;   V->posy = 28;V->depart='o'; break; /*Milieu gauche*/
		case 4 : V->posx = 205; V->posy = 26;V->depart='e'; break; /*Milieu droite*/
		case 5 : V->posx = 83;  V->posy = 53;V->depart='s'; break; /*Bas gauche*/
		case 6 : V->posx = 130; V->posy = 53;V->depart='s'; break; /*Bas centre*/
		case 7 : V->posx = 159; V->posy = 53;V->depart='s'; break; /*Bas droite*/
		default : break;
	}
	V->lm='n'; /*last move inconnu*/
	V->etat='a'; /*etat actif*/
return V;
}

Liste_V INSERTION_V(Liste_V liste_v){ //en tete
	/* Création du nouvel élément */
	VOITURE *new = malloc(sizeof(*new));
	new = INIT_V();
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
	VOITURE *save = NULL;
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
		save = tmp->NXT; /*je fais un swap pour pouvoir free l'elt inactif*/
		tmp->NXT=replace; /*L'elt qui pointait sur l'elt inactif pointe maintenant sur le suivant*/
		tmp=save;
		free(tmp);
	}
}


void carrefour(VOITURE* tmp, char **MAT){
	int cpt=0; /*compteur de directionsd'un carrefour*/
	int choice;
	/*On compte le nombre de direction possible*/

    /*droite*/
	if(MAT[tmp->posy-1][tmp->posx]=='r' && tmp->lm != 'g' && tmp->lc != 'g') 
		cpt += 1;
	if(MAT[tmp->posy-1][tmp->posx]=='D' && tmp->lm == 'd' && tmp->lc != 'g')
		cpt +=1;

    /*gauche*/
	if(MAT[tmp->posy-1][tmp->posx-2]=='r' && tmp->lm != 'd' && tmp->lc != 'd')
		cpt += 2;
	if(MAT[tmp->posy-1][tmp->posx-2]=='G' && tmp->lm == 'g' && tmp->lc != 'd')
		cpt += 2;

    /*bas*/
	if(MAT[tmp->posy][tmp->posx-1]=='r' && tmp->lm != 'h' && tmp->lc != 'h') 
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='E' && tmp->lm != 'h') 
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='G' && tmp->lm == 'b' && tmp->lc != 'h') 
		cpt += 4;
	if(MAT[tmp->posy][tmp->posx-1]=='D' && (tmp->lm == 'b' || tmp->lm == 'd') && tmp->lc != 'h') 
		cpt += 4;

    /*haut*/
	if(MAT[tmp->posy-2][tmp->posx-1]=='r' && tmp->lm != 'b' && tmp->lc != 'b') 
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='H' && tmp->lm == 'h' && tmp->lc != 'b')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='D' && (tmp->lm == 'h' || tmp->lm == 'd') && tmp->lc != 'b')
		cpt += 8;
	if(MAT[tmp->posy-2][tmp->posx-1]=='G' && (tmp->lm == 'h' || tmp->lm == 'g') && tmp->lc != 'b')
		cpt += 8;
	
	/*on choisit la direction à prendre en fonction du carrefour*/
	switch(cpt){
	case 1: tmp->posx += 1; /*juste le droit d'aller à droite*/
		tmp->lc = tmp->lm;
		tmp->lm = 'd';
	break;
	case 2: tmp->posx -= 1; /*juste le droite d'aller à gauche*/
		tmp->lc = tmp->lm;
		tmp->lm = 'g';
	break;
	case 4: tmp->posy += 1; /*juste le droit de descendre*/
		tmp->lc = tmp->lm;
		tmp->lm = 'b';
	break;
	case 5: if((choice=rand()%2)==1){
			tmp->posx += 1; /*va à droite*/
			tmp->lc = tmp->lm;
			tmp->lm = 'd';
		}
		else if(choice%2==0){
			tmp->posy += 1; /*va à bas*/
			tmp->lc = tmp->lm;
			tmp->lm = 'b';
		}
	break;
	case 6: if((choice=rand()%2)==1){
			tmp->posx -= 1; /*va en gauche*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'g';
		}
		else if(choice%2==0){
			tmp->posy += 1; /*va en bas*/
			tmp->lc = tmp->lm;
			tmp->lm = 'b'; 
		}
	break;
	case 7: if((choice=rand()%3)==1){
			tmp->posx -= 1; /*va en gauche*/ 		
			tmp->lc = tmp->lm;
			tmp->lm = 'g';
		}
		else if(choice%3==2){
			tmp->posx += 1; /*va en droite*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'd';
		}
		else if(choice%3==0){
			tmp->posy += 1; /*va en bas*/
			tmp->lc = tmp->lm;
			tmp->lm = 'b'; 
		} 
	break;
	case 8: tmp->posy -= 1; /*juste le droit de monter*/
		tmp->lc = tmp->lm;
		tmp->lm = 'h';
	break;
	case 9: if((choice=rand()%2)==1){
			tmp->posx += 1; /*va à droite*/
			tmp->lc = tmp->lm;
			tmp->lm = 'd';
		}
		else if(choice%2==0){
			tmp->posy -= 1; /*va à haut*/
			tmp->lc = tmp->lm;
			tmp->lm = 'h';
		}
	break;
	case 10: if((choice=rand()%2)==1){
			tmp->posx -= 1; /*va en gauche*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'g';
		}
		else if(choice%2==0){
			tmp->posy -= 1; /*va en haut*/
			tmp->lc = tmp->lm;
			tmp->lm = 'h'; 
		}
	break;
	case 11: if((choice=rand()%3)==1){
			tmp->posx -= 1; /*va en gauche*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'g';
		}
		else if(choice%3==2){
			tmp->posx += 1; /*va en droite*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'd';
		}
		else if(choice%3==0){
			tmp->posy -= 1; /*va en haut*/
			tmp->lc = tmp->lm;
			tmp->lm = 'h'; 
		} 
	break;
	case 12: if((choice=rand()%2)==1){
			tmp->posy += 1; /*va en bas*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'b';
		}
		else if(choice%2==2){
			tmp->posy -= 1; /*va en haut*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'h';
		}
	break;
	case 13: if((choice=rand()%3)==1){
			tmp->posy += 1; /*va en bas*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'b';
		}
		else if(choice%3==2){
			tmp->posx += 1; /*va en droite*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'd';
		}
		else if(choice%3==0){
			tmp->posy -= 1; /*va en haut*/
			tmp->lc = tmp->lm;
			tmp->lm = 'h';
		}
	break;
	case 14: if((choice=rand()%3)==1){
			tmp->posx -= 1; /*va en gauche*/ 
			tmp->lc = tmp->lm;
			tmp->lm = 'g';
		}
		else if(choice%3==2){
			tmp->posy += 1; /*va en bas*/
			tmp->lc = tmp->lm; 
			tmp->lm = 'b';
		}
		else if(choice%3==0){
			tmp->posy -= 1; /*va en haut*/
			tmp->lc = tmp->lm;
			tmp->lm = 'h'; 
		}
	break;
	default : printf("booom et le compteur vaut %d \n",cpt); 
	}

}

void deplacement_voiture(Liste_V liste_v, VOITURE *tmp, char **MAT){
	int choice;
	while(tmp != NULL){
		if((tmp->posx != 155 || tmp->posy != 53) && (tmp->posx != 79 || tmp->posy != 53) && (tmp->posx != 126 || tmp->posy != 53) && (tmp->posx != 1 || tmp->posy != 26) && (tmp->posx != 204 || tmp->posy != 28) && (tmp->posx != 83 || tmp->posy != 1) && (tmp->posx != 204 || tmp->posy != 7) && (tmp->posx != 1 || tmp->posy != 5))
		{
			if(tmp-> depart == 's' && tmp->lm == 'n'){ /*va en HAUT (pour commencer un départ du SUD)*/
				tmp->posy -= 1;
				tmp->lm = 'h';
			}
			else if(tmp->depart == 'n' && tmp->lm == 'n'){
				tmp->posy += 1;
				tmp->lm = 'b';
			}
			else if(tmp->depart == 'e' && tmp->lm == 'n'){
				tmp->posx -= 1;
				tmp->lm = 'g';
			}
			else if(tmp->depart == 'o' && tmp->lm == 'n'){
				tmp->posx += 1;
				tmp->lm = 'd';
			}
////////////////////////////////
			else if(MAT[tmp->posy-1][tmp->posx-1] == 'c'){ /*lorsqu'on arrive à un carrefour*/
				carrefour(tmp, MAT); //test de la fonction carrefour
			}
////////////////////////////////
			else if(HOK && tmp->lm != 'b'){ /*monte*/
				tmp->posy -= 1;
				tmp->lm = 'h';
			}
			else if(DOK && tmp->lm != 'g'){ /*droite*/
				tmp->posx += 1;
				tmp->lm = 'd'; 
			}
			else if(GOK && tmp->lm != 'd'){ /*gauche*/
				tmp->posx -= 1;
				tmp->lm = 'g';
			}
			else if(BOK && tmp->lm != 'h'){ /*bas*/
				tmp->posy += 1;
				tmp->lm = 'b';
			}
////////////////////////////////
			else printf("WTF?!");
				/*finir les déplacements*/
			tmp=tmp->NXT; /*passe à l'élément suivant de la liste*/
		}
		else
		{	
			tmp->etat = 'i'; /*état inactif*/
			tmp=tmp->NXT; /*passe à l'élément suivant de la liste*/
		}
	}
}

void refresh(int c, Liste_V liste_v, VOITURE *tmp, char **MAT){
//	animation_eau(c);
	//deplacement_tram(c);
	while(tmp != NULL)
	{	
		if(tmp->etat != 'i'){
			couleur("40");
			couleur("33");
			printf("\33[%d;%dH🚖 \n", tmp->posy, tmp->posx);
			couleur("0");
			printf("\33[53;1H\n");
			//MAT[tmp->posy-1][tmp->posx-1]='v';
			tmp = tmp->NXT;
		}
		else tmp = tmp->NXT; /*passe à l'élément suivant de la liste*/
	}
	wait(4);
//	animation_eau(c);
	//effacement_tram(c);
	tmp=liste_v; /*reinitialisation de tmp*/
	while(tmp != NULL)
	{
		couleur("40");
		printf("\33[%d;%dH  \n", tmp->posy, tmp->posx);
		couleur("0");
		printf("\33[53;1H\n");
		tmp = tmp->NXT; /*passe à l'élément suivant de la liste*/
	}
}



