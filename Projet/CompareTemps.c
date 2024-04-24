#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFERSIZE 256

int main(int argc, char *argv[]){
    
    if (argc!=2){
        fprintf(stderr, "Usage: ./CompareTemps entier\n");
        return 1;
    }

    Chaines *c;
    FILE *fic4 = fopen("temps_de_calcul.txt", "w");
    Reseau *reseau = NULL;
    clock_t deb, fin;
    double temps;
    int nbpoints=0;

    if(atoi(argv[1])==0){
        return 0;
    }else{
        if (atoi(argv[1])>3 || atoi(argv[1])<0){
            printf("Entier invalide");
        }else{
            if(atoi(argv[1])==1){ //LISTE CHAINEE

                for (int i=500; i<5000; i+=500){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    reseau = reconstitueReseauListe(c);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    //printf("nb points chaine 1 : %d\n",nbPoints(c->chaines->points));
                    while(c->chaines){
                        nbpoints+=nbPoints(c->chaines->points);
                        c->chaines=c->chaines->suiv;
                    }
                    fprintf(fic4, "%d %.7lf \n", nbpoints, temps);
                }
            }else if (atoi(argv[1])==2){ //TABLE DE HACHAGE

                for (int i=500; i<1000; i+=500){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    printf("Debut\n");
                    int M = 1000; 
                    reseau = reconstitueReseauHachage(c, M);
                    fin = clock();
                    printf("fin\n");
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    deb = clock();
                    reseau = reconstitueReseauHachage(c, i);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    while(c->chaines){
                        nbpoints+=nbPoints(c->chaines->points);
                        c->chaines=c->chaines->suiv;
                    }
                    fprintf(fic4, "%d %.7lf \n", nbpoints, temps);
                }
            }else{ //ARBRE QUATERNAIRE

                for (int i=500; i<5000; i+=500){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    printf("debut \n");
                    reseau = reconstitueReseauArbre(c);
                    fin = clock();
                    printf("fin\n");
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    while(c->chaines){
                        nbpoints+=nbPoints(c->chaines->points);
                        c->chaines=c->chaines->suiv;
                    }
                    fprintf(fic4, "%d %.7lf \n", nbpoints, temps);
                }
            }
        }
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    return 0;
}
