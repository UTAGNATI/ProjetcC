#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "menu.h"
#include "affichage_carte.h"
#include "launchers.h"

//PERMET DE RECUPERER UNE ENTREE LORS DE L'EXECUTION
char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO,TCSANOW,&oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if(c != EOF){
		ungetc(c,stdin); result = getchar();
	}
	return result;
}

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

void CHARGEMENT_MAP_DANGER(int nb_lignes, int nb_colonnes, char **mat){
	int nbl,nbc;	
	FILE* fic = NULL;
	fic=fopen("map_danger.txt", "r");
	for(nbl=0;nbl<nb_lignes;nbl++){
		
			fgets(mat[nbl], nb_colonnes, fic);

	}
	fclose(fic);
}

void CHARGEMENT_Carte_Perm(int nb_lignes, int nb_colonnes, char **mat){
	int nbl,nbc;	
	FILE* fic = NULL;
	fic=fopen("CartePerm.txt", "r");
	for(nbl=0;nbl<nb_lignes;nbl++){
		
			fgets(mat[nbl], nb_colonnes, fic);

	}
	fclose(fic);
}

void CHARGEMENT_Carte_Perm_Danger(int nb_lignes, int nb_colonnes, char **mat){
	int nbl,nbc;	
	FILE* fic = NULL;
	fic=fopen("CartePerm_Danger.txt", "r");
	for(nbl=0;nbl<nb_lignes;nbl++){
		
			fgets(mat[nbl], nb_colonnes, fic);

	}
	fclose(fic);
}

