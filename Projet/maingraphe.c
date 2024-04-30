#include "Graphe.h"
#include "Reseau.h"
#include "Struct_File.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f =fopen("05000_USA-road-d-NY.cha", "r");
    Chaines *c = lectureChaines(f);
    Reseau *r = reconstitueReseauListe(c);

    Graphe *g = creerGraphe(r);    
    afficherGraphe(g);
    //printf("%d\n",plusCourtChemin(g,3,4));

    liberer_graphe(g);
    libererChaines(c);
    libererReseau(r);
    fclose(f); 
    return 0;
}