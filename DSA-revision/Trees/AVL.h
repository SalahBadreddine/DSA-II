#ifndef AVL_H
#define AVL_h

#include <iostream>
using namespace std;

template<class Comparable>
class AVLTree {
private:
    struct AvlNode {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode (const Comparable & x, AvlNode* left, AvlNode* right, int height = 0): element(element), left(left),
        right (right), height(height) {};
    }

    int height (AvlNode* root) {
        return root->height;
    }

    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > 1 )
			// Left left imbalance
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
			// Left right imbalance
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > 1 )
			// Right right imbalance
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
			// Right left imbalance
            else
                doubleWithRightChild( t );
        
		// Update the height
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(k2->left->height, k2->right->height) + 1;
        k1->height = max(k1->left->height, k1->right->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
	 
	// right right imbalance
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
	 
	// right left imbalance
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

public:

};

#endif