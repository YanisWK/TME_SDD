#include "Chaine.h"
#include "SVGwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFERSIZE 256

CellPoint *creer_CellPoint(double x,double y){
    /*Crée une cellule de point de coordonnées x et y.
    
    Paramètres :
    - x,y : coordonnées 
    */
    CellPoint *new=(CellPoint *)malloc(sizeof(CellPoint));
    new->x=x;
    new->y=y;
    new->suiv=NULL;
    return new;
}

CellChaine *creer_CellChaine(int num,CellPoint *points){
    /*Crée une cellule de chaîne.

    Paramètres :
    - num : numéro de la chaîne
    - points : pointeur vers une liste de points
    */
    CellChaine *new=(CellChaine *)malloc(sizeof(CellChaine));
    new->numero=num;
    new->points=points;
    new->suiv=NULL;
    return new;
    }

Chaines *creer_Chaine(int gamma,int nbChaines,CellChaine * chaines){
    /*Insère un point en tête d'une liste de points.
    
    Paramètres :
    - gamma : nombre maximal de fibres par cable
    - nbChaines : nombre de chaines
    - chaines : liste de chaines
    */
    Chaines *new=(Chaines*)malloc(sizeof(Chaines));
    new->gamma=gamma;
    new->nbChaines=nbChaines;
    new->chaines=chaines;
    return new;
    }



CellPoint * inserer_teteCP(CellPoint *points,double x,double y){
    /*Insère un  point en tête d'une liste de points.
    Paramètres :
    - points : liste de points
    - x,y : coordonnées du point
    */
    CellPoint * point=creer_CellPoint(x,y);
    point->suiv=points;
    return point;
}

CellChaine * inserer_teteCC(CellChaine *Lchaine,int num,CellPoint *points){
    /*Insère une  chaîne en tête d'une liste de chaînes.
    paramètres :
    - Lchaine : liste de chaines
    - num : numéro de la chaine
    - points : liste de points de la chaine
    */
    CellChaine *chaine=creer_CellChaine(num,points);
    chaine->suiv=Lchaine;
    return chaine;
}

int nbPoints(CellPoint * points){
    /*Calcule le nombre de points dans une liste de points.
    
    Paramètre :
    - points : liste de points
    */
    int nb=0;
    CellPoint* tmp =points;
    while (tmp){
        nb+=1;
        tmp=tmp->suiv; 
    }
    return nb;
}


Chaines* lectureChaines(FILE *f){
    /*Lit les chaînes d'un fichier et les stocke dans une structure Chaines.*/
    if(f==NULL){
        return NULL;
    }
    char buffer[BUFFERSIZE];
    fgets(buffer,BUFFERSIZE,f);
    int nbChain;
    int Gamma;
    sscanf(buffer,"NbChain: %d",&nbChain);
    fgets(buffer,BUFFERSIZE,f);
    sscanf(buffer,"Gamma: %d",&Gamma);

    CellChaine * chaines=NULL;
    for (int i=0; i<nbChain; i++){
        fgets(buffer, BUFFERSIZE, f);
        int numero, nbPoints;
        sscanf(buffer, "%d %d %[^\n]", &numero, &nbPoints,buffer);
        CellPoint *points=NULL;      
        for (int j=0; j<nbPoints; j++){
            double x, y;
            sscanf(buffer,"%lf %lf %[^\n]", &x, &y,buffer);
            //mettre le point en fin de la liste de CellPoints 
            points=inserer_teteCP(points,x,y);
        }
        //mettre la chaine en fin de la liste de Chaines
        chaines=inserer_teteCC(chaines,numero,points);
    }
    Chaines *c=creer_Chaine(Gamma,nbChain,chaines);
    
    return c;
}

void ecrireChaines(Chaines *C, FILE *f){
    /*Écrit les données d'une structure de chaînes dans un fichier.*/
    if(!f){
        printf("Fichier inexistant.");
        return;
    }
    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
    CellChaine * chainesC = C->chaines;
    while(chainesC){
        fprintf(f, "%d %d", chainesC->numero, nbPoints(chainesC->points));
        CellPoint *points=chainesC->points;
        while(points){
            fprintf(f, " %.2f %.2f", points->x, points->y);
            points=points->suiv;
        }
        fprintf(f, "\n");
        chainesC=chainesC->suiv;
    }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

double longueurChaine(CellChaine *c){
    /*Calcule la longueur d'une chaîne.*/
    double distance;
    CellPoint * points=c->points;
    while(points->suiv){
        double xA=points->x;
        double yA=points->y;
        double xB=points->suiv->x;
        double yB=points->suiv->y;
        distance+=sqrt(pow(xB-xA,2)+pow(yB-yA,2));
        points=points->suiv;
    }
    return distance;
}


double longueurTotale(Chaines *C){
    /*Calcule la longueur totale de toutes les chaînes.*/
    double distanceTot;
    CellChaine * chaines=C->chaines;
    while(chaines){
        distanceTot+=longueurChaine(chaines);
        chaines=chaines->suiv;
    }
    return distanceTot;
}


int comptePointsTotal(Chaines *C){
    /*Compte le nombre total d'occurences de points d'une structure de chaines.*/
    int oc=0;
    CellChaine *chaines = C->chaines;
    
    if (C){
        //parcourt toutes les chaines 
        while (chaines){
            CellPoint *pointactuel = chaines->points;
            //parcourt tous les points de la chaine courante
            while (pointactuel){
                CellChaine *chainecour = C->chaines;
                //parcourt toutes les chaines à comparer
                while (chainecour){
                    if (chainecour->numero != chaines->numero){
                        CellPoint *pointcompare = chainecour->points;
                        //parcourt tous les points de la chaine à comparer
                        while (pointcompare){
                            if (pointactuel->x == pointcompare->x && pointactuel->y == pointcompare->y){
                                    oc+=1;
                                    break;
                            }     
                            pointcompare=pointcompare->suiv;
                        }
                    }
                    chainecour=chainecour->suiv;
                    
                }
                pointactuel = pointactuel->suiv;
            } 
            chaines=chaines->suiv;
        }
    }
    return oc;
}

void libererChaines(Chaines *c){
    /* Libère la mémoire d'une structure de chaines.*/
    CellChaine *chaine = c->chaines;
    while (chaine){
        CellPoint *point = chaine->points;
        while (point){
            CellPoint *tmp = point;
            point = point->suiv;
            free(tmp);
        }
        CellChaine *tmpchaine = chaine;
        chaine = chaine->suiv;
        free(tmpchaine);
    }
    free(c);
}