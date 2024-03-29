#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Hachage.h"

#define A (sqrt(5)-1)/2

TableHachage * CreeTableHachage(int tailleMax){
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
    return y + (x + y)*(x + y + 1)/2;
}

int h(int k,int M){
    return((int) (M*((k*A)-(int)(k*A))));
}

CellCommodite * creeCommoditeHachage(Noeud * extrA,Noeud * extrB){
    CellCommodite * new=(CellCommodite *)malloc(sizeof(CellCommodite));
    new->extrA=extrA;
    new->extrB=extrB;
    new->suiv=NULL;
    return new;
}

CellCommodite * ajout_teteCellCommoditeHachage(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
    CellCommodite * tete=creeCommoditeHachage(extrA,extrB);
    tete->suiv=commodites;
    return tete;
}

void insererVoisinsHachage(Noeud *n1, Noeud *n2){
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