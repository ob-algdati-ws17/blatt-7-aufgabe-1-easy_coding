#include "AVLTree.h"

using namespace std;

AVLTree::Node::Node(int const value) : key(value) {
}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

AVLTree::~AVLTree() {
    delete root;
}

bool AVLTree::insert(const int value) {
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
                if (current->bal != 0) {
                    upin(current); // fixing balance
                }
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                // add Node to the right
                current->right = toInsert;
                current->right->previous = current;
                current->bal++;
                if (current->bal != 0) {
                    upin(current); // fixing balance
                }
                return true;
            }
            current = current->right;
        }
    }
}

bool AVLTree::remove(const int value) {
    if (root == nullptr) {
        return false;
    }

    auto current = root;

    while (true) {
        if (current->key == value) {
            break;
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

    if (current == root && current->left == nullptr && current->right == nullptr) {
        root = nullptr;
        delete current;
        return true;
    }

    if (current->left == nullptr && current->right == nullptr) {
        // Deletion without successor
        deleteWithoutChild(current);
    } else if (current->left == nullptr && current->right != nullptr ||
               current->left != nullptr && current->right == nullptr) {
        // Deletion with one successor
        deleteWithOneChild(current);
    } else if (current->left != nullptr && current->right != nullptr) {
        // Deletetion with two successors
        deleteWithTwoChild(current);
    }

    return false;
}

void AVLTree::deleteWithoutChild(AVLTree::Node *node) {
    if (node == root) {
        root = nullptr;
        delete node;
        return;
    }

    // left
    if (node->previous->left == node) {
        node->previous->left = nullptr;
        // balance was -1 is now 0
        if (node->previous->bal == -1) {
            node->previous->bal = 0;
            upout(node->previous);
            // balance was 0 is now 1
        } else if (node->previous->bal == 0) {
            node->previous->bal = 1;
            // balance was 1 is now 2
        } else if (node->previous->bal == 1) {
            if (node->previous->right->bal == 1) {
                rotateLeft(node->previous);
            } else {
                rotateRightLeft(node->previous);
            }
        }
    } else {
        // right
        node->previous->right = nullptr;
        // balance was 1 is now 0
        if (node->previous->bal == 1) {
            node->previous->bal = 0;
            upout(node->previous);
            // balance was 0 is now -1
        } else if (node->previous->bal == 0) {
            node->previous->bal = -1;
            // balance was -1 is now -2
        } else if (node->previous->bal == -1) {
            if (node->previous->left->bal == -1) {
                rotateRight(node->previous);
            } else {
                rotateLeftRight(node->previous);
            }
        }
    }

    delete node;
}

void AVLTree::deleteWithOneChild(AVLTree::Node *node) {

    // child left
    if (node->left != nullptr) {
        auto child = node->left;
        node->key = child->key;
        node->right = nullptr;
        node->left = nullptr;
        node->bal = 0;
        if (node->previous != nullptr) {
            upout(node);
        }
        delete child;

    } else {

        // child right
        auto child = node->right;
        node->key = child->key;
        node->right = nullptr;
        node->left = nullptr;
        node->bal = 0;
        if (node->previous != nullptr) {
            upout(node);
        }
        delete child;
    }


}

void AVLTree::deleteWithTwoChild(AVLTree::Node *node) {

    // find a replacement
    auto sym = node->left;
    while (sym->right != nullptr) {
        sym = sym->right;
    }
    // switch keys
    int nodeKey = node->key;
    node->key = sym->key;
    sym->key = nodeKey;

    // delete switched node
    if (sym->right == nullptr && sym->left == nullptr) {
        deleteWithoutChild(sym);
    } else {
        deleteWithOneChild(sym);
    }

}

void AVLTree::upout(AVLTree::Node *node) {
    if (node == root) {
        return;
    }
    // left successor
    if (node == node->previous->left) {
        if (node->previous->bal == -1) {
            node->previous->bal = 0;
            upout(node->previous);
            return;
        } else if (node->previous->bal == 0) {
            node->previous->bal = 1;
            return;
        } else {
            if (node->previous->right->bal == 0) {
                rotateLeft(node->previous);
                node->bal = 0;
                node->previous->bal = 1;
                node->previous->previous->bal = -1;
            } else if (node->previous->right->bal == 1) {
                rotateLeft(node->previous);
                node->bal = 0;
                node->previous->bal = 0;
                node->previous->previous->bal = 0;
                upout(node->previous->previous);
            } else {
                int saveBalance = node->previous->right->left->bal;
                rotateRightLeft(node->previous);
                auto root = node->previous->previous;
                root->bal = 0;
                root->left->left->bal = 0;
                root->left->bal = 0;
                root->right->bal = 0;
                if (saveBalance == 1) {
                    root->left->bal = -1;
                } else if (saveBalance == -1) {
                    root->right->bal = 1;
                }
                upout(root);

            }
        }
    } else {
        // right successor
        if (node->previous->bal == 1) {
            node->previous->bal = 0;
            upout(node->previous);
            return;
        } else if (node->previous->bal == 0) {
            node->previous->bal = -1;
            return;
        } else {
            if (node->previous->left->bal == 0) {
                rotateRight(node->previous);
                node->bal = 0;
                node->previous->bal = -1;
                node->previous->previous->bal = 1;
            } else if (node->previous->left->bal == -1) {
                rotateRight(node->previous);
                node->bal = 0;
                node->previous->bal = 0;
                node->previous->previous->bal = 0;
                upout(node->previous->previous);
            } else {
                int saveBalance = node->previous->left->right->bal;
                rotateLeftRight(node->previous);
                auto root = node->previous->previous;
                root->bal = 0;
                root->right->right->bal = 0;
                root->left->bal = 0;
                root->right->bal = 0;
                if (saveBalance == 1) {
                    root->left->bal = -1;
                } else if (saveBalance == -1) {
                    root->right->bal = 1;
                }
                upout(root);
            }
        }
    }

}

bool AVLTree::search(const int value) {

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
        return;

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
        return;
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
    if (helperNodeRL != nullptr) {
        helperNodeRL->previous = node;
    }
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
    if (helperNodeLR != nullptr) {
        helperNodeLR->previous = node;
    }
    node->bal = 0;
    helperNodeL->bal = 0;

}

void AVLTree::rotateLeftRight(AVLTree::Node *node) {
    rotateLeft(node->left);
    rotateRight(node);
}

void AVLTree::rotateRightLeft(AVLTree::Node *node) {
    rotateRight(node->right);
    rotateLeft(node);
}

bool AVLTree::isEmpty() {
    return root == nullptr;
}

vector<int> *AVLTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AVLTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
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

vector<int> *AVLTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AVLTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

vector<int> *AVLTree::inorderBalance() const {
    if (root == nullptr)
        return nullptr;
    return root->inorderBalance();
}

vector<int> *AVLTree::Node::inorderBalance() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorderBalance();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(bal);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorderBalance();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}


