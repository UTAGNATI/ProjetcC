#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"



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

void launcher_test(){
	printf("\033[2J"); /*clear screen*/
	printf("\33[1;1H"); /*place le curseur en haut à droite*/
	int nb_lignes=53;
	int nb_colonnes=206;
	char **carte = INIT_MAT_C(nb_lignes,nb_colonnes); /*tableau de char contenant les coordonnées de la route, des carrefours, des trottoirs, et de l'eau*/
	char **emplacement_v = INIT_MAT_C(nb_lignes, nb_colonnes); /*tableau de char que l'on va mettre à jour à chaque fois qu'une voiture se deplace*/

	CHARGEMENT_MAP(nb_lignes,nb_colonnes,carte);
	REMPLISSAGE_MAT_V(nb_lignes,nb_colonnes, emplacement_v);

	
	//Parcour de liste
	int c=0; char quit = 'a'; /*c est un entier qui va etre incrémenté de 1 à chaque tour de boucle*/ 

	Liste_V liste_v = NULL; /*TRES IMPORTANT*/
	
	Liste_F liste_f = Formation_feu(emplacement_v);
	
	Liste_T liste_t = Creation_tram(); 
	
	//VOITURE* tmp = malloc(sizeof(VOITURE)); /*initialisation d'une voiture de parcour de liste*/

	while ((quit=key_pressed()) != 'q'){
		affichage_txt();
		if(c%15 == 0){ 	/*on insert une voiture sur la carte tout les 6 tours de boucle*/
			liste_v = INSERTION_V(liste_v, emplacement_v);
		}
		feu(c,liste_f,emplacement_v);
		refresh(c, liste_v, liste_t, liste_v, liste_t);
		//AFFICHAGE_MAT_C(nb_lignes,nb_colonnes,emplacement_v);
		deplacement_voiture(liste_v, liste_v,carte,emplacement_v);
		deplacement_tram(liste_t,liste_t,carte);
		
		SUPPRESSION_V(liste_v); /*on vérifie si une voiture n'est plus utilisée et si c'est le cas on la retire de la liste puis on la free*/
		//SUPPRESSION_V(liste_v);
		
		printf("\33[54;1HLa liste contient %d elements \n", content(liste_v)); /*on replace le curseur en bas à gauche pour éviter qu'il se balade partout lors de l'execution*/
																				/*on affiche en temps rééls le nombre d'éléments présents dans la liste*/
		c+=1; 	/*on incrémente c*/
	}
	//AFF_LISTE(liste_v);


	/*On libère l'espace alloué dynamiquement*/
	//free(tmp);
	free(liste_v);
	free(liste_f);
	free(liste_t);
	LIB_MAT_C(nb_lignes,carte);
	LIB_MAT_C(nb_lignes,emplacement_v);
}


int main(){
	srand(time(NULL));
	
	launcher_test();
	
	printf("Fin de l'execution. \n");
return 0;
}
