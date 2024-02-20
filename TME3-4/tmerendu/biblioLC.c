#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre_LC(int num,char* titre,char* auteur){
    Livre *new= malloc(sizeof(Livre));
    new->num= num;
    new->titre=strdup(titre);
    new->auteur=strdup(auteur);
    new->suiv=NULL;
    return new;
}

void liberer_livre_LC(Livre *l){
    if (l){
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

Biblio* creer_biblio_LC(){
    Biblio *new = malloc(sizeof(Biblio));
    new->L= NULL;
    return new;
}

void liberer_biblio_LC(Biblio* b){
    Livre *cour = b->L;
    while(cour){
        Livre *tmp=cour;
        cour=cour->suiv;
        liberer_livre_LC(tmp);
    }
    free(b);
}

void inserer_en_tete_LC(Biblio* b,int num,char* titre,char* auteur){
    Livre *tete=creer_livre_LC(num,titre,auteur);
    tete->suiv=b->L;
    b->L=tete;
}


void afficherLivre_LC(Livre *l){
    if (l){
        printf("Numéro : %d\n", l->num);
        printf("Titre : %s\n", l->titre);
        printf("Auteur : %s\n", l->auteur);
    }
}

void afficherBiblio_LC(Biblio *b){
    Livre *cour = b->L; 
    while (cour){
        afficherLivre_LC(cour);
        printf("\n");
        cour = cour->suiv;
    }
}

Livre* rechercheLivreNum_LC(Biblio *b,int num){
    if (b == NULL){
        return NULL;
    }

    Livre *cour=b->L;
    while(cour){
        if(cour->num==num){
            return (cour);
        }
        cour=cour->suiv;
    }
    return NULL;
}

Livre* rechercheLivreTitre_LC(Biblio *b,char* titre){
    if (b == NULL){
        return NULL;
    }

    Livre* cour=b->L;
    while(cour){
        if(strcmp(cour->titre,titre)==0){
            return(cour);
        }
        cour=cour->suiv;
    }
    return NULL;
}

Biblio* LivresAuteurs_LC(Biblio*b,char* auteur){
    if (b == NULL){
        return NULL;
    }
    
    Biblio *BiblioAut=creer_biblio_LC();
    Livre* cour=b->L;
    while(cour){
        if(strcmp(cour->auteur,auteur)==0){
            inserer_en_tete_LC(BiblioAut,cour->num,cour->titre,auteur);
        }
        cour=cour->suiv;
    }
    return BiblioAut;
}


void supprimerLivre_LC(Biblio* b, int num, char* titre, char* auteur){
    Livre* prec = NULL, * cour = b->L;

    while (cour){
        if (cour->num == num && strcmp(cour->titre, titre) == 0 && strcmp(cour->auteur, auteur) == 0){
            if (!prec){
                b->L = cour->suiv;
            }else{
                prec->suiv = cour->suiv;
            }
            liberer_livre_LC(cour);
            return;
        }
        prec = cour;
        cour = cour->suiv;
    }
}

Biblio* fusion_LC(Biblio *b1, Biblio *b2){
    Livre *cour1 = b1->L;
    Livre *cour2 = b2->L;

    while (cour2){
        inserer_en_tete_LC(b1, cour2->num, cour2->titre, cour2->auteur);
        cour2 = cour2->suiv;
    }
    liberer_biblio_LC(b2);
    return b1;
}

Biblio* RecherchePlusieurs_LC(Biblio* b){
    Biblio* Bibliodoublon = creer_biblio_LC();
    Livre* Livreactuel = b->L;

    while (Livreactuel) {
        Livre* Livrecompare = b->L;
        int count = 0;
        while (Livrecompare){
            if (Livreactuel->num != Livrecompare->num && strcmp(Livreactuel->auteur, Livrecompare->auteur) == 0 &&
                strcmp(Livreactuel->titre, Livrecompare->titre) == 0){
                // inserer_en_tete_LC(Bibliodoublon, Livreactuel->num, Livreactuel->titre, Livreactuel->auteur);
                // break;
                count++;
            }
            Livrecompare = Livrecompare->suiv;
        }
        if (count > 0) {
            inserer_en_tete_LC(Bibliodoublon, Livreactuel->num, Livreactuel->titre, Livreactuel->auteur);
        }

        Livreactuel = Livreactuel->suiv;
    }
    return Bibliodoublon;
}
