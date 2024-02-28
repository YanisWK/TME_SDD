#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

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

void inserer_finCP(CellPoint *points,double x,double y){
    CellPoint * point=creer_CellPoint(x,y);
    CellPoint * tmp=points;
    if(!tmp){
        points=creer_CellPoint(x,y);
        return;
    }
    while(tmp->suiv){
        tmp=tmp->suiv;
    }
    tmp->suiv=point;
}

void inserer_finCC(CellChaine *Lchaine,int num,CellPoint *points){
    CellChaine *chaine=creer_CellChaine(num,points);
    CellChaine *tmp=Lchaine;
    if(tmp==NULL){
        Lchaine=creer_CellChaine(num,points);
        return;
    }
    while(tmp->suiv){
        tmp=tmp->suiv;
    }
    tmp->suiv=chaine;
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
        sscanf(buffer, "%d %d %s", &numero, &nbPoints,buffer);
        CellPoint *points=NULL;      
        for (int j=0; j<nbPoints; j++){
            double x, y;
            sscanf(buffer,"%lf %lf %s", &x, &y,buffer);
            //mettre le point en fin de la liste de CellPoints 
            inserer_finCP(points,x,y);
        }
        //mettre la chaine en fin de la liste de Chaines
        inserer_finCC(chaines,numero,points);
    }
    Chaines *c=creer_Chaine(Gamma,nbChain,chaines);
    
    return c;
}