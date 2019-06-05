#ifndef SPLAY_HPP
#define SPLAY_HPP

struct node {
  int key;
  node * left;
  node * right;
};

class SplayTree {
public:
    SplayTree() { }

    struct node * newNode(int key);
    struct node * rightRotate(struct node *x);
    struct node * leftRotate(struct node *x);
    struct node * splay(struct node *node, int key);
    node * search(node *root, int key);
    node * insert(node *root, int key);
    struct node* delete_key(struct node *root, int key);
    void preOrder(struct node *root);
    void inOrder(struct node *root);
    void posOrder(struct node *root);
};

#endif
