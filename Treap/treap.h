#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct noTreap{
    int valor;
    int prioridade; // Prioridade segue a propriedade do Max Heap
    struct noTreap *esq;
    struct noTreap *dir;
} noTreap;

// int ctdRotacao;
// int ctdAcessos;

noTreap* fazNovoNoTreap(int);
noTreap* rotacaoDireitaTreap(noTreap *);
noTreap* rotacaoEsquerdaTreap(noTreap *);
noTreap* inserirNoTreap(noTreap *, noTreap *);
void imprimeInOrderTreap(noTreap *);
void imprimePreOrderTreap(noTreap *);
void imprimePosOrderTreap(noTreap *);
noTreap* buscaTreap(noTreap *, int);