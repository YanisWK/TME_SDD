#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

int main(int argc, char** argv){
    if (argc != 3){
        printf("Erreur ./main <nomfichier> <un nombre>\n");
    }else{
    //printf("nom fichier = %s , numero ligne %s \n",argv[1],argv[2]); 
    Biblio *bibli=charger_n_entrees(argv[1],atoi(argv[2]));
    if(bibli){
        afficherBiblio(bibli);
    }
    return 0;
}
}