//
// Created by Erik Karlsson on 4/1/16.
//

#ifndef RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H
#define RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H

#include "RBNode.h"

class RedBlackTree
{
    public:
        RedBlackTree();

        void insert(RBNode *insertNode);

    private:
        RBNode *_root;

        int height;

        int size;

        void rotateRight(RBNode *y);

        void rotateLeft(RBNode *x);

        void insert_fixup(RBNode *z);

        void delete_fixup(RBNode *x);

        void transplant(RBNode *u, RBNode *v);

        void deleteNode(RBNode *deleteNode);

        RBNode *minimum(RBNode *x);

        RBNode *maximum(RBNode *x);
};

#endif //RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H
