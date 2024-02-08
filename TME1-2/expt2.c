#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int ** alloue_matrice(int n){
    int ** tab = malloc(n*sizeof(int*));
    for (int i=0; i<n; i++){
        *(tab+i)=malloc(n*sizeof(int));
    }
    return tab;
}

void desalloue_matrice(int **tab,int n){
    for (int i=0; i<n; i++){
        free(tab[i]);
    }
    free(tab);
}


void remplir_tab(int ** tab, int n, int val){
    for (int i=0; i<n; i++){
        for (int j=0;j<n;j++){
            tab[i][j]=rand()%(val);
        }
    }
}

void afficher_matrice(int** tab, int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("tab[%d][%d] = %d\n", i,j,tab[i][j]);
        }
    }
}

void diff(int **tab, int n){
    printf("diff1\n");
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            for (int k = i; k<n; k++){
                int s;
                if (k == i){
                    s = j+1;
                }else{
                    s = 0;
                }
                for (int l=s; l<n; l++){
                    if (tab[i][j] == tab[k][l]){
                        printf("tab[%d][%d] = tab[%d][%d]\n", i, j, k, l);
                    }
                }
            }
        }
    }
}

typedef struct pos{
    int row;
    int col;
    int  v;
    struct pos *prec;
    struct pos *suiv;
}Pos;

void diff2(int **tab, int n, int val){
    Pos *h = NULL, *p = NULL;

    for(int i = 0; i < val; i++){
        Pos *new = (Pos*)malloc(sizeof(Pos));
        new->v = i;
        new->row = -1;
        new->col = -1;
        new->suiv = NULL;
        new->prec = p;

        if (p != NULL){
            p->suiv = new;
        } else {
            h = new;
        }
        p = new;
    }

    printf("diff2\n");

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            p = h;
            while (tab[i][j] != p->v) {
                p = p->suiv;
            }
            if ((p->row == -1) && (p->col == -1)){
                // Valeur pas encore rencontrée
                p->row = i;
                p->col = j;
            } else{
                // Valeur déjà rencontrée, on récupère sa position
                printf("tab[%d][%d] = tab[%d][%d]\n", p->row, p->col, i, j);
            }
        }
    }
    while (h != NULL) {
        p = h;
        h = h->suiv;
        free(p);
    }
}


int main(){
    srand(time(NULL));
    int n=4, val=10;
    int** mat=alloue_matrice(n);
    remplir_tab(mat,n,val);
    afficher_matrice(mat,n);
    diff(mat,n);
    diff2(mat,n,val);

    desalloue_matrice(mat,n);
    return 0;
}