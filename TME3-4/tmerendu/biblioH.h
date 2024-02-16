#include <stdio.h>
#include <stdlib.h>

typedef struct livreh{
    int clef;
    struct livreh* suivant;
} LivreH;

typedef struct table{
    int nE; 
    int m; 
    LivreH** T; 
} BiblioH;