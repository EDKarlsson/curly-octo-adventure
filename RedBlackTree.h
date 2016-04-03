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

        void insert(int key, std::string value);

        void remove(int key);

        bool findKey(int key);

        std::string getValue(int key);

        bool isEmpty() const;

        int getSize() const;


    private:
        RBNode *_root;

        int size;

        void rotateRight(RBNode *y);

        void rotateLeft(RBNode *x);

        void insert_fixup(RBNode *z);

        void delete_fixup(RBNode *x);

        void transplant(RBNode *u, RBNode *v);

        void deleteNode(RBNode *deleteNode);

        RBNode *minimum(RBNode *x);

        RBNode *maximum(RBNode *x);

        RBNode *findNode(RBNode *x, int key);

        void insertNode(RBNode *insertNode);
};

#endif //RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H
