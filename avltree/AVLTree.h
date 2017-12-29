#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>
#include <iostream>

using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        int bal = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;

        ~Node();

        Node(int value);

        vector<int> *preorder() const;

        vector<int> *inorder() const;

        vector<int> *postorder() const;

        vector<int> *inorderBalance() const;
    };

    Node *root = nullptr;

    void upin(Node *node);

    void upout(Node *node);

    void rotateLeft(Node *node);

    void rotateRight(Node *node);

    void rotateLeftRight(Node *node);

    void rotateRightLeft(Node *node);

    void deleteWithoutChild(Node *node);

    void deleteWithOneChild(Node *node);

    void deleteWithTwoChild(Node *node);

public:
    ~AVLTree();

    bool insert(int value);

    bool remove(int value);

    bool search(int value);

    bool isEmpty();

    vector<int> *preorder() const;

    vector<int> *inorder() const;

    vector<int> *postorder() const;

    vector<int> *inorderBalance() const;
};

#endif //AVLTREE_AVLTREE_H
