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

    // CellChaine *chaines = c->chaines;
    // while (chaines){
    //     CellPoint *points = chaines->points;
    //     while (points){
    //         rechercheCreeNoeudListe(new, points->x, points->y);
    //         points = points->suiv;
    //     }
    //     chaines = chaines->suiv;
    // }

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
        noeudR = noeudR->suiv;
    }
    Noeud *nr = creerNoeud(R->nbNoeuds+1,x,y,NULL);
    R->noeuds=ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
    R->nbNoeuds+=1;
    return nr;
}

Reseau* reconstitueReseauListe(Chaines *C){
    Reseau * reseau=creerReseau(C);
    Noeud * V=NULL; //noeud precedent
    CellChaine * chaines=C->chaines;
    while(chaines){
        CellPoint *points=chaines->points;

        //Noeud *V = NULL;
        while(points){
            //recherche ou crée le noeud correspondant au point
            Noeud *cour = rechercheCreeNoeudListe(reseau, points->x, points->y);
            
            //s'il y a un noeud precedent
            if (V){
                CellNoeud *voisins = creerCellNoeud(cour);
                voisins->suiv = V->voisins; 
                //ajoute le noeud courant aux voisins du noeud precedent
                V->voisins = voisins;
            }

            V = cour; //noeud courant devient noeud precedent

            points = points->suiv;
        }
        chaines = chaines->suiv;
    }
    return reseau;
}