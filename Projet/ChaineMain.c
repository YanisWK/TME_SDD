#include "Chaine.h"
#include "Chaine.c"

int main() {
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nb de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);
    CellChaine* cc = c->chaines;
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
        

    fclose(f);
}
