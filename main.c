#include <stdio.h>
#include <stdlib.h>
#include "ArvoreLLRB.h"
int main(){
    ArvLLRB * raiz = cria_ArvLLRB();

    int i, N = 9, val[9] = {11,2,1,5,4,7,8,14,15};

    for(i=0; i< N; i++){
        insere_ArvLLRB(raiz,val[i]);
    }

    emOrdem_ArvLLRB(raiz,0);

    printf("\n\n==========================\n\n");

    remove_ArvLLRB(raiz,4);
    emOrdem_ArvLLRB(raiz,0);
    printf("\n\n==========================\n\n");
    remove_ArvLLRB(raiz,1);
    emOrdem_ArvLLRB(raiz,0);

    return 0;
}