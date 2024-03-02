#include "Reseau.h"
#include <stdlib.h>

CellNoeud * creerCellNoeud(Noeud *nd){
    CellNoeud * new=(CellNoeud*)malloc(sizeof(CellNoeud));
    new->nd=nd;
    new->suiv=NULL;
    return new;
}


Noeud * creerNoeud(int num,double x,double y,CellNoeud *voisins){
    Noeud * new=(Noeud *)malloc(sizeof(Noeud));
    new->num=num;
    new->x=x;
    new->y=y;
    new->voisins=voisins;
    return new;
}

CellNoeud * ajout_teteCellNoeud(CellNoeud * cn,double x,double y,int num){
    Noeud * node=creerNoeud(num,x,y,NULL);
    CellNoeud * tete=creerCellNoeud(node);
    tete->suiv=cn;
    return tete;
}

Reseau * creerReseau(Chaines *c){
    Reseau * new=(Reseau *)malloc(sizeof(Reseau));
    new->nbNoeuds = 0;
    new->gamma = c->gamma;
    new->noeuds = NULL;
    new->commodites = NULL;
    return new;
}


Noeud * rechercheCreeNoeudListe(Reseau *R, double x,double y){
    CellNoeud *noeudR =R->noeuds;

    /*Parcourir le reseau et chercher le noeud correspondant sinon le crée*/
    while (noeudR){
        double nX=noeudR->nd->x;
        double nY=noeudR->nd->y;
        if(nX==x && nY==y){
            return noeudR->nd;;
        }
    }
    
    ajout_teteCellNoeud(noeudR,x,y,R->nbNoeuds+1);
    R->nbNoeuds=R->nbNoeuds+1;
    return noeudR->nd;
}

Reseau* reconstitueReseauListe(Chaines *C){
    Reseau * reseau=creerReseau(C);
    Noeud * V=NULL; //noeud precedent
    CellChaine * chaines=C->chaines;
    while(chaines){
        CellPoint *points=chaines->points;

        //Noeud *V = NULL;
        while(points){
            Noeud *cour = rechercheCreeNoeudListe(reseau, points->x, points->y);

            if (V){
                CellNoeud *voisins = creerCellNoeud(cour);
                voisins->suiv = V->voisins; 
                //ajoute le noeud courant aux voisins du noeud precedent
                V->voisins = voisins;
            }

            V = cour;

            points = points->suiv;
        }
        chaines = chaines->suiv;
    }
    return reseau;
}