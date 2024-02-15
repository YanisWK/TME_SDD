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
    liberer_livre(b->L);
    free(b);
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre *tete=creer_livre(num,titre,auteur);
    tete->suiv=b->L;
    b->L=tete;
}

void affichelivre(Livre *l){
    if (l){
        printf("Numéro : %d\n", l->num);
        printf("Titre : %s\n", l->titre);
        printf("Auteur : %s\n", l->auteur);
    }
}

void affichebiblio(Biblio *b){
    if (b && b->L){
        while (b->L){
            affichelivre(b->L);
            printf("\n");
            b->L = b->L->suiv;
        }
    }
}

Livre *rechnum(Biblio *b, int num){
    while (b->L){
        if (b->L->num == num){
            return b->L;
        }
        b->L = b->L->suiv;
    }
    return NULL;
}

Livre *rechtit(Biblio *b, char * titre){
    while (b->L){
        if (strcmp(b->L->titre, titre) == 0){
            return b->L;
        }
        b->L = b->L->suiv;
    }
    return NULL;
}

Biblio *rechaut(Biblio *b, char *auteur){
    Biblio *res = creer_biblio();
    while (b->L){
        if (strcmp(b->L->auteur, auteur) == 0){
            inserer_en_tete(res, b->L->num, b->L->titre, b->L->auteur);
        }
        b->L = b->L->suiv;
    }
    return res;
}

Biblio* fusion(Biblio *b1, Biblio *b2){
    Livre *cour = b1->L;
    while (cour != NULL && cour->suiv != NULL){
        cour = cour->suiv;
    }

    if (!cour){
        cour->suiv = b2->L;
    }else{
        b1->L = b2->L;
    }

    liberer_biblio(b2);
    return b1;
}
