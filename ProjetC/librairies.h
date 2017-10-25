#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#define couleur(param) printf("\033[%sm",param)

#define HOK (MAT[tmp->posy-2][tmp->posx-1]=='r' || MAT[tmp->posy-2][tmp->posx-1]=='w' || MAT[tmp->posy-2][tmp->posx-1]=='c' || MAT[tmp->posy-2][tmp->posx-1]=='S' || MAT[tmp->posy-2][tmp->posx-1]=='H' || MAT[tmp->posy-2][tmp->posx-1]=='B' || MAT[tmp->posy-2][tmp->posx-1]=='D')
#define DOK (MAT[tmp->posy-1][tmp->posx]=='r' || MAT[tmp->posy-1][tmp->posx]=='w' || MAT[tmp->posy-1][tmp->posx]=='c' || MAT[tmp->posy-1][tmp->posx]=='S' || MAT[tmp->posy-1][tmp->posx]=='H' || MAT[tmp->posy-1][tmp->posx]=='B' || MAT[tmp->posy-1][tmp->posx]=='D')
#define GOK (MAT[tmp->posy-1][tmp->posx-2]=='r' || MAT[tmp->posy-1][tmp->posx-2]=='w' || MAT[tmp->posy-1][tmp->posx-2]=='c' || MAT[tmp->posy-1][tmp->posx-2]=='S' || MAT[tmp->posy-1][tmp->posx-2]=='H' || MAT[tmp->posy-1][tmp->posx-2]=='B' || MAT[tmp->posy-1][tmp->posx-2]=='D')
#define BOK (MAT[tmp->posy][tmp->posx-1]=='r' || MAT[tmp->posy][tmp->posx-1]=='w' || MAT[tmp->posy][tmp->posx-1]=='c' || MAT[tmp->posy][tmp->posx-1]=='S' || MAT[tmp->posy][tmp->posx-1]=='H' || MAT[tmp->posy][tmp->posx-1]=='B' || MAT[tmp->posy][tmp->posx-1]=='D')

//-------------------------------------------------------------------------------------//

struct voiture {
	char direction;
	char depart;
	char lm;
	char lc;
	int posx;
	int posy;
	int vitesse;
	int ID;
	//char alignement;
	//char type;
	char marque[30];
	//char ravitaillement;
	char etat;
	
	struct voiture *NXT;
};
typedef struct voiture VOITURE;


struct train {
	char direction;
	int posx;
	int posy; //invariante
	int vitesse;
	char etat;
	int ID;
	struct train *NXT;
};
typedef struct train TRAIN;


struct pieton {
	char objectif; //ce qu'il va faire sur la carte
	int posx;
	int posy;
	int vitesse;
	char etat;
	int ID;
	struct pieton *NXT;
};
typedef struct pieton PIETON;

//-----------------------------------------------------------------------------------//


typedef VOITURE* Liste_V;
typedef TRAIN* Liste_T;
typedef PIETON* Liste_P;


//faire une fonction d'INIT_VEHICULE qui permet d'ajouter un vehicule sur la liste des vehicules existant (lorsqu'il entre dans la carte)

//faire une fonction d'SUPR_VEHICULE qui permet de supprimer un vehicule de la liste des vehicules existants (lorsqu'il sort de la carte)

//faire l'initialisation de la liste qui va contenir les vehicules sur la carte
