#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template <class Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode (const Comparable & x, BinaryNode* left, BinaryNode* right) : element(x), left(left), right(right) {};
        BinaryNode (Comparable && x, BinaryNode* left, BinaryNode* right) : element(move(x)), left(left), right(right) {};
        
    };

    BinaryNode* root;
    void insert (Comparable && x, BinaryNode* & t) {
        if (t == nullptr) {
            t = new BinaryNode (move(x), nullptr, nullptr);
        } else if (x < t->element) {
            insert (x, t->left);
        } else if (x > t->element) {
            insert (x, t->right);
        }
    }

    BianryNode * findMin (const BinaryNode* t) {
        if (t == nullptr) {
            return nullptr;
        } else if (t->left == nullptr) {
            return t;
        } else {
            findMin(t->left);
        }
    }

    BinaryNode * findMax (const BinaryNode* t) {
        if (t == nullptr) {
            return nullptr;
        } else if (t->right == nullptr) {
            return t;
        } 
        return findMax(t->right);
    }

    BinaryNode* findMinIterative(const BinaryNode* t) {
        if (t == nullptr) {
            return nullptr;
        } 
        while (t->left != nullptr) {
            t = t->left;
        }
        return t;
    }

    void deleteNode (const Comparable &x, BinaryNode* & t) {
        if (t == nullptr) {
            return ;
        }
        if (x < t->element) {
            deleteNode (t->left);
        } else if (x > t->element) {
            deleteNode (t->right);
        } else {
            // Case 1 t has two children 
            if (t->left != nullptr && t->right != nullptr) {
                t->element = findMin(t->right)->element;
                deleteNode(t->element, t->right);
            } else {
                BinaryNode * oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }
    }

public:
    BinarySearchTree () {
        root = nullptr;
    }

    void insert (Comparable && x) {
        insert (x, root);
    }

    void deleteNode (const Comparable & x) {
        deleteNode(x, root);
    }

    int NumOfNodes (BinaryNode* node = root) const {
        if (node == nullptr) {
            return 0;
        } else {
            return 1 + NumOfNodes(node->left) + numOfNodes(node->right);
        }
    }

    int NumOfLeaves (BinaryNode * node = root) const {
        if (node = nullptr) {
            return 0;
        } else if (node->left == nullptr && node->right == nullptr) {
            return 1;
        } else {
            return NumOfLeaves(node->left) + NumOfLeaves(node->right);
        }
    }

    int NumOfFullNodes (BinaryNode* node = root) const {
        if (node == nullptr) {
            return 0
        } else if (node->left == nullptr || node->right == nullptr) {
            return NumOfFullNodes(node->left) + NumOfFullNodes(node->right);
        } else {
            return 1 + NumOfFullNodes(node->left) + NumOfFullNodes(node->right);
        }
    }   

    int depthTree (BinaryNode* node = root) const {
        if (node == nullptr || (node->right == nullptr && node->left == nullptr)) {
            return 0;
        } else {
            return 1 + max (depthTree(node->left), depthTree(node->right));
        }
    }
};

#endif