void REMPLISSAGE_MAT_V(int nb_lignes, int nb_colonnes, char **mat){
	int nbl,nbc;	
	for(nbl=0;nbl<nb_lignes;nbl++){
		for(nbc=0;nbc<nb_colonnes;nbc++){
			mat[nbl][nbc]=' ';
		}
	}
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



FEU* INIT_FEU(int posx, int posy, int x, int y, char color, char **MAT){
	FEU* F = malloc(sizeof(FEU));
	F->posx=posx;
	F->posy=posy;
	F->couleur=color;
	F->x=x;
	F->y=y;
	if(color=='g'){
		F->bloc='a';
	}
	else if(color=='r'){
		F->bloc='b';
	}
}

Liste_F INSERTION_F(Liste_F liste_f, int posx, int posy, int x, int y, char color,char **MAT){
	/* Création du nouvel élément */
	FEU *new = malloc(sizeof(*new));
	new = INIT_FEU(posx, posy, x, y, color,MAT);
	/* On assigne l'adresse de l'element suivant au nouveau */
	new->NXT = liste_f;

	return new;
} 

void feu(int c, Liste_F liste_f, char **MAT){
	FEU *tmp=liste_f;
	/*les feus du bloc a deviennent verts et ceux du bloc b deviennent rouges*/
	if(c%200 >= 0 && c%200 < 85){
		while(tmp != NULL){
			if(tmp->bloc == 'a'){
				tmp->couleur = 'g';
				MAT[tmp->y-1][tmp->x-1]=' ';
				couleur_ex("38","46");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				
				printf("\33[54;1H\n");
				tmp=tmp->NXT;
			}
			else if(tmp->bloc == 'b'){
				tmp->couleur = 'r';
				MAT[tmp->y-1][tmp->x-1]='V';
				couleur_ex("38","196");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				
				printf("\33[54;1H\n");
				tmp=tmp->NXT;
			}
		}
	}
	/*ROUGE INETERMEDIAIRE (pour synchronisation)*/
	else if(c%200 >= 85 && c%200 < 100){
		while(tmp != NULL){
				tmp->couleur = 'r';
				MAT[tmp->y-1][tmp->x-1]='V';
				couleur_ex("38","196");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				tmp=tmp->NXT;
		}
	}
	/*les feux du bloc a deviennent rouges et ceux du bloc b deviennent verts*/
	else if(c%200 >= 100 && c%200 < 185){
		while(tmp != NULL){
			if(tmp->bloc == 'a'){
				tmp->couleur = 'r';
				MAT[tmp->y-1][tmp->x-1]='V';
				couleur_ex("38","196");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				
				printf("\33[54;1H\n");
				tmp=tmp->NXT;
			}
			else if(tmp->bloc == 'b'){
				tmp->couleur = 'g';
				MAT[tmp->y-1][tmp->x-1]=' ';
				couleur_ex("38","46");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				
				printf("\33[54;1H\n");
				tmp=tmp->NXT;
			}
		}
	}
	else if(c%200 >= 185 && c%200 < 200){
		while(tmp != NULL){
				tmp->couleur = 'r';
				MAT[tmp->y-1][tmp->x-1]='V';
				couleur("31");
				printf("\33[%d;%dH🚦\n",tmp->posy,tmp->posx);
				couleur("0");
				
				printf("\33[54;1H\n");
				tmp=tmp->NXT;
		}
	}
}


Liste_F Formation_feu(char **MAT){
	Liste_F liste_f = NULL;
	liste_f = INSERTION_F(liste_f,85,30,83,30,'g',MAT);
	liste_f = INSERTION_F(liste_f,77,24,79,24,'g',MAT);
	liste_f = INSERTION_F(liste_f,86,25,86,26,'r',MAT);
	liste_f = INSERTION_F(liste_f,76,29,75,28,'r',MAT);
	
	liste_f = INSERTION_F(liste_f,85,15,83,15,'g',MAT);
	liste_f = INSERTION_F(liste_f,77,3,79,3,'g',MAT);
	liste_f = INSERTION_F(liste_f,86,4,86,5,'r',MAT);
	liste_f = INSERTION_F(liste_f,75,8,75,7,'r',MAT);
	
	liste_f = INSERTION_F(liste_f,124,32,126,32,'g',MAT);
	liste_f = INSERTION_F(liste_f,132,38,130,38,'g',MAT);
	liste_f = INSERTION_F(liste_f,133,33,133,34,'r',MAT);
	
	liste_f = INSERTION_F(liste_f,153,32,155,32,'r',MAT);
	liste_f = INSERTION_F(liste_f,161,38,159,38,'r',MAT);
	liste_f = INSERTION_F(liste_f,152,37,151,36,'g',MAT);
	
	
	return liste_f;
}


/*Fonction de delai*/
void wait(int wtime){
	//wtime en centième de seconde
	int i;
	for(i=0;i<wtime*10000000;i++){
		//ne rien faire
	}
}


void refresh(int c, Liste_V liste_v, Liste_T liste_t, Liste_P liste_p, VOITURE *tmp, TRAIN *tmp_t, PIETON *tmp_p) {
	animation_eau(c);

	while(tmp != NULL) //VOITURE
	{	
		if(tmp->etat != 'i' && tmp->etat != 'r' && tmp->etat != 'x'){
			couleur("40");
			if(strcmp(tmp->marque,"Renault")==0){
				couleur("38;5;118");/////////////////////////////////////////////////////////////////////
				printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
				couleur("0");
			}
			else if(strcmp(tmp->marque,"Mini")==0){
				couleur("38;5;33");
				printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
				couleur("0");
			}
			else if(strcmp(tmp->marque,"Ferrari")==0){
				couleur("38;5;196");
				printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
				couleur("0");
			}
			else if(strcmp(tmp->marque,"Transit")==0){
				couleur("38;5;202");
				printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
				couleur("0");
			}
			else {
				couleur("38;5;226");
				printf("\33[%d;%dHV\n", tmp->posy, tmp->posx);
				couleur("0");
			}
			
			printf("\33[54;1H\n");
			tmp = tmp->NXT;
		}
		else if(tmp->etat == 'r'){
			//incrémente une variable à chaque tour pour le temps que le voiture fasse l'essence
			tmp=tmp->NXT;
		}
		else tmp = tmp->NXT; /*passe à l'élément suivant de la liste*/
	}

	while(tmp_p != NULL) {
		if(tmp_p->etat != 'i' && tmp_p->etat != 'o') {
			if(tmp_p->posy == 16 && tmp_p->posx < 88 && tmp_p->posx > 73 && (tmp_p->lm == 'g' || tmp_p->lm == 'd')) 
				{ }
			else	
				printf("\33[%d;%dHP\n", tmp_p->posy, tmp_p->posx);
		}
		

		printf("\33[54;1H\n");
		tmp_p=tmp_p->NXT;
	}

	
	while(tmp_t != NULL)  //TRAIN  
	{
		couleur("38;5;61");
/////////////////////////////////////////      gestion train o->e

		if(tmp_t->direction == 'e' && tmp_t->posx == 1)
			printf("\33[%d;%dHT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 2)
			printf("\33[%d;%dHTT\n",tmp_t->posy,tmp_t->posx-1);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 3)
			printf("\33[%d;%dHTTT\n",tmp_t->posy,tmp_t->posx-2);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 4)
			printf("\33[%d;%dHTTTT\n",tmp_t->posy,tmp_t->posx-3);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 5)
			printf("\33[%d;%dHTTTTT\n",tmp_t->posy,tmp_t->posx-4);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 6)
			printf("\33[%d;%dHTTTTTT\n",tmp_t->posy,tmp_t->posx-5);
		else if(tmp_t->direction == 'e' && tmp_t->posx > 6 && tmp_t->posx < 198)
			printf("\33[%d;%dHTTTTTTT\n",tmp_t->posy,tmp_t->posx-6);
			
		else if(tmp_t->direction == 'e' && tmp_t->posx == 197)
			printf("\33[%d;%dHTTTTTTT\n",tmp_t->posy,tmp_t->posx-6);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 198)
			printf("\33[%d;%dHTTTTTT\n",tmp_t->posy,tmp_t->posx-5);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 199)
			printf("\33[%d;%dHTTTTT\n",tmp_t->posy,tmp_t->posx-4);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 200)
			printf("\33[%d;%dHTTTT\n",tmp_t->posy,tmp_t->posx-3);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 201)
			printf("\33[%d;%dHTTT\n",tmp_t->posy,tmp_t->posx-2);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 202)
			printf("\33[%d;%dHTT\n",tmp_t->posy,tmp_t->posx-1);
		else if(tmp_t->direction == 'e' && tmp_t->posx == 203)
			printf("\33[%d;%dHT\n",tmp_t->posy,tmp_t->posx);
			
