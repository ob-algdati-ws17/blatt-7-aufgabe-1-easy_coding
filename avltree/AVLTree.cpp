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
    return false;
}

bool AVLTree::remove(const int value) {
    cout << "Tree remove" << endl;
    return false;
}

bool AVLTree::search(const int value) {
    cout << "Tree search" << endl;
    return false;
}
