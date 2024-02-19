#include <stdio.h>
#include <stdlib.h>


typedef struct livreh {
    int clef; 
    struct livreh* suivant;
} LivreH;

typedef struct {
    int nE; /*nb d’elements de la table de hachage*/
    int m; /*taille de la table de hachage*/
    LivreH** T; /*table de hachage avec resolution des collisions par chainage*/
} BiblioH;


int fonctionClef(char *auteur);
LivreH* creer_livre(int num, char* titre, char* auteur);
void liberer_livre(LivreH* l);
BiblioH* creer_biblio(int m);
void liberer_biblio(BiblioH* b);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b, int num, char* titre, char* auteur);
void afficherLivre(LivreH* livre);
void afficherBiblio(BiblioH* b);
LivreH* rechercheClef(BiblioH *b,int clef);
void supprimerLivre(Biblio* b, int num, char* titre, char* auteur);
BiblioH* fusion(Biblio* b1,Biblio* b2);
BiblioH* RecherchePlusieurs(Biblio *b);