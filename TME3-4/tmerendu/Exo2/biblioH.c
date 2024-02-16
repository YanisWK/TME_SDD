#include <stdio.h>
#include <stdlib.h>

int fonctionClef(char *auteur){
    int clef = 0,i=0;
    while (*(auteur+i)!='\0'){
        clef += (int)(*(auteur+i));
        i++;
    }
    return clef;
}

LivreH* creer_livre(int num, char* titre, char *auteur){
    LivreH *new = malloc(sizeof(LivreH));
    new->clef = fonctionClef(auteur);
    new->suivant = NULL;
    return new;
}


void liberer_livre(LivreH *l){
    free(l);
}

BiblioH* creer_biblio(int m){
    BiblioH *new = malloc(sizeof(BiblioH));
    new->nE = 0;
    new->m = m;
    new->T = (LivreH**)malloc(m*sizeof(LivreH*));
    for (int i=0; i<m; i++){
        new->T[i] = NULL;
    }
    return new;
}

void liberer_biblio(BiblioH* b){
    for (int i=0; i<b->m; i++){
        LivreH *cour = b->T[i];
        while (cour != NULL){
            LivreH *tmp = cour->suivant;
            liberer_livre(cour);
            cour = tmp;
        }
    }
    free(b->T);
    free(b);
}
