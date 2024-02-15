#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

int main(int argc, char** argv){
    if (argc != 3){
        printf("Erreur ./main <nomfichier> <un nombre>\n");
        exit(1);
    }

    charger_n_entrees(argv[1],atoi(argv[2]));
    return 0;
}