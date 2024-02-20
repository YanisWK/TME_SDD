#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "entreeSortieH.h"
#include "entreeSortieLC.h"

#define TAILLE 10





int main(){

    Biblio * LC=creer_biblio_LC();
    BiblioH * H=creer_biblio_H(30);

    LivreH* LH1=creer_livre_H(1,"spy","endo");
    LivreH* LH2=creer_livre_H(2,"x","tatsu");
    LivreH* LH3=creer_livre_H(3,"family","ya");
    LivreH* LH4=creer_livre_H(4,"is","ama");
    LivreH* LH5=creer_livre_H(5,"goated","zing");

    Livre *LC1=creer_livre_LC(1,"spy","endo");
    Livre *LC2=creer_livre_LC(2,"x","tatsu");
    Livre *LC3=creer_livre_LC(3,"family","ya");
    Livre *LC4=creer_livre_LC(4,"is","ama");
    Livre *LC5=creer_livre_LC(5,"goated","zing");


    



}