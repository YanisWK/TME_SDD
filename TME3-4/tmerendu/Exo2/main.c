#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"

int main(){
    printf("%d\n", fonctionClef("Tatsuya Endo")); //testé sur https://www.dcode.fr/code-ascii
    printf("%d\n", fonctionHachage(fonctionClef("Tatsuya Endo"), 6));
    return 0;
}