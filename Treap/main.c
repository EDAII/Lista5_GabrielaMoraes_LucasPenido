#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio_ext.h>
#include "funcoesMenu.h"
#include "treap.h"

int main(int argc, char *argv[]){
    // Variáveis
    int opcaoMenu, qtdNos, opcaoOperacao, opcaoOperacaoTreap, valorDeletado, valorBuscado;
    int vBuscado;
    double inicio, fim, tempoPreenchimento;
    int *numerosArvore = NULL;
    noTreap *rTreap, *noTreap, *resposta = NULL;

    do{
        LIMPA_TELA;
        opcaoMenu = menu();
        switch(opcaoMenu){
            case TREAP:
                LIMPA_TELA;
                printf("======================= TREAP =========================");
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

                printf("\nMontando árvore Treap...");
                // ctdRotacao = 0;
                for(int i = 0; i < qtdNos; i++){
                    noTreap = fazNovoNoTreap(*(numerosArvore + i));
                    rTreap = inserirNoTreap(rTreap, noTreap);
                }
                // printf("\n\nQuantidade de rotações para inserir respeitando a propriedade do Max Heap: %d", ctdRotacao);
                printf("\n\nTravessia In Order: ");
                printf("[ ");
                imprimeInOrderTreap(rTreap);
                printf("]");
                printf("\n\nTravessia Pre Order ao final: ");
                printf("[ ");
                imprimePreOrderTreap(rTreap);
                printf("]");
                printf("\n\nTravessia Pos Order ao final: ");
                printf("[ ");
                imprimePosOrderTreap(rTreap);
                printf("]");
                do{
                    opcaoOperacaoTreap = menuOperacoes();
                    switch(opcaoOperacaoTreap){
                        case 1:
                            // ctdAcessos = 0;
                            printf("Valor a ser buscado: ");
                            scanf("%d", &vBuscado);
                            resposta = buscaTreap(rTreap, vBuscado);
                            if(resposta == NULL){
                                printf("\nNó não encontrado");
                            }
                            // printf("\n\nQuantidade de acessos para realizar busca: %d", ctdAcessos);
                        break;
                        case 2:
                            printf("\nNão implementado!");
                        break;
                    }
                }while(opcaoOperacaoTreap != 0);

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
