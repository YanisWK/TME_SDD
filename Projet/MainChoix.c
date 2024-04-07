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
        fprintf(stderr, "Usage: ./ReconstitueReseau fichier\n");
        return 1;
    }

    FILE *f =fopen(argv[1], "r");
    Chaines *c = lectureChaines(f);
    FILE *fic4 = fopen("temps_de_calcul.txt", "w");


    Reseau *reseau = NULL;
    clock_t deb, fin;
    double temps;

    //LISTE CHAINEE
    deb = clock();
    reseau = reconstitueReseauListe(c);
    fin = clock();
    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
    fprintf(fic4, "Liste chaînée : ");
    fprintf(fic4, "%lf secondes\n", temps);
    fprintf(fic4, "\n");
    
    //TABLE DE HACHAGE
    deb = clock();
    int M = 50; 
    reseau = reconstitueReseauHachage(c, M);
    fin = clock();
    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
    fprintf(fic4, "Table de hachage :\n");
    for (int i=M; i<=70; i++){
        deb = clock();
        reseau = reconstitueReseauHachage(c, i);
        fin = clock();
        temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
        fprintf(fic4, "M = %d : %lf secondes\n", i, temps);
    }
    fprintf(fic4, "\n");
    sleep(2);


    //ARBRE QUATERNAIRE
    deb = clock();
    reseau = reconstitueReseauArbre(c);
    fin = clock();
    temps = ((double)(fin - deb))/CLOCKS_PER_SEC;
    fprintf(fic4, "Arbre quaternaire :\n");
    fprintf(fic4, "\n%lf secondes\n", temps);

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    fclose(f);
    return 0;
}