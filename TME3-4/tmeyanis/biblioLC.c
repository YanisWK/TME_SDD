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



void afficheLivre(Livre *l){
    printf("Le livre qui se nomme %s ecris par %s possede le numero %d\n",l->titre,l->auteur,l->num);
}
void afficherBiblio(Biblio *b){
    Biblio *courant=b;
    while(b->L){
        afficheLivre(courant->L);
        courant->L=courant->L->suiv;
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

Biblio* RecherchePlusieurs(Biblio *b){
    /*Je vais faire deux boucle while, la premiere sert a avoir le livre pour lequel
        on va le comparer avec les autres livres la deuxieme est donc celle qui permet de faire cette comapraison
        lors de la comparaison je verifie si les livre on le meme nom meme auteur mais pas le meme numero
        si c'est le cas j'ajoute uniquement le livre actuelle dans ma bibliodoublon
    */
    Biblio * Bibliodoublon=creer_biblio();
    Livre* Livreactuel=b->L;
    while(Livreactuel){
        Livre* Livrecompare=b->L;
        while(Livrecompare){
            if(Livreactuel->num!=Livrecompare->num && (strcmp(Livreactuel->auteur,Livrecompare->auteur)==0)&& (strcmp(Livreactuel->titre,Livrecompare->titre)==0)){
                inserer_en_tete(Bibliodoublon,Livreactuel->num,Livreactuel->titre,Livreactuel->auteur);
                Livrecompare=NULL; 
            }
            Livrecompare=Livrecompare->suiv
        }
        Livreactuel=Livreactuel->suiv;
    }
    return Bibliodoublon;
}


//Salut ines