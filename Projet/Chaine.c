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
    int nbPoints;
    fscanf(f,"NbChain: %d\n",nbChaines);
    fscanf(f,"Gamma: %d\n",Gamma);
    while(chainesC){
        num=chainesC->numero;
        nbPoints=chainesC->
        fscanf("%d %d")
    }


}

