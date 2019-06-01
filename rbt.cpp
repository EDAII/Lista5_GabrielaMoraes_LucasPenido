#include <bits/stdc++.h>
#include "rbt.hpp"

using namespace std;

// Variáveis Globais;
int i = 0;
Node *child;
Node *grand;

// Protótipos:
bool checkCase3To3();
bool checkCase2To3();
bool checkCase1To3();

bool checkCase3To3() {
  grand = child->parent->parent;
  Node *uncle = new Node;

  if (grand->right == child->parent) {
    uncle = grand->left;
  }
  else if (grand->left == child->parent) {
    uncle = grand->right;
  }
  else {
    uncle = NULL;
  }

  if (uncle != NULL && uncle->color == red) {

    child->parent->color = black;
    uncle->color = black;
    grand->color = red;
    child = grand;
    return checkCase1To3();
  }
  else {
    return true;
  }
}

bool checkCase2To3() {
  if (child->parent->color == black) {
    // Não faz nada
    return false;
  }
  else {
    // Checa se o pai e o tio são vermelhos
    return checkCase3To3();
  }
}

bool checkCase1To3() {
  if (child->parent == NULL) {
    child->color = black;
    return false;
  }
  else {
    // Checa a cor do pai.
    return checkCase2To3();
  }
}

void Tree::insert(int element){
  // Insere o elemento na posição correta da árvore

  Node *no = new Node;
  no->value = element;
  no->left = NULL;
  no->right = NULL;
  no->parent = NULL;
  no->color = red;

  /* Caso a árvore esteja vazia. */
  if (root == NULL) {
    root = no;
  }
  else {
    Node *temp = new Node;
    Node *ant = new Node;

    temp = root;
    while (temp != NULL) {
      ant = temp;
      if (element == temp->value) {
        delete no;
        return;
      }
      if (element > temp->value) {
        temp = temp->right;
      }
      else {
        temp = temp->left;
      }
    }
    if (element > ant->value) {
      ant->right = no;
    }
    else {
      ant->left = no;
    }
    no->parent = ant;
  }

  child = no;
  // Checa se o novo nó é nulo.
  bool ans = checkCase1To3();

  if (ans) {
    // Caso 4
    Node *grand = new Node;
    grand = child->parent->parent;

    if (child == child->parent->right && child->parent == grand->left) {
      rotate_left(grand, child->parent, child);
      child = child->left;
    }
    else if (child == child->parent->left && child->parent == grand->right) {
      rotate_right(grand, child->parent, child);
      child = child->right;
    }

    // Caso 5
    child->parent->color = black;
    grand->color = red;

    if (child == child->parent->left && child->parent == grand->left) {
      rotate_right(grand->parent, child->parent->parent, child->parent);
      if (child->parent->parent == NULL) {
        root = child->parent;
      }
    }
    else if (child == child->parent->right && child->parent == grand->right) {
      rotate_left(grand->parent, child->parent->parent, child->parent);
    }
  }
}

// NÃO FINALIZADO
void correctDoubleBlack(Node* parent, Node* sibling) {
  if (sibling->color && sibling->left == NULL && sibling->right == NULL) {
    parent->color = black;
    sibling->color = red;
  }
  else if (sibling->color && parent->right == sibling) {

  }
}

// NÃO FINALIZADO
void Tree::erase(int element){
  // Remove o elemento da árvore, se ele existir

  Node *temp = new Node;
  Node *tempParent = new Node;

  temp = root;

  if (temp == NULL) {
    return;
  }
  /* Procura o elemento a ser removido. */
  while (temp->value != element) {
    tempParent = temp;
    if (element > temp->value) {
      temp = temp->right;
    }
    else if (element < temp->value) {
      temp = temp->left;
    }
    if (temp == NULL) {
      return;
    }
  }

  // Caso o elemento a ser removido seja vermelho
  if (!temp->color) {
    // Caso o elemento a ser removido seja folha
    if (temp->right == NULL && temp->left == NULL) {
      if (tempParent->right == temp) {
        delete(temp);
        temp = NULL;
        tempParent->right = NULL;
      }
      else {
        delete(temp);
        temp = NULL;
        tempParent->left = NULL;
      }
    }
    else {
      Node *rem = new Node;
      rem = temp;

      // Procura o predecessor do nó a ser retirado
      temp = temp->left;
      while (temp->right != NULL) {
        tempParent = temp;
        temp = temp->right;
      }

      // Caso o predecessor seja vermelho
      if (!temp->color) {
        rem->value = temp->value;
        if (temp->right != NULL) {
          temp->right->parent = tempParent;
        }
        tempParent->right = temp->left;
        delete(temp);
      }
    }
  }
  else {
    // Caso o elemento a ser removido seja folha
    if (temp->right == NULL && temp->left == NULL) {
      Node *sibling = new Node;

      if (temp = tempParent->left) {
        tempParent->left = NULL;
        sibling = tempParent->right;
      }
      else {
        tempParent->right = NULL;
        sibling = tempParent->left;
      }
      delete(temp);

      correctDoubleBlack(tempParent, sibling);

    }
  }
}

