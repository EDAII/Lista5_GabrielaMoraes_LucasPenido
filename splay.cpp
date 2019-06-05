// fonte: https://www.geeksforgeeks.org/
// C implementation Splay Tree
#include<stdio.h>
#include<stdlib.h>
#include "splay.hpp"

/* Aloca um novo nó */
struct node * SplayTree::newNode(int key) {
  struct node* node = (struct node*)malloc(sizeof(struct node));
  node->key = key;
  node->left = node->right = NULL;
  return (node);
}

/* Rotaciona para a direita o nó x */
struct node * SplayTree::rightRotate(struct node *x) {
  struct node *y = x->left;
  x->left = y->right;
  y->right = x;
  return y;
}

/* Roraciona para a esquerda o nó x */
struct node * SplayTree::leftRotate(struct node *x) {
  struct node *y = x->right;
  x->right = y->left;
  y->left = x;
  return y;
}

// Explicação: https://www.geeksforgeeks.org/splay-tree-set-1-insert/
// A função splay traz a chave desejada para a raiz se ele estiver presente na árvore
// Se a chave não estiver presente, então traz para a raiz o último nó acessado
// Esta função modifica a árvore e retorna a raiz.
struct node * SplayTree::splay(struct node *node, int key)
{
  // O nó é nulo ou a chave foi encontrada
  if (node == NULL || node->key == key)
  return node;

  // A chave está para o lado esquerdo do nó acessado
  if (node->key > key) {
    // A chave não está na árvore
    if (node->left == NULL) return node;

    // Zig-Zig (Left Left)
    // 2 rotações para a esquerda
    if (node->left->key > key) {
      // Recursivamente traz a chave para o filho da esquerda do filho da esquerda
      // do nó acessado
      node->left->left = splay(node->left->left, key);

      // Realiza a primeira rotação para a direita do nó acessado
      node = rightRotate(node);
    } else if (node->left->key < key) { // Zag-Zig (Left Right)
      // Uma rotação para esquerda e uma para a direita

      // Recursivamente traz a chave para o filho da direita do filho da esquerda
      // do nó acessado
      node->left->right = splay(node->left->right, key);

      // Realiza a primeira rotação para a esquerda do nó acessado
      if (node->left->right != NULL)
      node->left = leftRotate(node->left);
    }

    // Realiza a segunda rotação
    return (node->left == NULL)? node: rightRotate(node);
  }
  else {// A chave está no lado direito do nó acessado
    // A chave não está na árvore
    if (node->right == NULL) return node;

    // Zig-Zag (Right Left)
    // Uma rotação para a direita e uma para esquerda
    if (node->right->key > key) {
      // Recursivamente traz a chave para o filho da esquerda do filho da direita
      // do nó acessado
      node->right->left = splay(node->right->left, key);

      // Realiza a primeira rotação para a direita do nó acessado
      if (node->right->left != NULL)
      node->right = rightRotate(node->right);
    } else if (node->right->key < key) { // Zag-Zag (Right Right)
      // Realiza 2 rotações para a direita

      // Recursivamente traz a chave para o filho da direita do filho da direita
      // do nó acessado
      node->right->right = splay(node->right->right, key);

      // Realiza a primeira rotação para a esquerda do nó acessado
      node = leftRotate(node);
    }

    // Realiza a segunda rotação para o nó acessado
    return (node->right == NULL)? node: leftRotate(node);
  }
}

// Função de busca
// retorna o novo nó da árvore
// Se a chave for encontrada ela se torna a raiz
node * SplayTree::search(node *root, int key) {
  return splay(root, key);
}

// Explicação: https://www.geeksforgeeks.org/splay-tree-set-2-insert-delete/
// Função para inserir um nova chave key
// na árvore passando a raiz
node * SplayTree::insert(node *root, int key) {
  // Caso a raiz for nula
  if (root == NULL) return newNode(key);

  // Traz o nó com a chave mais próxima para a raiz da árvore
  root = splay(root, key);

  // Se a chave já estiver na árvore
  if (root->key == key) return root;

  // Caso contrário, alocar um novo nó
  node *newnode = newNode(key);

  // Se a chave da raiz for maior, então
  // a raiz vira o filho da direita do novo nó
  // e copia o filho da esquerda da raiz para o filho da esquerda do novo nó
  if (root->key > key) {
    newnode->right = root;
    newnode->left = root->left;
    root->left = NULL;
  }

  // Se a chave da raiz for menor, então
  // a raiz vira o filho da esquerda do novo nó
  // e copia o filho da direita da raiz para o filho da direita do novo nó
  else {
    newnode->left = root;
    newnode->right = root->right;
    root->right = NULL;
  }

  // novo nó se torna a raiz da árvore
  return newnode;
}

// Explicação https://www.geeksforgeeks.org/splay-tree-set-3-delete/
// Função que deleta um nó da árvore. Retorna uma nova raiz da árvore
// depois de apagar o nó
struct node* SplayTree::delete_key(struct node *root, int key) {
  struct node *temp;
  // Caso a raiz for nula
  if (root == NULL) return NULL;

  // Traz o nó com a chave mais próxima para a raiz da árvore
  root = splay(root, key);

  // Caso a chave não esteja presente, então
  // retorna a raiz
  if (root->key != key)
  return root;

  // Caso a chave exista

  // Se o filho da esquerda não existir
  // então o filho da direita se torna a raiz
  if (root->left == NULL) {
    temp = root;
    root = root->right;
  } else {
    temp = root;

    // Traz o maior nó da árvore da esquerda para a raiz
    root = splay(root->left, key);

    // Torna o filho da direita da raiz anterior
    // como o filho da direita da nova raiz.
    root->right = temp->right;
  }

  // Libera a raiz anterior, que é o nó contendo
  // a chave que desejamos apagar
  free(temp);

  // Retorna a nova raiza da árvore
  return root;

}

// Emprime a pre ordem da árvore
void SplayTree::preOrder(struct node *root) {
  if (root != NULL) {
    preOrder(root->left);
    printf("%d ", root->key);
    preOrder(root->right);
  }
}

void SplayTree::inOrder(struct node *root) {
  if (root != NULL) {
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
  }
}

void SplayTree::posOrder(struct node *root) {
  if (root != NULL) {
    posOrder(root->left);
    printf("%d ", root->key);
    posOrder(root->right);
  }
}
