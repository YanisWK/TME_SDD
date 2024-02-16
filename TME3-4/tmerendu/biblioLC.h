#include <stdio.h>
#include <stdlib.h>

typedef struct livre {

    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
} Livre ;

typedef struct{ /* Tete fictive */
    Livre * L ; /* Premier element */
} Biblio ;

void liberer_livre(Livre *l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);

void afficheLivre(Livre *l);
void afficherBiblio(Biblio *b);

Livre* rechercheLivreNum(Biblio *b,int num);
Livre* rechercheLivreTitre(Biblio *b,char* titre);
Biblio* BiblioAuteur(Biblio*b,char* auteur);
Biblio* FusionBiblio(Biblio* b1,Biblio* b2);
