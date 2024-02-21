#include <stdio.h>
#include <stdlib.h>

typedef struct livre {

    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
} Livre ;

typedef struct{ /* Tete fictive */
    Livre * L; /* Premier element */
} Biblio ;

Livre* creer_livre_LC(int num,char* titre,char* auteur);
void liberer_livre_LC(Livre *l);
Biblio* creer_biblio_LC();
void liberer_biblio_LC(Biblio* b);
void inserer_en_tete_LC(Biblio* b,int num,char* titre,char* auteur);

void afficherLivre_LC(Livre *l);
void afficherBiblio_LC(Biblio *b);

Livre* rechercheLivreNum_LC(Biblio *b,int num);
Livre* rechercheLivreTitre_LC(Biblio *b,char* titre);
Biblio* LivresAuteurs_LC(Biblio*b,char* auteur);
void supprimerLivre_LC(Biblio* b, int num, char* titre, char* auteur);
Biblio* fusion_LC(Biblio* b1,Biblio* b2);
Biblio* RecherchePlusieurs_LC(Biblio *b);