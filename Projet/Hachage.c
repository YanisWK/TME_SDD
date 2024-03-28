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
    
}