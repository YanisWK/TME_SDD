#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre_LC(int num,char* titre,char* auteur){
    /*
    Retourne le livre d'attributs num, titre, auteur

    Paramètres :
    num, titre, auteur : attribut du livre à créer
    */

    Livre *new= malloc(sizeof(Livre));
    new->num= num;
    new->titre=strdup(titre);
    new->auteur=strdup(auteur);
    new->suiv=NULL;
    return new;
}

void liberer_livre_LC(Livre *l){
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

Biblio* creer_biblio_LC(){
    /*
    Retourne une bibliothèque vide
    */

    Biblio *new = malloc(sizeof(Biblio));
    new->L= NULL;
    return new;
}

void liberer_biblio_LC(Biblio* b){
    /*
    Libère l'espace alloué pour chacun des livres d'une bibliothèque

    Paramètre :
    b : bibliothèque à libérer
    */

    if(b==NULL){
        return;
    }
    Livre *cour = b->L;
    while(cour){
        Livre *tmp=cour;
        cour=cour->suiv;
        liberer_livre_LC(tmp);
    }
    free(b);
}

void inserer_en_tete_LC(Biblio* b,int num,char* titre,char* auteur){
    /*
    Insère un livre en tête d'une bibliothèque

    Paramètres:
    b : bibliothèque
    num, titre, auteur : attribut du livre à créer
    */

    Livre *tete=creer_livre_LC(num,titre,auteur);
    tete->suiv=b->L;
    b->L=tete;
}


void afficherLivre_LC(Livre *l){
    /*
     Affiche les informations d'un livre

     Paramètre :
     l : livre à afficher
    */

    if (l){
        printf("Numéro : %d\n", l->num);
        printf("Titre : %s\n", l->titre);
        printf("Auteur : %s\n", l->auteur);
    }
}

void afficherBiblio_LC(Biblio *b){
    /*
    Affiche chacun des livres d'une bibliothèque

    Paramètre :
    b : bibliothèque à afficher
    */

    Livre *cour = b->L; 
    while (cour){
        afficherLivre_LC(cour);
        printf("\n");
        cour = cour->suiv;
    }
}

Livre* rechercheLivreNum_LC(Biblio *b,int num){
    /*
    Recherche un livre par son numéro dans une bibliothèque

    Paramètres :
    b: bibliothèque
    num: numéro du livre à rechercher
    */

    if (b == NULL){
        return NULL;
    }

    Livre *cour=b->L;
    while(cour){
        if(cour->num==num){
            return (cour);
        }
        cour=cour->suiv;
    }
    // Retourne NULL si le livre n'est pas trouvé
    return NULL;
}

Livre* rechercheLivreTitre_LC(Biblio *b,char* titre){
    /*
    Recherche un livre par son titre dans une bibliothèque

    Paramètres :
    b: bibliothèque
    titre: titre du livre à rechercher
    */

    if (b == NULL){
        return NULL;
    }

    Livre* cour=b->L;
    while(cour){
        if(strcmp(cour->titre,titre)==0){
            return(cour);
        }
        cour=cour->suiv;
    }
    // Retourne NULL si le livre n'est pas trouvé
    return NULL;
}

Biblio* LivresAuteurs_LC(Biblio*b,char* auteur){
    /*
    Crée une nouvelle bibliothèque avec les livres d'un auteur donné

    Paramètres :
    b: bibliothèque d'origine
    auteur: auteur des livres à rechercher
    */

    if (b == NULL){
        return NULL;
    }
    
    Biblio *BiblioAut=creer_biblio_LC();
    Livre* cour=b->L;
    while(cour){
        if(strcmp(cour->auteur,auteur)==0){
            inserer_en_tete_LC(BiblioAut,cour->num,cour->titre,auteur);
        }
        cour=cour->suiv;
    }
    return BiblioAut;
}


void supprimerLivre_LC(Biblio* b, int num, char* titre, char* auteur){
    /*
    Supprime un livre de la bibliothèque

    Paramètres:
    b : bibliothèque
    num, titre, auteur : attribut du livre à supprimer

    */

    Livre* prec = NULL, * cour = b->L;

    while (cour){
        if (cour->num == num && strcmp(cour->titre, titre) == 0 && strcmp(cour->auteur, auteur) == 0){
            //si le livre est trouvé

            if (!prec){  //cas où le livre se trouve en tête de liste                
                b->L = cour->suiv;
            }else{
                prec->suiv = cour->suiv;
            }
            liberer_livre_LC(cour); //supprime le livre
            return;
        }
        prec = cour;
        cour = cour->suiv;
    }
}

void fusion_LC(Biblio *b1, Biblio *b2){
    /*
    Fusionne deux bibliothèques en ajoutant les livres de la deuxième à la première

    Paramètres:
    b1 : première bibliothèque
    b2 : deuxième bibliothèque qui sera libérée après la fusion

    */

    Livre *cour2 = b2->L;

    while (cour2){
        inserer_en_tete_LC(b1, cour2->num, cour2->titre, cour2->auteur);
        cour2 = cour2->suiv;
    }
    liberer_biblio_LC(b2);
}


Biblio* RecherchePlusieurs_LC(Biblio* b){
    /*
    Retourne une nouvelle bibliothèque contenant les livres ayant plusieurs exemplaires dans une bibliothèque donnée

    Paramètre:
    b: bibliothèque d'origine
    */
    Biblio* Bibliodoublon = creer_biblio_LC();
    Livre* Livreactuel = b->L;

    while (Livreactuel) {
        Livre* Livrecompare = b->L;
        while (Livrecompare){
            if (Livreactuel->num != Livrecompare->num && strcmp(Livreactuel->auteur, Livrecompare->auteur) == 0 &&
                strcmp(Livreactuel->titre, Livrecompare->titre) == 0){
                inserer_en_tete_LC(Bibliodoublon, Livreactuel->num, Livreactuel->titre, Livreactuel->auteur);
                break;
            }
            Livrecompare = Livrecompare->suiv;
        }

        Livreactuel = Livreactuel->suiv;
    }
    return Bibliodoublon;
}
