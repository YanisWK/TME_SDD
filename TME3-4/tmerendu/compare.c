#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "entreeSortieH.h"
#include "entreeSortieLC.h"

#define TAILLE 10

int main(){

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
    printf("Meilleur cas H\n");
    clock_t beginHnumBest = clock();
    LivreH* rec1 = rechercheLivreNum_H(H,1);
    clock_t endHnumBest = clock();
    double Hnumbest=(double)(endHnumBest - beginHnumBest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par num en H : %.2fs\n", Hnumbest);
    
    printf("Pire cas H (livre absent)\n");
    clock_t beginHnumWorst=clock();
    LivreH* rec2 = rechercheLivreNum_H(H,6);
    clock_t endHnumWorst=clock();
    double Hnumworst=(double)(endHnumWorst - beginHnumWorst) / CLOCKS_PER_SEC;
    afficherLivre_H(rec2);
    printf("Pire temps de recherche par num en H : %.2fs\n", Hnumworst);;


    printf("Meilleur cas LC\n");
    clock_t beginLCnumBest = clock();
    Livre* rec3 = rechercheLivreNum_LC(LC, 1);
    clock_t endLCnumBest = clock();
    double LCnumbest = (double)(endLCnumBest - beginLCnumBest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par num en LC : %.2fs\n", LCnumbest);

    printf("Pire cas LC (livre absent)\n");
    clock_t beginLCnumWorst = clock();
    Livre* rec4 = rechercheLivreNum_LC(LC, 6);
    clock_t endLCnumWorst = clock();
    double LCnumworst = (double)(endLCnumWorst - beginLCnumWorst) / CLOCKS_PER_SEC;
    printf("Pire temps de recherche par num en LC : %.2fs\n", LCnumworst);

//---------------------------------------------------
    printf("Meilleur cas H\n");
    clock_t beginHtitbest = clock();
    LivreH* rec5 = rechercheLivreTitre_H(H, "family");
    clock_t endHtitbest = clock();
    double Htitbest = (double)(endHtitbest - beginHtitbest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par titre en H : %.2fs\n", Htitbest);

    printf("Pire cas H (livre absent)\n");
    clock_t beginHtitworst = clock();
    LivreH* rec6 = rechercheLivreTitre_H(H, "panini");
    clock_t endHtitworst = clock();
    double Htitworst = (double)(endHtitworst - beginHtitworst) / CLOCKS_PER_SEC;
    printf("Pire temps de recherche par titre en H : %.2fs\n", Htitworst);


    printf("Meilleur cas LC\n");
    clock_t beginLCtitbest = clock();
    Livre* rec7 = rechercheLivreTitre_LC(LC, "family");
    clock_t endLCtitbest = clock();
    double LCtitbest = (double)(endLCtitbest - beginLCtitbest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par titre en LC : %.2fs\n", LCtitbest);

    printf("Pire cas LC (livre absent)\n");
    clock_t beginLCtitworst = clock();
    Livre* rec8 = rechercheLivreTitre_LC(LC, "panini");
    clock_t endLCtitworst = clock();
    double LCtitworst = (double)(endLCtitworst - beginLCtitworst) / CLOCKS_PER_SEC;
    printf("Pire temps de recherche par titre en LC : %.2fs\n", LCtitworst);

//------------------------------------------------------------

    printf("Meilleur cas H\n");
    clock_t beginHautbest = clock();
    BiblioH* rec9 = LivresAuteurs_H(H, "zing");
    clock_t endHautbest = clock();
    double Hautbest = (double)(endHautbest - beginHautbest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par auteur en H : %.2fs\n", Hautbest);

    printf("Pire cas H\n");
    clock_t beginHautworst = clock();
    BiblioH* rec10 = LivresAuteurs_H(H, "zing");
    clock_t endHautworst = clock();
    double Hautworst = (double)(endHautworst - beginHautworst) / CLOCKS_PER_SEC;
    printf("Pire temps de recherche par auteur en H : %.2fs\n", Hautworst);


    printf("Meilleur cas LC\n");
    clock_t beginLCautbest = clock();
    Biblio* rec11 = LivresAuteurs_LC(LC, "zing");
    clock_t endLCautbest = clock();
    double LCautbest = (double)(endLCautbest - beginLCautbest) / CLOCKS_PER_SEC;
    printf("Meilleur temps de recherche par auteur en LC : %.2fs\n", LCautbest);

    printf("Pire cas LC\n");
    clock_t beginLCautworst = clock();
    Biblio* rec12 = LivresAuteurs_LC(LC, "jing");
    clock_t endLCautworst = clock();
    double LCautworst = (double)(endLCautworst - beginLCautworst) / CLOCKS_PER_SEC;
    printf("Pire temps de recherche par auteur en LC : %.2fs\n", LCautworst);


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

    return 0;
}