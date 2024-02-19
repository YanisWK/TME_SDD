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

Livre* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(Livre *l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);

void afficherLivre(Livre *l);
void afficherBiblio(Biblio *b);

Livre* rechercheLivreNum(Biblio *b,int num);
Livre* rechercheLivreTitre(Biblio *b,char* titre);
Biblio* BiblioAuteur(Biblio*b,char* auteur);
void supprimerLivre(Biblio* b, int num, char* titre, char* auteur);
Biblio* fusion(Biblio* b1,Biblio* b2);
Biblio* RecherchePlusieurs(Biblio *b);