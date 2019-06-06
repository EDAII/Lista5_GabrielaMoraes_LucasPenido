#include <bits/stdc++.h>
#include <stdio.h>
#include "rbt.hpp"
#include "splay.hpp"

using namespace std;

#define LIMPA_TELA system("clear");
#define LIMPA_BUFFER fflush(stdin);

#define Criar 1
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
  printf("\n1. Criar arvores Splay e Vermelho e Preto");
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
       vetor[i] = rand() % 100000000 + 1;
       status =  NREPETIDO;
       for (aux = 0; (aux < i) && (status == NREPETIDO); aux++){
           if (vetor[i] == vetor[aux])
              status = REPETIDO;
        }
     } while (status == REPETIDO);
  }
  return vetor;
}

int* preencheVetorParaBusca(int *vetor, int tamanho) {
  srand (time(NULL));
  // Variáveis
  int i, aux, status;
  // Instruções
  for (i = 0; i < tamanho; i++) {
    vetor[i] = rand() % tamanho;
  }
  return vetor;
}

int validaOperacao(int operacao){
  while(operacao < 0 || operacao > 5){
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
    printf("\n3. Em Ordem");
    printf("\n4. Pre Ordem");
    printf("\n5. Pos Ordem");
    printf("\n0. Sair");
    printf("\n\nDigite o número da operação que deseja desempenhar: ");
    scanf("%d", &operacao);
    operacao = validaOperacao(operacao);

    return operacao;

}

int main() {
  Tree arvoreVermelhoEPreto;
  SplayTree splayArvore;
  struct node *root = NULL;

  int opcaoMenu, qtdNos, opcaoOperacao, opcaoOperacaoTreap, valorDeletado, valorBuscado, ctdRotacao, ctdAcessos;
  double inicio, fim, tempoPreenchimento, tempoMontagem, tempoBusca, tempoRemocao;
  int *numerosArvore = NULL;
  int *vetorBusca = NULL;

  do{
    LIMPA_TELA;
    opcaoMenu = menu();
    switch(opcaoMenu){
      case Criar:
      LIMPA_TELA;
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
      getchar();
      printf("======================= Splay =========================");
      printf("\n\nMontando árvore Splay...");
      splayArvore.ctdRotacao = 0;
      inicio = clock();
      for(int i = 0; i < qtdNos; i++){
        root = splayArvore.insert(root, *(numerosArvore + i));
      }
      fim = clock();
      tempoMontagem = ((double)(fim-inicio)/CLOCKS_PER_SEC);
      printf("\n\nTempo para montagem da árvore Splay: %lf s", tempoMontagem);
      printf("\n\nQuantidade de rotações para inserir balanceado: %d", splayArvore.ctdRotacao);

      printf("\n\n================== Vermelho e Preto ===================");
      printf("\n\nMontando árvore Vermelho e Preto...");
      arvoreVermelhoEPreto.ctdRotacao = 0;
      inicio = clock();
      for(int i = 0; i < qtdNos; i++){
        arvoreVermelhoEPreto.insert(*(numerosArvore + i));
      }
      fim = clock();
      tempoMontagem = ((double)(fim-inicio)/CLOCKS_PER_SEC);
      printf("\n\nTempo para montagem da árvore Vermelho e Preto: %lf s", tempoMontagem);
      printf("\n\nQuantidade de rotações para inserir balanceado: %d", arvoreVermelhoEPreto.ctdRotacao);

      do{
        opcaoOperacao = menuOperacoes();
        switch(opcaoOperacao){
          case 1:
          vetorBusca = NULL;
          printf("\n\nDigite quantidade de números que deseja buscar: ");
          scanf("%d", &valorBuscado);
          vetorBusca = (int *) malloc (valorBuscado * sizeof(int));
          vetorBusca = preencheVetorParaBusca(vetorBusca, valorBuscado);

          splayArvore.ctdAcessos = 0;
          splayArvore.ctdRotacao = 0;
          inicio = clock();
          for (int i = 0; i < valorBuscado; i++) {
            splayArvore.search(root, *(numerosArvore + i));
          }
          fim = clock();
          tempoBusca = ((double)(fim-inicio)/CLOCKS_PER_SEC);
          printf("======================= Splay =========================");
          printf("\n\nTempo para realizar busca: %lf s\n\n", tempoBusca);
          printf("\n\nQuantidade de acessos para realizar busca na Splay: %d", splayArvore.ctdAcessos);
          printf("\n\nQuantidade de rotações para realizar a busca: %d", splayArvore.ctdRotacao);

          arvoreVermelhoEPreto.ctdAcessos = 0;
          arvoreVermelhoEPreto.ctdRotacao = 0;
          inicio = clock();
          for (int i = 0; i < valorBuscado; i++) {
            arvoreVermelhoEPreto.find(*(numerosArvore + i));
          }
          fim = clock();
          tempoBusca = ((double)(fim-inicio)/CLOCKS_PER_SEC);
          printf("\n\n================== Vermelho e Preto ===================");
          printf("\n\nTempo para realizar busca: %lf s\n\n", tempoBusca);
          printf("\n\nQuantidade de acessos para realizar busca na Vermelho e Preto: %d", arvoreVermelhoEPreto.ctdAcessos);
          printf("\n\nQuantidade de rotações para realizar a busca: %d", arvoreVermelhoEPreto.ctdRotacao);

          break;
          case 2:
          printf("======================= Splay =========================");
          splayArvore.ctdRotacao = 0;
          splayArvore.ctdAcessos = 0;
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
          printf("\n\nQuantidade de acessos para realizar remoção: %d", splayArvore.ctdAcessos);
          printf("\n\nQuantidade de rotações para realizar a remoção: %d", splayArvore.ctdRotacao);
          printf("\n\nAperte ENTER para continuar... ");
          LIMPA_BUFFER;
          getchar();
          printf("\n\nTravessia In Order ao final: ");
          printf("[ ");
          splayArvore.inOrder(root);
          printf("]\n\n");
          printf("\n\nAperte ENTER para continuar... ");
          LIMPA_BUFFER;
          getchar();
          break;
          case 3:
          printf("\n\nTravessia In Order na Splay: ");
          printf("[ ");
          splayArvore.inOrder(root);
          printf("]");
          printf("\n\nTravessia In Order na Vermelho e Preto: ");
          printf("[ ");
          arvoreVermelhoEPreto.print_inorder();
          printf("]");
          break;
          case 4:
          printf("\n\nTravessia Pre Order na Splay: ");
          printf("[ ");
          splayArvore.preOrder(root);
          printf("]");
          printf("\n\nTravessia Pre Order na Vermelho e Preto: ");
          printf("[ ");
          arvoreVermelhoEPreto.print_preorder();
          printf("]");
          break;
          case 5:
          printf("\n\nTravessia Pos Order na Splay: ");
          printf("[ ");
          splayArvore.posOrder(root);
          printf("]");
          printf("\n\nTravessia Pos Order na Vermelho e Preto: ");
          printf("[ ");
          arvoreVermelhoEPreto.print_postorder();
          printf("]");
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
