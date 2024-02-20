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
    printf("7 - Fusion_fusion_LCner deux bibliothèques\n");
    printf("8 - Rechercher tous les exemplaires de chaque ouvrage d'une bibliothèque\n"); // Nouvelle option

    /*Peut etre ajout de la fusion_LC et on doit ajouter le cas recherche tout les ouvrages avec plusieurs exemplaire*/
    printf("Que voulez vous faire ?\n");
}

void choixStructure(){
    printf("1 - Structure Liste Chainées\n");
    printf("2 - Structure Hachage\n");
    printf("Quel structure voulez vous utilisez ?\n");

}


int main(int argc, char** argv){
    if (argc != 3){
        printf("Erreur ./main <nomfichier> <un nombre>\n");
        exit(1);
    }

    Biblio *B = charger_n_entrees_LC(argv[1],atoi(argv[2]));    
    
    // enregistrer_biblio(b, "saved.txt");

    // Biblio *b1= creer_biblio_LC();
    // Biblio *b2= creer_biblio_LC();

    // inserer_en_tete_LC(b1,1,"Spy x Family 1","Tatsuya Endo");
    // inserer_en_tete_LC(b1,2,"Spy x Family 2","Tatsuya Endo");    
    // inserer_en_tete_LC(b2,3,"Spy x Family 3","Tatsuya Endo");
    // inserer_en_tete_LC(b2,4,"Spy x Family 4","Tatsuya Endo");

    // Biblio *b3 = fusion_LC(b1,b2);
    // supprimerLivre_LC(b3,2,"Spy x Family 2","Tatsuya Endo");
    // afficherBiblio_LC(b3);
    
    // inserer_en_tete_LC(b1,3,"Spy x Family 3","Tatsuya Endo");
    // inserer_en_tete_LC(b1,4,"Spy x Family 2","Tatsuya Endo");

    Biblio *b4 = RecherchePlusieurs_LC(b4);
    //afficherBiblio_LC(b4);
    
    // liberer_biblio_LC(b4);
    //liberer_biblio_LC(b3);
    // liberer_biblio_LC(b2);
    // liberer_biblio_LC(b1);


    char *entree;
    int rep;
    int choix;
    choixStructure();
    char buffer[BUFFERSIZE];
    entree=fgets(buffer,BUFFERSIZE,stdin);
    choix=atoi(entree);

    if(choix==1){
        do{
            menu();
            entree=fgets(buffer,BUFFERSIZE,stdin);
            rep=atoi(entree);
            int num;
            char titre[256];
            char auteur[256];
            
        switch(rep){
            case 1:
                printf("Affichage :\n");
                afficherBiblio_LC(B);
                break;
            case 2:
                /*Pour le numero faire le cas où le numero est déjà present dans la biblio*/            
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
                inserer_en_tete_LC(B,num,titre,auteur);
                printf("Insertion realisé ! \n");
                break;

            case 3:
                printf("Veuillez entree le numero de l'oeuvre que vous voulez trouver\n");
                entree=fgets(buffer,BUFFERSIZE,stdin);
                num=atoi(entree);
                if(num==0 || entree[0]=='\n'){
                    printf("Erreur format\n");
                    break;
                }
                Livre *book=rechercheLivreNum_LC(B,num);
                if (book){
                    printf("Oeuvre trouvé !\n");
                    afficherLivre_LC(book);
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
                book=rechercheLivreTitre_LC(B,entree);
                if (book){
                    printf("Oeuvre trouvé !\n");
                    afficherLivre_LC(book);
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
                Biblio *Bibauteur=LivresAuteurs_LC(B,entree);
                if(Bibauteur->L){
                    printf("Livres de l'auteur trouvé !\n");
                    afficherBiblio_LC(Bibauteur);
                    
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
                supprimerLivre_LC(B,num,titre,auteur);
                //printf("Si le livre etait bien dans la bibliotheque et bien il n'y est plu\n");

        }
    }while(rep!=0);

    }
    

    
    return 0;
}