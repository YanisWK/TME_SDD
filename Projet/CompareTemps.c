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

    char *entree=malloc(sizeof(char));
    int rep;

    do{    
        char buffer[BUFFERSIZE];
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
        if (sscanf(entree, "%d", &rep) != 1){
            printf("Entrée invalide. Usage : <un entier>\n");
        }
        switch(rep){
            case 1:
            //LISTE CHAINEE

                for (int i=0; i<50; i+=5){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    reseau = reconstitueReseauListe(c);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    fprintf(fic4, "Liste chaînée :\n");
                    fprintf(fic4, "%lf %lf \n", longueurChaine(c->chaines), temps);
                    fprintf(fic4, "\n");
                }
                break;

            case 2:
            //TABLE DE HACHAGE

                for (int i=0; i<5000; i+=500){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    int M = 50; 
                    reseau = reconstitueReseauHachage(c, M);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    fprintf(fic4, "Table de hachage :\n");
                    for (int i=M; i<=100; i+=5){
                        deb = clock();
                        reseau = reconstitueReseauHachage(c, i);
                        fin = clock();
                        temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                        fprintf(fic4, "%lf %lf\n", longueurChaine(c->chaines), temps);
                    }
                    fprintf(fic4, "\n");
                }
                break;

            case 3:
            //ARBRE QUATERNAIRE

                for (int i=0; i<50; i+=5){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    reseau = reconstitueReseauArbre(c);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    fprintf(fic4, "Arbre quaternaire :\n");
                    fprintf(fic4, "%lf %lf\n", longueurChaine(c->chaines), temps);
                    fprintf(fic4, "\n");
                }
                break;
        }
    }while(rep!=0);

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    free(entree);
    return 0;
}
