#include "Chaine.h"
#include "Reseau.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nb de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);
    //TESTS EXERCICE 1
    // CellChaine* cc = c->chaines;
    // if(!cc){
    //     printf("Chaine vide\n");
    // }
    // while(cc){
    //     printf("Chaine %d:\n", cc->numero);
    //     CellPoint *cp = cc->points;
    //     while (cp){
    //         printf("(%.2lf, %.2lf)\t", cp->x, cp->y);
    //         cp = cp->suiv;
    //     }
    //     printf("\n");
        
    //     printf("longueur de la chaine %d : %.2lf\n", cc->numero, longueurChaine(cc));

    //     cc = cc->suiv;
    // }

    // printf("longueur totale : %.2lf\n", longueurTotale(c));

    // afficheChainesSVG(c, "00014_burma.cha");
    // printf("nombre d'occurences : %d\n", comptePointsTotal(c));


    //TESTS EXERCICE 2
    Reseau *R = reconstitueReseauListe(c);

    printf("noeuds du reseau:\n");
    CellNoeud *n = R->noeuds;
    while (n){
        printf("noeud %d: %.2lf, %.2lf\n", n->nd->num, n->nd->x, n->nd->y);
        n = n->suiv;
    }

    // printf("commodites du reseau:\n");
    // CellCommodite *com = R->commodites;
    // while (com){
    //     printf("commodite noeud %d - noeud %d\n", com->extrA->num, com->extrB->num);
    //     com = com->suiv;
    // }

    fclose(f);
}