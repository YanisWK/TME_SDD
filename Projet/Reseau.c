#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <time.h>

CellNoeud * creerCellNoeud(Noeud *nd){
    /*Crée une cellule avec le noeud donné.

    Paramètre :
    - nd : nœud à ajouter à la cellule.
    */
    CellNoeud * new=(CellNoeud*)malloc(sizeof(CellNoeud));
    new->nd=nd;
    new->suiv=NULL;
    return new;
}


Noeud * creerNoeud(int num,double x,double y,CellNoeud *voisins){
    /*Crée un nœud.

    Paramètres :
    - num : numéro du nœud
    - x,y : coordonnées du nœud
    - voisins : liste des voisins du nœud
    */
    Noeud * new=(Noeud *)malloc(sizeof(Noeud));
    new->num=num;
    new->x=x;
    new->y=y;
    new->voisins=voisins;
    return new;
}

CellNoeud * ajout_teteCellNoeud(CellNoeud * cn,double x,double y,int num){
    /*Ajoute un nœud en tête d'une liste de cellules de nœuds

    Paramètres :
    - cn : liste de cellules de nœuds
    - num : numéro du nœud
    - x,y : coordonnées du nœud
    - voisins : liste des voisins du nœud
    */
    Noeud * node=creerNoeud(num,x,y,NULL);
    CellNoeud * tete=creerCellNoeud(node);
    tete->suiv=cn;
    cn=tete;
    return cn;
}

Reseau * creerReseau(Chaines *c){
    /*Crée un réseau à partir d'une structure de chaînes donnée

    Paramètre :
    - c : chaînes 
    */
    Reseau * new=(Reseau *)malloc(sizeof(Reseau));
    new->nbNoeuds = 0;
    new->gamma = c->gamma;
    new->noeuds = NULL;
    new->commodites = NULL;
    return new;
}

CellCommodite * creeCommodite(Noeud * extrA,Noeud * extrB){
    /*Crée une commodité à partir de deux nœuds donnés.

    Paramètres :
    - extrA, extrB : premier et dernier noeuds de la commodité
   */
    CellCommodite * new=(CellCommodite *)malloc(sizeof(CellCommodite));
    new->extrA=extrA;
    new->extrB=extrB;
    new->suiv=NULL;
    return new;
}

CellCommodite * ajout_teteCellCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
    /*Ajoute une nouvelle commodité en tête d'une liste de commodités.

    Paramètres :
    - commodites : liste de commodités
    - extrA, extrB : premier et dernier noeuds de la commodité
    */
    CellCommodite * tete=creeCommodite(extrA,extrB);
    tete->suiv=commodites;
    return tete;
}

CellCommodite * rechercheCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
    /*Recherche une commodité dans une liste de commodités à partir de ses deux nœuds.

    Paramètres :   
    - commodites : liste de commodités
    - extrA, extrB : premier et dernier noeuds de la commodité 
    */
    CellCommodite * cour=commodites;
    while(cour){
        if(cour->extrA==extrA && cour->extrB==extrB){
            return cour;
        }
        cour=cour->suiv;
    }
    return NULL;
}



Noeud * rechercheCreeNoeudListe(Reseau *R, double x,double y){
    /*Recherche ou crée un nœud dans un réseau à partir de ses coordonnées.

    Paramètres :
    - R : réseau dans lequel rechercher ou créer le nœud
    - x,y : coordonnée x du nœud
    */
    CellNoeud *noeudR = R->noeuds;
    
    while (noeudR){
        if(noeudR->nd->x==x && noeudR->nd->y==y){
            return noeudR->nd;;
        }    
        noeudR = noeudR->suiv;
    }    

    R->noeuds=ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
    R->nbNoeuds+=1;
    return R->noeuds->nd;
}

void insererVoisins(Noeud *n1, Noeud *n2){
    /*Insère deux nœuds comme voisins l'un de l'autre.

    Paramètres :
    - n1, n2 : nœuds voisins
    */
    CellNoeud *p1= n1->voisins;
    while (p1){
        if(p1->nd==n2){
            return;
        }
        p1=p1->suiv;
    }
    CellNoeud *new=malloc(sizeof(CellNoeud));
    new->nd=n2;
    new->suiv= n1->voisins;
    n1->voisins=new;
}

