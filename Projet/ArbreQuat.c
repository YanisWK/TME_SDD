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



void insererNoeudArbre(Noeud *n,ArbreQuat ** a,ArbreQuat **parent){
    double pX=n->x;
    double pY=n->y;
    double PcentreX=(*parent)->xc;
    double PcentreY=(*parent)->yc;
    if((*a)==NULL){
        if(pX<PcentreX && pY<PcentreY){ //Sud ouest
            (*parent)->so=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->so->noeud=n;
        }
        if(pX>=PcentreX && pY<PcentreY){//Sud Est
            (*parent)->se=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->se->noeud=n;
        }
        if(pX<PcentreX && pY>=PcentreY){//Nord Ouest
            (*parent)->no=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->no->noeud=n;
        }
        if(pX>=PcentreX && pY>=PcentreY){//Nord Est
            (*parent)->ne=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->ne->noeud=n;
        }
        
    }
    double acentreX=(*a)->xc;
    double acentreY=(*a)->yc;
    double anoeudX=(*a)->noeud->x;
    double anoeudY=(*a)->noeud->y;
    if((*a)->noeud!=NULL){
        /*Nouveau noeud */
        insererNoeudArbre((*a)->noeud,NULL,&(*a));
        insererNoeudArbre(n,NULL,&(*a));
        (*a)->noeud=NULL;
    }
    if(((*a != NULL) && ((*a)->noeud == NULL))){
                if(pX<PcentreX && pY<PcentreY){ //Sud ouest
            (*parent)->so=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->so->noeud=n;
        }
        if(pX>=PcentreX && pY<PcentreY){//Sud Est
            (*parent)->se=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->se->noeud=n;
        }
        if(pX<PcentreX && pY>=PcentreY){//Nord Ouest
            (*parent)->no=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->no->noeud=n;
        }
        if(pX>=PcentreX && pY>=PcentreY){//Nord Est
            (*parent)->ne=creerArbreQuat(pX,pY,((*parent)->coteX)/2,((*parent)->coteY)/2);
            (*parent)->ne->noeud=n;
        }
    }
}