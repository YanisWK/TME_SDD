#include "Graphe.h"
#include "Reseau.h"
#include "Struct_File.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f =fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    Reseau *r = reconstitueReseauListe(c);

    Graphe *g = creerGraphe(r);    
    afficherGraphe(g);
    int *dejaVisite = malloc(g->nbsom * sizeof(int)); 
    for (int i = 0; i<g->nbsom; i++){
        dejaVisite[i] = 0; //aucun sommet visité
    }
    printf("%d\n",plusCourtChemin(g,3,4));

    liberer_graphe(g);
    libererChaines(c);
    libererReseau(r);
    fclose(f); 
    return 0;
}