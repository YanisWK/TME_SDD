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
LivreH* creer_livre_H(int num, char* titre, char* auteur);
void liberer_livre_H(LivreH* l);
BiblioH* creer_biblio_H(int m);
void liberer_biblio_H(BiblioH* b);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b, int num, char* titre, char* auteur);
void afficherLivre_H(LivreH* livre);
void afficherBiblio_H(BiblioH* b);
LivreH* rechercheClef(BiblioH *b,int clef);
void supprimerLivre_H(BiblioH* b, int clef);
BiblioH* fusion(BiblioH* b1,BiblioH* b2);
BiblioH* RecherchePlusieurs_H(BiblioH *b);