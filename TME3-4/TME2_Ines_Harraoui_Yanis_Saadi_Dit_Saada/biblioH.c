#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "biblioH.h"

int fonctionClef(char *auteur){
    /*
    Retourne La clé de hachage à partir d'un auteur donné en calculant les valeurs ASCII de chaque lettre du nom
    
    Paramètre:
    auteur : nom de l'auteur 

    */

    int clef = 0,i=0;
    while (*(auteur+i)!='\0'){
        clef += (int)(*(auteur+i));
        i++;
    }
    return clef;
}

LivreH *creer_livre_H(int num, char *titre, char *auteur){
    /*
    Crée un nouveau livre avec les attributs donnés

    Paramètres:
    num,titre,auteur : attributs d'un livre
    */
    LivreH *new = malloc(sizeof(LivreH));
    if (!new) {
        return NULL;
    }
    new->clef = fonctionClef(auteur);
    new->num = num;
    new->titre = strdup(titre); 
    new->auteur = strdup(auteur);
    new->suivant = NULL;
    return new;
}


void liberer_livre_H(LivreH *l){
    /*
    Libère la mémoire allouée du livre l
    
    Paramètre :
    l: Livre à libérer
    */
    if (l){
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

BiblioH *creer_biblio_H(int m){
    /*
    Crée une nouvelle bibliothèque de livres avec une table de hachage de taille m

    Paramètres:
    m :taille de la table de hachage
    */
    BiblioH *new = malloc(sizeof(BiblioH));
    if (!new){
        free(new); 
        return NULL;
    }

    new->T = (LivreH**)malloc(m * sizeof(LivreH*));
    if (new->T == NULL){
        free(new);
        return NULL;
    }

    new->m = m;
    new->nE = 0;

    for (int i=0; i<m; i++){
        new->T[i] = NULL;
    }

    return new;
}

void liberer_biblio_H(BiblioH *b){
    /*
    Libère la mémoire occupée par chacun des livres puis celle de la bibliothèque

    Paramètre:
    b : bibliothèque
    */
    if (b){
        for (int i = 0; i<b->m; i++){
            LivreH *cour = b->T[i];
            while (cour){
                LivreH* tmp = cour;
                cour = cour->suivant;
                liberer_livre_H(tmp);
            }
        }
        free(b->T); 
        free(b);
    }
}

int fonctionHachage(int cle, int m){ 
    /*
    Renvoie l'indice de la clé dans la table de hachage, où un élément avec cette clé doit être stocké

    Paramètres:
    cle: clé de hachage calculée (ici, cle sera un appel à fonctionCle pour des raisons d'efficacité)
    m : taille de la table de hachage
    */
    return (int)floor(m*(cle*((sqrt(5)-1)/2)-floor(cle*((sqrt(5)-1)/2))));
}

void inserer(BiblioH *b, int num, char *titre, char *auteur){
    /*
    Insère un nouveau livre dans la bibliothèque de livres en utilisant la table de hachage.
    
    Paramètres:
    b: bibliothèque
    num,titre,auteur : attributs d'un livre
    */
    int ind=fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* new = creer_livre_H(num, titre, auteur);
    new->suivant = b->T[ind];
    b->T[ind] = new;
    b->nE++; //nb d'éléments+1
}

void afficherLivre_H(LivreH *l){
    /*
     Affiche les informations d'un livre

     Paramètre :
     l : livre à afficher
    */
    printf("Numéro: %d Titre: %s Auteur: %s\n",l->num,l->titre,l->auteur);
}

void afficherBiblio_H(BiblioH *b){
    /*
    Affiche chacun des livres dans la table de hachage d'une bibliothèque

    Paramètre :
    b : bibliothèque à afficher
    */

    for (int i=0; i<b->m; i++){
        LivreH* cour = b->T[i];
        while (cour){
            afficherLivre_H(cour);
            printf("\n");
            cour = cour->suivant;
        }
    }
}

LivreH* rechercheLivreNum_H(BiblioH *b, int num){
     /*
    Recherche un livre par son numéro dans une bibliothèque

    Paramètres :
    b: bibliothèque
    num: numéro du livre à rechercher
    */

    if (b == NULL){
        return NULL;
    }

    for (int i=0; i<b->m; i++){
        LivreH* l=b->T[i];
        while (l){
            if (l->num == num){
                return l;
            }
            l = l->suivant;
        }
    }
    // Retourne NULL si le livre n'est pas trouvé
    return NULL;
}

LivreH* rechercheLivreTitre_H(BiblioH *b, char *titre){
    /*
    Recherche un livre par son titre dans une bibliothèque

    Paramètres :
    b: bibliothèque
    titre: titre du livre à rechercher
    */

    if (b == NULL){
        return NULL;
    }

    for (int i=0; i<b->m; i++){
        LivreH* l = b->T[i];
        while (l){
            if (strcmp(l->titre, titre) == 0){
                return l;
            }
            l = l->suivant;
        }
    }
    // Retourne NULL si le livre n'est pas trouvé
    return NULL;
}

BiblioH* LivresAuteurs_H(BiblioH *b, char *auteur){
    /*
    Crée une nouvelle bibliothèque avec les livres d'un auteur donné

    Paramètres :
    b: bibliothèque d'origine
    auteur: auteur des livres à rechercher
    */

    if (b == NULL){
        return NULL;
    }
    
    BiblioH* res = creer_biblio_H(b->m);
    for (int i = 0; i < b->m; i++){
        LivreH* l = b->T[i];
        while (l){
            if (strcmp(l->auteur, auteur) == 0){
                inserer(res, l->num, l->titre, l->auteur);
            }
            l = l->suivant;
        }
    }
    return res;
}

void supprimerLivre_H(BiblioH *b, int num, char *titre, char *auteur){
    /*
    Supprime un livre de la bibliothèque

    Paramètres:
    b : bibliothèque
    num, titre, auteur : attribut du livre à supprimer

    */

    int ind = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* prec = NULL;
    LivreH* cour = b->T[ind];

    while (cour){
        if (cour->num == num && strcmp(cour->titre, titre) == 0 && strcmp(cour->auteur,auteur) == 0){
            if (prec==NULL){ //cas où le livre est en tete de la liste 
                b->T[ind]= cour->suivant;
            }else{
                prec->suivant = cour->suivant;
            }
            liberer_livre_H(cour);
            b->nE--; //diminue le nombre d'elements de 1
            return;
        }
        prec = cour;
        cour = cour->suivant;
    }
}

void fusion_H(BiblioH *b1,BiblioH *b2){
    /*
    Fusionne deux bibliothèques en ajoutant les livres de la table de hachage de la deuxième à la première

    Paramètres:
    b1 : première bibliothèque
    b2 : deuxième bibliothèque qui sera libérée après la fusion

    */

    if (b2->m == 0){
        liberer_biblio_H(b2);
    }

    for (int i=0; i<b2->m; i++){
        LivreH* cour = b2->T[i];

        //Parcourt les livres de la table de b2
        while (cour){
            LivreH* tmp=cour;
            cour = cour->suivant;            
            inserer(b1, tmp->num, tmp->titre, tmp->auteur);
        }
    }
    liberer_biblio_H(b2);
}

BiblioH* RecherchePlusieurs_H(BiblioH *b){
    /*
    Retourne une nouvelle bibliothèque contenant les livres ayant plusieurs exemplaires dans une bibliothèque donnée

    Paramètre:
    b: bibliothèque d'origine
    */

    BiblioH* bibliodoublon = creer_biblio_H(b->m);

    //Parcourt la table de hachage
    for (int i=0; i<b->m; i++){
        LivreH* livreActuel = b->T[i];

        //Parcourt le livre de la i-ème liste de la table
        while (livreActuel){

            //Calcule l'indice de hachage pour l'auteur du livre actuel
            int ind=fonctionHachage(fonctionClef(livreActuel->auteur), b->m);
            LivreH* livreCompare = b->T[ind];

            //Parcourt la liste chainée à cet indice
            while (livreCompare){
                if (livreActuel->num != livreCompare->num && strcmp(livreActuel->auteur, livreCompare->auteur) == 0 && strcmp(livreActuel->titre, livreCompare->titre) == 0){                        
                    //Insère le livre en double dans la nouvelle bibliothèque
                    inserer(bibliodoublon, livreActuel->num, livreActuel->titre, livreActuel->auteur);
                    break;
                }
                livreCompare = livreCompare->suivant;
            }
            livreActuel = livreActuel->suivant;
        }
    }
    return bibliodoublon;
}