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

    if(((*a != NULL) && ((*a)->noeud == NULL))){
        if(pX<acentreX && pY<acentreY){ //Sud ouest
            insererNoeudArbre(n,(*a)->so,(*a));
        }
        if(pX>=acentreX && pY<acentreY){//Sud Est
            insererNoeudArbre(n,(*a)->se,(*a));
        }
        if(pX<acentreX && pY>=acentreY){//Nord Ouest
            insererNoeudArbre(n,(*a)->no,(*a));
        }
        if(pX>=acentreX && pY>=acentreY){//Nord Est
            insererNoeudArbre(n,(*a)->ne,(*a));
        }
    }
    if((*a)->noeud!=NULL && ((*a)->noeud!=NULL)){
        /*Nouveau noeud */
        insererNoeudArbre((*a)->noeud,NULL,&(*a));
        insererNoeudArbre(n,NULL,&(*a));
        (*a)->noeud=NULL; //PEUT CAUSER UN PROBLEME MEMOIRE
    }
}

Reseau* reconstitueReseauArbre(Chaines* C){
    Reseau *reseau = creerReseau();
    ArbreQuat *a = NULL;
    CellChaine *chaines = C->chaines;

    while(chaines){
        CellPoint *points = chaines->points;
        while (points){
            Noeud *n = creerNoeud(points->x, points->y);
            insererNoeudArbre(n,&a,NULL);
            points = points->suiv;
        }
        chaines = chaines->suiv;
    }
    return reseau;
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
    if((*a->noeud != NULL) && ((*a)->noeud!=NULL)){
        if(((*a)->noeud->x=x && (*a)->noeud->y=y)){
            return (*a)->noeud;
        }else{
            ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
            R->nbNoeuds+=1;
            insererNoeudArbre(R->noeuds->nd,a,&parent);
        }
    }
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
