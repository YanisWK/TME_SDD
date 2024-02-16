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


void afficherLivre(Livre *l){
    if (l){
        printf("Numéro : %d\n", l->num);
        printf("Titre : %s\n", l->titre);
        printf("Auteur : %s\n", l->auteur);
    }
}

void afficherBiblio(Biblio *b){
    Livre *cour = b->L; 
    while (cour){
        afficherLivre(cour);
        printf("\n");
        cour = cour->suiv;
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


void supprimerLivre(Biblio* b, int num, char* titre, char* auteur){
    Livre* prec = NULL, * cour = b->L;

    while (cour){
        if (cour->num == num && strcmp(cour->titre, titre) == 0 && strcmp(cour->auteur, auteur) == 0){
            if (!prec){
                b->L = cour->suiv;
            }else{
                prec->suiv = cour->suiv;
            }
            liberer_livre(cour);
            return;
        }
        prec = cour;
        cour = cour->suiv;
    }
}

Biblio* fusion(Biblio *b1, Biblio *b2){
    Biblio *b3 = creer_biblio();

    Livre *cour1 = b1->L;
    Livre *cour2 = b2->L;

    while (cour2){
        inserer_en_tete(b3, cour2->num, cour2->titre, cour2->auteur);
        cour2 = cour2->suiv;
    }

    while (cour1 != NULL){
        inserer_en_tete(b3, cour1->num, cour1->titre, cour1->auteur);
        cour1 = cour1->suiv;
    }
    return b3;
}

Biblio* RecherchePlusieurs(Biblio* b) {
    Biblio* Bibliodoublon = creer_biblio();
    Livre* Livreactuel = b->L;

    while (Livreactuel) {
        Livre* Livrecompare = b->L;
        while (Livrecompare) {
            if (Livreactuel->num != Livrecompare->num && strcmp(Livreactuel->auteur, Livrecompare->auteur) == 0 &&
                strcmp(Livreactuel->titre, Livrecompare->titre) == 0){
                inserer_en_tete(Bibliodoublon, Livreactuel->num, Livreactuel->titre, Livreactuel->auteur);
                break;
            }
            Livrecompare = Livrecompare->suiv;
        }
        Livreactuel = Livreactuel->suiv;
    }
    return Bibliodoublon;
}
