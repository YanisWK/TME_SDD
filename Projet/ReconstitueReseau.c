#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFERSIZE 256

void menu(){
    printf("0- Sortir du programme\n");
    printf("1- Liste Chainée\n");
    printf("2- Table de Hachage\n");
    printf("3- Arbre\n");
    printf("Quelle structure voulez vous choisir ?\n");
}

int main(int argc, char *argv[]){
    
    if (argc!=3){
        fprintf(stderr, "Usage: ./ReconstitueReseau nom_fichier entier\n");
        return 1;
    }

    FILE *f =fopen(argv[1], "r");
    Chaines *c = lectureChaines(f);
    FILE *fic1 = fopen("burmaliste.txt", "w");
    FILE *fic2 = fopen("burmahachage.txt", "w");
    FILE *fic3 = fopen("burmaarbre.txt", "w");


    Reseau *reseau = NULL;
    char buffer[BUFFERSIZE];
    menu();
    if(argv[2]==0){
        return 0;
    }else{
        if (argv[2]>3 || argv[2]<0 || argv[1]==NULL){
            printf("Fichier ou entier invalide");
        }else{
            if(argv[2]==1){ //LISTE CHAINEE
                reseau = reconstitueReseauListe(c);
                ecrireReseau(reseau, fic1);
                afficheReseauSVG(reseau, "burmaliste.svg");             
                break;
            }else if argv[2]==2){ //TABLE DE HACHAGE
                int M = 50; 
                reseau = reconstitueReseauHachage(c, M);
                ecrireReseau(reseau, fic2);            
                afficheReseauSVG(reseau, "burmahachage.svg");  
                break;
            }else{ //ARBRE QUATERNAIRE
                reseau = reconstitueReseauArbre(c);
                ecrireReseau(reseau, fic3);
                afficheReseauSVG(reseau, "burmaarbre.svg");             
                break;  
            }        
        }
    }
    
    libererChaines(c);
    libererReseau(reseau);
    fclose(fic1);   
    fclose(fic2);   
    fclose(fic3);   
    fclose(f);
    return 0;
}