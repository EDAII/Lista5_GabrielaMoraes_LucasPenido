#include "treap.h"

noTreap* fazNovoNoTreap(int novoValor){
    // Criar um nó novo como folha
    noTreap *novoNo = (noTreap*) malloc(sizeof(noTreap));

    novoNo->valor = novoValor;
    novoNo->prioridade = rand() % 1000000 + 1; 
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    
    return novoNo;
}

noTreap* rotacaoDireitaTreap(noTreap *no){
    noTreap *esqNo = no->esq;
    noTreap *dirEsqNo = esqNo->dir;
    printf("\nRealizando rotação para direita no Nó %d", no->valor);

    esqNo->dir = no;
    no->esq = dirEsqNo;

    return esqNo;

}

noTreap* rotacaoEsquerdaTreap(noTreap *no){
    noTreap *dirNo = no->dir;
    noTreap *esqDirNo = dirNo->esq;
    printf("\nRealizando rotação para esquerda no Nó %d", no->valor);
        
    dirNo->esq = no;
    no->dir = esqDirNo;

    return dirNo;
}

noTreap* inserirNoTreap(noTreap *raiz, noTreap *novoNo){

    if(raiz == NULL){
        return novoNo;
    }

    if(novoNo->valor < raiz->valor){
        raiz->esq = inserirNoTreap(raiz->esq, novoNo);

        // Adequar, caso necessário, a prioridade à propriedade do Max Heap
        if(raiz->esq->prioridade > raiz->prioridade){
            // ctdRotacao++;
            raiz = rotacaoDireitaTreap(raiz);
        }
    }
    else { 
        raiz->dir = inserirNoTreap(raiz->dir, novoNo);

        if(raiz->dir->prioridade > raiz->prioridade){
            // ctdRotacao++;
            raiz = rotacaoEsquerdaTreap(raiz);
        }
    }

    return raiz;
}

void imprimeInOrderTreap(noTreap *raiz){
    if(!(raiz == NULL)){
        imprimeInOrderTreap(raiz->esq);
        printf("\nvalor do nó: %d/", raiz->valor);
        printf("prioridade: %d\n", raiz->prioridade);
        imprimeInOrderTreap(raiz->dir);
    }
}

void imprimePreOrderTreap(noTreap *raiz){
    if(!(raiz == NULL)){
        printf("\nvalor do nó: %d/", raiz->valor);
        printf("prioridade: %d\n", raiz->prioridade);
        imprimePreOrderTreap(raiz->esq);
        imprimePreOrderTreap(raiz->dir);
    }
}

void imprimePosOrderTreap(noTreap *raiz){
    if(!(raiz == NULL)){
        imprimePosOrderTreap(raiz->esq);
        imprimePosOrderTreap(raiz->dir);
        printf("\nvalor do nó: %d/", raiz->valor);
        printf("prioridade: %d\n", raiz->prioridade);
    }
}

noTreap* buscaTreap(noTreap *raiz, int valor){
    if(raiz == NULL){
        return raiz;
    }
    if(raiz->valor == valor){
        printf("\nNó encontrado!");
        printf("\nPai: %d\n",raiz->valor);
        if(raiz->dir == NULL && raiz->esq == NULL){
            printf("\n\nEsse nó não possui irmãos\n\n");
        }
        else if (raiz->dir != NULL){
            printf("Irmão: %d\n\n", raiz->dir->valor);
        }
        else{
            printf("Irmão: %d\n\n", raiz->esq->valor);
        }
        return raiz;
    }
    else if(valor < raiz->valor){
        return buscaTreap(raiz->esq, valor);
    }
    else{
        return buscaTreap(raiz->dir, valor);
    }

}