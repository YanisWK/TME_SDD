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
        inserer_en_teteLC(b,num,strdup(titre),strdup(auteur));
        i++;
    }
    fclose(f);
	return b;
}
