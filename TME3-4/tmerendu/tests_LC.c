#include <stdio.h>
#include "entreeSortieLC.h"

int main(){

    // Création d'une bibliothèque biblio_LC
    Biblio *b1 = creer_biblio_LC();
    inserer_en_tete_LC(b1, 1, "Ascent", "Phoenix");
    inserer_en_tete_LC(b1, 2, "Lotus", "Raze");
    afficherBiblio_LC(b1);
    printf("\n");

    // Recherche de livre par titre (l1) et par numéro (l2)
    // Livre *l1 = rechercheLivreTitre_LC(b1, "Lotus"),*l2 = rechercheLivreNum_LC(b1, 2);
    // printf("Recherche par titre:\n");
    // afficherLivre_LC(l1);
    // printf("\n");
    // printf("Recherche par numéro:\n");
    // afficherLivre_LC(l2);
    // printf("\n");
    
    Biblio *b2 = creer_biblio_LC();
    inserer_en_tete_LC(b2, 3, "Haven", "Omen");
    inserer_en_tete_LC(b2, 4, "Breeze", "Yoru");
    afficherBiblio_LC(b2);
    printf("\n");

    // Fusion de b1 et b2
    fusion_LC(b1, b2);
    printf("Fusion de bibliothèques:\n");
    afficherBiblio_LC(b1);
    printf("\n");

    // Enregistrement et chargement de la bibliothèque bfusion dans un fichier saved.txt
    enregistrer_biblio_LC(b1, "saved.txt");
    Biblio *bchargee = charger_n_entrees_LC("saved.txt", 4);
    printf("Chargement de n entrées:\n");
    afficherBiblio_LC(bchargee);
    printf("\n");

    inserer_en_tete_LC(bchargee, 5, "Lotus", "Raze");
    inserer_en_tete_LC(bchargee, 6, "Breeze", "Yoru");

    enregistrer_biblio_LC(bchargee,"saved.txt");
    // Recherche d'exemplaires dans la bibliothèque bchargee
    Biblio *bdouble = RecherchePlusieurs_LC(bchargee);
    printf("Bibliothèque des livres à plusieurs exemplaires:\n");
    afficherBiblio_LC(bdouble);

    // Suppression d'un livre
    supprimerLivre_LC(bchargee, 4, "Breeze", "Yoru");
    printf("Suppression d'un livre de la bibliothèque bchargee:\n");
    afficherBiblio_LC(bchargee);
    printf("\n");

    // // Libération de la mémoire
    liberer_biblio_LC(b1);
    // liberer_biblio_LC(bdouble);
    //liberer_biblio_LC(bchargee);

    return 0;
}