#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 256

void menu(){
    printf("0- Sortir du programme\n");
    printf("1- Liste Chainée\n");
    printf("2- Table de Hachage\n");
    printf("3- Arbre\n");
    printf("Quelle structure voulez vous choisir ?\n");
}

int main(int argc, char *argv[]){
    
    if (argc!=2){
        fprintf(stderr, "Usage: ./ReconstitueReseau fichier\n");
        return 1;
    }

    FILE *f =fopen(argv[1], "r");
    Chaines *c = lectureChaines(f);
    FILE *fic = fopen("burrrrma.txt", "w");
    Reseau *reseau = reconstitueReseauListe(c);
    char *entree;
    int rep;

    do{
        char buffer[BUFFERSIZE];
        menu();
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
        switch(rep){
            case 1: //LISTE CHAINEE
                ecrireReseau(reseau, fic); 
                afficheReseauSVG(reseau, "burrrrma.svg");             
                break;
            case 2: //TABLE DE HACHAGE
                // reseau = reconstitueReseauHachage(c,100);
                // ecrireReseau(reseau, fic); 
                // afficheReseauSVG(reseau, "burrrrma.svg");  
                break;
            case 3: //ARBRE QUATERNAIRE
                break;          
        }
    }while(rep!=0);
    if(!rep){
        return 0;
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic);   
    fclose(f);
    return 0;
}