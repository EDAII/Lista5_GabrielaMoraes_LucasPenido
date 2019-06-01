#ifndef RBT_HPP
#define RBT_HPP

enum Color{red, black};

struct Node {
    int value;
    Node * left;
    Node * right;
    Node * parent;
    Color color;
};

class Tree {
public:
    Node * root;

    Tree() { root = NULL; }

    void insert(int element);
    void erase(int element);

    void rotate_right(Node *gr, Node *par, Node *ch);
    void rotate_left(Node *gr, Node *par, Node *ch);

    bool find(int element);

    void clear();
    bool empty();
    int size();
    int black_height();

    void print_preorder();
    void print_inorder();
    void print_postorder();

};

#endif
