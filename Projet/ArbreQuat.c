#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"

void chaineCoordMinMax(Chaines* C,double* xmin,double* ymin,double *xmax,double *ymax){
    CellChaine *courant=C->chaines;
    while(courant){
        CellPoint *points=courant->points;
        while(points){
            double x=points->x;
            double y=points->y;
            if(x<(*xmin)){
                *xmin=x;
            }else if(x>(*xmax)){
                *xmax=x;
            }
            if(y<(*ymin)){
                *ymin=y;
            }else if(y>(*ymax)){
                *ymax=y;
            }
            points=points->suiv;
        }
        courant=courant->suiv;
    }
}

ArbreQuat* creerArbreQuat(double xc,double yc,double coteX,double coteY){
    ArbreQuat *abr=(ArbreQuat *)malloc(sizeof(ArbreQuat));
    abr->xc=xc;
    abr->yc=yc;
    abr->coteX=coteX;
    abr->coteY=coteY;
    abr->noeud=NULL;
    abr->no=NULL;
    abr->ne=NULL;
    abr->se=NULL;
    abr->so=NULL;
    return abr;
}



void insererNoeudArbre(Noeud *n, ArbreQuat **a, ArbreQuat **parent) {
    double pX = n->x;
    double pY = n->y;
    double PcentreX = (*parent)->xc;
    double PcentreY = (*parent)->yc;

    ArbreQuat *tmpParent = *parent; // Pointeur temporaire pour le parent
    ArbreQuat **tmpA = a; // Pointeur temporaire pour l'arbre

    //cas arbre vide
    if ((*tmpA) == NULL) {
        if (pX < PcentreX && pY < PcentreY) { // Sud ouest
            tmpParent->so = creerArbreQuat(pX, pY, (tmpParent->coteX) / 2, (tmpParent->coteY) / 2);
            tmpParent->so->noeud = n;
            (*tmpA) = tmpParent;
        }
        if (pX >= PcentreX && pY < PcentreY) { // Sud Est
            tmpParent->se = creerArbreQuat(pX, pY, (tmpParent->coteX) / 2, (tmpParent->coteY) / 2);
            tmpParent->se->noeud = n;
            (*tmpA) = tmpParent;
        }
        if (pX < PcentreX && pY >= PcentreY) { // Nord Ouest
            tmpParent->no = creerArbreQuat(pX, pY, (tmpParent->coteX) / 2, (tmpParent->coteY) / 2);
            tmpParent->no->noeud = n;
            (*tmpA) = tmpParent;
        }
        if (pX >= PcentreX && pY >= PcentreY) { // Nord Est
            tmpParent->ne = creerArbreQuat(pX, pY, (tmpParent->coteX) / 2, (tmpParent->coteY) / 2);
            tmpParent->ne->noeud = n;
            (*tmpA) = tmpParent;
        }
    }

    // cas noeud interne
    double acentreX = (*tmpA)->xc;
    double acentreY = (*tmpA)->yc;

    if (((*tmpA) != NULL) && ((*tmpA)->noeud == NULL)) {
        if (pX < acentreX && pY < acentreY) { // Sud ouest
            insererNoeudArbre(n, &((*tmpA)->so), tmpA);
        }
        if (pX >= acentreX && pY < acentreY) { // Sud Est
            insererNoeudArbre(n, &((*tmpA)->se), tmpA);
        }
        if (pX < acentreX && pY >= acentreY) { // Nord Ouest
            insererNoeudArbre(n, &((*tmpA)->no), tmpA);
        }
        if (pX >= acentreX && pY >= acentreY) { // Nord Est
            insererNoeudArbre(n, &((*tmpA)->ne), tmpA);
        }
    }

    // cas feuille
    if ((*tmpA)->noeud != NULL) {
        /* Nouveau noeud */
        Noeud *ancienNoeud = (*tmpA)->noeud;
        insererNoeudArbre(ancienNoeud, tmpA, parent); // réinsère le nœud actuel
        insererNoeudArbre(n, tmpA, parent); // insère le nouveau nœud
        (*tmpA)->noeud = NULL; // PEUT CAUSER UN PROBLEME MEMOIRE
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R,ArbreQuat** a,ArbreQuat *parent ,double x,double y){
    if((*a==NULL)){
        ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
        R->nbNoeuds+=1;
        insererNoeudArbre(R->noeuds->nd,a,&parent);
    }
    if(((*a != NULL) && ((*a)->noeud == NULL))){
        double acentreX=(*a)->xc;
        double acentreY=(*a)->yc;
        if(x<acentreX && y<acentreY){ //Sud ouest
            rechercheCreeNoeudArbre(R,&(*a)->so,(*a),x,y);
        }
        if(x>=acentreX && y<acentreY){//Sud Est
            rechercheCreeNoeudArbre(R,&(*a)->se,(*a),x,y);
        }   
        if(x<acentreX && y>=acentreY){//Nord Ouest
            rechercheCreeNoeudArbre(R,&(*a)->no,(*a),x,y);
        }
        if(x>=acentreX && y>=acentreY){//Nord Est
            rechercheCreeNoeudArbre(R,&(*a)->ne,(*a),x,y);
        }
    }
    if(((*a)->noeud != NULL) && ((*a)->noeud!=NULL)){
        if(((*a)->noeud->x==x && (*a)->noeud->y==y)){
            return (*a)->noeud;
        }else{
            ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
            R->nbNoeuds+=1;
            insererNoeudArbre(R->noeuds->nd,a,&parent);
        }
    } 
    return R->noeuds->nd;
}

Reseau* reconstitueReseauArbre(Chaines* C){
    Reseau *reseau = creerReseau(C);
    ArbreQuat *a = NULL;
    CellChaine *chaines = C->chaines;
    while(chaines){
        CellPoint *points = chaines->points;
        while (points){
            Noeud *n = rechercheCreeNoeudArbre(reseau,&a,a,points->x,points->y);
            insererNoeudArbre(n,&a,NULL);
            points = points->suiv;
        }
        chaines = chaines->suiv;
    }
    return reseau;
}


void libererArbre(ArbreQuat *a){
    if (!a) return;
    libererArbre(a->so);
    libererArbre(a->se);
    libererArbre(a->no);
    libererArbre(a->ne);
    if (a->noeud){
        free(a->noeud);
    }
    free(a);
}

void afficherArbreQuat(ArbreQuat *a){
    if (a == NULL){
        return;
    }
    printf("Noeud: (%lf, %lf)\n", a->xc, a->yc);
    printf("Arbre sud-ouest:\n");
    afficherArbreQuat(a->so);
    printf("Arbre sud-est:\n");
    afficherArbreQuat(a->se);
    printf("Arbre nord-ouest:\n");
    afficherArbreQuat(a->no);
    printf("Arbre nord-est:\n");
    afficherArbreQuat(a->ne);
}