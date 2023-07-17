#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int chave;
    //dados dependem da aplicacao
    struct no * dir;
    struct no * esq;
}NO;


NO *raiz = NULL;

NO * busca_arvore(int x, NO *pt){
    if(pt == NULL){ //arv. vazia
        return NULL;
    }else if(x == pt->chave){ //encontrado
        return pt;
    }else if(x < pt->chave){
        //esq! :D
        if(pt->esq == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->esq);
        }
    }else{
        //dir
        if(pt->dir == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->dir);
        }
    }
}

void insercao_arvore(int x){
    NO * pt = busca_arvore(x, raiz);
    if(pt != NULL){ //arvore nao ta vazia
        if(pt->chave == x){
            printf("Chave duplicada!\n");
        }else{
            NO *pt1 = malloc(sizeof(NO));
            pt1->chave = x;
            pt1->esq = NULL;
            pt1->dir = NULL;
            if(x <pt->chave){
                pt->esq = pt1;
            }else{
                pt->dir = pt1;
            }
        }
    }else{//arvore vazia
        NO *pt1 = malloc(sizeof(NO));
        pt1->chave = x;
        pt1->esq = NULL;
        pt1->dir = NULL;
        raiz = pt1;
        
    }
}

NO *remocao_arvore(NO *pt, int valor) {
    if (pt == NULL)
        return NULL;
    else if (pt->chave > valor)
        pt->esq = remocao_arvore(pt->esq, valor);
    else if (pt->chave < valor)
        pt->dir = remocao_arvore(pt->dir, valor);
    else { /* achou o nó a remover */
        if (pt->esq == NULL && pt->dir == NULL) { // nó sem filho
            // free(pt);
            pt = NULL;
        } else if (pt->esq == NULL) { // nó só tem filho à direita
            NO *t = pt;
            pt = pt->dir;
            // free(t);
        } else if (pt->dir == NULL) { // nó só tem filho à esquerda
            NO *t = pt;
            pt = pt->esq;
            // free(t);
        } else { // nó tem os dois filhos
            NO *f = pt->esq;
            while (f->dir != NULL) {
                f = f->dir;
            }
            pt->chave = f->chave; /* troca as informações */
            f->chave = valor;
            pt->esq = remocao_arvore(pt->esq, valor);
        }
    }
    return pt;
}

void update_arvore(NO *pt, int valor_antigo, int valor_novo) {
    NO *no = busca_arvore(valor_antigo, pt);

    if (no != NULL && no->chave == valor_antigo) {
        no->chave = valor_novo;
        printf("Valor atualizado com sucesso!\n");
    } else {
        printf("Valor não encontrado na árvore!\n");
    }
}


void pre(NO *pt){
    
    printf("%d ", pt->chave);
    if(pt->esq != NULL){
        pre(pt->esq);
    }
    if(pt->dir != NULL){
        pre(pt->dir);
    }
}



int main(){
    insercao_arvore(30);
    insercao_arvore(20);
    insercao_arvore(40);
    insercao_arvore(10);
    insercao_arvore(25);
    insercao_arvore(5);
    insercao_arvore(15);
    insercao_arvore(22);
    insercao_arvore(35);
    insercao_arvore(50);
    insercao_arvore(45);
    insercao_arvore(60);

    
    printf("Árvore original: ");
    pre(raiz);
    printf("\n");

    // Caso 1: Remover a raiz da sub-árvore que é folha (valor 5)
    raiz = remocao_arvore(raiz, 5);
    printf("Árvore após remover a raiz folha (5): ");
    pre(raiz);
    printf("\n");

    // Caso 2: Remover a raiz da sub-árvore que possui um único filho (valor 25)
    raiz = remocao_arvore(raiz, 25);
    printf("Árvore após remover a raiz com um filho (25): ");
    pre(raiz);
    printf("\n");

    // Caso 3: Remover a raiz da sub-árvore que possui dois filhos (valor 30)
    raiz = remocao_arvore(raiz, 30);
    printf("Árvore após remover a raiz com dois filhos (30): ");
    pre(raiz);
    printf("\n");

    update_arvore(raiz, 22, 9);
    printf("Árvore após atualizar o valor 22 para 9: ");
    pre(raiz);
    printf("\n");


    return 0;
}
