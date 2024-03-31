#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
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
    FILE *fic1 = fopen("burmaliste.txt", "w");
    FILE *fic2 = fopen("burmahachage.txt", "w");
    FILE *fic3 = fopen("burmaarbre.txt", "w");

    Reseau *reseau = NULL;

    char *entree;
    int rep;

    do{
        char buffer[BUFFERSIZE];
        menu();
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
         if (sscanf(entree, "%d", &rep) != 1) {
            printf("Entrée invalide. Usage : <un entier>\n");
        }
        switch(rep){
            case 1: //LISTE CHAINEE
                reseau = reconstitueReseauListe(c);
                ecrireReseau(reseau, fic1); 
                afficheReseauSVG(reseau, "burmaliste.svg");             
                break;
            case 2: //TABLE DE HACHAGE
                int M = 70;
                reseau = reconstitueReseauHachage(c, M);
                ecrireReseau(reseau, fic2); 
                afficheReseauSVG(reseau, "burmahachage.svg");  
                break;
            case 3: //ARBRE QUATERNAIRE
                ArbreQuat *a = NULL; 
                double xmin, ymin, xmax, ymax;
                chaineCoordMinMax(c, &xmin, &ymin, &xmax, &ymax);
                a = creerArbreQuat((xmin+xmax)/2, (ymin+ymax)/2, xmax-xmin, ymax-ymin);
                afficherArbreQuat(a);
                reseau = reconstitueReseauArbre(c);
                ecrireReseau(reseau, fic3);
                afficheReseauSVG(reseau, "burmaarbre.svg");             
                break;          
        }
    }while(rep!=0);
    if(!rep){
        return 0;
    }

    libererChaines(c);
    libererReseau(reseau);
    fclose(fic1);   
    fclose(fic2);   
    fclose(fic3);   
    fclose(f);
    return 0;
}