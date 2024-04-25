#include "Graphe.h"
#include "Reseau.h"
#include <stdio.h>
#include <stdlib.h>

Arete *creer_arete(int u, int v){
    Arete *new = malloc(sizeof(Arete));
    new->u = u;
    new->v = v;
    return new;
}

Cellule_arete * creer_cellarete(Arete *a){
    Cellule_arete *new = malloc(sizeof(Cellule_arete));
    new->a = a;
    new->suiv = NULL;
    return new;
}

Sommet *creer_sommet(int num, int x, int y){
    Sommet *new = malloc(sizeof(Sommet));
    new->num = num;
    new->x = x;
    new->y = y;
    new->L_voisin = NULL;
    return new;
}

Commod *creer_commod(int e1, int e2){
    Commod *new = malloc(sizeof(commod));
    new->e1 = e1;
    new->e2 = e2;
    return new;
}

void *ajout_tetecommod(int e1, int e2, Graphe *g){
    Commod * new = creer_commod(e1, e2);
    g->T_commod[nbcommod] = new;  
    g->nbcommod ++;
}

void *ajout_tetesommet(int x, int y, int num, Graphe *g){
    Commod * new = creer_sommer(num, x, y);
    g->T_som[num] = new;  
    g->nbsom ++;
}

void insererVoisinsArete(Sommet u, Sommet v){
    Cellule_arete *p1= u->L_voisins;
    while (p1){
        if(p1->a->v==v){
            return;
        }
        p1=p1->suiv;
    }
    Arete *new_arete = creer_arete(u,v);
    Cellule_arete *new = creer_cellarete(new_arete);
    new->suiv= p1->L_voisins;
    p1->L_voisins=new;
}

Graphe* creerGraphe(Reseau* r){
    int nbnoeuds = 0;
    CellNoeud *pr = r->noeuds;
    while(pr){
        nbnoeuds++;
    }
    Sommet **T_som = malloc(sizeof(Sommet*)*nbnoeuds);

    pr = r->noeuds;
    while(pr){
        T_som[pr->nd->num] = creer_sommet(pr->nd->num, pr->nd->x, pr->nd->y);
        pr = pr->suiv;
    }

    pr = r->noeuds;
    while (pr){
        CellNoeud *v = pr->nd->voisins; //voisins de pr
        while (v){
            Sommet *voisin = T_som[v->nd->num]; 
            insererVoisinsArete(T_som[pr->nd->num], voisin);
            insererVoisinsArete(voisin, T_som[pr->nd->num]);
            v = v->suiv;
        }
        pr = pr->suiv;
    }

    Graphe *g = malloc(sizeof(Graphe));
    g->T_som = T_som;
    g->T_commod = NULL; 
    g->nbsom = nbnoeuds;
    g->nbcommod = 0; 

    return g;
}

void liberer_cellarete(Cellule_arete *ar){
    free(ar->a);
    free(a);
}

void liberer_sommet(Sommet *s){
    while(s->L_voisin){
        Cellule_arete *tmp = s->L_voisin;
        s->L_voisin = s->L_voisin->suiv;
        liberer_cellarete(tmp);
    }
    free(s->L_voisin);
    free(s);
}

void liberer_graphe(Graphe *g){
    Sommet **T_som = g->T_som;
    for(int i=0; i<g->nbsom;i++){
        liberer_sommet(T_som[i]);
    }
    for(int j=0; j<nbcommod; j++){
        free(T_commod[j]);
    }
    free(g);
}