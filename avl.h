#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
} noAvl;

int ctdRotacao;
int ctdAcessos;

//Protótipos
int max(int, int);
void print2DUtil(noAvl *, int);
int retornaAlturaNo(noAvl *);
int calculaFatorBalanceamento(noAvl *);
noAvl* criaNovoNo(int);
noAvl* insereNo(noAvl *, noAvl *);
noAvl* rotacaoDireita(noAvl *);
noAvl* rotacaoEsquerda(noAvl *);
void imprimePreOrder(noAvl *);
void imprimeInOrder(noAvl *);
void imprimePosOrder(noAvl *);
noAvl* removeValor(noAvl *, int);
noAvl* encontraSucessor(noAvl *);
int buscaValor(noAvl *, int);