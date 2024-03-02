#include "Reseau.h"


void main(){
    printf("1- Liste Chainée\n");
    printf("2- Table de Hachage\n");
    printf("3- Arbre\n");
    printf("Quelle structure voulez vous choisir ?\n");
}

int main(int argc, char *argv[]){
    if (argc!=3){
        fprintf(stderr, "Usage: ./ReconstitueReseau fichier structure\n");
        return 1;
    }

    FILE *f =fopen(argv[1], "r");

    Chaines *c = lectureChaines(f);

    Reseau *r;

    switch(atoi(argv[2])){
        case 1:
            r =reconstitueReseauListe(c);
            break;
        case 2:
            break;
        case 3:
            break;
    }

    fclose(f);
}