#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdexcept>

template <class Comparable>
class BinarySearchTree {
public:
    BinarySearchTree( );
    BinarySearchTree( const BinarySearchTree & rhs );
    BinarySearchTree( BinarySearchTree && rhs );
    ~BinarySearchTree( );
    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    bool contains( const Comparable & x ) const {
        return contains(x, root);
    }
    bool isEmpty( ) const {
        return (root==nullptr);
    }
    void printTree( ostream & out = cout ) const;
    void makeEmpty( );
    void insert( const Comparable & x ) {
        insert(x, root);
    }
    void insert( Comparable && x ) {
        insert(x, root);
    }
    void remove( const Comparable & x ) {
        remove(x, root);
    }
    Comparable findMin () const {
        return findMin(root)->element;
    }

    Comparable findMax () const {
        return findMax(root)->element;
    }
    BinarySearchTree & operator=( const BinarySearchTree & rhs );
    BinarySearchTree & operator=( BinarySearchTree && rhs );

private:
    struct BinaryNode {
        Comparable element;
        BinaryNode* left; // left child 
        BinaryNode* right; // right child 

        BinaryNode (const Comparable & element=Comparable(), BinaryNode* left=nullptr, BinaryNode* right=nullptr)
        : element(element), left(left), right(right) {}

        BinaryNode (const Comparable&& element=Comparable(), BinaryNode* left=nullptr, BinaryNode* right=nullptr)
        : element(std::move(element)), left(left), right(right) {}
    };

    BinaryNode* root;

    void insert( const Comparable & x, BinaryNode * & t ) {
        if (contains(x)) {
            throw std::exception("The tree already contains the element");
        }
        if (t == nullptr) {
            t = new BinaryNode(x, nullptr, nullptr);
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
    }

	void insert( Comparable && x, BinaryNode * & t ) {
        if (contains(x)) {
            throw std::exception("The tree already contains the element");
        }
        if (t == nullptr) {
            t = new BinaryNode(x, nullptr, nullptr);
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
    }

 	void remove( const Comparable & x, BinaryNode * & t ) {
        if (!contans(x)) {
            throw std::exception ("The tree doesn't contain this element !");
        } else {
            if (x < t->element) {
                remove(x, t->left);
            } else if (x > t->element) {
                remove(x, t->right);
            } else { // x == t->element, we delete the node
                // we have three cases 
                if (t->left != nullptr && t->right != nullptr) {
                    // the node has two childs
                    t->element = findMin(t->right)->element;
                    remove(t->element, t->right)
                } else {
                    BinaryNode* oldNode = t;
                    t = (t->left)? t->left : t->right;
                    delete oldNode;
                }
            }
        }
    }

	bool contains( const Comparable & x, BinaryNode *t ) const {
        if (t == nullptr) {
            return false;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains (x, t->right);
        } else {
            return true; // (t->element == x)
        }
    }
    BinaryNode * findMin( BinaryNode *t ) const {
        if (t == nullptr) {
            throw std::exception("The tree is empty !");
        } else if (t->left != nullptr) {
            return findMin(t->left);
        } 
        return t;
    };
	BinaryNode * findMax( BinaryNode *t ) const {
        if (t == nullptr) {
            throw std::exception("The tree is empty !");
        } else if (t->right != nullptr) {
            return findMax(t->right);
        } 
        return t;
    };
	void makeEmpty( BinaryNode * & t ){
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
 	void printTree( BinaryNode *t) const {
        if (t!=nullptr) {
            cout << t->element;
            printTree(t->left);
            printTree(t->right);
        } 
    };
	BinaryNode * clone( BinaryNode *t ) const;
};

#endif