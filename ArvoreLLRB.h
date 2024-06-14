// PCO001 - ALGORITMOS E ESTRUTURAS DE DADOS
// ANNA LUIZA PEREIRA ROSA - 2024100865
// JOÃO VITOR DE FARIA - 2024100678
// YTALO YSMAICON GOMES - 20223103915

typedef struct NO* ArvLLRB; //Criação do ponteiro para a árvore
ArvLLRB* criar_arvore();
void liberar_arvore(ArvLLRB* raiz);
int inserir_novo_no(ArvLLRB* raiz,int valor);
int remover_no_arvore(ArvLLRB *raiz, int valor);
int verifica_arvore_vazia(ArvLLRB *raiz);
int total_nos_arvore(ArvLLRB *raiz);
int altura_arvore(ArvLLRB *raiz);
int buscar_na_arvore(ArvLLRB *raiz, int valor);
void percorrer_pre_ordem(ArvLLRB *raiz, int H);
void percorrer_em_ordem(ArvLLRB *raiz, int H);
void percorrer_pos_ordem(ArvLLRB *raiz, int H);