Reseau* reconstitueReseauListe(Chaines *C){
    /*Reconstitue un réseau à partir d'une structure de chaînes donnée.

    Paramètre :
    - C : chaînes
    */
    Reseau * reseau=creerReseau(C);
    CellCommodite * commodites=NULL;
    CellChaine * chaines=C->chaines;
    Noeud *extrA=NULL;
    Noeud *extrB=NULL;
    while(chaines){
        CellPoint *points=chaines->points;    
        Noeud * V=NULL; //noeud precedent

        extrA=rechercheCreeNoeudListe(reseau,points->x,points->y);
        while(points){
            //recherche ou crée le noeud correspondant au point
            Noeud *cour = rechercheCreeNoeudListe(reseau, points->x, points->y);
            
            //s'il y a un noeud precedent
            if (V){
                insererVoisins(V,cour);
                insererVoisins(cour,V);
            }

            V = cour; //noeud courant devient noeud precedent
            
            if(!points->suiv){
                extrB=rechercheCreeNoeudListe(reseau,points->x,points->y);
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

int nbLiaisons(Reseau *R){
    /*Compte le nombre de liaisons dans un réseau.

    Paramètre :
    - R : réseau
    */
    int cpt=0;
    CellNoeud *noeud=R->noeuds;
    while(noeud){
        CellNoeud *voisins=noeud->nd->voisins;
        while(voisins){
            cpt++;
            voisins=voisins->suiv;
        }
        noeud=noeud->suiv;
    }
    return cpt/2;
}

int nbCommodites(Reseau *R){
    /*Compte le nombre de commodités dans un réseau.

    Paramètre :
    - R : réseau
    */
    int cpt=0;
    CellCommodite *com=R->commodites;
    while(com){
        cpt++;
        com=com->suiv;
    }
    return cpt;
}

void ecrireReseau(Reseau *R, FILE *f){
    /*Écrit le contenu d'un réseau dans un fichier.

    Paramètres :
    - R : réseau
    - f : pointeur vers le fichier
    */
    if(f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }

    fprintf(f,"NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f,"NbLiaisons: %d\n", nbLiaisons(R));
    fprintf(f,"NbCommodites: %d\n", nbCommodites(R));
    fprintf(f,"Gamma: %d\n", R->gamma);

    fprintf(f,"\n");
    CellNoeud *noeud = R->noeuds;
    while(noeud){
        fprintf(f,"v %d %.6lf %.6lf\n", noeud->nd->num, noeud->nd->x, noeud->nd->y);
        noeud = noeud->suiv;
    }

    fprintf(f,"\n");
    
    CellNoeud *liaison = R->noeuds;
    while(liaison){
        CellNoeud *voisin = liaison->nd->voisins;
        while(voisin){
            if(liaison->nd->num < voisin->nd->num){
                fprintf(f,"l %d %d\n", liaison->nd->num, voisin->nd->num);
            }
            voisin=voisin->suiv;
        }
        liaison = liaison->suiv;
    }

    fprintf(f,"\n");

    CellCommodite *com = R->commodites;
    while(com){
        fprintf(f,"k %d %d\n", com->extrA->num, com->extrB->num);
        com = com->suiv;
    }
}

void libererCellNoeud(CellNoeud *cn){
    /*Libère la mémoire allouée pour une liste de cellules de nœuds.

    Paramètre :
    - cn : liste de cellules de nœuds
    */
    while (cn){
        CellNoeud *tmp = cn;
        cn = cn->suiv;
        free(tmp->nd);
        free(tmp);
    }
}

void libererCellCommodite(CellCommodite *com){
    /*Libère la mémoire allouée pour une liste de commodités.

    Paramètre :
    - com : liste de commodités
    */
    while (com){
        CellCommodite *tmp = com;
        com = com->suiv;
        free(tmp);
    }
}

void libererReseau(Reseau *R){
    /*Libère la mémoire allouée pour un réseau, ses nœuds et ses commodités.

    Paramètre :
    - R : réseau à libérer.
    */
    libererCellNoeud(R->noeuds);
    libererCellCommodite(R->commodites);
    free(R);
}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax){
    Chaines* c = malloc(sizeof(Chaines));
    c->gamma = rand()%(10)-1;
    c->nbChaines = nbChaines;
    c->chaines = NULL;
    //srand(time(NULL));
    for(int i=0;i<nbChaines;i++){        
        CellChaine* new = malloc(sizeof(CellChaine));
        new->numero = i;
        new->points = NULL;
        for (int j = 0; j < nbPointsChaine; j++){
            CellPoint* point = malloc(sizeof(CellPoint));
            point->x = rand()%(xmax);
            point->y = rand()%(ymax);
            //printf("x : %lf , y : %lf\n",point->x,point->y);
            point->suiv = new->points;
            new->points = point;
        }
        new->suiv = c->chaines;
        c->chaines = new;
    }
    return c;
}
