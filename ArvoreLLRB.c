// PCO001 - ALGORITMOS E ESTRUTURAS DE DADOS
// ANNA LUIZA PEREIRA ROSA - 2024100865
// JOÃO VITOR DE FARIA - 2024100678
// YTALO YSMAICON GOMES - 20223103915

#include <stdio.h>
#include <stdlib.h>
#include "ArvoreLLRB.h" //Inclui os protótipos das funções

//Define as cores dos nós
#define VERMELHO 1
#define PRETO 0

//Define a estrutura de cada nó da árvore
typedef struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
} NO;

//Função para alocação da memória necessária para criação da árvore
ArvLLRB* criar_arvore(){
    ArvLLRB* raiz = (ArvLLRB*) malloc(sizeof(ArvLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

//Função para liberar um único nó da árvore
void liberar_no(NO* no){
    if(no == NULL)
        return;
    liberar_no(no->esq);
    liberar_no(no->dir);
    free(no);
    no = NULL;
}

//Função para liberar a árvore como um todo
void liberar_arvore(ArvLLRB* raiz){
    if(raiz == NULL)
        return;
    liberar_no(*raiz);
    free(raiz);
}

//Função para buscar um nó na árvore
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

//Função para fazer uma rotação à esquerda na árvore
 NO* rotacionar_esquerda( NO* A){
     NO* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

//Função para fazer uma rotação à direita na árvore
 NO* rotacionar_direita( NO* A){
     NO* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

//Função para definir a cor de um nó na árvore
int cor( NO* H){
    if(H == NULL)
        return PRETO;
    else
        return H->cor;
}

//Função para redefinir a cor de um nó na árvore
void trocar_cor_no( NO* H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

//Função para inserção de um nó na árvore
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

//Função para inserção de nós na árvore
int inserir_novo_no(ArvLLRB* raiz, int valor){
    int resp;

    *raiz = inserir_no(*raiz,valor,&resp);
    if((*raiz) != NULL)
        (*raiz)->cor = PRETO;

    return resp;
}

//Função que garante o balanceamento da árvore
 NO* balancear_arvore( NO* H){
    if(cor(H->dir) == VERMELHO)
        H = rotacionar_esquerda(H);

    if(H->esq != NULL && cor(H->esq) == VERMELHO && cor(H->esq->esq) == VERMELHO)
        H = rotacionar_direita(H);

    if(cor(H->esq) == VERMELHO && cor(H->dir) == VERMELHO)
        trocar_cor_no(H);

    return H;
}

//Função para mover um nó vermelho para a esquerda
NO* mover_2esq_VERMELHO( NO* H){
    trocar_cor_no(H);
    if(cor(H->dir->esq) == VERMELHO){
        H->dir = rotacionar_direita(H->dir);
        H = rotacionar_esquerda(H);
        trocar_cor_no(H);
    }
    return H;
}

//Função para mover um nó vermelho para a direita
NO* mover_2dir_VERMELHO( NO* H){
    trocar_cor_no(H);
    if(cor(H->esq->esq) == VERMELHO){
        H = rotacionar_direita(H);
        trocar_cor_no(H);
    }
    return H;
}

//Função para remover o menor nó da árvore
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

//Função para procurar o menor nó da árvore
NO* procurar_menor_no( NO* atual){
     NO *no1 = atual;
     NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

//Função para remover um nó da árvore
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

//Função para remover nós da árvore
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

//Função para verificar se árvore está vazia
int verifica_arvore_vazia(ArvLLRB *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

//Função para contagem de nós na árvore
int total_nos_arvore(ArvLLRB *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;

    int alt_esq = total_nos_arvore(&((*raiz)->esq));
    int alt_dir = total_nos_arvore(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

//Função para calcular a altura da árvore
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

//Função para percorrer a árvore em pós-ordem
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

//Função para percorrer a árvore em ordem
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

//Função para percorrer a árvore em pré-ordem
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