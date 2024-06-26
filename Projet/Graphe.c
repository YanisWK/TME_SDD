#include "Graphe.h"
#include <stdio.h>
#include <stdlib.h>


Arete *creer_arete(int u, int v){
    /* Crée une arête entre deux sommets.

   Paramètres :
   - u : identifiant du premier sommet
   - v : identifiant du deuxième sommet
   */
    Arete *new = malloc(sizeof(Arete));
    new->u = u;
    new->v = v;
    return new;
}

Cellule_arete * creer_cellarete(Arete *a){
    /* Crée une cellule d'arête contenant une arête.

   Paramètre :
   - a : arête 
   */
    Cellule_arete *new = malloc(sizeof(Cellule_arete));
    new->a = a;
    new->suiv = NULL;
    return new;
}

Sommet *creer_sommet(int num, int x, int y){
    /* Crée un sommet.

    Paramètres :
    - num : identifiant 
    - x,y : coordonnées du sommet
    */
    Sommet *new = malloc(sizeof(Sommet));
    new->num = num;
    new->x = x;
    new->y = y;
    new->L_voisin = NULL;
    return new;
}

Commod creer_commod(int e1, int e2){
    /* Crée une commodité avec deux extrémités.

    Paramètres :
    - e1 : identifiant de la première extrémité
    - e2 : identifiant de la deuxième extrémité
    */
    Commod new;
    new.e1 = e1;
    new.e2 = e2;
    return new;
}

Cellule_arete *ajout_teteCellule_arete(Cellule_arete *ca, Sommet *u, Sommet *v){
    /* Ajoute une cellule d'arête en tête d'une liste de cellules d'arête.

    Paramètres :
    - ca : liste de cellules d'arête
    - u : sommet de départ 
    - v : sommet d'arrivée 
    */
    Arete *a = creer_arete(u->num, v->num);
    if (!a) return ca;
    Cellule_arete *tete = creer_cellarete(a);
    tete->suiv = ca;
    return tete;
}


void ajout_commod(int e1, int e2, Graphe *g){
    /* Ajoute une commodité à un graphe.

    Paramètres :
    - e1 : identifiant de la première extrémité
    - e2 : identifiant de la deuxième extrémité
    - g : graphe
    */
    Commod new = creer_commod(e1, e2);
    g->T_commod[g->nbcommod]=new;  
    g->nbcommod ++;
}

void ajout_sommet(int x, int y, int num, Graphe *g){
    /* Ajoute un sommet à un graphe.
    Paramètres :
    - x,y : coordonnées du sommet
    - num : identifiant du sommet
    - g : graphe
    */
    Sommet * new = creer_sommet(num, x, y);
    g->T_som[num] = &(*new);  
    g->nbsom ++;
}

void insererVoisinsArete(Sommet* u, Sommet* v){
    /* Insère une arête reliant deux sommets.

    Paramètres :
    - u : premier sommet de l'arête
    - v : deuxième sommet de l'arête 
    */
    Arete *a = creer_arete(u->num, v->num);
    if (!a) return;
    Cellule_arete *new = creer_cellarete(a); 
    if (!new){
        free(a); 
        return;
    }
    if (!u->L_voisin){
        u->L_voisin = new;
    }else{
        new->suiv = u->L_voisin; 
        u->L_voisin = new; 
    }
}

Graphe* creerGraphe(Reseau* r){
    /* Crée un graphe à partir d'un réseau.

    Paramètre :
    - r : réseau
    */
    int nbnoeuds = 0; 
    CellNoeud *pr = r->noeuds;

    // Calcul du nombre de noeuds en parcourant la liste de noeuds du réseau
    while(pr){ 
        nbnoeuds++;
        pr = pr->suiv;
    }

    Sommet **T_som = malloc(sizeof(Sommet*)*(nbnoeuds+1));

    // Calcul du nombre de commodités dans le réseau
    int nbCommod = nbCommodites(r);

    // Parcours de la liste de noeuds du réseau
    pr = r->noeuds;
    while(pr){
        // Création des sommets du graphe à partir des noeuds
        T_som[pr->nd->num] = creer_sommet(pr->nd->num, pr->nd->x, pr->nd->y);
        pr = pr->suiv;
    }

    pr = r->noeuds;
    // Ajout des arêtes en parcourant les voisins de chaque noeud
    while (pr){
        CellNoeud *v = pr->nd->voisins;
        while (v){
            Sommet *voisin = T_som[v->nd->num]; 
            insererVoisinsArete(T_som[pr->nd->num], voisin);
            v = v->suiv;
        }
        pr = pr->suiv;
    }
    
    // Création du graphe
    Graphe *g = malloc(sizeof(Graphe));
    g->T_som = T_som;
    g->T_commod = malloc(sizeof(Commod)*nbCommod); 
    g->nbsom = nbnoeuds;
    g->nbcommod = 0; 
    
    // Ajout des commodités
    CellCommodite *commodites = r->commodites;
    int i=0;
    while (commodites){
        g->T_commod[i].e1 = commodites->extrA->num;
        g->T_commod[i].e2 = commodites->extrB->num;
        commodites = commodites->suiv;
        g->nbcommod++;
        i++;
    }

    return g;
}


