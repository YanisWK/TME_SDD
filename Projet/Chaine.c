#include "Chaine.h"
#include "SVGwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFERSIZE 256

CellPoint *creer_CellPoint(double x,double y){
    CellPoint *new=(CellPoint *)malloc(sizeof(CellPoint));
    new->x=x;
    new->y=y;
    new->suiv=NULL;
    return new;
}

CellChaine *creer_CellChaine(int num,CellPoint *points){

    CellChaine *new=(CellChaine *)malloc(sizeof(CellChaine));
    new->numero=num;
    new->points=points;
    new->suiv=NULL;
    return new;
    }

Chaines *creer_Chaine(int gamma,int nbChaines,CellChaine * chaines){
    Chaines *new=(Chaines*)malloc(sizeof(Chaines));
    new->gamma=gamma;
    new->nbChaines=nbChaines;
    new->chaines=chaines;
    return new;
    }

CellPoint * inserer_finCP(CellPoint *points,double x,double y){
    CellPoint * point=creer_CellPoint(x,y);
    CellPoint * tmp=points;
    if(!tmp){
        points=creer_CellPoint(x,y);
        return points;
    }
    while(tmp->suiv){
        tmp=tmp->suiv;
    }
    tmp->suiv=point;
    return points;
}

CellChaine * inserer_finCC(CellChaine *Lchaine,int num,CellPoint *points){
    CellChaine *chaine=creer_CellChaine(num,points);
    CellChaine *tmp=Lchaine;
    if(tmp==NULL){
        Lchaine=creer_CellChaine(num,points);
        return Lchaine;
    }
    while(tmp->suiv){
        tmp=tmp->suiv;
    }
    tmp->suiv=chaine;
    return Lchaine;
}

int nbPoints(CellPoint * points){
    int nb=0;
    CellPoint* tmp =points;
    while (tmp){
        nb+=1;
        tmp=tmp->suiv; 
    }
    return nb;
}


Chaines* lectureChaines(FILE *f){
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
            points=inserer_finCP(points,x,y);
        }
        //mettre la chaine en fin de la liste de Chaines
        chaines=inserer_finCC(chaines,numero,points);
    }
    Chaines *c=creer_Chaine(Gamma,nbChain,chaines);
    
    return c;
}

void ecrireChaines(Chaines *C, FILE *f){
    if(!f){
        printf("Fichier inexistant.");
        return;
    }
    CellChaine * chainesC = C->chaines;
    int Gamma = C->gamma;
    int nbChaines=C->nbChaines;
    int num;
    int nbPc;
    fscanf(f,"NbChain: %d\n",&nbChaines);
    fscanf(f,"Gamma: %d\n",&Gamma);
    while(chainesC){
        num=chainesC->numero;
        CellPoint *points=chainesC->points;
        nbPc=nbPoints(points);
        fscanf(f,"%d %d ",&num,&nbPc);
        while(points){
            fscanf(f,"%lf %lf ",&points->x,&points->y);
            points=points->suiv;
        }
        fscanf(f,"\n");
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

int comptePointsTotal(Chaines *C){
    int oc=0;
    if (C){
        while (C->chaines){
            while (C->chaines->points){
                CellPoint *actuel = C->chaines->points;
                while (actuel->suiv){
                    CellPoint *compare = actuel->suiv;
                    if (actuel->x == compare->x && actuel->y == compare->y){
                        oc+=1;
                    }
                    compare=compare->suiv;
                }
            }
        }
    }
    return oc;
}