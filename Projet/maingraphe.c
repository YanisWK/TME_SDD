#include "Graphe.h"
#include "Reseau.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *f =fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    Reseau *r = reconstitueReseauListe(c);

    Graphe *g = creerGraphe(r);    
    afficherGraphe(g);

    liberer_graphe(g);
    libererChaines(c);
    libererReseau(r);
    fclose(f); 
    return 0;
}