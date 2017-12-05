#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

class AVLTree {
private:
    struct Node {
        const int key;
        int bal = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;

        ~Node();

        Node(int value);

        Node(int value, Node *l, Node *r);

    };

    Node *root = nullptr;

public:
    ~AVLTree();

    bool insert(int value);

    bool remove(int value);

    bool search(int value);

};

#endif //AVLTREE_AVLTREE_H
