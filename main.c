#include <stdio.h>
#include <stdlib.h>
#include "ArvoreLLRB.h"
int main(){
    ArvLLRB * raiz = criar_arvore();

    int i, N = 9, val[9] = {11,2,1,5,4,7,8,14,15};

    for(i=0; i< N; i++){
        inserir_novo_no(raiz,val[i]);
    }

    percorrer_em_ordem(raiz,0);

    printf("\n\n==========================\n\n");

    remover_no_arvore(raiz,4);
    percorrer_em_ordem(raiz,0);
    printf("\n\n==========================\n\n");
    remover_no_arvore(raiz,1);
    percorrer_em_ordem(raiz,0);

    return 0;
}