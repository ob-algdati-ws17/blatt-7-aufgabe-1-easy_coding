#include "AVLTree.h"
#include <iostream>

using namespace std;

AVLTree::Node::Node(int const value)
        : key(value) {
    cout << "Node constructor 1" << endl;
}

AVLTree::Node::Node(int const value, AVLTree::Node *l, AVLTree::Node *r)
        : key(value), left(l), right(r) {
    cout << "Node constructor 2" << endl;
}

AVLTree::Node::~Node() {
    cout << "Node destructor" << endl;
}

AVLTree::~AVLTree() {
    cout << "Tree destructor" << endl;

}

bool AVLTree::insert(const int value) {
    cout << "Tree insert" << endl;
    auto toInsert = new Node(value);

    if (root == nullptr) {
        root = toInsert;
        return true;
    }

    auto current = root;

    while (true) {
        if (current->key == value) {
            return false;
        }
        if (value < current->key) {
            if (current->left == nullptr) {
                // add Node to the left
                current->left = toInsert;
                current->left->previous = current;
                upin(current->left); // fixing balance
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                // add Node to the right
                current->right = toInsert;
                current->right->previous = current;
                upin(current->right); // fixing balance
                return true;
            }
            current = current->right;
        }
    }
}

bool AVLTree::remove(const int value) {
    cout << "Tree remove" << endl;
    return false;
}

bool AVLTree::search(const int value) {
    cout << "Tree search" << endl;

    if (root == nullptr) {
        return false;
    }

    auto current = root;

    while (true) {
        if (current->key == value) {
            return true;
        }
        if (value < current->key) {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                return false;
            }
        } else {
            if (current->right != nullptr) {
                current = current->right;
            } else {
                return false;
            }
        }
    }
}

void AVLTree::upin(AVLTree::Node *node) {
    if (root == node) {
        return;
    }

    if (node->previous->bal == 1) {
        if (node->key < node->previous->key) {
            node->previous->bal--;
        } else {
            node->previous->bal++;
            // could get +2
        }

    }
    if (node->previous->bal == -1) {
        if (node->key < node->previous->key) {
            node->previous->bal--;
            // could get -2
        } else {
            node->previous->bal++;
        }
    }
    if (node->previous->bal == 0) {
        if (node->key < node->previous->key) {
            node->previous->bal--;
        } else {
            node->previous->bal++;
        }
    }

    upin(node->previous);
}

void AVLTree::rotateLeft(AVLTree::Node *node) {

}

void AVLTree::rotateRight(AVLTree::Node *node) {

}
