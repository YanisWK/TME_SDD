#include "Chaine.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 256

int main(){
    FILE *f = fopen("00014_burma.cha", "r");
    Chaines* c = lectureChaines(f);

    FILE *fichier = fopen("Chaines.txt", "w");
    ecrireChaines(c, fichier);

    libererChaines(c);
    fclose(fichier);
    fclose(f);
    return 0;
}