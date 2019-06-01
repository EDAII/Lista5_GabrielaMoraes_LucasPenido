#include <bits/stdc++.h>
#include "rbt.hpp"

using namespace std;

int main() {
    Tree arvore;

    if (arvore.empty()) cout << "Arvore vazia" << endl;
    arvore.insert(17);
    arvore.insert(26);
    arvore.insert(8);
    arvore.insert(5);
    arvore.insert(6);
    arvore.insert(7);

    arvore.print_preorder();
    cout << "--\n";
    arvore.print_inorder();
    cout << "--\n";
    arvore.print_postorder();
    cout << "--\n";

    cout << "Tamanho = " << arvore.size() << endl;
    cout << "Altura  = " << arvore.black_height() << endl;
    if (arvore.find(42)) cout << 17 << " encontrado!\n";
    if (arvore.find(63)) cout << 63 << " encontrado!\n";
    if (arvore.find( 8)) cout <<  8 << " encontrado!\n";
    if (arvore.find( 5)) cout <<  5 << " encontrado!\n";
    if (arvore.find( 7)) cout <<  7 << " encontrado!\n";

    cout << "--\n";
    arvore.erase(17);
    arvore.erase(48);

    arvore.print_preorder();
    cout << "--\n";
    arvore.print_inorder();
    cout << "--\n";
    arvore.print_postorder();
    cout << "--\n";


    arvore.erase(26);
    arvore.erase(5);
    arvore.erase(8);
    arvore.erase(7);
    arvore.erase(6);

    cout << "--\n";
    arvore.print_preorder();
    cout << "--\n";
    arvore.print_inorder();
    cout << "--\n";
    arvore.print_postorder();
    cout << "--\n";

    cout << "Tamanho = " << arvore.size() << endl;
    cout << "Altura  = " << arvore.black_height() << endl;

    if (arvore.find(42)) cout << 42 << " encontrado!\n";
    if (arvore.find(63)) cout << 63 << " encontrado!\n";
    if (arvore.find(48)) cout << 48 << " encontrado!\n";
    if (arvore.find( 5)) cout <<  5 << " encontrado!\n";
    if (arvore.find(57)) cout << 57 << " encontrado!\n";

    if (arvore.empty()) cout << "Arvore vazia" << endl;

    arvore.clear();
    if (arvore.empty()) cout << "Arvore vazia" << endl;

    arvore.print_preorder();
    arvore.print_inorder();
    arvore.print_postorder();
    return 0;
}
