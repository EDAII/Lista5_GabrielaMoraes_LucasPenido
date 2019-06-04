#include "avl.h"

noAvl* criaNovoNo(int valor){
    // Criar um nó novo como folha
    noAvl *novoNo = (noAvl*) malloc(sizeof(noAvl));

    novoNo->valor = valor;
    novoNo->altura = 0; 
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    
    return novoNo;
}

int retornaAlturaNo(noAvl *no){

    if(no == NULL){
        return 0;
    }

    return no->altura;
}

int calculaFatorBalanceamento(noAvl *raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return (retornaAlturaNo(raiz->esq) - retornaAlturaNo(raiz->dir));
    }
}

noAvl* insereNo(noAvl *raiz, noAvl *novoNo){
    int fatorBalanceamento = 0;

    if(raiz == NULL){
        return novoNo;
    }
    if(novoNo->valor < raiz->valor){
        raiz->esq = insereNo(raiz->esq, novoNo);
    }
    else if (novoNo->valor > raiz->valor){
        raiz->dir = insereNo(raiz->dir, novoNo);
    }
    else{
        return raiz;
    }
    
    raiz->altura = 1 + (max(retornaAlturaNo(raiz->esq), retornaAlturaNo(raiz->dir)));

    fatorBalanceamento = calculaFatorBalanceamento(raiz);

    // Rotações no ramo da esquerda
    if(fatorBalanceamento >= 2){
        if(novoNo->valor < raiz->esq->valor){
            ctdRotacao++;
            return rotacaoDireita(raiz);
        }
        else{
            ctdRotacao = ctdRotacao + 2;
            raiz->esq = rotacaoEsquerda(raiz->esq);
            return rotacaoDireita(raiz);
        }
    }
    else if(fatorBalanceamento <= -2){
        if(novoNo->valor < raiz->dir->valor){
            ctdRotacao = ctdRotacao + 2;
            raiz->dir = rotacaoDireita(raiz->dir);
            return rotacaoEsquerda(raiz);
        }
        else{
            ctdRotacao++;
            return rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

int max(int a, int b){  
    return (a > b)? a : b;  
}  

noAvl* rotacaoDireita(noAvl *no){
    noAvl *esqNo = no->esq;
    noAvl *dirEsqNo = esqNo->dir;
    printf("\nRealizando rotação para direita no Nó %d", no->valor);

    esqNo->dir = no;
    no->esq = dirEsqNo;

    no->altura = max(retornaAlturaNo(no->esq), retornaAlturaNo(no->dir)) + 1;
    esqNo->altura = max(retornaAlturaNo(no->esq), retornaAlturaNo(no->dir)) + 1;

    return esqNo;

}

noAvl* rotacaoEsquerda(noAvl *no){
    noAvl *dirNo = no->dir;
    noAvl *esqDirNo = dirNo->esq;
    printf("\nRealizando rotação para esquerda no Nó %d", no->valor);
        
    dirNo->esq = no;
    no->dir = esqDirNo;

    no->altura = max(retornaAlturaNo(no->esq), retornaAlturaNo(no->dir)) + 1;
    dirNo->altura = max(retornaAlturaNo(no->esq), retornaAlturaNo(no->dir)) + 1;

    return dirNo;
}

//Imprime em 2D
void print2DUtil(noAvl *raiz, int space){
  //Declarações

  //Instruções
    if (raiz == NULL)
        return;

    space += 10;

    print2DUtil(raiz->dir, space);

    printf("\n");
    for (int i = 10; i < space; i++){
      printf(" ");
    }
    printf("%d\n", raiz->valor);

    print2DUtil(raiz->esq, space);
}

void imprimePreOrder(noAvl *raiz){
    if(!(raiz == NULL)){
        printf("%d\t", raiz->valor);
        imprimePreOrder(raiz->esq);
        imprimePreOrder(raiz->dir);
    }
}

void imprimeInOrder(noAvl *raiz){
    if(!(raiz == NULL)){
        imprimeInOrder(raiz->esq);
        printf("%d\t", raiz->valor);
        imprimeInOrder(raiz->dir);
    }
}

void imprimePosOrder(noAvl *raiz){
    if(!(raiz == NULL)){    
        imprimePosOrder(raiz->esq);
        imprimePosOrder(raiz->dir);
        printf("%d\t", raiz->valor);
    }
}

noAvl* encontraSucessor(noAvl *no){
  //Declarações
   noAvl *aux = no;

  //Instruções
  while(aux-> esq != NULL){
    aux = aux->esq;
  }

  return aux;
}

noAvl* removeValor(noAvl *raiz, int valorDeletado){
  //Declarações
  noAvl *aux = NULL;
  int fatorBalanceamento = 0;

  //Instruções
  ctdAcessos++;
  
  if(raiz == NULL){
    return raiz; // Arvore vazia
  }

  if(valorDeletado > raiz->valor){
    raiz->dir = removeValor(raiz->dir, valorDeletado);

  }else if(valorDeletado < raiz->valor){
    raiz->esq = removeValor(raiz->esq, valorDeletado);
  }
  else{

    //Remover folha
    if(raiz->esq == NULL && raiz->dir == NULL){
      raiz = NULL;
      return raiz;
    }
    //Remover nó com 1 filho
    if(raiz->esq == NULL && raiz->dir != NULL){
      aux = raiz->dir;
      raiz = aux;
    }
    if(raiz->esq != NULL && raiz->dir == NULL){
      aux = raiz->esq;
      raiz = aux;
    }
    //Remover nó com 2 filhos
    if(raiz-> esq != NULL && raiz->dir != NULL){
      aux = encontraSucessor(raiz->dir);
      raiz->valor = aux->valor;
      raiz->dir = removeValor(raiz->dir, aux->valor);
    }
  }
    raiz->altura = 1 + (max(retornaAlturaNo(raiz->esq), retornaAlturaNo(raiz->dir)));

    fatorBalanceamento = calculaFatorBalanceamento(raiz);

    //Rotações no ramo da esquerda
    if(fatorBalanceamento >= 2){
        if(calculaFatorBalanceamento(raiz->esq) >= 0){
            ctdRotacao++;
            return rotacaoDireita(raiz);
        }
        else{
            ctdRotacao = ctdRotacao+2;
            raiz->esq = rotacaoEsquerda(raiz->esq);
            return rotacaoDireita(raiz);
        }
    }
    else if(fatorBalanceamento <= -2){
        if(calculaFatorBalanceamento(raiz->dir) <= 0){
            ctdRotacao++;
            return rotacaoEsquerda(raiz);
        }
        else{
            ctdRotacao = ctdRotacao + 2;
            raiz->dir = rotacaoDireita(raiz->dir);
            return rotacaoEsquerda(raiz);
        }
    }
  return raiz;
}

int buscaValor(noAvl *raiz, int valor){
  //Declarações

  //Instruções
  ctdAcessos++;

  if (!(raiz == NULL)){
    if(valor == raiz->valor){
        printf("\n\nRaiz\n");
        printf("\nAltura do nó: %d", raiz->altura);
        return 0;

    }else if((raiz->esq != NULL) && valor < raiz->valor){
        if(raiz->esq->valor == valor){
            printf("\nNó encontrado!");
            printf("\nAltura do nó: %d", raiz->esq->altura);
            printf("\nPai: %d\n",raiz->valor);
            if(!(raiz->dir == NULL)){
                printf("Irmão: %d\n\n", raiz->dir->valor);
            }
            else{
                printf("\n\nEsse nó não possui irmãos\n\n");
            }
            return 0;
        }
        buscaValor(raiz->esq, valor);
    }else if((raiz->dir != NULL)){
      if(raiz->dir->valor == valor){
        printf("\nNó encontrado!");
        printf("\nAltura do nó: %d", raiz->esq->altura);
        printf("\nPai: %d\n",raiz->valor);
        if(!(raiz->esq == NULL)){
            printf("Irmão: %d\n\n", raiz->esq->valor);
        }
        else{
            printf("\n\nEsse nó não possui irmãos\n\n");
        }
        return 0;
      }
      buscaValor(raiz->dir, valor);
    }else{
      printf("\n\nNó não encontrado!\n\n");
      return -1;
    }
  }
}
