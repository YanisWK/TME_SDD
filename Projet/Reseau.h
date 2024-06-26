#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;


CellNoeud * creerCellNoeud(Noeud *nd);
Noeud * creerNoeud(int num,double x,double y,CellNoeud *voisins);
CellNoeud * ajout_teteCellNoeud(CellNoeud * cn,double x,double y,int num);
Reseau * creerReseau(Chaines *c);
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
CellCommodite * ajout_teteCellCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB);
CellCommodite * rechercheCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB);
void insererVoisins(Noeud *n1, Noeud *n2);

void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
void libererCellNoeud(CellNoeud *cn);
void libererCellCommodite(CellCommodite *com);
void libererReseau(Reseau *R);

Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax);
#endif