//////////////////////////////////////////		gestion train e->o
					
		else if(tmp_t->direction == 'o' && tmp_t->posx == 203)
			printf("\33[%d;%dHT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 202)
			printf("\33[%d;%dHTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 201)
			printf("\33[%d;%dHTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 200)
			printf("\33[%d;%dHTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 199)
			printf("\33[%d;%dHTTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 198)
			printf("\33[%d;%dHTTTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx < 199 && tmp_t->posx > 6)
			printf("\33[%d;%dHTTTTTTT\n",tmp_t->posy,tmp_t->posx);

		else if(tmp_t->direction == 'o' && tmp_t->posx == 7)
			printf("\33[%d;%dHTTTTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 6)
			printf("\33[%d;%dHTTTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 5)
			printf("\33[%d;%dHTTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 4)
			printf("\33[%d;%dHTTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 3)
			printf("\33[%d;%dHTTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 2)
			printf("\33[%d;%dHTT\n",tmp_t->posy,tmp_t->posx);
		else if(tmp_t->direction == 'o' && tmp_t->posx == 1)
			printf("\33[%d;%dHT\n",tmp_t->posy,tmp_t->posx);	
		
		couleur("0");
		printf("\33[54;1H\n");
		tmp_t=tmp_t->NXT;
			
	}
	
	wait(5);
	
	animation_eau(c);

	tmp=liste_v; /*reinitialisation de tmp*/
	while(tmp != NULL)
	{	
		if(tmp->etat != 'r') {
			couleur("40");
			printf("\33[%d;%dH  \n", tmp->posy, tmp->posx);
			couleur("0");
		}
		
		printf("\33[54;1H\n");
		
		tmp = tmp->NXT; /*passe à l'élément suivant de la liste*/
	}

	
	tmp_p=liste_p;
	while(tmp_p != NULL) {
		if(tmp_p->etat == 'a') {
			if(tmp_p->posy == 16 && tmp_p->posx < 88 && tmp_p->posx > 73 && (tmp_p->lm == 'g' || tmp_p->lm == 'd')) 
				{ }
			else if(tmp_p->lm == 'h' || tmp_p->lm == 'b' || tmp_p->posy == 16)
				printf("\33[%d;%dH \n", tmp_p->posy, tmp_p->posx);
			else if(tmp_p->posy == 4 || tmp_p->posy == 25 || tmp_p->posy == 29 || tmp_p->posy == 33 || tmp_p->posy == 37 || tmp_p->posy == 46)
				printf("\33[%d;%dH─\n", tmp_p->posy, tmp_p->posx);
			else
				printf("\33[%d;%dH \n", tmp_p->posy, tmp_p->posx);
		}
		else if(tmp_p->etat == 'm') { }

		printf("\33[54;1H\n");
		tmp_p=tmp_p->NXT;
	}
	

	tmp_t=liste_t;
	while(tmp_t != NULL)
	{
		if(tmp_t->direction == 'o' && tmp_t->posx > 0 && tmp_t->posx < 198)
			printf("\33[%d;%dH────────\n", tmp_t->posy, tmp_t->posx);
		else if(tmp_t->direction == 'e' && tmp_t->posx > 6 && tmp_t->posx < 204)
			printf("\33[%d;%dH────────\n", tmp_t->posy, tmp_t->posx-6);
		else {
			printf("\33[%d;%dH────────\n", tmp_t->posy, 1);
			printf("\33[%d;%dH────────\n", tmp_t->posy, 197);
		}
		printf("\33[54;1H\n");
		tmp_t = tmp_t->NXT; //passe à l'élément suivant de la liste
	}

}




