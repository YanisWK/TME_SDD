#include "Chaine.h"

int main() {
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nb de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);
    CellChaine* cc = c->chaines;
    if(!cc){
        printf("Chaine vide\n");
    }
    while(cc){
        printf("Chaine %d:\n", cc->numero);
        CellPoint *cp = cc->points;
        while (cp){
            printf("(%.2lf, %.2lf)\t", cp->x, cp->y);
            cp = cp->suiv;
        }
        printf("\n");
        cc = cc->suiv;
    }


    afficheChainesSVG(c, "00014_burma.cha");

    fclose(f);
}


