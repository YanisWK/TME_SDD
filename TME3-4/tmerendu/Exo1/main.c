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
        int num;
        char titre[256];
        char auteur[256];
        //scanf(" %d",&rep);
        switch(rep){
            case 1:
                printf("Affichage :\n");
                afficherBiblio(B);
                break;
            case 2:
            /*peut être je peux changer la variable entree par le buffer*/

                printf("Veuillez ecrire le numero le titre et enfin l'auteur de l'ouvrage.\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);

                num=atoi(entree);
                if(entree[0]=='\n'|| num==0){
                    printf("Erreur format\n");
                    break;
                }
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }              
                strcpy(titre,entree);
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                strcpy(auteur,entree);
                inserer_en_tete(B,num,titre,auteur);
                printf("Insertion realisé ! \n");
                break;

                //printf("num : %d\n titre : %s\n auteur : %s\n",num,titre,auteur);

            case 3:
                printf("Veuillez entree le numero de l'oeuvre que vous voulez trouver\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);
                num=atoi(entree);
                if(num==0 || entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                Livre *book=rechercheLivreNum(B,num);
                if (book){
                    printf("Oeuvre trouvé !\n");
                    afficherLivre(book);
                    break;
                }
                printf("L'oeuvre numero %d n'existe pas.\n",num);
                break;
                
            case 4:
                printf("Veuillez entree le titre de l'oeuvre que vous voulez trouver\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                book=rechercheLivreTitre(B,entree);
                if (book){
                    printf("Oeuvre trouvé !\n");
                    afficherLivre(book);
                    break;
                }
                printf("L'oeuvre %s n'existe pas.\n",entree);
                break;
            case 5:
                printf("Veuillez entree le nom de l'auteur.\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                Biblio *Bibauteur=BiblioAuteur(B,entree);
                if(Bibauteur){
                    printf("Livres de l'auteur trouvé !\n");
                    afficherBiblio(Bibauteur);
                    
                    break;
                }
                printf("Il n'y a pas de livre écris par cet auteur !\n");
                break;
            case 6:
                printf("Veuillez entree le numero le titre et l'auteur de l'ouvrage a supprimé\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);

                num=atoi(entree);
                if(entree[0]=='\n'|| num==0){
                    printf("Erreur format\n");
                    break;
                }
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }              
                strcpy(titre,entree);
                entree=fgets(buffer,BUFFERSIZE,stdin);
                if(entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                strcpy(auteur,entree);
                printf("Supression en cours du livre de numero %d de nom %s d'auteur %s \n",num,titre,auteur);
                supprimerLivre(B,num,titre,auteur);
                //printf("Si le livre etait bien dans la bibliotheque et bien il n'y est plu\n");

        }
    }while(rep!=0);

    
    return 0;
}