#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "biblioH.h"

int fonctionClef(char *auteur){
    int clef = 0,i=0;
    while (*(auteur+i)!='\0'){
        clef += (int)(*(auteur+i));
        i++;
    }
    return clef;
}

LivreH *creer_livre_H(int num, char *titre, char *auteur){
    LivreH *new = malloc(sizeof(LivreH));
    new->clef = fonctionClef(auteur);
    new->suivant = NULL;
    return new;
}


void liberer_livre_H(LivreH *l){
    free(l);
}

BiblioH *creer_biblio_H(int m){
    BiblioH *new = malloc(sizeof(BiblioH));
    new->nE = 0;
    new->m = m;
    new->T = (LivreH**)malloc(m*sizeof(LivreH*));
    for (int i=0; i<m; i++){
        new->T[i] = NULL;
    }
    return new;
}

void liberer_biblio_H(BiblioH *b){
    for (int i=0; i<b->m; i++){
        LivreH *cour = b->T[i];
        while (cour != NULL){
            LivreH *tmp = cour->suivant;
            liberer_livre_H(cour);
            cour = tmp;
        }
    }
    free(b->T);
    free(b);
}

int fonctionHachage(int cle, int m){ 
    //cle est un appel à la fonction fonctionClef de l'auteur recherché
    //renvoie l'indice de la clé dans la table de hachage, où un élément avec cette clé doit être stocké
    return (int)floor(m*(cle*((sqrt(5)-1)/2)-floor(cle*((sqrt(5)-1)/2))));
}

void inserer(BiblioH *b, int num, char *titre, char *auteur){
    int ind=fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* new = creer_livre_H(num, titre, auteur);
    new->suivant = b->T[ind];
    b->T[ind] = new;
    b->nE++; //nb d'éléments+1
}

void afficherLivre_H(LivreH *l){
    printf("Clé : %d Numéro: %d Titre: %s Auteur: %s\n", l->clef,l->num,l->titre,l->auteur);
}

void afficherBiblio_H(BiblioH *b){
    for (int i=0; i<b->m; i++){
        LivreH* cour = b->T[i];
        while (cour){
            afficherLivre_H(cour);
            printf("\n");
            cour = cour->suivant;
        }
    }
}

LivreH* rechercheLivreNum_H(BiblioH *b, int num) {
    for (int i=0; i<b->m; i++){
        LivreH* l=b->T[i];
        while (l){
            if (l->num == num){
                return l;
            }
            l = l->suivant;
        }
    }
    return NULL;
}

LivreH* rechercheLivreTitre_H(BiblioH *b, char *titre){
    for (int i=0; i<b->m; i++){
        LivreH* l = b->T[i];
        while (l){
            if (strcmp(l->titre, titre) == 0){
                return l;
            }
            l = l->suivant;
        }
    }
    return NULL;
}

BiblioH* LivresAuteurs_H(BiblioH *b, char *auteur){
    BiblioH* res = creer_biblio_H(b->m);
    for (int i = 0; i < b;->m; i++){
        LivreH* l = b->T[i];
        while (l){
            if (strcmp(l->auteur, auteur) == 0){
                inserer(res, l->num, l->titre, l->auteur);
            }
            l = l->suivant;
        }
    }
    return res;
}

void supprimerLivre_H(BiblioH *b, int num, char *titre, char *auteur){
    int ind = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* prec = NULL;
    LivreH* cour = b->T[ind];

    while (cour){
        if (cour->num == num && strcmp(cour->titre, titre) == 0 && strcmp(cour->auteur,auteur) == 0){
            if (prec==NULL){ //cas où le livre est en tete de la liste 
                b->T[ind]= cour->suivant;
            }else{
                prec->suivant = cour->suivant;
            }
            liberer_livre_H(cour);
            b->nE--; //diminue le nombre d'elements de 1
            return;
        }
        prec = cour;
        cour = cour->suivant;
    }
}

BiblioH* fusion_H(BiblioH *b1,BiblioH *b2){
    for (int i = 0; i<b2->m; i++){
        LivreH* l = b2->T[i];
        while (l){
            inserer(b1, l->num, l->titre, l->auteur);
            LivreH* tmp = l;
            l = l->suivant;
            free(tmp);
        }
    }
    free(b2->T);
    free(b2);
    return b1;
}

BiblioH* RecherchePlusieurs_H(BiblioH *b){
    return;
}