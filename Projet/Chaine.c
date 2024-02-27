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
        points=point;
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
    if(!tmp){
        Lchaine=chaine;
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


    Chaines* c =malloc(sizeof(Chaines));
    c->gamma =Gamma;
    c->nbChaines =nbChain;
    c->chaines =NULL; 

    for (int i=0; i<nbChain; i++){
        fgets(buffer, BUFFERSIZE, f);
        int numero, nbPoints;
        sscanf(buffer, "%d %d", &numero, &nbPoints);

        CellChaine* cc =malloc(sizeof(CellChaine));
        cc->numero = numero;
        cc->points = NULL;
        
        double x, y;
        sscanf(buffer,"%*d %*d %lf %lf", &x, &y);

        for (int j=0; j<nbPoints; j++){

            CellPoint* cp =malloc(sizeof(CellPoint));
            cp->x = x;
            cp->y = y;
            cp->suiv = NULL;

            CellPoint* cc_points = cc->points;

            //mettre le point en fin de la liste de CellPoints 
            if (!cc_points){
                cc->points =cp;
            }else{
                CellPoint* tmp = cc->points;
                while (tmp->suiv){
                    tmp = tmp->suiv;
                }
                tmp->suiv = cp;
            }

            sscanf(buffer, "%*f %*f %lf %lf", &x, &y);
        }
        
        //mettre la chaine en fin de la liste de Chaines
        if (!c->chaines){
                c->chaines =cc;
        }else{
                CellChaine* tmp = c->chaines;
                while (tmp->suiv){
                    tmp = tmp->suiv;
                }
                tmp->suiv = cc;
        }
    }
    
    return c;
}