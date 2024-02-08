#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* alloue_tableau(int n){
    int* t = malloc(sizeof(int)*n);
    return *(&t);
}

void alloue_tab2(int **t, int n){
    *t=malloc(sizeof(int)*n);
}

void desalloue_tableau(int *t){
    free(t);
}

int * remplir_tableau(int v, int* t,int n){
    for (int i=0; i<n;i++){
        t[i]= (int)(rand()%(v));
    }
    return t;
}

void afficher_tableau(int *t, int n){
    for(int i=0; i<n; i++){
        printf("%d  ", t[i]);
    }
    printf("\n");
}

int scdiff(int *t,int n){
    int s=0;
    for(int i=1; i<n; i++){
        for(int j=0; j<n;j++){
            s+=(t[i]-t[j])*(t[i]-t[j]);
        }
    }
    return s;
}

int scdiff2(int *t, int n){
    int s = 0, s2 = 0;
    for(int i = 0; i<n; i++){
        s += t[i];
        s2 += t[i]*t[i];
    }
    return n*s2 - s*s;
}

int main() {
    int n=5;
    int *t=alloue_tableau(n);
    t=remplir_tableau(2,t,n);
    afficher_tableau(t,n);
    printf("%d\n",scdiff(t,n));
    printf("%d\n",scdiff2(t,n));

    clock_t temps_initial, temps_final;
    double temps_cpu_sc, temps_cpu_sc2;

    //mesure le temps CPU pour l'algo de complexité O(n²)
    temps_initial = clock();
    scdiff(t, n);
    temps_final = clock();
    temps_cpu_sc = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    //printf("%f secondes\n", temps_cpu_sc);

    //mesure le temps CPU pour l'algo de complexité O(n)
    temps_initial = clock();
    scdiff2(t, n);
    temps_final = clock();
    temps_cpu_sc2 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    //printf("%f secondes\n", temps_cpu_sc2);

    desalloue_tableau(t);
    return 0;
}