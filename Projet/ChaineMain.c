#include "Chaine.h"

int main() {
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nombre de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);

    CellChaine *cc = c->chaines;

    

    fclose(f);
}
