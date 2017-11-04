void AFF_LISTE(Liste_V liste_v);
VOITURE* INIT_V(char **MAT);
Liste_V INSERTION_V(Liste_V liste_v, char **MAT);
void SUPPRESSION_V(Liste_V liste_v);
int content(Liste_V liste_v);
int empty(Liste_V liste_v);
void carrefour(VOITURE* tmp, char **MAT, char **MAT_V);
void deplacement_voiture(Liste_V liste_v, VOITURE *tmp, char **MAT, char **MAT_V);