CellChaine * plusCourtChemin(Graphe *g, int u, int v){
    /* Trouve le plus court chemin entre deux sommets.

    Paramètres :
    - g : graphe
    - u : identifiant du premier sommet
    - v : identifiant du deuxième sommet
    */
    // Allocation d'une file pour le parcours en largeur
    S_file *file=malloc(sizeof(S_file)); 
    Init_file(file); 

    // Enfile le sommet de départ u
    enfile(file, u); 
    int valu;

    // Création des tableaux pour le parcours en largeur
    int *tabvisite = (int*)malloc(sizeof(int)*(g->nbsom+1));
    int *tabPere=(int*)malloc(sizeof(int)*(g->nbsom+1));
    for(int i=1;i<g->nbsom;i++){
        tabvisite[i]=0;
        tabPere[i]=0;
    }
    tabvisite[u] = 1; 
    tabPere[u]=-1;

    // Parcours en largeur jusqu'à atteindre v ou parcourir tous les sommets du graphe
    while (!estFileVide(file)){
        int valu=defile(file);
        if(valu==v){
            break;
        }
        // Parcours des voisins du sommet valu
        Cellule_arete * cour=g->T_som[valu]->L_voisin;
        while(cour!=NULL){
            int valv=cour->a->v;
            // Si voisin pas visité, on l'enfile et met dans le tableau des prédécesseurs
            if(tabvisite[valv]==0){
                tabvisite[valv]=1;
                enfile(file,valv);
                tabPere[valv]=valu;
            }
            cour=cour->suiv;
        }
    }
    valu=v;
    int C=0;
    // Création d'une liste pour stocker le chemin
    CellChaine * parcours=malloc(sizeof(CellChaine));
    parcours->numero=v;
    parcours->points=NULL;
    // Reconstruction du chemin à partir du tableau des prédécesseurs
    while(valu!=-1){
        valu=tabPere[valu];
        if(valu==-1){
            continue;
        }else{
            C+=1;
            parcours=inserer_teteCC(parcours,valu,NULL);
        }
    }
    // Libération de la mémoire allouée dynamiquement
    free(tabvisite);
    free(tabPere);
    return parcours;
}


int reorganiseReseau(Reseau *r){
    /* Réorganise un réseau qui satisfait gamma.

    Paramètre :
    - r : réseau
    */
   // Création du graphe
    Graphe * G=creerGraphe(r);
    // Création de la matrice pour le comptage des arêtes entre les sommets
    int **matrice=malloc(sizeof(int*)*(G->nbsom+1));
    for(int i=0;i<G->nbsom+1;i++){
        matrice[i]=malloc(sizeof(int)*(G->nbsom+1));
        for(int j=0;j<G->nbsom+1;j++){
            matrice[i][j]=0;
        }
    }
    // Création du tableau de listes chainées pour stocker les chemins des commodités
    CellChaine **chaineCommod=malloc(sizeof(CellChaine *)*G->nbcommod);
    for(int i=0;i<G->nbcommod;i++){
        // On trouve le plus court chemin entre les extrémités de la commodité
        chaineCommod[i]=plusCourtChemin(G,G->T_commod[i].e1,G->T_commod[i].e2);

        CellChaine * prec=chaineCommod[i];
        CellChaine * courant=prec->suiv;

        // Parcours du chemin et mise à jour de la matrice
        while(courant && prec){
            matrice[prec->numero][courant->numero]+=1;
            matrice[courant->numero][prec->numero]+=1;
            prec=courant;
            courant=courant->suiv;
        }
    }

    // Affichage de la matrice et vérification des conditions de gamma
    for(int i=1;i<G->nbsom+1;i++){
        printf("\n");
        for(int j=1;j<G->nbsom+1;j++){
            //printf("%d ", matrice[i][j]);
            if(matrice[i][j]>=G->gamma){
                return 0; //condition non satisfaite
            }
        }
    }

    // Libération de la mémoire
    libererMatrice(matrice,G->nbsom+1);
    liberer_graphe(G);
    return 1; //condition de gamma satisfaite
}

void libererMatrice(int **matrice, int taille) {
    if (!matrice) return;
    for (int i = 0; i < taille; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void liberer_sommet(Sommet *s){
    /* Libère la mémoire d'un sommet et ses arêtes voisines.

    Paramètre :
    - s : sommet à libérer 
    */
    Cellule_arete *p = s->L_voisin;
    while (p){
        Cellule_arete *tmp = p; 
        p = p->suiv;
        free(tmp->a);
        free(tmp);
    }
    free(s);
}

void liberer_graphe(Graphe *g){
    /* Libère la mémoire d'un graphe.*/
    if(!g) return;
    for(int i=0; i< g->nbsom; i++){
        if(g->T_som[i]){
            liberer_sommet(g->T_som[i]);
        }
    }
    free(g->T_commod);
    free(g);
}

void afficherGraphe(Graphe *g){
    /*Fonction d'affichage*/
    for (int i = 1; i<g->nbsom+1    ; i++){
        Sommet *sommet = g->T_som[i];
        printf("Sommet %d -> ", sommet->num);
        printf("Voisins : ");
        Cellule_arete *voisin = sommet->L_voisin;
        while (voisin){
            printf("%d ", voisin->a->v);
            voisin = voisin->suiv;
        }
        printf("\n");
    }

    printf("Commodités : ");
    for (int i=0; i<g->nbcommod; i++){
        printf("%d %d", g->T_commod[i].e1, g->T_commod[i].e2);
    }
}