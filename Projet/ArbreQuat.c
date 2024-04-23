#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "math.h"

void chaineCoordMinMax(Chaines* C,double* xmin,double* ymin,double *xmax,double *ymax){
    /* Calcule les coordonnées minimales et maximales des points dans les chaînes.
    
    Paramètres:
    - C : chaînes 
    - xmin, ymin, xmax, ymax : pointeurs vers les coordonnées minimales et maximales
    */    
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
    /* Crée un arbre quaternaire.

    Paramètres:
    - xc, yc : coordonnées du centre de l'arbre
    - coteX, coteY : longueur et largeur de l'arbre
    */
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
    /* Insère un nœud dans un arbre.
    
    Paramètres :
    - n : nœud à insérer 
    - a : pointeur vers l'arbre
    - parent : nœud parent de l'arbre
    */
    double pX=n->x;
    double pY=n->y;
    double PcentreX=parent->xc;
    double PcentreY=parent->yc;
    double PcoteX=parent->coteX;
    double PcoteY=parent->coteY;

    //cas arbre vide
    if((*a)==NULL || a==NULL){
        ArbreQuat *res;
        if(pX<PcentreX && pY<PcentreY){//Sud ouest
            res=creerArbreQuat(PcentreX-(PcoteX/4),PcentreY-(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->so=res;
        }
        if(pX>=PcentreX && pY<PcentreY){//Sud Est
            res=creerArbreQuat(PcentreX+(PcoteX/4),PcentreY-(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->se=res;
        }
        if(pX<PcentreX && pY>=PcentreY){//Nord Ouest
            res=creerArbreQuat(PcentreX-(PcoteX/4),PcentreY+(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->no=res;
        }
        if(pX>=PcentreX && pY>=PcentreY){//Nord Est
            res=creerArbreQuat(PcentreX+(PcoteX/4),PcentreY+(PcoteY/4),(parent->coteX)/2,(parent->coteY)/2);
            parent->ne=res;
        }
        res->noeud=n;
    }else{
        //cas noeud interne

        double acentreX=(*a)->xc;
        double acentreY=(*a)->yc;

        if((*a)->noeud == NULL){
<<<<<<< HEAD
            if(pX<acentreX && pY<acentreY){ //Sud ouest
                insererNoeudArbre(n,&((*a)->so),*a);
=======
            if(pX<acentreX && pY<acentreY){//Sud ouest
                insererNoeudArbre(n,&(*a)->so,*a);
>>>>>>> 052878b6eb173ae7467ce56213b63e4d1bcce0c4
            }
            if(pX>=acentreX && pY<acentreY){//Sud Est
                insererNoeudArbre(n,&((*a)->se),*a);
            }
            if(pX<acentreX && pY>=acentreY){//Nord Ouest
                insererNoeudArbre(n,&((*a)->no),*a);
            }
            if(pX>=acentreX && pY>=acentreY){//Nord Est
                insererNoeudArbre(n,&((*a)->ne),*a);
            }
        }else{
            //cas feuille

            insererNoeudArbre((*a)->noeud,NULL,*a);
            insererNoeudArbre(n,NULL,*a);
            (*a)->noeud=NULL; 
        }
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R,ArbreQuat** a,ArbreQuat *parent ,double x,double y){
<<<<<<< HEAD
    if((*a==NULL)){
        printf("Creer\n");
=======
    /* Recherche ou crée un nœud dans un arbre.
    
    Paramètres:
    - R : réseau de noeuds
    - a : pointeur vers l'arbre 
    - parent : nœud parent de l'arbre 
    - x, y : coordonnées du noeud à rechercher ou à créer
    */
   if((*a==NULL)){
>>>>>>> 052878b6eb173ae7467ce56213b63e4d1bcce0c4
        R->noeuds = ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
        R->nbNoeuds+=1;
        insererNoeudArbre(R->noeuds->nd,a,parent);
        return R->noeuds->nd;
    }
    else if(((*a)->noeud!=NULL)){
        if(((*a)->noeud->x==x && (*a)->noeud->y==y)){
            printf("Trouvé\n");
            return (*a)->noeud;
        }else{
            double acentreX=(*a)->xc;
            double acentreY=(*a)->yc;
            if(x<acentreX && y<acentreY){ //Sud ouest
                return rechercheCreeNoeudArbre(R,&(*a)->so,(*a),x,y);
            }
            if(x>=acentreX && y<acentreY){//Sud Est
                return rechercheCreeNoeudArbre(R,&(*a)->se,(*a),x,y);
            }   
            if(x<acentreX && y>=acentreY){//Nord Ouest
                return rechercheCreeNoeudArbre(R,&(*a)->no,(*a),x,y);
            }
            if(x>=acentreX && y>=acentreY){//Nord Est
                return rechercheCreeNoeudArbre(R,&(*a)->ne,(*a),x,y);
            }
        }
    } 
    else{
        double acentreX=(*a)->xc;
        double acentreY=(*a)->yc;
        if(x<acentreX && y<acentreY){//Sud ouest
            return rechercheCreeNoeudArbre(R,&(*a)->so,(*a),x,y);
        }
        if(x>=acentreX && y<acentreY){//Sud Est
            return rechercheCreeNoeudArbre(R,&(*a)->se,(*a),x,y);
        }   
        if(x<acentreX && y>=acentreY){//Nord Ouest
            return rechercheCreeNoeudArbre(R,&(*a)->no,(*a),x,y);
        }
        if(x>=acentreX && y>=acentreY){//Nord Est
            return rechercheCreeNoeudArbre(R,&(*a)->ne,(*a),x,y);
        }
        
    }
    return R->noeuds->nd; 
}



Reseau* reconstitueReseauArbre(Chaines* C){
    /* Reconstitue un réseau à partir des chaînes avec un arbre.

    Paramètre:
    - C : chaînes
    */
    Reseau *reseau = creerReseau(C);
    CellCommodite *commodites =NULL;
    double xmin=0,xmax=0,ymin=0,ymax=0;
    chaineCoordMinMax(C,&xmin,&xmax,&ymin,&ymax);
    
    ArbreQuat *a=creerArbreQuat((xmin+xmax)/2,(ymin+ymax)/2,xmax-xmin,ymax-ymin);
    //afficherArbreQuat(parent);
    CellChaine * chaines=C->chaines;

    Noeud *extrA=NULL;
    Noeud *extrB=NULL;

    while(chaines){
        CellPoint *points = chaines->points;
        Noeud *V=NULL;
        extrA=rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);
        while (points){
            Noeud *cour = rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);
            if (V){
                insererVoisins(V,cour);
                insererVoisins(cour,V);
            }
            V=cour;
            if(!points->suiv){
                extrB=rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);
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
    /* Libère la mémoire d'un arbre.
    
    Paramètre:
    - a : arbre 
    */
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
    /* Affiche les informations d'un arbre.

    Paramètre:
    - a : arbre
    */
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