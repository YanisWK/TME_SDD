#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFERSIZE 256

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
    if(atoi(argv[2])==0){
        return 0;
    }else{
        if (atoi(argv[2])>3 || atoi(argv[2])<0 || argv[1]==NULL){
            printf("Fichier ou entier invalide");
        }else{
            if(atoi(argv[2])==1){ //LISTE CHAINEE
                reseau = reconstitueReseauListe(c);
                ecrireReseau(reseau, fic1);
                afficheReseauSVG(reseau, "burmaliste.svg");             
            }else if (atoi(argv[2])==2){ //TABLE DE HACHAGE
                int M = 50; 
                reseau = reconstitueReseauHachage(c, M);
                ecrireReseau(reseau, fic2);            
                afficheReseauSVG(reseau, "burmahachage.svg");  
            }else{ //ARBRE QUATERNAIRE
                reseau = reconstitueReseauArbre(c);
                ecrireReseau(reseau, fic3);
                afficheReseauSVG(reseau, "burmaarbre.svg"); 
                     
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