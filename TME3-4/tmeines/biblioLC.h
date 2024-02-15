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
void fusion(Biblio *b1, Biblio *b2);
