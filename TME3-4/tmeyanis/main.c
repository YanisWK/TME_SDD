#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

int main(int argc, char** argv){
    if (argc != 2){
        printf("Erreur ./main <nomfichier> <un nombre>");
    }else{
    Biblio *bibli=charger_n_entrees(argv[0],atoi(argv[1]));
    if(bibli){
        printf("cool");
    }
    return 0;
}
}