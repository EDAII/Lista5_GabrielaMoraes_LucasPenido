#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio_ext.h>
#include "funcoesMenu.h"
#include "avl.h"

int main(int argc, char *argv[]){
    // Variáveis
    int opcaoMenu, qtdNos, opcaoOperacao, opcaoOperacaoTreap, valorDeletado, valorBuscado;
    double inicio, fim, tempoPreenchimento, tempoMontagem, tempoBusca, tempoRemocao;
    int *numerosArvore = NULL;
    noAvl *raizAvl, *novoNoAvl = NULL;

    do{
        LIMPA_TELA;
        opcaoMenu = menu();
        switch(opcaoMenu){
            case AVL:
                LIMPA_TELA;
                printf("======================= AVL =========================");
                qtdNos = escolheQtdNos();
                numerosArvore = (int *) malloc (qtdNos * sizeof(int));
                inicio = clock();
                numerosArvore = preencheVetorAleatorio(numerosArvore, qtdNos);
                fim = clock();
                tempoPreenchimento = ((double)(fim-inicio)/CLOCKS_PER_SEC);
                printf("\n\nTempo para o preenchimento do vetor: %lf s\n\n", tempoPreenchimento);
                printf("Vetor gerado: ");
                printf("[ ");
                for(int i = 0; i < qtdNos; i++){
                    printf("%d\t", *(numerosArvore + i));
                }
                printf("]");
                printf("\n\nAperte ENTER para continuar... ");
                LIMPA_BUFFER;
                getchar();
                printf("\n\nMontando árvore AVL...");
                ctdRotacao = 0;
                inicio = clock();
                for(int i = 0; i < qtdNos; i++){
                    novoNoAvl = criaNovoNo(*(numerosArvore + i));
                    raizAvl = insereNo(raizAvl, novoNoAvl);
                }
                fim = clock();
                tempoMontagem = ((double)(fim-inicio)/CLOCKS_PER_SEC);
                printf("\n\nTempo para montagem da árvore: %lf s\n\n", tempoMontagem);
                printf("\n\nQuantidade de rotações para inserir balanceado: %d", ctdRotacao);
                printf("\n\nTravessia In Order ao final: ");
                printf("[ ");
                imprimeInOrder(raizAvl);
                printf("]");
                printf("\n\nTravessia Pre Order ao final: ");
                printf("[ ");
                imprimePreOrder(raizAvl);
                printf("]");
                printf("\n\nTravessia Pos Order ao final: ");
                printf("[ ");
                imprimePosOrder(raizAvl);
                printf("]");
                print2DUtil(raizAvl, 0);
                do{
                    opcaoOperacao = menuOperacoes();
                    switch(opcaoOperacao){
                        case 1:
                            ctdAcessos = 0;
                            printf("\n\nDigite o valor que deseja buscar: ");
                            scanf("%d", &valorBuscado);
                            inicio = clock();
                            buscaValor(raizAvl, valorBuscado);
                            fim = clock();
                            tempoBusca = ((double)(fim-inicio)/CLOCKS_PER_SEC);
                            printf("\n\nTempo para realizar busca: %lf s\n\n", tempoBusca);
                            printf("\n\nQuantidade de acessos para realizar busca: %d", ctdAcessos);
                        break;
                        case 2:
                            ctdRotacao = 0;
                            ctdAcessos = 0;
                            printf("\n\nTravessia In Order antes da remoção: ");
                            printf("[ ");
                            imprimeInOrder(raizAvl);
                            printf("]");
                            printf("\n\nDigite o valor que deseja remover: ");
                            scanf("%d", &valorDeletado);
                            inicio = clock();
                            raizAvl = removeValor(raizAvl, valorDeletado);
                            fim = clock();
                            tempoRemocao = ((double)(fim-inicio)/CLOCKS_PER_SEC);
                            printf("\n\nTempo para realizar remoção: %lf s\n\n", tempoRemocao);
                            printf("\n\nQuantidade de acessos para realizar remoção: %d", ctdAcessos);
                            printf("\n\nTravessia In Order ao final: ");
                            printf("[ ");
                            imprimeInOrder(raizAvl);
                            printf("]\n\n");
                            print2DUtil(raizAvl, 0);
                            printf("\n\nAperte ENTER para continuar... ");
                            LIMPA_BUFFER;
                            getchar();
                        break;
                    }
                }while(opcaoOperacao != 0);
            break;

            case SAIR:
                LIMPA_TELA;
                printf("Liberando ponteiros");
                free(numerosArvore);
                printf("\nEncerrando programa\n");
            break;
        }
    }while (opcaoMenu != 0);

    return 0;
}
