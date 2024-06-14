#include <stdio.h>
#include <stdlib.h>
#include "ArvoreLLRB.h"

#define VERMELHO 1
#define PRETO 0

typedef struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
} NO;

ArvLLRB* criar_arvore(){
    ArvLLRB* raiz = (ArvLLRB*) malloc(sizeof(ArvLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void liberar_no(NO* no){
    if(no == NULL)
        return;
    liberar_no(no->esq);
    liberar_no(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvore(ArvLLRB* raiz){
    if(raiz == NULL)
        return;
    liberar_no(*raiz);
    free(raiz);
}

int buscar_na_arvore(ArvLLRB *raiz, int valor){
    if(raiz == NULL)
        return 0;
     NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

 NO* rotacionar_esquerda( NO* A){
     NO* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

 NO* rotacionar_direita( NO* A){
     NO* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

int cor( NO* H){
    if(H == NULL)
        return PRETO;
    else
        return H->cor;
}

void trocar_cor_no( NO* H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

 NO* inserir_no( NO* H, int valor, int *resp){
    if(H == NULL){
         NO *novo;
        novo = ( NO*)malloc(sizeof( NO));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }

        novo->info = valor;
        novo->cor = VERMELHO;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if(valor == H->info)
        *resp = 0;
    else{
        if(valor < H->info)
            H->esq = inserir_no(H->esq,valor,resp);
        else
            H->dir = inserir_no(H->dir,valor,resp);
    }


    if(cor(H->dir) == VERMELHO && cor(H->esq) == PRETO)
        H = rotacionar_esquerda(H);

    if(cor(H->esq) == VERMELHO && cor(H->esq->esq) == VERMELHO)
        H = rotacionar_direita(H);

    if(cor(H->esq) == VERMELHO && cor(H->dir) == VERMELHO)
        trocar_cor_no(H);

    return H;
}

int inserir_novo_no(ArvLLRB* raiz, int valor){
    int resp;

    *raiz = inserir_no(*raiz,valor,&resp);
    if((*raiz) != NULL)
        (*raiz)->cor = PRETO;

    return resp;
}

 NO* balancear_arvore( NO* H){
    if(cor(H->dir) == VERMELHO)
        H = rotacionar_esquerda(H);

    if(H->esq != NULL && cor(H->esq) == VERMELHO && cor(H->esq->esq) == VERMELHO)
        H = rotacionar_direita(H);

    if(cor(H->esq) == VERMELHO && cor(H->dir) == VERMELHO)
        trocar_cor_no(H);

    return H;
}

 NO* mover_2esq_VERMELHO( NO* H){
    trocar_cor_no(H);
    if(cor(H->dir->esq) == VERMELHO){
        H->dir = rotacionar_direita(H->dir);
        H = rotacionar_esquerda(H);
        trocar_cor_no(H);
    }
    return H;
}

 NO* mover_2dir_VERMELHO( NO* H){
    trocar_cor_no(H);
    if(cor(H->esq->esq) == VERMELHO){
        H = rotacionar_direita(H);
        trocar_cor_no(H);
    }
    return H;
}

 NO* remover_menor_no( NO* H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq) == PRETO && cor(H->esq->esq) == PRETO)
        H = mover_2esq_VERMELHO(H);

    H->esq = remover_menor_no(H->esq);
    return balancear_arvore(H);
}

 NO* procurar_menor_no( NO* atual){
     NO *no1 = atual;
     NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

 NO* remover_no( NO* H, int valor){
    if(valor < H->info){
        if(cor(H->esq) == PRETO && cor(H->esq->esq) == PRETO)
            H = mover_2esq_VERMELHO(H);

        H->esq = remover_no(H->esq, valor);
    }else{
        if(cor(H->esq) == VERMELHO)
            H = rotacionar_direita(H);

        if(valor == H->info && (H->dir == NULL)){
            free(H);
            return NULL;
        }

        if(cor(H->dir) == PRETO && cor(H->dir->esq) == PRETO)
            H = mover_2dir_VERMELHO(H);

        if(valor == H->info){
             NO* x = procurar_menor_no(H->dir);
            H->info = x->info;
            H->dir = remover_menor_no(H->dir);
        }else
            H->dir = remover_no(H->dir, valor);
    }
    return balancear_arvore(H);
}

int remover_no_arvore(ArvLLRB *raiz, int valor){
    if(buscar_na_arvore(raiz,valor)){
         NO* h = *raiz;
        *raiz = remover_no(h,valor);
        if(*raiz != NULL)
            (*raiz)->cor = PRETO;
        return 1;
    }else
        return 0;
}

int verifica_arvore_vazia(ArvLLRB *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int total_nos_arvore(ArvLLRB *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;

    int alt_esq = total_nos_arvore(&((*raiz)->esq));
    int alt_dir = total_nos_arvore(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

int altura_arvore(ArvLLRB *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_arvore(&((*raiz)->esq));
    int alt_dir = altura_arvore(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void  percorrer_pos_ordem(ArvLLRB *raiz, int H){
    if(raiz == NULL)
        return;

    if(*raiz != NULL){
        percorrer_pos_ordem(&((*raiz)->esq),H+1);
        percorrer_pos_ordem(&((*raiz)->dir),H+1);

        if((*raiz)->cor == VERMELHO)
            printf("%d  Vermelho: H(%d) \n",(*raiz)->info,H);
        else
            printf("%d  Preto: H(%d) \n",(*raiz)->info,H);

    }
}

void percorrer_em_ordem(ArvLLRB *raiz, int H){
    if(raiz == NULL)
        return;

    if(*raiz != NULL){
        percorrer_em_ordem(&((*raiz)->esq),H+1);

        if((*raiz)->cor == VERMELHO)
            printf("%dR: H(%d) \n",(*raiz)->info,H);
        else
            printf("%dB: H(%d) \n",(*raiz)->info,H);

        percorrer_em_ordem(&((*raiz)->dir),H+1);
    }
}

void percorrer_pre_ordem(ArvLLRB *raiz,int H){
    if(raiz == NULL)
        return;

    if(*raiz != NULL){
        if((*raiz)->cor == VERMELHO)
            printf("%d  Vermelho: H(%d) \n",(*raiz)->info,H);
        else
            printf("%d  Preto: H(%d) \n",(*raiz)->info,H);

        percorrer_pre_ordem(&((*raiz)->esq),H+1);
        percorrer_pre_ordem(&((*raiz)->dir),H+1);
    }
}