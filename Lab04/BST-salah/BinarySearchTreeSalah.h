#ifndef BINARYSEARCH_TREE
#define BINARYSEARCH_TREE

#include<iostream>
#include<stdexcept>
#include<algorithm>

using namespace std;

template <class T>
class BinarySearchTree {
    struct BinaryNode {
        T data;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const T& data = T(), BinaryNode* left=nullptr, BinaryNode* right=nullptr): data(data), left(left), right(right) {}
        BinaryNode(const BinaryNode& node): data(node.data) {
            left = (node.left) ? new BinaryNode(*node.left) : nullptr;
            right = (node.right) ? new BinaryNode(*node.right) : nullptr;
        }
        BinaryNode(BinaryNode&& node): data(move(node.data)), left(node.left), right(node.right) {
            node.left = nullptr;
            node.right = nullptr;
        }
        ~BinaryNode () {
            delete left;
            delete right;
        }
    };

    BinaryNode* root;

    void destroyTree(BinaryNode* node) {
        // This function will be called by the destructor to recursively destroy the nodes 
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        destroyTree(root);
    }

    bool isFound (const T& element) const {
        return isFound(element, root);
    }

    bool isEmpty () {
        return root == nullptr;
    }

    void insert(const T& element) {
        insert(element, root);
    }

    void remove(const T& element) {
        if (isEmpty()) {
            cout << "The tree is empty" << endl;
        } else {
            remove(element, root);
        }
    }

    T findMin() const {
        return findMin(root)->data;
    }

    T findMax() const {
        return findMax(root)->data;
    }

    // Exo 1 functions:

    int nodesCount() {
        return nodeCount(root);
    }

    int leavesCount() {
        return leavesCount(root);
    }

    int fullNodesCount() {
        return fullNodesCount(root);
    }

    int depth() {
        return depth(root);
    }

    void printTree() {
        return printTree(root);
    }

    T findKth (int k) {
        return findKth(k, root);
    }

    // Exo 2 function

    friend BinarySearchTree<int> generateRandomTree(int n);

private:

    T findKth (int k, BinaryNode* root, int& count=1) {
        if (root == nullptr) {
            return -1;
        } 
        // Process left sub-tree
        T leftResult = findKth(k, root->left, count);
        if (leftResult != -1) {
            return leftResult;
        }

        // Process the root
        if (count == k) {
            return root->data;
        }
        count++;

        // Process the right sub-tree
        return findKth(k, root->right, count);
    }

    bool isFound(const T& element, BinaryNode* node) const {
        if (node == nullptr) {
            return false;
        }
        if (node->data == element) {
            return true;
        } 
        if (element < node->data) {
            return isFound(element, node->left);
        } else {
            return isFound(element, node->right);
        }
    }

    void insert(const T& element, BinaryNode* &node) {
        if(node == nullptr) {
            node = new BinaryNode (element, nullptr, nullptr);
        }
        if (element < node->data) {
            insert(element, node->left);
        } else if (element > node->data) {
            insert(element, node->right);
        }
    }

    void remove(const T& element, BinaryNode* & node) {
        if (!isFound(element)) {
            throw runtime_error("The tree doesn't contain the element");
        } 
        if (element < node->data) {
            return remove(element, node->left);
        } else if (element > node->data) {
            return remove(element, node->right);
        } else { // we found the node
            if (node->left!=nullptr && node->right!=nullptr) { // has two childs
                BinaryNode* minNode = findMin(node->right);
                node->data = minNode->data;
                remove(minNode->data, node->right);
            } else {
               BinaryNode* oldNode = node;
               node = (node->left) ? node->left : node->right
               delete oldNode;
            }
        }
    }

    BinaryNode* findMin (BinaryNode* node) const {
        if (node == nullptr) {
            throw exception("The tree is empty");
        }
        if (node->left != nullptr) {
            return findMin(node->left);
        } 
        return node;
    }

    BinaryNode* findMax (BinaryNode* node) const {
        if (node == nullptr) {
            throw runtime_error("The tree is empty");
        } 
        if (node->right != nullptr) {
            return findMax(node->right);
        } 
        return node;
    }

    // Exo 1 help functions

    int nodesCount(BinaryNode* node) { // O(n) where n is the size of the tree
        if (node == nullptr) {
            return 0;
        } else {
            return 1 + nodeCount(node->left) + nodeCount(node->right);
        }
    }

    int leavesCount(BinaryNode* node) { // O(n) where n is the size of the tree
        if (node == nullptr) {
            return 0;
        } 
        if (node->left == nullptr && node->right == nullptr) { // The node is a leaf
            return 1; // we just return 1 because no need for further recursive calls, we reached the end !
        }
        return leavesCount(node->left) + leavesCount(node->right);
    }

    int fullNodesCount(BinaryNode* node) { // O(n) where n is the size of the tree
        if (node==nullptr) {
            return 0;
        }
        if (node->left != nullptr && node->right != nullptr) { // has two children (full node)
            return 1 + fullNodesCount(node->left) + fullNodesCount(node->right);
        } else {
            return fullNodesCount(node->left) + fullNodesCount(node->right);
        }
    }

    int depth(BinaryNode* node) { // O(n) where n is the size of the tree
        if (node==nullptr) {
            return 0;
        } else if (node->left==nullptr && node->right==nullptr) {
            return 0;
        }
        return 1 + max(depth(node->left), depth(node->right));
    }

    void printTree(BinaryNode* node) { // O(n) where n is the size of the tree
        if (node!=nullptr) {
            cout << node->data << endl;
            printTree(node->left);
            printTree(node->right);
        }
    }
};

BinarySearchTree<int> generateRandomTree(int n) {
    int keys[n];
    for (int i=1; i<=n; i++) {
        keys[i] = i;
    }
    
}

#endif