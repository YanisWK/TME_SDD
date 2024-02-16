#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

#define BUFFERSIZE 256

void menu(){
    printf("0 - Sortir du programme\n");
    printf("1 - Affichage\n");
    printf("2 - Inserer ouvrage\n");
    printf("3 - Rechercher ouvrage par numéro\n");
    printf("4 - Rechercher ouvrage par titre\n");
    printf("5 - Rechercher tous les livres d'un même auteur\n");
    printf("6 - Supprimer  ouvrage\n");

    printf("Que voulez vous faire ?\n");

}


int main(int argc, char** argv){
    // if (argc != 3){
    //     printf("Erreur ./main <nomfichier> <un nombre>\n");
    //     exit(1);
    // }

    // Biblio *b = charger_n_entrees(argv[1],atoi(argv[2]));    
    
    // enregistrer_biblio(b, "saved.txt");

    Biblio *b1= creer_biblio();
    Biblio *b2= creer_biblio();

    inserer_en_tete(b1,1,"Spy x Family 1","Tatsuya Endo");
    inserer_en_tete(b1,2,"Spy x Family 2","Tatsuya Endo");    
    inserer_en_tete(b2,3,"Spy x Family 3","Tatsuya Endo");
    inserer_en_tete(b2,4,"Spy x Family 4","Tatsuya Endo");

    // Biblio *b3 = fusion(b1,b2);
    // supprimerLivre(b3,2,"Spy x Family 2","Tatsuya Endo");
    // afficherBiblio(b3);
    
    inserer_en_tete(b1,3,"Spy x Family 3","Tatsuya Endo");
    inserer_en_tete(b1,4,"Spy x Family 2","Tatsuya Endo");

    Biblio *b4 = RecherchePlusieurs(b1);
    //afficherBiblio(b4);
    
    liberer_biblio(b4);
    //liberer_biblio(b3);
    liberer_biblio(b2);
    liberer_biblio(b1);

    Biblio* B=creer_biblio();
    char *entree;
    int rep;
    do{
        char buffer[BUFFERSIZE];
        menu();
        entree=fgets(buffer,BUFFERSIZE,stdin);
        rep=atoi(entree);
        //scanf(" %d",&rep);
        switch(rep){
            case 1:
                printf("Affichage :\n");
                afficherBiblio(B);
                break;
            case 2:
                int num;
                char titre[256];
                char auteur[256];
                printf("Veuillez ecrire le numero puis le nom et enfin l'auteur de l'ouvrage.\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);
                
                num=atoi(entree);
                entree=fgets(buffer,BUFFERSIZE,stdin);
                strcpy(titre,entree);
                entree=fgets(buffer,BUFFERSIZE,stdin);
                strcpy(auteur,entree);
                //printf("num %d titre %s auteur %s\n",num,titre,auteur);




            case 3:
            case 4:
            case 5:
            case 6:
        }
    }while(rep!=0);

    
    return 0;
}