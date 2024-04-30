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
    CellChaine * parcours=plusCourtChemin(g,4,8);
    // while(parcours){
    //     printf("%d\n",parcours->numero);
    //     parcours=parcours->suiv;
    // }
    liberer_graphe(g);
    libererChaines(c);
    libererReseau(r);
    fclose(f); 
    return 0;
}