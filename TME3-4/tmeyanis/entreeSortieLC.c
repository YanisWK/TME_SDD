#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){
    FILE *f=fopen(nomfic,'r');
    int num;
    char* titre;
    char* auteur;
    Biblio *newBiblio=creer_biblio();

    if(f==NULL){
        printf("Erreur");
        return NULL;
    }
    char buffer[256];
    while(n>0){
        fgets(buffer,256,f);
        sscanf(buffer,"%d %s %s",&num,titre,auteur);

    }


}






void enregistrer_biblio(Biblio *b, char* nomfic);