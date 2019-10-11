
char key_pressed();
int **INIT_MAT(int nb_lignes, int nb_colonnes);
char **INIT_MAT_C(int nb_lignes, int nb_colonnes);
void LIB_MAT(int nb_lignes, int **mat);
void LIB_MAT_C(int nb_lignes, char **mat);
void CHARGEMENT_MAT(int nb_lignes, int nb_colonnes, int **mat);
void CHARGEMENT_MAP(int nb_lignes, int nb_colonnes, char **mat);
void CHARGEMENT_MAP_DANGER(int nb_lignes, int nb_colonnes, char **mat);
void CHARGEMENT_Carte_Perm(int nb_lignes, int nb_colonnes, char **mat);
void CHARGEMENT_Carte_Perm_Danger(int nb_lignes, int nb_colonnes, char **mat);
void REMPLISSAGE_MAT_V(int nb_lignes, int nb_colonnes, char **mat);
void AFFICHAGE_MAT(int NB_L,int NB_C, int **MAT);
void AFFICHAGE_MAT_C(int NB_L,int NB_C, char **MAT);
void AFFICHAGE_ROUTE(int NB_L,int NB_C, int **MAT);



FEU* INIT_FEU(int posx, int posy, int x, int y, char color,char **MAT);
Liste_F INSERTION_F(Liste_F liste_f, int posx, int posy, int x, int y, char color,char **MAT);
Liste_F Formation_feu(char **MAT);
void feu(int c, Liste_F liste_f, char **MAT);


void refresh(int c, Liste_V liste_v, Liste_T liste_t, Liste_P liste_p, VOITURE *tmp, TRAIN *tmp_t, PIETON *tmp_p);


void wait(int wtime);
