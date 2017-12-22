#include "AVLTree.h"
#include <functional>
#include <vector>
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
                current->bal--;
                upin(current); // fixing balance
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                // add Node to the right
                current->right = toInsert;
                current->right->previous = current;
                current->bal++;
                upin(current); // fixing balance
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
    if (node == nullptr) {
        return;
    }
    if (node->previous == nullptr) {
        return;
    }
    // Insert to the Left
    if (node == node->previous->left) {

        // 1. Case: previous was 0 -> upin needed
        if (node->previous->bal == 0) {
            node->previous->bal = -1;
            upin(node->previous);

            // 2. Case: previous was 1 -> nothing special needed here
        } else if (node->previous->bal == 1) {
            node->previous->bal = 0;

            // 3. Case: previous was -1 and and current is -1 -> normal right rotation needed
        } else if (node->previous->bal == -1 && node->bal == -1) {
            rotateRight(node->previous);

            // 4. Case: previous was -1 and current is 1 -> left-right rotation needed
        } else if (node->previous->bal == -1 && node->bal == 1) {
            rotateLeftRight(node->previous);
        }

        // Insert to the Right
    } else if (node == node->previous->right) {

        // 1. Case: previous was 0 -> upin needed
        if (node->previous->bal == 0) {
            node->previous->bal = 1;
            upin(node->previous);

            // 2. Case: previous was -1 -> nothing special needed here
        } else if (node->previous->bal == -1) {
            node->previous->bal = 0;

            // 3. Case: previous was 1 and and current is 1 -> normal left rotation needed
        } else if (node->previous->bal == 1 && node->bal == 1) {
            rotateLeft(node->previous);

            // 4. Case: previous was 1 and current is -1 -> right-left rotation needed
        } else if (node->previous->bal == 1 && node->bal == -1) {
            rotateRightLeft(node->previous);
        }
    }
}


void AVLTree::rotateLeft(AVLTree::Node *node) {
    auto helperNodeRL = node->right->left;
    auto helperNodeR = node->right;

    if (node != root) {
        if (node->previous->left == node) {
            node->previous->left = helperNodeR;
        } else {
            node->previous->right = helperNodeR;
        }
        helperNodeR->previous = node->previous;
    }

    if (node == root) {
        root = helperNodeR;
        helperNodeR->previous = nullptr;
    }

    helperNodeR->left = node;
    node->previous = helperNodeR;
    node->right = helperNodeRL;
//    if (helperNodeRL) {
//        helperNodeRL->previous = node;
//    }
    node->bal = 0;
    helperNodeR->bal = 0;
}

void AVLTree::rotateRight(AVLTree::Node *node) {
    auto helperNodeLR = node->left->right;
    auto helperNodeL = node->left;

    if (node != root) {
        if (node->previous->left == node) {
            node->previous->left = helperNodeL;
        } else {
            node->previous->right = helperNodeL;
        }
        helperNodeL->previous = node->previous;
    }

    if (node == root) {
        root = helperNodeL;
        helperNodeL->previous = nullptr;
    }
    helperNodeL->right = node;
    node->previous = helperNodeL;
    node->left = helperNodeLR;
//    if (helperNodeLR) {
//        helperNodeLR->previous = node;
//    }
    node->bal = 0;
    helperNodeL->bal = 0;

}

void AVLTree::rotateLeftRight(AVLTree::Node *node) {
    cout << "rotate left right" << endl;
    rotateLeft(node->left);
    rotateRight(node);

}

void AVLTree::rotateRightLeft(AVLTree::Node *node) {
    cout << "rotate right left" << endl;
    rotateRight(node->right);
    rotateLeft(node);
}

bool AVLTree::isEmpty() {
    return root == nullptr;
}

vector<int> *AVLTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AVLTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}