void Tree::rotate_right(Node *gr, Node *par, Node *ch){
  //Rotaciona para a direita os nós

  if (gr != NULL) {
    if (gr->left == par) {
      gr->left = ch;
    }
    else {
      gr->right = ch;
    }
    ch->parent = gr;
  }
  else {
    // Caso ele não tenha avo, o nó se tornará a raiz.
    ch->parent = NULL;
    root = ch;
  }

  // Atualiza o pai da sub árvore da direita.
  if (ch->right != NULL) {
    ch->right->parent = par;
  }
  par->left = ch->right;
  ch->right = par;
  par->parent = ch;
}

void Tree::rotate_left(Node *gr, Node *par, Node *ch){
  //Rotaciona para a esquerda os

  if (gr != NULL) {
    if (gr->left == par) {
      gr->left = ch;
    }
    else {
      gr->right = ch;
    }
    ch->parent = gr;
  }
  else {
    // Caso ele não tenha avo, o nó se tornará a raiz.
    ch->parent = NULL;
    root = ch;
  }

  // Atualiza o pai da sub árvore da esquerda.
  if (ch->left != NULL) {
    ch->left->parent = par;
  }
  par->right = ch->left;
  ch->left = par;
  par->parent = ch;
}

bool Tree::find(int element){
  // Procura o elemento na árvore

  Node *temp = new Node;

  temp = root;
  while (temp != NULL) {
    if (element == temp->value) {
      return true;
    }
    else if (element > temp->value) {
      temp = temp->right;
    }
    else {
      temp = temp->left;
    }
  }

  return false;
}

void clearRecursive(Node* temp) {
  /* Remove todos os nós da árvore recursivamente. */
  if (temp == NULL) {
    return;
  }
  else {
    clearRecursive(temp->left);
    clearRecursive(temp->right);
    delete(temp);
    if (temp->right != NULL) {
      temp->right = NULL;
    }
    if (temp->left != NULL) {
      temp->left = NULL;
    }
    temp = NULL;
  }
}

void Tree::clear(){
  // Remove todos os nós da árvore

  Node *temp = new Node;
  temp = root;
  clearRecursive(temp);
  root = NULL;
}

bool Tree::empty(){
  // Verifica se a árvore está ou não vazia

  if (root == NULL) {
    return true;
  }
  else {
    return false;
  }
}

int sizeRecursive(Node *temp) {
  /* Verifica o número de nós da árvore recursivamente. */
  int nodeLeft, nodeRight;

  if (temp == NULL) {
    return 0;
  }
  nodeLeft = sizeRecursive(temp->left);
  nodeRight = sizeRecursive(temp->right);
  return nodeLeft + nodeRight + 1;

}

int Tree::size(){
  // Verifica a quantidade de nós na árvore

  Node *temp = new Node;
  temp = root;

  return sizeRecursive(temp);
}

int black_heightRecursive(Node *temp) {
  int height = 0;
  if (temp != NULL) {
    if (temp->color) {
      height = 1 + black_heightRecursive(temp->right);
    }
    else {
      height = black_heightRecursive(temp->right);
    }
  }

  return height;
}

int Tree::black_height(){
  // Verifica a altura preta da árvore

  Node *temp = new Node;
  temp = root;

  return black_heightRecursive(temp);
}

string defineColor(int numberColor) {
  if (numberColor == 1) {
    return "preto";
  }
  else {
    return "vermelho";
  }
}

void printRecursive(Node* temp, string order) {
  /* Faz a travessia recursivamente. */

  if (order == "preOrder") {
    if (temp == NULL) {
      return;
    }
    else {
      if (i == 0) {
        i++;
        std::cout << temp->value << '(' << defineColor(temp->color) << ')';
      }
      else {
        std::cout << ' ' << temp->value << '(' << defineColor(temp->color) << ')';
      }
      printRecursive(temp->left, "preOrder");
      printRecursive(temp->right, "preOrder");
    }
  }

  else if (order == "inOrder") {
    if (temp == NULL) {
      return;
    }
    else {
      printRecursive(temp->left, "inOrder");
      if (i == 0) {
        i++;
        std::cout << temp->value << '(' << defineColor(temp->color) << ')';
      }
      else {
        std::cout << ' ' << temp->value << '(' << defineColor(temp->color) << ')';
      }
      printRecursive(temp->right, "inOrder");
    }
  }

  else if (order == "postOrder") {
    if (temp == NULL) {
      return;
    }
    else {
      printRecursive(temp->left, "postOrder");
      printRecursive(temp->right, "postOrder");
      if (i == 0) {
        i++;
        std::cout << temp->value << '(' << defineColor(temp->color) << ')';
      }
      else {
        std::cout << ' ' << temp->value << '(' << defineColor(temp->color) << ')';
      }
    }
  }
}

void Tree::print_preorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós
  i = 0;

  Node *temp = new Node;
    temp = root;
  if (temp != NULL) {
    printRecursive(temp, "preOrder");
    printf("\n");
  }
}

void Tree::print_inorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós

  i = 0;

  Node *temp = new Node;
  temp = root;
  if (temp != NULL) {
    printRecursive(temp, "inOrder");
    printf("\n");
  }
}

void Tree::print_postorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós
  i = 0;

  Node *temp = new Node;
  temp = root;
  if (temp != NULL) {
    printRecursive(temp, "postOrder");
    printf("\n");
  }
}
