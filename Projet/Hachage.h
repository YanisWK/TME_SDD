#include <stdio.h>
#include <stdlib.h>
#include <Reseau.h>

typedef struct TH{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud ** T;
} TableHachage ;



int f(int x, int y);
int h(int k,int M);

Reseau * reconstitueReseauHachage(Chaines *C,int M);