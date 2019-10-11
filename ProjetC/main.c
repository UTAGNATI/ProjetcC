#include "librairies.h"
#include "fonctions.h"
#include "vehicules.h"
#include "pietons.h"
#include "trains.h"
#include "menu.h"
#include "affichage_carte.h"
#include "launchers.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    printf("\033[2J"); /*clear screen*/
    system("setterm -cursor off"); //etteint le curseur
    menu();
    printf("\033[2J"); /*clear screen*/
    printf("\33[1;1H");
    printf("Fin de l'execution. \n");
    //system("killall play");       //arrtee tous les processus de play (au cas où)
    system("setterm -cursor on"); //rallume le curseur
return 0;
}
