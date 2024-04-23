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

    if(atoi(argv[1])==0){
        return 0;
    }else{
        if (atoi(argv[1])>3 || atoi(argv[1])<0){
            printf("Entier invalide");
        }else{
            if(atoi(argv[1])==1){ //LISTE CHAINEE
            
                for (int i=0; i<50; i+=5){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    reseau = reconstitueReseauListe(c);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    fprintf(fic4, "Liste chaînée :\n");
                    fprintf(fic4, "%d %lf \n", comptePointsTotal(c), temps);
                    fprintf(fic4, "\n");
                }
            }else if (atoi(argv[1])==2){ //TABLE DE HACHAGE

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
                        fprintf(fic4, "%d %lf\n", comptePointsTotal(c), temps);
                    }
                    fprintf(fic4, "\n");
                }
            }else{ //ARBRE QUATERNAIRE

                for (int i=0; i<50; i+=5){
                    c = generationAleatoire(i,100,5000,5000);

                    deb = clock();
                    reseau = reconstitueReseauArbre(c);
                    fin = clock();
                    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
                    fprintf(fic4, "Arbre quwaternaire :\n");
                    fprintf(fic4, "%d %lf\n", comptePointsTotal(c), temps);
                    fprintf(fic4, "\n");
                }
            }
        }
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    return 0;
}
