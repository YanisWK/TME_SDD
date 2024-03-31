#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Hachage.h"

#define A (sqrt(5)-1)/2

TableHachage * CreeTableHachage(int tailleMax){
    /*Crée une nouvelle table de hachage avec une taille maximale donnée.

    Paramètre :
    - tailleMax : taille maximale de la table de hachage
    */
    TableHachage *Table = (TableHachage *)malloc(sizeof(TableHachage));
    Table->nbElement=0;
    Table->tailleMax=tailleMax;
    Table->T=malloc(sizeof(CellNoeud *)*tailleMax);
    for(int i=0;i<tailleMax;i++){
        Table->T[i]=NULL;
    }
    return Table;
}

int f(int x, int y){
    /* Calcule la clé de hachage pour un point donné.

    Paramètres :
    - x,y : coordonnées du point
    */
    return y + (x + y)*(x + y + 1)/2;
}

int h(int k,int M){
    /*Fonction de hachage pour une table de hachage de taille M.
    Retourne la position dans la table de hachage calculée à partir de la clé k et de la taille M.

    Paramètres :
    - k : clé de hachage.
    - M : taille de la table de hachage.
    */
    return((int) (M*((k*A)-(int)(k*A))));
}

CellCommodite * creeCommoditeHachage(Noeud * extrA,Noeud * extrB){
    /*Crée une nouvelle commodité entre les deux nœuds aux extremités d'une chaîne.

    Paramètres :
    - extrA, extrB : premier et dernier nœuds de la commodité
    */
    CellCommodite * new=(CellCommodite *)malloc(sizeof(CellCommodite));
    new->extrA=extrA;
    new->extrB=extrB;
    new->suiv=NULL;
    return new;
}

CellCommodite * ajout_teteCellCommoditeHachage(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
    /*Ajoute une nouvelle commodité en tête de la liste de commodités.

    Paramètres :
    - commodites : liste de commodités existante
    - extrA, extrB : premier et dernier nœuds de la commodité
    */
    CellCommodite * tete=creeCommoditeHachage(extrA,extrB);
    tete->suiv=commodites;
    return tete;
}

void insererVoisinsHachage(Noeud *n1, Noeud *n2){
    /*Insère un nœud voisin à la liste des voisins d'un nœud.

    Paramètres :
    - n1 : nœud auquel ajouter un voisin
    - n2 : nœud voisin à ajouter
    */
    CellNoeud *p1= n1->voisins;
    while (p1){
        if(p1->nd==n2){
            return;
        }
        p1=p1->suiv;
    }
    CellNoeud *new=malloc(sizeof(CellNoeud));
    new->nd=n2;
    new->suiv= n1->voisins;
    n1->voisins=new;
}

Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage *H,double x,double y){
    /*Recherche un nœud dans la table de hachage et le crée s'il n'existe pas encore.

    Paramètres :
    - R : réseau dans lequel ajouter le nœud
    - H : table de hachage du noeud à rechercher
    - x, y : coordonnées du nœud
    */
    int k=f(x,y);
    int pos=h(k,H->tailleMax);
    CellNoeud *cour = H->T[pos];
    while (cour != NULL) {
        if (cour->nd->x == x && cour->nd->y == y) {
            return cour->nd; 
        }
        cour = cour->suiv;
    }

    Noeud * nd=creerNoeud(H->nbElement+1,x,y,NULL);
    CellNoeud *cn =creerCellNoeud(nd);
    cn->suiv = H->T[pos];
    H->T[pos] = cn;
    H->nbElement += 1;
    cn->suiv = R->noeuds;
    R->noeuds = cn;
    R->nbNoeuds = R->nbNoeuds + 1;
    return nd;
}

Reseau * reconstitueReseauHachage(Chaines *C,int M){
    /*Reconstitue un réseau en utilisant une table de hachage pour accélérer le processus.

    Paramètres :
    - C : liste des chaînes pour reconstituer le réseau
    - M : taille de la table de hachage
    */
    Reseau * R=creerReseau(C);
    TableHachage *H=CreeTableHachage(M);
    CellCommodite * commodites=NULL;
    CellChaine * chaines=C->chaines;
    Noeud *ExtrA=NULL;
    Noeud *ExtrB=NULL;

    while(chaines){
        CellPoint *points=chaines->points;
        Noeud * V=NULL;
        ExtrA=rechercheCreeNoeudHachage(R,H,points->x,points->y);
        while(points){
            Noeud *cour=rechercheCreeNoeudHachage(R,H,points->x,points->y);
            if(V){
                insererVoisins(V,cour);
                insererVoisins(cour,V);
            }
            V=cour;
            if(!points->suiv){
                ExtrB=rechercheCreeNoeudHachage(R,H,points->x,points->y);
            }
            points = points->suiv;
        }
        if(ExtrA && ExtrB && ExtrA != ExtrB){
            commodites=ajout_teteCellCommoditeHachage(commodites,ExtrA,ExtrB);
        }
        chaines = chaines->suiv;
    }
    R->commodites=commodites;
    return R;
}