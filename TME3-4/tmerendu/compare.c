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
    inserer_en_tete_LC(LC,5,"goated","zing");

    printf("Recherche numero Hachage\n");
    /*
    Faire la recherche du premier numero et d'un numero qui n'existe pas
    et repeter ça pour titre auteur,(meilleure pire des cas en gros)
    et le faire avec LC et comparer les resultats
    */
    printf("Meilleure\n");
    clock_t beginHnumBest = clock();

    rechercheLivreNum_H(H,1);

    clock_t endHnumBest = clock();
    double Hnumbest=(double)(endHnumBest - beginHnumBest) / CLOCKS_PER_SEC;
    printf("Pire\n");
    clock_t beginHnumWorst=clock();
    rechercheLivreNum_H(H,6);
    clock_t endHnumWorst=clock();
    double Hnumworst=(double)(endHnumWorst - beginHnumWorst) / CLOCKS_PER_SEC;



    



}