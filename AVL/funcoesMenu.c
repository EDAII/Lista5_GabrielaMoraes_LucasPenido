#include "funcoesMenu.h"

int menu(){
    int escolha;

    printf("=============== Menu Principal ==========================");
    printf("\n1. AVL");
    printf("\n0. Sair");
    printf("\n\nDigite o número da opção que deseja desempenhar: ");
    scanf("%d", &escolha);
    escolha = validaEscolha(escolha);

    return escolha;

}

int validaEscolha(int escolha){
  while(escolha < 0 || escolha > 1){
      printf("\nOpção inválida! Tente novamente");
      printf("\n\nDigite o número da opção que deseja desempenhar: ");
      scanf("%d", &escolha);
  }
  return escolha;
}

int escolheQtdNos(){
    int qtdNos;
    do{
        printf("\n\nQuantos nós a árvore possuirá ? ");
        scanf("%d", &qtdNos);
    }while (qtdNos < 1);

    return qtdNos;
}

int* preencheVetorAleatorio(int *vetor, int tamanho){
  // Variáveis
  int i, aux, status;
  // Instruções
  for (i = 0; i < tamanho; i++) {
     do {
       vetor[i] = rand() % 1000000 + 1;
       status =  NREPETIDO;
       for (aux = 0; (aux < i) && (status == NREPETIDO); aux++){
           if (vetor[i] == vetor[aux])
              status = REPETIDO;
        }
     } while (status == REPETIDO);
  }
  return vetor;
}

int menuOperacoes(){
    int operacao;

    printf("\n\n=============== Operações ==========================");
    printf("\n1. Busca");
    printf("\n2. Remover");
    printf("\n0. Sair");
    printf("\n\nDigite o número da operação que deseja desempenhar: ");
    scanf("%d", &operacao);
    operacao = validaOperacao(operacao);

    return operacao;

}

int validaOperacao(int operacao){
  while(operacao < 0 || operacao > 2){
      printf("\nOpção inválida! Tente novamente");
      printf("\n\nDigite o número da operação que deseja desempenhar: ");
      scanf("%d", &operacao);
  }
  return operacao;
}
