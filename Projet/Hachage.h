#include <stdio.h>
#include <stdlib.h>
#include <Reseau.h>

typedef struct TH{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud ** T;
} TableHachage ;



int f(int x, int y);