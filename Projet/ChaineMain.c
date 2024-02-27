#include "Chaine.h"

int main() {
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nombre de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);

    CellChaine *cr = c->chaines;

    while (cr){
        printf("\nChaine %d:\n", cr->numero);

        CellPoint *cp = cr->points;

        while (cp){
            printf("Point (%.2f, %.2f)\n", cp->x, cp->y);
            cp = cp->suiv;
        }
        cr = cr->suiv;
    }

    fclose(f);
    return 0;
}
