#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

int main(int argc, char** argv){
    if (argc != 3){
        printf("Erreur ./main <nomfichier> <un nombre>\n");
        exit(1);
    }

    Biblio *b = charger_n_entrees(argv[1],atoi(argv[2]));    
    
    enregistrer_biblio(b, "saved.txt");
    liberer_biblio(b);

    return 0;
}