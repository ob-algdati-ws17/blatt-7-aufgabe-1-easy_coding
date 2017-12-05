#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

class AVLTree {
private:
    class Node {
    private:
        const int key;
        Node *left = nullptr;
        Node *right = nullptr;
    public:
        Node(const int);
    };

public:
    ~AVLTree();

    bool insert(const int);

    bool remove(const int);

    bool search(const int);

};

#endif //AVLTREE_AVLTREE_H
