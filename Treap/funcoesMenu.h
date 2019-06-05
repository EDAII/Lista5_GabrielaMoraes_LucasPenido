#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
    #define LIMPA_TELA system("cls");
    #define LIMPA_BUFFER fflush(stdin);
#else defined(__linux__) || defined(__unix__)
    #define LIMPA_TELA system("clear");
    #define LIMPA_BUFFER __fpurge(stdin);
#endif

//Constantes
#define TREAP 1
#define SAIR 0
#define REPETIDO 0
#define NREPETIDO 1

//Prototipos
int menu();
int validaEscolha(int);
int escolheQtdNos();
int* preencheVetorAleatorio(int *, int);
int menuOperacoes();
int validaOperacao(int);
