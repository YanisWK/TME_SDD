#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 256

void menu(){
    printf("0- Sortir du programme\n");
    printf("1- Liste Chainée\n");
    printf("2- Table de Hachage\n");
    printf("3- Arbre\n");
    printf("Quelle structure voulez vous choisir ?\n");
}

int main(int argc, char *argv[]){
    
    if (argc!=2){
        fprintf(stderr, "Usage: ./ReconstitueReseau fichier\n");
        return 1;
    }

    FILE *f =fopen(argv[1], "r");

    Chaines *c = lectureChaines(f);
    fclose(f);

    char *entree;
    int rep;

    do{
        char buffer[BUFFERSIZE];
        menu();
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
        switch(rep){
            case 1:
                Reseau *r =reconstitueReseauListe(c);
                printf("noeuds du reseau:\n");
                CellNoeud *n = r->noeuds;
                while (n){
                    printf("v %d %.2lf, %.2lf\n", n->nd->num, n->nd->x, n->nd->y);
                    n = n->suiv;
                }
                printf("commodites du reseau:\n");
                CellCommodite *com = r->commodites;
                while (com){
                    printf("l %d %d\n", com->extrA->num, com->extrB->num);
                    com = com->suiv;
                }
                CellNoeud *nn = r->noeuds;
                while (nn){                
                    CellNoeud *v = nn->nd->voisins;
                    printf("k ");
                    while (v){
                        printf("%d ", v->nd->num);
                        v = v->suiv;
                    }
                    printf("\n");
                    nn=nn->suiv;
                }
                break;
        }
    }while(rep!=0);
    if(!rep){
        return 0;
    }
    fclose(f);
    return 0;
}