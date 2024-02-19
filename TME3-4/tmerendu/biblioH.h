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
void afficher_livre(LivreH* livre);
void afficher_biblio(BiblioH* b);
LivreH* recherche_par_numero(BiblioH* b, int numero);
LivreH* recherche_par_titre(BiblioH* b, char* titre);
BiblioH* recherche_par_auteur(BiblioH* b, char* auteur);
void suppression_ouvrage(BiblioH* b, int numero, char* auteur, char* titre);
void fusion_biblios(BiblioH* b1, BiblioH* b2);
BiblioH* exemplaires_multiples(BiblioH* b);