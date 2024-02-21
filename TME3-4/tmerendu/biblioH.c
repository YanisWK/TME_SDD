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
    new->num = num;
    new->titre = strdup(titre); 
    new->auteur = strdup(auteur);
    new->suivant = NULL;

    return new;
}


void liberer_livre_H(LivreH *l){
    if (l){
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

BiblioH *creer_biblio_H(int m){
    BiblioH *new = malloc(sizeof(BiblioH));
    if (new == NULL){
        exit(EXIT_FAILURE);
    }

    new->T = (LivreH**)malloc(m * sizeof(LivreH*));
    if (new->T == NULL){
        free(new);  
        exit(EXIT_FAILURE);
    }
    return new;
}

void liberer_biblio_H(BiblioH *b) {
    if (b){
        for (int i = 0; i < b->m; i++){
            LivreH *cour = b->T[i];
            while (cour){
                LivreH* tmp = cour;
                cour = cour->suivant;
                liberer_livre_H(tmp);
            }
        }
    }
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
    printf("Numéro: %d Titre: %s Auteur: %s\n",l->num,l->titre,l->auteur);
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

LivreH* rechercheLivreNum_H(BiblioH *b, int num){
    if (b == NULL){
        return NULL;
    }

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
    if (b == NULL){
        return NULL;
    }

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
    if (b == NULL){
        return NULL;
    }
    
    BiblioH* res = creer_biblio_H(b->m);
    for (int i = 0; i < b->m; i++){
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
    if (b2->m == 0){
        liberer_biblio_H(b2);
        return b1;
    }

    for (int i=0; i<b2->m; i++){
        LivreH* cour = b2->T[i];
        while (cour){
            LivreH* tmp=cour; // on supprime un par un les livres de b2
            cour = cour->suivant;            
            inserer(b1, tmp->num, tmp->titre, tmp->auteur);
        }
    }
    liberer_biblio_H(b2);
    return b1;
}

BiblioH* RecherchePlusieurs_H(BiblioH *b){
    BiblioH* bibliodoublon = creer_biblio_H(b->m);

    for (int i=0; i<b->m; i++){
        LivreH* livreActuel = b->T[i];
        while (livreActuel){
            int trouve = 0;

            for (int j=0; j<bibliodoublon->m; j++){
                LivreH* livreCompare = bibliodoublon->T[j];
                while (livreCompare){
                    if (livreActuel->num == livreCompare->num && strcmp(livreActuel->auteur, livreCompare->auteur) == 0 && strcmp(livreActuel->titre, livreCompare->titre) == 0){
                        trouve = 1;
                        break;
                    }
                    livreCompare = livreCompare->suivant;
                }
                if (trouve) {
                    break;
                }
            }

            if (!trouve) {
                inserer(bibliodoublon, livreActuel->num, livreActuel->titre, livreActuel->auteur);
            }
            livreActuel = livreActuel->suivant;
        }
    }

    return bibliodoublon;
}
