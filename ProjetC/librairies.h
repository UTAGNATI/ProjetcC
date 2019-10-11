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

#define couleur_ex(param1,param2) printf("\33[%s;5;%sm",param1,param2)

#define HOK (MAT[tmp->posy-2][tmp->posx-1]=='r' || MAT[tmp->posy-2][tmp->posx-1]=='x' || MAT[tmp->posy-2][tmp->posx-1]=='l' || MAT[tmp->posy-2][tmp->posx-1]=='e' || MAT[tmp->posy-2][tmp->posx-1]=='w' || MAT[tmp->posy-2][tmp->posx-1]=='c' || MAT[tmp->posy-2][tmp->posx-1]=='S' || MAT[tmp->posy-2][tmp->posx-1]=='H' || MAT[tmp->posy-2][tmp->posx-1]=='B' || MAT[tmp->posy-2][tmp->posx-1]=='D')
#define DOK (MAT[tmp->posy-1][tmp->posx]=='r' || MAT[tmp->posy-1][tmp->posx]=='x' || MAT[tmp->posy-1][tmp->posx]=='l' || MAT[tmp->posy-1][tmp->posx]=='e' || MAT[tmp->posy-1][tmp->posx]=='w' || MAT[tmp->posy-1][tmp->posx]=='c' || MAT[tmp->posy-1][tmp->posx]=='S' || MAT[tmp->posy-1][tmp->posx]=='H' || MAT[tmp->posy-1][tmp->posx]=='B' || MAT[tmp->posy-1][tmp->posx]=='D')
#define GOK (MAT[tmp->posy-1][tmp->posx-2]=='r' || MAT[tmp->posy-1][tmp->posx-2]=='x' || MAT[tmp->posy-1][tmp->posx-2]=='l' || MAT[tmp->posy-1][tmp->posx-2]=='e' || MAT[tmp->posy-1][tmp->posx-2]=='w' || MAT[tmp->posy-1][tmp->posx-2]=='c' || MAT[tmp->posy-1][tmp->posx-2]=='S' || MAT[tmp->posy-1][tmp->posx-2]=='H' || MAT[tmp->posy-1][tmp->posx-2]=='B' || MAT[tmp->posy-1][tmp->posx-2]=='D')
#define BOK (MAT[tmp->posy][tmp->posx-1]=='r' || MAT[tmp->posy][tmp->posx-1]=='x' || MAT[tmp->posy][tmp->posx-1]=='l' || MAT[tmp->posy][tmp->posx-1]=='e' || MAT[tmp->posy][tmp->posx-1]=='w' || MAT[tmp->posy][tmp->posx-1]=='c' || MAT[tmp->posy][tmp->posx-1]=='S' || MAT[tmp->posy][tmp->posx-1]=='H' || MAT[tmp->posy][tmp->posx-1]=='B' || MAT[tmp->posy][tmp->posx-1]=='D')

#define PHOK (MAT[tmp->posy-2][tmp->posx-1]=='p' || MAT[tmp->posy-2][tmp->posx-1]=='m' || MAT[tmp->posy-2][tmp->posx-1]=='f' || MAT[tmp->posy-2][tmp->posx-1]=='t' || MAT[tmp->posy-2][tmp->posx-1]=='w' || MAT[tmp->posy-2][tmp->posx-1]=='b' || MAT[tmp->posy-2][tmp->posx-1]=='c' || MAT[tmp->posy-2][tmp->posx-1]=='S' || MAT[tmp->posy-2][tmp->posx-1]=='H')
#define PDOK (MAT[tmp->posy-1][tmp->posx]=='p' || MAT[tmp->posy-1][tmp->posx]=='m' || MAT[tmp->posy-1][tmp->posx]=='f' || MAT[tmp->posy-1][tmp->posx]=='t' || MAT[tmp->posy-1][tmp->posx]=='w' || MAT[tmp->posy-1][tmp->posx]=='b' || MAT[tmp->posy-1][tmp->posx]=='c' || MAT[tmp->posy-1][tmp->posx]=='S' || MAT[tmp->posy-1][tmp->posx]=='H')
#define PGOK (MAT[tmp->posy-1][tmp->posx-2]=='p' || MAT[tmp->posy-1][tmp->posx-2]=='m' || MAT[tmp->posy-1][tmp->posx-2]=='f' || MAT[tmp->posy-1][tmp->posx-2]=='t' || MAT[tmp->posy-1][tmp->posx-2]=='w' || MAT[tmp->posy-1][tmp->posx-2]=='b' || MAT[tmp->posy-1][tmp->posx-2]=='c' || MAT[tmp->posy-1][tmp->posx-2]=='S' || MAT[tmp->posy-1][tmp->posx-2]=='H')
#define PBOK (MAT[tmp->posy][tmp->posx-1]=='p' || MAT[tmp->posy][tmp->posx-1]=='m' || MAT[tmp->posy][tmp->posx-1]=='f' || MAT[tmp->posy][tmp->posx-1]=='t' || MAT[tmp->posy][tmp->posx-1]=='w' || MAT[tmp->posy][tmp->posx-1]=='b' || MAT[tmp->posy][tmp->posx-1]=='c' || MAT[tmp->posy][tmp->posx-1]=='S' || MAT[tmp->posy][tmp->posx-1]=='H')

