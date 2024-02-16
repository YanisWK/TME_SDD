#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

void menu(){
    printf("Que voulez vous faire ?")
}



int main(int argc, char** argv){
    if (argc != 3){
        printf("Erreur ./main <nomfichier> <un nombre>\n");
    }else{
    //printf("nom fichier = %s , numero ligne %s \n",argv[1],argv[2]); 
    Biblio *bibli=charger_n_entrees(argv[1],atoi(argv[2]));
    afficherBiblio(bibli);
    return 0;
}
}