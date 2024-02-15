#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){
    int num;
    char titre[256];
    char auteur[256];
    FILE *f=fopen(nomfic,"r");
    Biblio *b=creer_biblio();
    char buffer[256];
    int i=0;
    while(i<n){
        fgets(buffer,256,f);
        sscanf(buffer,"%d %s %s", &num, titre, auteur);
        inserer_en_tete(b,num,strdup(titre),strdup(auteur));
        i++;
    }
    fclose(f);
	return b;
}

void enregistrer_biblio(Biblio *b, char* nomfic){
    int num;
    char * titre;
    char * auteur;
    FILE *f = fopen(nomfic, "w");
    if(f == NULL){
        printf("Erreur d'ouverture de : %s\n", nomfic);
    }

	while(b->L){
        fprintf(f,"%d %s %s", num, titre, auteur);
		b->L = b->L->suiv;
	}

    fclose(f);
}