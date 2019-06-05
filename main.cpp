#include <bits/stdc++.h>
#include <stdio.h>
#include "rbt.hpp"
#include "splay.hpp"

using namespace std;

#define LIMPA_TELA system("clear");
#define LIMPA_BUFFER fflush(stdin);

#define Splay 1
#define SAIR 0
#define REPETIDO 0
#define NREPETIDO 1

int escolheQtdNos(){
    int qtdNos;
    do{
        printf("\n\nQuantos nós a árvore possuirá ? ");
        scanf("%d", &qtdNos);
    }while (qtdNos < 1);

    return qtdNos;
}

int validaEscolha(int escolha){
  while(escolha < 0 || escolha > 1){
      printf("\nOpção inválida! Tente novamente");
      printf("\n\nDigite o número da opção que deseja desempenhar: ");
      scanf("%d", &escolha);
  }
  return escolha;
}

int menu(){
  int escolha;

  printf("=============== Menu Principal ==========================");
  printf("\n1. Splay");
  printf("\n0. Sair");
  printf("\n\nDigite o número da opção que deseja desempenhar: ");
  scanf("%d", &escolha);
  escolha = validaEscolha(escolha);

  return escolha;
}

int* preencheVetorAleatorio(int *vetor, int tamanho){
  srand (time(NULL));
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

int validaOperacao(int operacao){
  while(operacao < 0 || operacao > 2){
      printf("\nOpção inválida! Tente novamente");
      printf("\n\nDigite o número da operação que deseja desempenhar: ");
      scanf("%d", &operacao);
  }
  return operacao;
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

int main() {
  Tree arvore;
  SplayTree splayArvore;
  struct node *root = NULL;

  int opcaoMenu, qtdNos, opcaoOperacao, opcaoOperacaoTreap, valorDeletado, valorBuscado, ctdRotacao, ctdAcessos;
  double inicio, fim, tempoPreenchimento, tempoMontagem, tempoBusca, tempoRemocao;
  int *numerosArvore = NULL;

  do{
    LIMPA_TELA;
    opcaoMenu = menu();
    switch(opcaoMenu){
      case Splay:
      LIMPA_TELA;
      printf("======================= Splay =========================");
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
      printf("\n\nMontando árvore Splay...");
      ctdRotacao = 0;
      inicio = clock();
      for(int i = 0; i < qtdNos; i++){
        root = splayArvore.insert(root, *(numerosArvore + i));
      }
      fim = clock();
      tempoMontagem = ((double)(fim-inicio)/CLOCKS_PER_SEC);
      printf("\n\nTempo para montagem da árvore: %lf s\n\n", tempoMontagem);
      printf("\n\nQuantidade de rotações para inserir balanceado: %d", ctdRotacao);
      printf("\n\nTravessia In Order ao final: ");
      printf("[ ");
      splayArvore.inOrder(root);
      printf("]");
      printf("\n\nTravessia Pre Order ao final: ");
      printf("[ ");
      splayArvore.preOrder(root);
      printf("]");
      printf("\n\nTravessia Pos Order ao final: ");
      printf("[ ");
      splayArvore.posOrder(root);
      printf("]");
      do{
        opcaoOperacao = menuOperacoes();
        switch(opcaoOperacao){
          case 1:
          ctdAcessos = 0;
          printf("\n\nDigite o valor que deseja buscar: ");
          scanf("%d", &valorBuscado);
          inicio = clock();
          splayArvore.search(root, valorBuscado);
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
          splayArvore.inOrder(root);
          printf("]");
          printf("\n\nDigite o valor que deseja remover: ");
          scanf("%d", &valorDeletado);
          inicio = clock();
          root = splayArvore.delete_key(root, valorDeletado);
          fim = clock();
          tempoRemocao = ((double)(fim-inicio)/CLOCKS_PER_SEC);
          printf("\n\nTempo para realizar remoção: %lf s\n\n", tempoRemocao);
          printf("\n\nQuantidade de acessos para realizar remoção: %d", ctdAcessos);
          printf("\n\nTravessia In Order ao final: ");
          printf("[ ");
          splayArvore.inOrder(root);
          printf("]\n\n");
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

  // if (arvore.empty()) cout << "Arvore vazia" << endl;
  // arvore.insert(17);
  // arvore.insert(26);
  // arvore.insert(8);
  // arvore.insert(5);
  // arvore.insert(6);
  // arvore.insert(7);
  //
  // arvore.print_preorder();
  // cout << "--\n";
  // arvore.print_inorder();
  // cout << "--\n";
  // arvore.print_postorder();
  // cout << "--\n";
  //
  // cout << "Tamanho = " << arvore.size() << endl;
  // cout << "Altura  = " << arvore.black_height() << endl;
  // if (arvore.find(42)) cout << 17 << " encontrado!\n";
  // if (arvore.find(63)) cout << 63 << " encontrado!\n";
  // if (arvore.find( 8)) cout <<  8 << " encontrado!\n";
  // if (arvore.find( 5)) cout <<  5 << " encontrado!\n";
  // if (arvore.find( 7)) cout <<  7 << " encontrado!\n";
  //
  // cout << "--\n";
  // arvore.erase(17);
  // arvore.erase(48);
  //
  // arvore.print_preorder();
  // cout << "--\n";
  // arvore.print_inorder();
  // cout << "--\n";
  // arvore.print_postorder();
  // cout << "--\n";
  //
  //
  // arvore.erase(26);
  // arvore.erase(5);
  // arvore.erase(8);
  // arvore.erase(7);
  // arvore.erase(6);
  //
  // cout << "--\n";
  // arvore.print_preorder();
  // cout << "--\n";
  // arvore.print_inorder();
  // cout << "--\n";
  // arvore.print_postorder();
  // cout << "--\n";
  //
  // cout << "Tamanho = " << arvore.size() << endl;
  // cout << "Altura  = " << arvore.black_height() << endl;
  //
  // if (arvore.find(42)) cout << 42 << " encontrado!\n";
  // if (arvore.find(63)) cout << 63 << " encontrado!\n";
  // if (arvore.find(48)) cout << 48 << " encontrado!\n";
  // if (arvore.find( 5)) cout <<  5 << " encontrado!\n";
  // if (arvore.find(57)) cout << 57 << " encontrado!\n";
  //
  // if (arvore.empty()) cout << "Arvore vazia" << endl;
  //
  // arvore.clear();
  // if (arvore.empty()) cout << "Arvore vazia" << endl;
  //
  // arvore.print_preorder();
  // arvore.print_inorder();
  // arvore.print_postorder();
  return 0;
}
