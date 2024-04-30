#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include <stdlib.h>
#include <stdio.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Struct_File.h"


typedef struct{
    int u,v; /* Numeros des sommets extremite */
 }Arete;

typedef struct cellule_arete{
    Arete *a; /* pointeur sur l’arete */ 
    struct cellule_arete* suiv;
 } Cellule_arete;

typedef struct {
    int num; /* Numero du sommet (le meme que dans T_som) */ 
    double x, y;
    Cellule_arete* L_voisin; /* Liste chainee des voisins */ }
Sommet;

typedef struct{
    int e1,e2; /* Les deux extremites de la commodite */
}Commod;

typedef struct{
    int nbsom; /* Nombre de sommets */
    Sommet ** T_som; /* Tableau de pointeurs sur sommets */
    int gamma;
    int nbcommod; /* Nombre de commodites */
    Commod* T_commod; /* Tableau des commodites */ 
} Graphe;

Arete *creer_arete(int u, int v);
Cellule_arete * creer_cellarete(Arete *a);
Sommet *creer_sommet(int num, int x, int y);
Commod *creer_commod(int e1, int e2);
Cellule_arete * ajout_teteCellule_arete(Cellule_arete * ca,Sommet* u,Sommet* v);
void ajout_commod(int e1, int e2, Graphe *g);
void ajout_sommet(int x, int y, int num, Graphe *g);
void insererVoisinsArete(Sommet* u, Sommet* v);
Graphe* creerGraphe(Reseau* r);
void liberer_sommet(Sommet *s);
void liberer_graphe(Graphe *g);
int len(int *tab);
CellChaine* plusCourtChemin(Graphe *g, int u, int v);
void afficherGraphe(Graphe *g);
#endif
