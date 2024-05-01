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
            // Coordonnées du premier point de la chaîne actuelle
            double x=points->x; 
            double y=points->y;
            
            // Mettre à jour les coordonnées minimales et maximales si nécessaire
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
        // Détermine la partie dans lequel insérer le nœud en fonction de ses coordonnées et du parent
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
        res->noeud=n; // Assigne le nœud à l'arbre

    }else{
        //cas noeud interne

        double acentreX=(*a)->xc;
        double acentreY=(*a)->yc;

        if((*a)->noeud == NULL){
            // Récursion pour insérer le nœud interne au bon endroit
            if(pX<acentreX && pY<acentreY){ //Sud ouest
                insererNoeudArbre(n,&((*a)->so),*a);
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
            // Insérer le nœud actuel dans l'arbre
            insererNoeudArbre((*a)->noeud,NULL,*a);
            insererNoeudArbre(n,NULL,*a);
            (*a)->noeud=NULL; 
        }
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R,ArbreQuat** a,ArbreQuat *parent ,double x,double y){
    // Cas arbre vide
    if((*a==NULL)){
        // Crée un nouveau nœud et l'ajoute à la tête du réseau
        R->noeuds = ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
        R->nbNoeuds+=1;
        // Insére le nœud dans l'arbre
        insererNoeudArbre(R->noeuds->nd,a,parent);
        return R->noeuds->nd;
    }
    else if(((*a)->noeud!=NULL)){ // Cas feuille
        // Vérifie si le nœud existe déjà
        if(((*a)->noeud->x==x && (*a)->noeud->y==y)){
            
            return (*a)->noeud;
        }else{
            // Cherche ou crée le nœud au bon endroit de manière récursive
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
    else{ // Cas noeud interne
        // Cherche ou crée le nœud au bon endroit de manière récursive
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
    Reseau *reseau = creerReseau(C); // Crée un réseau
    CellCommodite *commodites =NULL; // Initialise la liste des commodités

    double xmin=0,xmax=0,ymin=0,ymax=0; 
    // Calcule les coordonnées minimales et maximales de la lste de chaînes
    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax);
    // Crée un arbre à partir des coordonnées minimales et maximales
    ArbreQuat *a=creerArbreQuat(xmin+(xmin+xmax)/2,ymin+(ymin+ymax)/2,xmax-xmin,ymax-ymin);
    CellChaine * chaines=C->chaines;

    Noeud *extrA=NULL;
    Noeud *extrB=NULL;

    while(chaines){
        CellPoint *points = chaines->points; // tête de la chaîne
        Noeud *V=NULL; // noeud précédent

        // Assigne le premier point à l'extremité de la commodité 
        extrA=rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);
        while (points){        
            // Recherche ou crée les nœuds dans l'arbre pour chaque point de la chaîne
            Noeud *cour = rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);

            //s'il y a un noeud precedent
            if (V){
                insererVoisins(V,cour); // Lie le nœud actuel au nœud précédent en tant que voisins
                insererVoisins(cour,V); // Et inversement
            }
            V=cour; // Met à jour le nœud précédent

            if(!points->suiv){ // Si ce point est le dernier point de la chaîne
                // Recherche ou crée un nœud pour ce point et l'assigne à ExtrB
                extrB=rechercheCreeNoeudArbre(reseau,&a,NULL,points->x,points->y);
            }
            points = points->suiv;
        }
        // Si une commodité entre extrA et extrB n'existe pas déjà,
        // On ajoute cette commodité à la liste des commodités
        if(!rechercheCommodite(commodites,extrA,extrB)){
            commodites=ajout_teteCellCommodite(commodites,extrA,extrB);
        }
        chaines = chaines->suiv;
    }
    reseau->commodites=commodites; // Met à jour les commodités du réseau
    libererArbre(a);
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
    printf("Arbre sud-ouest:");
    afficherArbreQuat(a->so);
    printf("Arbre sud-est:");
    afficherArbreQuat(a->se);
    printf("Arbre nord-ouest:");
    afficherArbreQuat(a->no);
    printf("Arbre nord-est:");
    afficherArbreQuat(a->ne);
}