#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Hachage.h"

#define A (sqrt(5)-1)/2

TableHachage * CreeTableHachage(int tailleMax){
    /*Crée une nouvelle table de hachage avec une taille maximale donnée.

    Paramètre :
    - tailleMax : taille maximale de la table de hachage
    */
    TableHachage *Table = (TableHachage *)malloc(sizeof(TableHachage));
    Table->nbElement=0;
    Table->tailleMax=tailleMax;
    Table->T=malloc(sizeof(CellNoeud *)*tailleMax);
    for(int i=0;i<tailleMax;i++){
        Table->T[i]=NULL;
    }
    return Table;
}

int f(int x, int y){
    /* Calcule la clé de hachage pour un point donné.

    Paramètres :
    - x,y : coordonnées du point
    */
    return y + ((x + y)*(x + y + 1)/2);
}

int h(int k,int M){
    /*Fonction de hachage pour une table de hachage de taille M.
    Retourne la position dans la table de hachage calculée à partir de la clé k et de la taille M.

    Paramètres :
    - k : clé de hachage.
    - M : taille de la table de hachage.
    */
    return((int) (M*((k*A)-(int)(k*A))));
}


Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    /*Recherche un nœud dans un réseau ou en crée un nouveau s'il n'existe pas déjà.

    Paramètres :
    - R : réseau de chaines
    - H : table de hachage qui stocke les noeuds
    - x,y : coordonnées du noeud à trouver ou créer
    */

    // Calculer la clé de hachage pour les coordonnées du noeud
    int cles = f((int) x, (int) y);

    // Trouver la position dans la table de hachage
    int pos = h(cles, H->tailleMax);

    // Crée pointeur pour parcourir la liste de la position pos
    CellNoeud* cour = H->T[pos];

    // Parcourt la liste chaînée et vérifie si lz noeud existe déjà
    while (cour){
        if ((cour->nd->x == x) && (cour->nd->y == y)){
            return cour->nd;
        }
        cour = cour->suiv;
    }
    Noeud *nd =(creerNoeud(R->nbNoeuds+1,x,y,NULL));
    
    // Créer un nouveau nœud et l'ajoute à la table de hachage
    CellNoeud *pos_Hachage = creerCellNoeud(nd);
    pos_Hachage->suiv = H->T[pos];
    H->T[pos] = pos_Hachage;

    // Ajoute le nœud au réseau
    CellNoeud *pos_Reseau = creerCellNoeud(nd);
    pos_Reseau->suiv =  R->noeuds;
    R->noeuds = pos_Reseau;
    R->nbNoeuds += 1;
    return nd;
}


Reseau * reconstitueReseauHachage(Chaines *C,int M){
    /*Reconstitue un réseau en utilisant une table de hachage pour accélérer le processus.

    Paramètres :
    - C : liste des chaînes pour reconstituer le réseau
    - M : taille de la table de hachage
    */
    Reseau * R=creerReseau(C); // Crée un réseau vide à partir de la liste de chaînes
    TableHachage *H=CreeTableHachage(M); // Crée une table de hachage de taille M
    CellCommodite * commodites=NULL; // Initialise la liste des commodités
    CellChaine * chaines=C->chaines; // Pointeur sur la tête de liste des chaînes
    Noeud *ExtrA=NULL;
    Noeud *ExtrB=NULL;

    while(chaines){
        CellPoint *points=chaines->points; // Pointeur sur la tête de points de la chaîne
        Noeud * V=NULL; // Crée pointeur pour stocker le noeud précédent
        ExtrA=rechercheCreeNoeudHachage(R,H,points->x,points->y);  // Recherche ou crée un nœud pour le premier point
        while(points){
            // Recherche ou crée un nœud pour chaque point de la chaîne
            Noeud *cour=rechercheCreeNoeudHachage(R,H,points->x,points->y);
            if(V){ // Si ce n'est pas le premier point de la chaîne
                insererVoisins(V,cour); // Lie le nœud actuel au nœud précédent en tant que voisins
                insererVoisins(cour,V); // Et inversement
            }
            V=cour; // Met à jour le nœud précédent

            if(!points->suiv){  // Si ce point est le dernier point de la chaîne
                // Recherche ou crée un nœud pour ce point et l'assigne à ExtrB
                ExtrB=rechercheCreeNoeudHachage(R,H,points->x,points->y); 
            }
            points = points->suiv;
        }
        // Si une commodité entre ExtrA et ExtrB n'existe pas déjà,
        // On ajoute cette commodité à la liste des commodités
        if(!rechercheCommodite(commodites,ExtrA,ExtrB)){
            commodites=ajout_teteCellCommodite(commodites,ExtrA,ExtrB);
        }
        chaines = chaines->suiv;
    }
    R->commodites=commodites; // Assigne la liste des commodités au réseau
    LibererTableHachage(H); // Libère la mémoire de la table de hachage 
    return R;
}
void LibererTableHachage(TableHachage *table) {
    /* Libère la mémoire allouée pour une table de hachage.

    Paramètre :
    - table : pointeur vers la table de hachage à libérer
    */

    if (table == NULL) return;

    for (int i = 0; i<table->tailleMax; i++){
        CellNoeud *p = table->T[i]; //récupère la tête de chaque liste de la table
        while (p){
            // Libère chaque liste à l'aide d'une variable temporaire
            CellNoeud *temp = p;
            p = p->suiv;
            free(temp);
        }
    }

    free(table->T);
    free(table);
}
