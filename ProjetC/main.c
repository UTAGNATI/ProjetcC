#include "librairies.h"
#include "fonctions.h"
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
	printf("\33[0;0H"); /*place le curseur en haut à droite*/
	int nb_lignes=53;
	int nb_colonnes=206;
	char **carte = INIT_MAT_C(nb_lignes,nb_colonnes);

	CHARGEMENT_MAP(nb_lignes,nb_colonnes,carte);
	//AFFICHAGE_MAT_C(nb_lignes,nb_colonnes,carte);
	
	//Parcour de liste
	int c=0; char quit = 'a';
	int i;	
	Liste_V liste_v = NULL; /*TRES IMPORTANT*/
	//VOITURE* tmp = malloc(sizeof(VOITURE)); /*initialisation d'une voiture de parcour de liste*/
	
	while ((quit=key_pressed()) != 'q'){
		affichage_txt();
		if(c%3 == 0)
			liste_v = INSERTION_V(liste_v);
		refresh(c, liste_v, liste_v, carte);
		deplacement_voiture(liste_v, liste_v,carte);
		c+=1;
		SUPPRESSION_V(liste_v);
		printf("\33[53;1H\n");
		printf("La liste contient %d elements \n", content(liste_v));
		
	}
	AFF_LISTE(liste_v);
	/*On libère l'espace alloué dynamiquement*/
	//free(tmp);
	free(liste_v);
	LIB_MAT_C(nb_lignes,carte);
}


int main(){
	srand(time(NULL));
	launcher_test();
	printf("Ce programme fonctionne!!!! \n");
return 0;
}
