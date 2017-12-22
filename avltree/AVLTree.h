#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>
#include <iostream>

using namespace std;

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

        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    };

    Node *root = nullptr;

public:
    ~AVLTree();

    bool insert(int value);

    bool remove(int value);

    bool search(int value);

    void upin(Node *node);

    void rotateLeft(Node *node);

    void rotateRight(Node *node);

    void rotateLeftRight(Node *node);

    void rotateRightLeft(Node *node);

    bool isEmpty();

    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
};

#endif //AVLTREE_AVLTREE_H
