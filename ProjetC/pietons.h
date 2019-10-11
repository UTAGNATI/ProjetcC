void AFF_LISTE_P(Liste_P liste_p);
PIETON* INIT_P(char **MAT);
Liste_P INSERTION_P(Liste_P liste_p, char **MAT);
void SUPPRESSION_P(Liste_P liste_p);
int content_P(Liste_P liste_p);
int empty_P(Liste_P liste_p);
void continu(Liste_P liste_p, PIETON *tmp);
void sortie_carrefour_pieton(PIETON *tmp, char direction);
void carrefour_pietons(Liste_P liste_p, PIETON *tmp, char **MAT);

void deplacement_pietons(Liste_P liste_p, PIETON *tmp, char **MAT, char **MAT_P);
//void carrefour(VOITURE* tmp, char **MAT, char **MAT_V);

