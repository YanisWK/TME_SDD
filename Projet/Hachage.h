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
CellCommodite * creeCommodite(Noeud * extrA,Noeud * extrB);
CellCommodite * ajout_teteCellCommodite(CellCommodite * commodites,Noeud * extrA,Noeud * extrB);
Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage *H,double x,double y);
Reseau * reconstitueReseauHachage(Chaines *C,int M);
void LibererTableHachage(TableHachage *table);
