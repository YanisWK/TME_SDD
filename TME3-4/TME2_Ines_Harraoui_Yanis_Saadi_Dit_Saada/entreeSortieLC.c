#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees_LC(char* nomfic, int n){
    int num;
    char titre[256];
    char auteur[256];
    FILE *f=fopen(nomfic,"r");
    Biblio *b=creer_biblio_LC();
    char buffer[256];
    int i=0;
    while(i<n){
        fgets(buffer,256,f);
        sscanf(buffer,"%d %s %s", &num, titre, auteur);
        inserer_en_tete_LC(b,num,titre,auteur);
        i++;
    }
    fclose(f);
	return b;
}

void enregistrer_biblio_LC(Biblio *b, char* nomfic){;
    FILE *f = fopen(nomfic, "w");
    if(f == NULL){
        printf("Erreur d'ouverture de : %s\n", nomfic);
        exit(1);
    }

    Livre* cour= b->L;
	while(cour){
        fprintf(f,"%d %s %s\n", cour->num, cour->titre, cour->auteur);
		cour= cour->suiv;
	}

    fclose(f);
}


