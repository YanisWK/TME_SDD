#include <stdio.h>
#include "entreeSortieH.h"

int main(){

    // Création d'une bibliothèque biblio_LC
    BiblioH *b1 = creer_biblio_H(50);
    inserer(b1, 1, "Ascent", "Phoenix");
    inserer(b1, 2, "Lotus", "Raze");
    afficherBiblio_H(b1);
    printf("\n");

    // Recherche de livre par titre (l1) et par numéro (l2)
    LivreH *l1 = rechercheLivreTitre_H(b1, "Lotus"), *l2 = rechercheLivreNum_H(b1, 2);
    printf("Recherche par titre:\n");
    afficherLivre_H(l1);
    printf("\n");
    printf("Recherche par numéro:\n");
    afficherLivre_H(l2);
    printf("\n");

    BiblioH *b2 = creer_biblio_H(5); 
    inserer(b2, 3, "Haven", "Omen");
    inserer(b2, 4, "Breeze", "Yoru");
    printf("\n");

    // Fusion de b1 et b2
    BiblioH *bfusion = fusion_H(b1, b2);
    printf("Fusion de bibliothèques:\n");
    afficherBiblio_H(bfusion);
    printf("\n");

    // Enregistrement et chargement de la bibliothèque bfusion dans un fichier saved.txt
    enregistrer_biblio_H(bfusion, "saved.txt");
    BiblioH *bchargee = charger_n_entrees_H("saved.txt", 4, 5); 
    printf("Chargement de n entrées:\n");
    afficherBiblio_H(bchargee);
    printf("\n");

    
    inserer(bchargee, 5, "Lotus", "Raze");
    inserer(bchargee, 6, "Breeze", "Yoru");

    // Recherche d'exemplaires dans la bibliothèque bchargee
    BiblioH *bdouble = RecherchePlusieurs_H(bchargee);
    printf("Bibliothèque des livres à plusieurs exemplaires:\n");
    afficherBiblio_H(bdouble);

    // Suppression d'un livre
    supprimerLivre_H(bchargee, 4, "Breeze", "Yoru");
    printf("Suppression d'un livre de la bibliothèque bchargee:\n");
    afficherBiblio_H(bchargee);
    printf("\n");

    // Libération de la mémoire
    liberer_biblio_H(b1);
    liberer_biblio_H(bfusion);
    liberer_biblio_H(bchargee);
    liberer_biblio_H(bdouble);

    return 0;
}
