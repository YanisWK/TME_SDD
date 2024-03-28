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
    return y + (x + y)(x + y + 1)/2;
}

int h(int k,int M){
    return((int) (M*((k*A)-(int)(k*A))) );
}


Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage *H,double x,double y){
    int k=f(x,y);
    int pos=h(k,H->tailleMax);
    if(H->T[pos]!=NULL){
        return H->T[pos];
    }
    Noeud * nd=creerNoeud(H->nbElement+1,x,y,NULL);
    CellNoeud *cn =creerCellNoeud(nd);
    H->T[pos]=cn;
    H->nbElement+=1;
    cn->suiv=R->noeuds;
    R->noeuds=cn;
    R->nbNoeuds=R->nbNoeuds+1;
    return H->T[pos];
}

Reseau * reconstitueReseauHachage(Chaines *C,int M){
    Reseau * R=creerReseau(C);
    TableHachage *H=CreeTableHachage(M);
    CellCommodite * commodites=NULL;
    Noeud * V=NULL;
    CellChaine * chaines=C->chaines;
    Noeud *ExtrA=NULL;
    Noeud *ExtrB=NULL;

    while(chaines){
        CellPoint *points=chaines->points;
        ExtrA=rechercheCreeNoeudHachage(R,H,points->x,points->y);
        while(points){
            Noeud *cour=rechercheCreeNoeudHachage(R,H,points->x,points->y);
            if(V){
                insererVoisins(V,cour);
                CellCommodite *pcom = malloc(sizeof(CellCommodite));
                pcom->extrA = V;
                pcom->extrB = cour;
                pcom->suiv = reseau->commodites;
                reseau->commodites = pcom;
            }
            V=cour;
            if(!points->suiv){
                ExtrB=rechercheCreeNoeudHachage(R,H,points->x,points->y);
            }
            points = points->suiv;
        }
        if(!rechercheCommodite(commodites,ExtrA,ExtrB)){
            commodites=ajout_teteCellCommodite(commodites,ExtrA,ExtrB);
        }
        chaines = chaines->suiv;
        }
        R->commodites=commodites;
        return R;
}

