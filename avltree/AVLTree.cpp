#include "AVLTree.h"
#include <iostream>

using namespace std;

AVLTree::~AVLTree() {
 cout << "Tree Destructor" << endl;
}

bool AVLTree::insert(const int) {
    cout << "Tree Insert" << endl;
    return false;
}

bool AVLTree::remove(const int) {
    cout << "Tree Remove" << endl;
    return false;
}

bool AVLTree::search(const int) {
    cout << "Tree Search" << endl;
    return false;
}
