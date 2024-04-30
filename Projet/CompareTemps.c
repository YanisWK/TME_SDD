#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFERSIZE 256

int main(){
    Chaines *c;
    FILE *fic4 = fopen("temps_de_calcul.txt", "w");
    Reseau *reseau = NULL;
    clock_t deb, fin;
    double tempsListe, tempsHachage1, tempsHachage2, tempsHachage3, tempsArbre;
    int nbpoints=0;
    
    fprintf(fic4, "%s\t %s\t\t %s\t\t %s\t\t %s\t\t %s\t\n","Nb points","Liste","Hachage 1","Hachage 2","Hachage 3","Arbre");
    for (int i=500; i<=5000; i+=500){
        srand(time(NULL));
        c = generationAleatoire(i,100,5000,5000);
        

        // LISTE CHAINEE
        deb = clock();
        printf("Debut (Liste chaînée)\n");
        reseau = reconstitueReseauListe(c);
        fin = clock();
        printf("Fin (Liste chaînée)\n");
        tempsListe = ((double)(fin-deb))/CLOCKS_PER_SEC;
        
        // ARBRE QUATERNAIRE
        deb = clock();
        printf("Debut (Arbre quaternaire)\n");
        reseau = reconstitueReseauArbre(c);
        fin = clock();
        printf("Fin (Arbre quaternaire)\n");
        tempsArbre = ((double)(fin-deb))/CLOCKS_PER_SEC;
        
        // TABLE DE HACHAGE
        int M=10000;
        deb = clock();
        printf("Debut (Table de hachage) M=%d\n",M);
        reseau = reconstitueReseauHachage(c, M);
        fin = clock();
        printf("Fin (Table de hachage) M=%d\n",M);
        tempsHachage1 = ((double)(fin-deb))/CLOCKS_PER_SEC;

        M=50000;
        deb = clock();
        printf("Debut (Table de hachage) M=%d\n",M);
        reseau = reconstitueReseauHachage(c, M);
        fin = clock();
        printf("Fin (Table de hachage) M=%d\n",M);
        tempsHachage2 = ((double)(fin-deb))/CLOCKS_PER_SEC;

        M=100000;
        deb = clock();
        printf("Debut (Table de hachage) M=%d\n",M);
        reseau = reconstitueReseauHachage(c, M);
        fin = clock();
        printf("Fin (Table de hachage) M=%d\n",M);
        tempsHachage3 = ((double)(fin-deb))/CLOCKS_PER_SEC;
        while (c->chaines){
            nbpoints+=nbPoints(c->chaines->points);
            c->chaines=c->chaines->suiv;
        }
        fprintf(fic4, "%d\t\t %.7lf\t %.7lf\t\t %.7lf\t\t %.7lf\t\t %.7lf\n",nbpoints,tempsListe,tempsHachage1,tempsHachage2,tempsHachage3,tempsArbre);
        printf("\nFin de la Reconstitution pour %d points\n\n",nbpoints);
        nbpoints=0;   
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    return 0;
}
