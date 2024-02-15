#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,char* titre,char* auteur){
    Livre *new= malloc(sizeof(Livre));
    new->num= num;
    new->titre=strdup(titre);
    new->auteur=strdup(auteur);
    new->suiv=NULL;
    return new;
}

void liberer_livre(Livre *l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio *new = malloc(sizeof(Biblio));
    new->L= NULL;
    return new;
}

void liberer_biblio(Biblio* b){
    while(b->L){
        Livre *suiv=b->L->suiv;
        liberer_livre(b->L);
        b->L=suiv;
    }

    free(b);
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre *tete=creer_livre(num,titre,auteur);
    tete->suiv=b->L;
    b->L=tete;
}

void inserer_en_fin(Biblio *b,int num,char* titre,char* auteur){
    Livre *fin=creer_livre(num,titre,auteur);
    while(b->L->suiv){
        b->L->suiv=b->L->suiv->suiv;
    }
    b-L->suiv=fin;
}


void afficheLivre(Livre *l){
    printf("Le livre qui se nomme %s ecris par %s possede le numero %d\n",l->titre,l->auteur,l->num);
}
void afficherBiblio(Biblio *b){
    while(b->L){
        afficheLivre(b->L);
        b->L=b->L->suiv;
    }
}

Livre* rechercheLivreNum(Biblio *b,int num){
    while(b->L){
        if(b->L->num==num){
            return (b->L);
        }
        b->L=b->L->suiv;
    }
    return NULL;
}

Livre* rechercheLivreTitre(Biblio *b,char* titre){
    while(b->L){
        if(strcmp(b->L->titre,titre)==0){
            return(b->L);
        }
        b->L=b->L->suiv;
    }
    return NULL;
}

Biblio* BiblioAuteur(Biblio*b,char* auteur){
    Biblio *BiblioAut=creer_biblio();
    while(b->L){
        if(strcmp(b->L->auteur,auteur)==0){
            inserer_en_tete(BiblioAut,b->L->num,b->L->titre,auteur);
        }
        b->L=b->L->suiv;
    }
    return BiblioAut;
}

Biblio* FusionBiblio(Biblio* b1,Biblio* b2){

    while(b2->L){
        inserer_en_fin(b1,b2->L->num,b2->L->titre,b2->L->auteur);
        Livre* suiv=b2->L->suiv;
        liberer_livre(b2->L);
        b2->L=suiv;
    }
    return b1;
}
