#include "Graphe.h"
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
    Commod *new = malloc(sizeof(Commod));
    new->e1 = e1;
    new->e2 = e2;
    return new;
}

Cellule_arete *ajout_teteCellule_arete(Cellule_arete *ca, Sommet *u, Sommet *v){
    Arete *a = creer_arete(u->num, v->num);
    if (!a) return ca;
    Cellule_arete *tete = creer_cellarete(a);
    tete->suiv = ca;
    return tete;
}


void ajout_commod(int e1, int e2, Graphe *g){
    Commod * new = creer_commod(e1, e2);
    g->T_commod[g->nbcommod]=*new;  
    g->nbcommod ++;
}

void ajout_sommet(int x, int y, int num, Graphe *g){
    Sommet * new = creer_sommet(num, x, y);
    g->T_som[num] = &(*new);  
    g->nbsom ++;
}

void insererVoisinsArete(Sommet* u, Sommet* v){
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
    int nbnoeuds = 0;
    CellNoeud *pr = r->noeuds;
    while(pr){
        nbnoeuds++;
        pr = pr->suiv;
    }
    Sommet **T_som = malloc(sizeof(Sommet*)*(nbnoeuds+1));
    int nbCommod = nbCommodites(r);
    
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
            //insererVoisinsArete(voisin, T_som[pr->nd->num-1]);
            v = v->suiv;
        }
        pr = pr->suiv;
    }

    Graphe *g = malloc(sizeof(Graphe));
    g->T_som = T_som;
    g->T_commod = malloc(sizeof(Commod)*nbCommod); 
    g->nbsom = nbnoeuds;
    g->nbcommod = 0; 

    return g;
}

int len(int* tab){
    int cpt=0;
    while(*(tab+cpt)){
        cpt++;
    }
    return cpt;
}

int plusCourtChemin(Graphe *g, int u, int v){

    S_file *file=malloc(sizeof(S_file)); 
    Init_file(file); 
    enfile(file, u); 
    int valu;
    int *tabvisite = (int*)malloc(sizeof(int)*(g->nbsom));
    int *tabPere=(int*)malloc(sizeof(int)*(g->nbsom));
    for(int i=1;i<g->nbsom;i++){
        tabvisite[i]=0;
        tabPere[i]=0;
    }
    tabvisite[u] = 1; 
    tabPere[u]=-1;
    while (!estFileVide(file)){
        int valu=defile(file);
        printf("valu : %d \n",valu);
        if(valu==v){
            break;
        }
        Cellule_arete * cour=g->T_som[valu]->L_voisin;
        while(cour!=NULL){
            int valv=cour->a->v;
            printf("valvoisins = %d \n",valv);
            if(tabvisite[valv]==0){
                tabvisite[valv]=1;
                enfile(file,valv);
                tabPere[valv]=valu;
                printf("Trouvé ! \n");
            }
            cour=cour->suiv;
        }
    }
    valu=v;
    int C=0;
    while(valu!=-1){
        printf("C= %d , valu = %d \n",C,valu);
        valu=tabPere[valu];
        if(valu==-1){
            continue;
        }else{
            C+=1;
        }
    }
    return C;
}

int plusCourtChemin(Graphe *g, int u, int v){

    S_file *file=malloc(sizeof(S_file)); 
    Init_file(file); 
    enfile(file, u); 
    int valu;
    int *tabvisite = (int*)malloc(sizeof(int)*(g->nbsom));
    int *tabPere=(int*)malloc(sizeof(int)*(g->nbsom));
    for(int i=1;i<g->nbsom;i++){
        tabvisite[i]=0;
        tabPere[i]=0;
    }
    tabvisite[u] = 1; 
    tabPere[u]=-1;
    while (!estFileVide(file)){
        int valu=defile(file);
        printf("valu : %d \n",valu);
        if(valu==v){
            break;
        }
        Cellule_arete * cour=g->T_som[valu]->L_voisin;
        while(cour!=NULL){
            int valv=cour->a->v;
            printf("valvoisins = %d \n",valv);
            if(tabvisite[valv]==0){
                tabvisite[valv]=1;
                enfile(file,valv);
                tabPere[valv]=valu;
                printf("Trouvé ! \n");
            }
            cour=cour->suiv;
        }
    }
    valu=v;
    int C=0;
    while(valu!=-1){
        printf("C= %d , valu = %d \n",C,valu);
        valu=tabPere[valu];
        if(valu==-1){
            continue;
        }else{
            C+=1;
        }
    }
    return C;
}


void liberer_sommet(Sommet *s){
    Cellule_arete *p = s->L_voisin;
    while (p){
        Cellule_arete *tmp = p; 
        p = p->suiv;
        free(tmp);
    }
    free(s);
}

void liberer_graphe(Graphe *g){
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
}