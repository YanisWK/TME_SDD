#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>
#include <math.h>

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

CellPoint *creer_CellPoint(double x,double y);
CellChaine *creer_CellChaine(int num,CellPoint *points);
Chaines *creer_Chaine(int gamma,int nbChaines,CellChaine * chaines);
CellChaine * inserer_teteCC(CellChaine *Lchaine,int num,CellPoint *points);

CellPoint * inserer_teteCP(CellPoint *points,double x,double y);
CellChaine * inserer_teteCC(CellChaine *Lchaine,int num,CellPoint *points);
Chaines* lectureChaines(FILE *f);
void ecrireChaines(Chaines *C, FILE *f);
void afficheChainesSVG(Chaines *C, char* nomInstance);
double longueurChaine(CellChaine *c);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);
int nbPoints(CellPoint * points);
void libererChaines(Chaines *c);
void liberer_cellchaine(CellChaine *chaine);
#endif	