#define Bords_Pietons_S (tmp->posx != 162 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 113 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 95 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 152 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 133 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 123 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 86 || tmp->posy != 53 || tmp->lm != 'b') && (tmp->posx != 76 || tmp->posy != 53 || tmp->lm != 'b')
#define Bords_Pietons_N (tmp->posx != 86 || tmp->posy != 1 || tmp->lm != 'h') && (tmp->posx != 76 || tmp->posy != 1 || tmp->lm != 'h')
#define Bords_Pietons_G (tmp->posx != 1 || tmp->posy != 25 || tmp->lm != 'g') && (tmp->posx != 1 || tmp->posy != 9 || tmp->lm != 'g') && (tmp->posx != 1 || tmp->posy != 13 || tmp->lm != 'g') && (tmp->posx != 1 || tmp->posy != 29 || tmp->lm != 'g') && (tmp->posx != 1 || tmp->posy != 4 || tmp->lm != 'g') && (tmp->posx != 1 || tmp->posy != 16 || tmp->lm != 'g')
#define Bords_Pietons_D (tmp->posx != 203 || tmp->posy != 4 || tmp->lm != 'd') && (tmp->posx != 203 || tmp->posy != 9 || tmp->lm != 'd') && (tmp->posx != 203 || tmp->posy != 13 || tmp->lm != 'd') && (tmp->posx != 203 || tmp->posy != 25 || tmp->lm != 'd') && (tmp->posx != 203 || tmp->posy != 16 || tmp->lm != 'd')

//-------------------------------------------------------------------------------------//

struct voiture {
	char direction; /*zone d'arrivée (optionnelle)*/
	char depart; /*zone de depart*/
	char lm; /*last move*/
	char lc; /*last carrefour*/
	char tempo; /*char de sauvegarde*/
	int posx;
	int posy;
	int vitesse;
	char marque[30];
	char ravitaillement;
	int attente;
	char etat;

	struct voiture *NXT;
};
typedef struct voiture VOITURE;


struct train {
	int posx; //varie entre 1 et 204
	int posy; //invariante (10 ou 12)
	int vitesse; //0, 1 ou 2
	int nb; //place dans la suite de wagons
	char direction; // o ou e
	char etat; //a ou s ou i
	int attente; //commence à 0 et va jusqu'a 50 (tours de boucle) pour attendre à l'arret que les gens montent
	struct train *NXT;
};
typedef struct train TRAIN;


struct pieton {
	char objectif; //ce qu'il va faire sur la carte
	char depart; /* zone de depart */
	char lm;
	char tempo;
	char tunnel;
	int posx;
	int posy;
	//int vitesse;
	char etat; //i ou a ou t
	int ID;
	struct pieton *NXT;
};
typedef struct pieton PIETON;

struct feu {
	char couleur;
	int posx;
	int posy;

	char bloc;
	int x;
	int y;
	struct feu *NXT;
};
typedef struct feu FEU;

struct curseur {
    int posx;
    int posy;
};
typedef struct curseur CURSEUR;

//-----------------------------------------------------------------------------------//


typedef VOITURE* Liste_V;
typedef TRAIN* Liste_T;
typedef PIETON* Liste_P;
typedef FEU* Liste_F;

