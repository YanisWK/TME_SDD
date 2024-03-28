#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"

typedef struct TH{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud ** T;
} TableHachage ;


TableHachage * CreeTableHachage(int tailleMax);
int f(int x, int y);
int h(int k,int M);
Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage *H,double x,double y);
Reseau * reconstitueReseauHachage(Chaines *C,int M);