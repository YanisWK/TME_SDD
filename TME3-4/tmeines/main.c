#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

int main(int argc, char** argv){
    // if (argc != 3){
    //     printf("Erreur ./main <nomfichier> <un nombre>\n");
    //     exit(1);
    // }

    // Biblio *b = charger_n_entrees(argv[1],atoi(argv[2]));    
    
    // enregistrer_biblio(b, "saved.txt");

    Biblio *b1= creer_biblio();
    Biblio *b2= creer_biblio();

    inserer_en_tete(b1,1,"Spy x Family 1","Tatsuya Endo");
    inserer_en_tete(b1,2,"Spy x Family 2","Tatsuya Endo");    
    inserer_en_tete(b2,3,"Spy x Family 3","Tatsuya Endo");
    inserer_en_tete(b2,4,"Spy x Family 4","Tatsuya Endo");

    Biblio *b3 = fusion(b1,b2);
    affichebiblio(b3);
    
        
    // Biblio *b4 = rechexemplaires(b1);

    // supprimelivre(b4,2,"Spy x Family 2","Tatsuya Endo");
    // affichebiblio(b4);
    


    liberer_biblio(b3);
    liberer_biblio(b2);
    liberer_biblio(b1);


    return 0;
}