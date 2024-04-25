#include "Graphe.h"
#include "stdio.h"
#include "stdlib.h"

Arete * creer_arete(int u,int v){
    Arete * new=(Arete *)malloc(sizeof(Arete));
    new->u=u;
    new->v=v;
    return new;
}

Sommet * creer_sommet(int num,double x,double y,Cellule_arete * L_voisins){
    Sommet * new=(Sommet *)malloc(sizeof(Sommet));
    new->num=num;
    new->x=x;
    new->y=y;
    new->L_voisin=L_voisins;
    return new;
}

Cellule_arete * creer_Cellulearete(Arete * a){
    Cellule_arete * new=(Cellule_arete *)malloc(sizeof(Cellule_arete));
    new->a=a;
    new->suiv=NULL;
    return new;
}

Cellule_arete * ajout_teteCellule_arete(Cellule_arete * ca,int u,int v){
    Noeud * Arete=creer_arete(u,v);
    Cellule_arete * tete=creer_Cellulearete(Arete);
    tete->suiv=ca;
    ca=tete;
    return ca;
}

Graphe * creer_Graphe(Reseau * r){
    Graphe * graphe=(Graphe *)malloc(sizeof(Graphe));
    graphe->gamma=r->gamma;
    
    int nbsom=0;

    Sommet ** T_som=malloc();
}