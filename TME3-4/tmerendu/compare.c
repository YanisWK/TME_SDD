#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <math.h>
#include "entreeSortieH.h"
#include "entreeSortieLC.h"

#define TAILLE 10
#define BUFFERSIZE 256
#define THACHAGE 80000


void menu(){
    printf("0 - Sortir du programme\n");
    printf("1 - Comparaison du temps de calcul par numero ,titre,auteur\n");
    printf("2 - Comparaison temps de recherches d'ouvrages en plusieurs exemplaires\n");
    printf("Que voulez vous faire ?\n");
}
int main(){
    
    char *entree;
    int rep;
    do{
        char buffer[BUFFERSIZE];
        menu();
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
        //scanf(" %d",&rep);
        switch(rep){
            case 1:
                Biblio * LC= charger_n_entrees_LC("GdeBiblio.txt",5000);
                BiblioH *H = charger_n_entrees_H("GdeBiblio.txt",5000,10000);

                printf("---------------------------------------------------\n");
                printf("-----------------Recherche par num-----------------\n");
                printf("---------------------------------------------------\n");

                    clock_t beginHnumBest = clock();
                    LivreH* rec1 = rechercheLivreNum_H(H,1);
                    clock_t endHnumBest = clock();
                    double Hnumbest=(double)(endHnumBest - beginHnumBest) / CLOCKS_PER_SEC;
                    printf("Meilleur temps de recherche par num en H : %.12fs\n", Hnumbest);
                    
                    clock_t beginHnum1 = clock();
                    LivreH* rm1 = rechercheLivreNum_H(H,150);
                    clock_t endHnum1 = clock();
                    double Hnum1=(double)(endHnum1 - beginHnum1) / CLOCKS_PER_SEC;
                    printf("Temps de recherche pour num =150 en H : %.12fs\n", Hnum1);
                    
                    clock_t beginHnum2 = clock();
                    LivreH* rm2 = rechercheLivreNum_H(H,2500);
                    clock_t endHnum2 = clock();
                    double Hnum2=(double)(endHnum2 - beginHnum2) / CLOCKS_PER_SEC;
                    printf("Temps de recherche pour num =2500 en H : %.12fs\n", Hnum2);
                    
                    clock_t beginHnum3 = clock();
                    LivreH* rm3 = rechercheLivreNum_H(H,7500);
                    clock_t endHnum3 = clock();
                    double Hnum3=(double)(endHnum3 - beginHnum3) / CLOCKS_PER_SEC;
                    printf("Temps de recherche pour num =7500 en H : %.12fs\n", Hnum3);

                    clock_t beginHnumWorst=clock();
                    LivreH* rec2 = rechercheLivreNum_H(H,10000);
                    clock_t endHnumWorst=clock();
                    double Hnumworst=(double)(endHnumWorst - beginHnumWorst) / CLOCKS_PER_SEC;
                    printf("Pire temps de recherche par num en H : %.12fs\n", Hnumworst);;


                    clock_t beginLCnumBest = clock();
                    Livre* rec3 = rechercheLivreNum_LC(LC,1);
                    clock_t endLCnumBest = clock();
                    double LCnumbest = (double)(endLCnumBest - beginLCnumBest) / CLOCKS_PER_SEC;
                    printf("Meilleur temps de recherche par num en LC : %.12fs\n", LCnumbest);

                    clock_t beginLCnumWorst = clock();
                    Livre* rec4 = rechercheLivreNum_LC(LC,10000);
                    clock_t endLCnumWorst = clock();
                    double LCnumworst = (double)(endLCnumWorst - beginLCnumWorst) / CLOCKS_PER_SEC;
                    printf("Pire temps de recherche par num en LC : %.12fs\n", LCnumworst);

                printf("---------------------------------------------------\n");
                printf("----------------Recherche par titre----------------\n");
                printf("---------------------------------------------------\n");

                    clock_t beginHtitbest = clock();
                    LivreH* rec5 = rechercheLivreTitre_H(H,"WLRBBMQBHCDARZOWK");
                    clock_t endHtitbest = clock();
                    double Htitbest = (double)(endHtitbest - beginHtitbest) / CLOCKS_PER_SEC;
                    printf("Meilleur temps de recherche par titre en H : %.12fs\n", Htitbest);

                    clock_t beginHtitworst = clock();
                    LivreH* rec6 = rechercheLivreTitre_H(H, "existepas");
                    clock_t endHtitworst = clock();
                    double Htitworst = (double)(endHtitworst - beginHtitworst) / CLOCKS_PER_SEC;
                    printf("Pire temps de recherche par titre en H : %.12fs\n", Htitworst);


                    clock_t beginLCtitbest = clock();
                    Livre* rec7 = rechercheLivreTitre_LC(LC, "WLRBBMQBHCDARZOWK");
                    clock_t endLCtitbest = clock();
                    double LCtitbest = (double)(endLCtitbest - beginLCtitbest) / CLOCKS_PER_SEC;
                    printf("Meilleur temps de recherche par titre en LC : %.12fs\n", LCtitbest);

                    clock_t beginLCtitworst = clock();
                    Livre* rec8 = rechercheLivreTitre_LC(LC,"existepas");
                    clock_t endLCtitworst = clock();
                    double LCtitworst = (double)(endLCtitworst - beginLCtitworst) / CLOCKS_PER_SEC;
                    printf("Pire temps de recherche par titre en LC : %.12fs\n", LCtitworst);
                

                printf("---------------------------------------------------\n");
                printf("---------------Recherche par auteur----------------\n");
                printf("---------------------------------------------------\n");
                
                clock_t beginHautbest = clock();
                BiblioH* rec9 = LivresAuteurs_H(H,"yhidd");
                clock_t endHautbest = clock();
                double Hautbest = (double)(endHautbest - beginHautbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par auteur en H : %.12fs\n", Hautbest);

                clock_t beginHautworst = clock();
                BiblioH* rec10 = LivresAuteurs_H(H, "existepas");
                clock_t endHautworst = clock();
                double Hautworst = (double)(endHautworst - beginHautworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par auteur en H : %.12fs\n", Hautworst);


                clock_t beginLCautbest = clock();
                Biblio* rec11 = LivresAuteurs_LC(LC, "yhidd");
                clock_t endLCautbest = clock();
                double LCautbest = (double)(endLCautbest - beginLCautbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par auteur en LC : %.12fs\n", LCautbest);

                clock_t beginLCautworst = clock();
                Biblio* rec12 = LivresAuteurs_LC(LC, "existepas");
                clock_t endLCautworst = clock();
                double LCautworst = (double)(endLCautworst - beginLCautworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par auteur en LC : %.12fs\n", LCautworst);


                liberer_biblio_H(rec9);
                liberer_biblio_H(rec10);
                liberer_biblio_LC(rec11);
                liberer_biblio_LC(rec12);
                liberer_biblio_H(H);
                liberer_biblio_LC(LC);

                break;

            case 2:
                int n=1000;
                FILE * f=fopen("comparaison.txt","w");
                Biblio * BibLC=creer_biblio_LC();
                BiblioH * BibH=creer_biblio_H(THACHAGE);
                while(n<=50000){
                    BibLC=charger_n_entrees_LC("GdeBiblio.txt",n);
                    BibH=charger_n_entrees_H("GdeBiblio.txt",n,THACHAGE);

                    clock_t beginLC=clock();
                    RecherchePlusieurs_LC(BibLC);
                    clock_t endLC=clock();

                    double timeLC=(double)(endLC-beginLC)/CLOCKS_PER_SEC;

                    clock_t beginH=clock();
                    RecherchePlusieurs_H(BibH);
                    clock_t endH=clock();

                    double timeH=(double)(endH-beginH)/CLOCKS_PER_SEC;
                    
                    fprintf(f,"%d %.5f %.5f\n",n,timeH,timeLC);
                    n+=100;
                }
                liberer_biblio_H(BibH);
                liberer_biblio_LC(BibLC);
                break;
        }
}while(rep!=0);

    return 0;
}