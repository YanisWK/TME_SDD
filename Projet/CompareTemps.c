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
    double tempsListe, tempsHachage, tempsArbre;
    int nbpoints=0;
    
    fprintf(fic4, "%s\t %s\t\t %s\t\t %s\t %s\t\n","Nb points","Liste","M","Temps Hachage","Temps Arbre");
    for (int i=500; i<=5000; i+=500){
        c = generationAleatoire(i,100,5000,5000);
        while (c->chaines){
            nbpoints+=nbPoints(c->chaines->points);
            c->chaines=c->chaines->suiv;
        }

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
        srand(time(NULL));
        for(int j=1000; j<=5000; j+=1000){
            deb = clock();
            printf("Debut (Table de hachage) M=%d\n",j);
            reseau = reconstitueReseauHachage(c, j);
            fin = clock();
            printf("Fin (Table de hachage) M=%d\n",j);
            tempsHachage = ((double)(fin-deb))/CLOCKS_PER_SEC;
            fprintf(fic4, "%d\t\t %.7lf\t %d\t %.7lf\t\t %.7lf\n",nbpoints,tempsListe,j,tempsHachage,tempsArbre);
        }                 
        nbpoints=0;   
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic4);   
    return 0;
}
