#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "pietons.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"
#include "launchers.h"

void launcher_fluide() {
	//system("play -q ville.mp3 repeat 10 &"); //lance le fond musical
	printf("\033[2J"); /*clear screen*/
	printf("\33[1;1H\n"); /*place le curseur en haut à gauche*/
	affichage_txt();
	int nb_lignes=53;
	int nb_colonnes=206;
	char **carte = INIT_MAT_C(nb_lignes,nb_colonnes); /*tableau de char contenant les coordonnées de la route, des carrefours, des trottoirs, et de l'eau*/
	char **emplacement_v = INIT_MAT_C(nb_lignes, nb_colonnes); /*tableau de char que l'on va mettre à jour à chaque fois qu'une voiture se deplace*/
	char **carte_perm = INIT_MAT_C(nb_lignes, nb_colonnes);
	
	CHARGEMENT_Carte_Perm(nb_lignes,nb_colonnes,carte_perm);
	CHARGEMENT_MAP(nb_lignes,nb_colonnes,carte);
	REMPLISSAGE_MAT_V(nb_lignes,nb_colonnes, emplacement_v);

	
	//Parcour de liste
	int c=0; char quit = 'a'; /*c est un entier qui va etre incrémenté de 1 à chaque tour de boucle*/ 

	Liste_V liste_v = NULL; /*TRES IMPORTANT*/
	Liste_P liste_p = NULL;
	
	Liste_F liste_f = Formation_feu(emplacement_v);
	
	Liste_T liste_t = Creation_tram(); 
	

	while ((quit=key_pressed()) != 'q') {
		AFFICHAGE_PERM(nb_lignes,nb_colonnes,carte_perm);
		if(c%6 == 0) { 	//on insert une voiture sur la carte tout les 6 tours de boucle
			liste_v = INSERTION_V(liste_v, emplacement_v);
		}
		if(c%20==0) {
			liste_p = INSERTION_P(liste_p, emplacement_v);
		}
		
		if(c%300==0) {
			//system("play -q tram.mp3 &");
		}
		
		feu(c,liste_f,emplacement_v);
		refresh(c, liste_v, liste_t, liste_p,liste_v, liste_t, liste_p);
		deplacement_voiture(liste_v, liste_v,carte,emplacement_v);
		if(c%2==0) {
			deplacement_pietons(liste_p, liste_p, carte, emplacement_v);
		}
		deplacement_tram(liste_t,liste_t,carte,emplacement_v);
		
		SUPPRESSION_V(liste_v); //on vérifie si une voiture n'est plus utilisée et si c'est le cas on la retire de la liste puis on la free
		SUPPRESSION_P(liste_p);
		
		/*
		printf("\33[54;1HLa liste de voitures contient %d elements \n", content(liste_v)); //on replace le curseur en bas à gauche pour éviter qu'il se balade partout lors de l'execution
																				//on affiche en temps rééls le nombre d'éléments présents dans la liste
		printf("\33[55;1HLa liste de pietons contient %d elements \n", content_P(liste_p));
		*/

		c+=1; 	//on incrémente c
	}
	//system("killall play"); //permet de stopper le son à la fermeture du pregramme

	/*On libère l'espace alloué dynamiquement*/
	free(liste_v);
	free(liste_f);
	free(liste_t);
	free(liste_p);
	LIB_MAT_C(nb_lignes,carte);
	LIB_MAT_C(nb_lignes,emplacement_v);
}

void launcher_danger() {
	//system("play -q ville.mp3 repeat 10 &"); //lance le fond musical
	printf("\033[2J"); /*clear screen*/
	printf("\33[1;1H"); /*place le curseur en haut à gauche*/
	affichage_txt_danger();
	int nb_lignes=53;
	int nb_colonnes=206;
	char **carte = INIT_MAT_C(nb_lignes,nb_colonnes); /*tableau de char contenant les coordonnées de la route, des carrefours, des trottoirs, et de l'eau*/
	char **emplacement_v = INIT_MAT_C(nb_lignes, nb_colonnes); /*tableau de char que l'on va mettre à jour à chaque fois qu'une voiture se deplace*/
	char **carte_perm = INIT_MAT_C(nb_lignes, nb_colonnes);
	
	CHARGEMENT_Carte_Perm_Danger(nb_lignes,nb_colonnes,carte_perm);
	CHARGEMENT_MAP_DANGER(nb_lignes,nb_colonnes,carte);
	REMPLISSAGE_MAT_V(nb_lignes,nb_colonnes, emplacement_v);

	
	//Parcour de liste
	int c=0; char quit = 'a'; /*c est un entier qui va etre incrémenté de 1 à chaque tour de boucle*/ 

	Liste_V liste_v = NULL; /*TRES IMPORTANT*/
	Liste_P liste_p = NULL;
	
	Liste_F liste_f = Formation_feu(emplacement_v);
	
	Liste_T liste_t = Creation_tram(); 
	

	while ((quit=key_pressed()) != 'q') {
		printf("\33[1;1H"); /*place le curseur en haut à gauche*/
		//affichage_txt_danger(); //trop lourd lors de l'execution
		if(c%9 == 0) { 	//on insert une voiture sur la carte tout les 6 tours de boucle
			liste_v = INSERTION_V(liste_v, emplacement_v);
		}
		if(c%10==0) {
			liste_p = INSERTION_P(liste_p, emplacement_v);
		}
		
		if(c%300==0) {
			//system("play -q tram.mp3 &");
		}
		
		feu(c,liste_f,emplacement_v);
		refresh(c, liste_v, liste_t, liste_p,liste_v, liste_t, liste_p);
	
		AFFICHAGE_PERM(nb_lignes,nb_colonnes,carte_perm);
		
		
		deplacement_voiture(liste_v, liste_v,carte,emplacement_v);
		if(c%2==0) {
			deplacement_pietons(liste_p, liste_p, carte, emplacement_v);
		}
		deplacement_tram(liste_t,liste_t,carte,emplacement_v);
		
		SUPPRESSION_V(liste_v); //on vérifie si une voiture n'est plus utilisée et si c'est le cas on la retire de la liste puis on la free
		SUPPRESSION_P(liste_p);
		
		/*
		printf("\33[54;1HLa liste de voitures contient %d elements \n", content(liste_v)); //on replace le curseur en bas à gauche pour éviter qu'il se balade partout lors de l'execution
																				//on affiche en temps rééls le nombre d'éléments présents dans la liste
		printf("\33[55;1HLa liste de pietons contient %d elements \n", content_P(liste_p));
		*/
		
		c+=1; 	//on incrémente c
	}
	//system("killall play"); //permet de stopper le son à la fermeture du programme

	/*On libère l'espace alloué dynamiquement*/
	free(liste_v);
	free(liste_f);
	free(liste_t);
	free(liste_p);
	LIB_MAT_C(nb_lignes,carte);
	LIB_MAT_C(nb_lignes,emplacement_v);
}

