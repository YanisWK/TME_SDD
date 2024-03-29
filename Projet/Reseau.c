#include "Reseau.h"
#include "SVGwriter.h"
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
    cn=tete;
    return cn;
}

Reseau * creerReseau(Chaines *c){
    Reseau * new=(Reseau *)malloc(sizeof(Reseau));
    new->nbNoeuds = 0;
    new->gamma = c->gamma;
    new->noeuds = NULL;
    new->commodites = NULL;
    return new;
}

CellCommodite * creeCommodite(Noeud * extrA,Noeud * extrB){
    CellCommodite * new=(CellCommodite *)malloc(sizeof(CellCommodite));
    new->extrA=extrA;
    new->extrB=extrB;
    new->suiv=NULL;
    return new;
}

CellCommodite * ajout_teteCellCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
    CellCommodite * tete=creeCommodite(extrA,extrB);
    tete->suiv=commodites;
    return tete;
}

CellCommodite * rechercheCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB){
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
    CellNoeud *noeudR = R->noeuds;
    
    while (noeudR){
        double nX=noeudR->nd->x;
        double nY=noeudR->nd->y;
        if(nX==x && nY==y){
            return noeudR->nd;;
        }    
        noeudR = noeudR->suiv;
    }    

    R->noeuds=ajout_teteCellNoeud(R->noeuds,x,y,R->nbNoeuds+1);
    R->nbNoeuds+=1;
    return R->noeuds->nd;
}

void insererVoisins(Noeud *n1, Noeud *n2){
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
    int cpt=0;
    CellCommodite *com=R->commodites;
    while(com){
        cpt++;
        com=com->suiv;
    }
    return cpt;
}

void ecrireReseau(Reseau *R, FILE *f){
    if(f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }

    fprintf(f,"NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f,"NbLiaisons: %d\n", nbLiaisons(R));
    fprintf(f,"NbCommodites: %d\n", nbCommodites(R));
    fprintf(f,"Gamma: %d\n", R->gamma);

    printf("\n");
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
    while (cn){
        CellNoeud *tmp = cn;
        cn = cn->suiv;
        free(tmp->nd);
        free(tmp);
    }
}

void libererNoeud(Noeud *nd){
    free(nd);
}

void libererCellCommodite(CellCommodite *com){
    while (com){
        CellCommodite *tmp = com;
        com = com->suiv;
        free(tmp);
    }
}

void libererReseau(Reseau *R){
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
