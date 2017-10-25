

int **INIT_MAT(int nb_lignes, int nb_colonnes);
char **INIT_MAT_C(int nb_lignes, int nb_colonnes);
void LIB_MAT(int nb_lignes, int **mat);
void LIB_MAT_C(int nb_lignes, char **mat);
void CHARGEMENT_MAT(int nb_lignes, int nb_colonnes, int **mat);
void CHARGEMENT_MAP(int nb_lignes, int nb_colonnes, char **mat);
void AFFICHAGE_MAT(int NB_L,int NB_C, int **MAT);
void AFFICHAGE_MAT_C(int NB_L,int NB_C, char **MAT);
void AFFICHAGE_ROUTE(int NB_L,int NB_C, int **MAT);
void AFF_LISTE(Liste_V liste_v);

//void DEPLACEMENT_VOITURE(int **mat, VOITURE *V, char direc);
//Liste_V INITIALISATION_V();

VOITURE* INIT_V();
Liste_V INSERTION_V(Liste_V liste_v);
void SUPPRESSION_V(Liste_V liste_v);
int content(Liste_V liste_v);
void refresh(int c, Liste_V liste_v, VOITURE *tmp, char **MAT);
int empty(Liste_V liste_v);
void carrefour(VOITURE* tmp, char **MAT);
void deplacement_voiture(Liste_V liste_v, VOITURE *tmp, char **MAT);
void wait(int wtime);
