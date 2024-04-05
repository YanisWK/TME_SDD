#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "math.h"

void chaineCoordMinMax(Chaines* C,double* xmin,double* ymin,double *xmax,double *ymax){
    CellChaine *courant=C->chaines;
    while(courant){
        CellPoint *points=courant->points;
        while(points){
            double x=points->x;
            double y=points->y;
            if(x<*xmin){
                *xmin=x;
            }if(x>*xmax){
                *xmax=x;
            }
            if(y<*ymin){
                *ymin=y;
            }if(y>*ymax){
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



void insererNoeudArbre(Noeud *n,ArbreQuat ** a,ArbreQuat *parent){
    double pX=n->x;
    double pY=n->y;
    double PcentreX=parent->xc;
    double PcentreY=parent->yc;
    double PcoteX=parent->coteX;
    double PcoteY=parent->coteY;
    
    //cas arbre vide
    if(a==NULL||(*a)==NULL){
        /*Changer les coordonée du centre en faisant l'addition ou la soustraction du quart*/
        if(pX<PcentreX && pY<PcentreY){ //Sud ouest
            parent->so=creerArbreQuat(PcentreX-(PcoteX/4),PcentreY-(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->so->noeud=n;
            (*a)=parent;
        }
        if(pX>=PcentreX && pY<PcentreY){//Sud Est
            parent->se=creerArbreQuat(PcentreX+(PcoteX/4),PcentreY-(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->se->noeud=n;
            (*a)=parent;
        }
        if(pX<PcentreX && pY>=PcentreY){//Nord Ouest
            parent->no=creerArbreQuat(PcentreX-(PcoteX/4),PcentreY+(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->no->noeud=n;
            (*a)=parent;
        }
        if(pX>=PcentreX && pY>=PcentreY){//Nord Est
            parent->ne=creerArbreQuat(PcentreX+(PcoteX/4),PcentreY+(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->ne->noeud=n;
            (*a)=parent;
        }
        
    }else{
        //cas noeud interne

        double acentreX=(*a)->xc;
        double acentreY=(*a)->yc;

        if((*a)->noeud == NULL){
            if(pX<acentreX && pY<acentreY){ //Sud ouest
                insererNoeudArbre(n,&(*a)->so,*a);
            }
            if(pX>=acentreX && pY<acentreY){//Sud Est
                insererNoeudArbre(n,&(*a)->se,*a);
            }
            if(pX<acentreX && pY>=acentreY){//Nord Ouest
                insererNoeudArbre(n,&(*a)->no,*a);
            }
            if(pX>=acentreX && pY>=acentreY){//Nord Est
                insererNoeudArbre(n,&(*a)->ne,*a);
            }
        }else{
            //cas feuille

            /*Nouveau noeud */
            insererNoeudArbre((*a)->noeud,NULL,*a);
            insererNoeudArbre(n,NULL,*a);
            (*a)->noeud=NULL; //PEUT CAUSER UN PROBLEME MEMOIRE
        }
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R,ArbreQuat** a,ArbreQuat *parent ,double x,double y){
    if((*a==NULL)){
        R->noeuds = ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
        R->nbNoeuds+=1;
        insererNoeudArbre(R->noeuds->nd,a,parent);
        return R->noeuds->nd;
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
            R->noeuds=ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
            R->nbNoeuds+=1;
            insererNoeudArbre(R->noeuds->nd,a,parent);
        }
    } 
    return R->noeuds->nd;
}



Reseau* reconstitueReseauArbre(Chaines* C){
    Reseau *reseau = creerReseau(C);
    CellCommodite *commodites =NULL;
    ArbreQuat *a = NULL;
    double xmin=0,xmax=0,ymin=0,ymax=0;
    chaineCoordMinMax(C,&xmin,&xmax,&ymin,&ymax);
    
    ArbreQuat *parent=creerArbreQuat((xmin+xmax)/2,(ymin+ymax)/2,xmax-xmin,ymax-ymin);
    CellChaine * chaines=C->chaines;
    Noeud *extrA=NULL;
    Noeud *extrB=NULL;

    while(chaines){
        CellPoint *points = chaines->points;
        Noeud *V=NULL;
        extrA=rechercheCreeNoeudArbre(reseau,&a,parent,points->x,points->y);
        while (points){
            Noeud *cour = rechercheCreeNoeudArbre(reseau,&a,a,points->x,points->y);
            if (V){
                insererVoisins(V,cour);
                insererVoisins(cour,V);
            }
            V=cour;
            if(!points->suiv){
                extrB=rechercheCreeNoeudArbre(reseau,&a,parent,points->x,points->y);
            }
            points = points->suiv;
        }
        if(!rechercheCommodite(commodites,extrA,extrB)){
            commodites=ajout_teteCellCommodite(commodites,extrA,extrB);
        }
        chaines = chaines->suiv;
    }
    reseau->commodites=commodites;
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