#include <stdio.h>
#include <stdlib.h>

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
    free(l)
}

Biblio* creer_biblio(){
    Biblio *new = malloc(sizeof(Biblio));
    new->L= NULL;
    return new;
}