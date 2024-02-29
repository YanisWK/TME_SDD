#include "Chaine.c"
#include "SVGwriter.c"

int main() {
    FILE *f = fopen("00014_burma.cha", "r");

    Chaines* c = lectureChaines(f);

    printf("Nb de chaines : %d\nGamma : %d\n", c->nbChaines, c->gamma);
    CellChaine* cc = c->chaines;
    if(!cc){
        printf("Chaine vide\n");
    }
    while(cc){
        printf("Chaine %d:\n", cc->numero);
        CellPoint *cp = cc->points;
        while (cp){
            printf("(%.2lf, %.2lf)\t", cp->x, cp->y);
            cp = cp->suiv;
        }
        printf("\n");
        cc = cc->suiv;
    }

    CellPoint *p3=creer_CellPoint(3,3);

    inserer_finCP(p3,1,1);
    inserer_finCP(p3,2,2);

    CellPoint *p6=creer_CellPoint(6,6);

    inserer_finCP(p6,4,4);
    inserer_finCP(p6,5,5);

    CellChaine *ch1=creer_CellChaine(0, p3);
    inserer_finCC(ch1,1,p6);

    CellPoint *p7=creer_CellPoint(7,7);

    inserer_finCP(p7,8,8);
    inserer_finCP(p7,9,9);

    CellPoint *p0=creer_CellPoint(0,0);

    CellChaine *ch2=creer_CellChaine(0, p7);
    inserer_finCC(ch2,2,p0);
    inserer_finCC(ch1,2, p0); //met ch2 à la suite de ch1 

    Chaines *chs = creer_Chaine(5,2,ch1);

    afficheChainesSVG(chs, "00014_burma.cha");

    fclose(f);
}
