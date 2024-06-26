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
    printf("Resultat de Reorganise Reseau = %d \n",reorganiseReseau(r));
    liberer_graphe(g);
    libererChaines(c);
    libererReseau(r);
    fclose(f); 
    return 0;
}