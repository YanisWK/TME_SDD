#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieH.h"


BiblioH* charger_n_entrees_H(char *nomfic, int n, int m){
    int num;
    char titre[256];
    char auteur[256];
    FILE *f=fopen(nomfic,"r");
    BiblioH *b=creer_biblio_H(m);
    char buffer[256];
    int i=0;
    while(i<n){
        fgets(buffer,256,f);
        sscanf(buffer,"%d %s %s", &num, titre, auteur);
        inserer(b,num,strdup(titre),strdup(auteur));
        i++;
    }
    fclose(f);
	return b;
}

void enregistrer_biblio_H(BiblioH *b, char *nomfic){
    FILE *f = fopen(nomfic, "w");
    if(f == NULL){
        printf("Erreur d'ouverture de : %s\n", nomfic);
        exit(1);
    }

    for (int i=0; i<b->m; i++){
        LivreH *cour = b->T[i];
        while (cour){
            fprintf(f,"%d %s %s\n", cour->num, cour->titre, cour->auteur);
            cour= cour->suivant;
        }
	}

    fclose(f);
}