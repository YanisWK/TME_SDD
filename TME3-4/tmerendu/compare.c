#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <math.h>
#include "entreeSortieH.h"
#include "entreeSortieLC.h"

#define TAILLE 10
#define BUFFERSIZE 256


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
                Biblio * LC=creer_biblio_LC();
                BiblioH * H=creer_biblio_H(30);

                inserer(H,1,"spy","endo");
                inserer(H,2,"x","tatsu");
                inserer(H,3,"family","ya");
                inserer(H,4,"is","ama");
                inserer(H,5,"goated","zing");

                inserer_en_tete_LC(LC,1,"spy","endo");
                inserer_en_tete_LC(LC,2,"x","tatsu");
                inserer_en_tete_LC(LC,3,"family","ya");
                inserer_en_tete_LC(LC,4,"is","ama");
                inserer_en_tete_LC(LC,5,"goated","zing");;
                /*
                Faire la recherche du premier numero et d'un numero qui n'existe pas
                et repeter ça pour titre auteur,(meilleure pire des cas en gros)
                et le faire avec LC et comparer les resultats
                */
                clock_t beginHnumBest = clock();
                LivreH* rec1 = rechercheLivreNum_H(H,1);
                clock_t endHnumBest = clock();
                double Hnumbest=(double)(endHnumBest - beginHnumBest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par num en H : %.12fs\n", Hnumbest);
                
                clock_t beginHnumWorst=clock();
                LivreH* rec2 = rechercheLivreNum_H(H,6);
                clock_t endHnumWorst=clock();
                double Hnumworst=(double)(endHnumWorst - beginHnumWorst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par num en H : %.12fs\n", Hnumworst);;


                clock_t beginLCnumBest = clock();
                Livre* rec3 = rechercheLivreNum_LC(LC, 1);
                clock_t endLCnumBest = clock();
                double LCnumbest = (double)(endLCnumBest - beginLCnumBest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par num en LC : %.12fs\n", LCnumbest);

                clock_t beginLCnumWorst = clock();
                Livre* rec4 = rechercheLivreNum_LC(LC, 6);
                clock_t endLCnumWorst = clock();
                double LCnumworst = (double)(endLCnumWorst - beginLCnumWorst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par num en LC : %.12fs\n", LCnumworst);

            //---------------------------------------------------
                clock_t beginHtitbest = clock();
                LivreH* rec5 = rechercheLivreTitre_H(H, "family");
                clock_t endHtitbest = clock();
                double Htitbest = (double)(endHtitbest - beginHtitbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par titre en H : %.12fs\n", Htitbest);

                clock_t beginHtitworst = clock();
                LivreH* rec6 = rechercheLivreTitre_H(H, "panini");
                clock_t endHtitworst = clock();
                double Htitworst = (double)(endHtitworst - beginHtitworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par titre en H : %.12fs\n", Htitworst);


                clock_t beginLCtitbest = clock();
                Livre* rec7 = rechercheLivreTitre_LC(LC, "family");
                clock_t endLCtitbest = clock();
                double LCtitbest = (double)(endLCtitbest - beginLCtitbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par titre en LC : %.12fs\n", LCtitbest);

                clock_t beginLCtitworst = clock();
                Livre* rec8 = rechercheLivreTitre_LC(LC, "panini");
                clock_t endLCtitworst = clock();
                double LCtitworst = (double)(endLCtitworst - beginLCtitworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par titre en LC : %.12fs\n", LCtitworst);

            //------------------------------------------------------------

                clock_t beginHautbest = clock();
                BiblioH* rec9 = LivresAuteurs_H(H, "zing");
                clock_t endHautbest = clock();
                double Hautbest = (double)(endHautbest - beginHautbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par auteur en H : %.12fs\n", Hautbest);

                clock_t beginHautworst = clock();
                BiblioH* rec10 = LivresAuteurs_H(H, "jing");
                clock_t endHautworst = clock();
                double Hautworst = (double)(endHautworst - beginHautworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par auteur en H : %.12fs\n", Hautworst);


                clock_t beginLCautbest = clock();
                Biblio* rec11 = LivresAuteurs_LC(LC, "zing");
                clock_t endLCautbest = clock();
                double LCautbest = (double)(endLCautbest - beginLCautbest) / CLOCKS_PER_SEC;
                printf("Meilleur temps de recherche par auteur en LC : %.12fs\n", LCautbest);

                clock_t beginLCautworst = clock();
                Biblio* rec12 = LivresAuteurs_LC(LC, "jing");
                clock_t endLCautworst = clock();
                double LCautworst = (double)(endLCautworst - beginLCautworst) / CLOCKS_PER_SEC;
                printf("Pire temps de recherche par auteur en LC : %.12fs\n", LCautworst);


                liberer_livre_H(rec1);
                liberer_livre_H(rec2);
                liberer_livre_LC(rec3);
                liberer_livre_LC(rec4);
                liberer_livre_H(rec5);
                liberer_livre_H(rec6);
                liberer_livre_LC(rec7);
                liberer_livre_LC(rec8);
                liberer_biblio_H(rec9);
                liberer_biblio_H(rec10);
                liberer_biblio_LC(rec11);
                liberer_biblio_LC(rec12);
        }
    
    
}


    return 0;
}