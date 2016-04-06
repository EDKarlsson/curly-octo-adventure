//
// Created by Erik Karlsson on 4/1/16.
//

#ifndef RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H
#define RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H

#include "RBNode.h"
#include <sstream>
#include <deque>
#include <iomanip>
#include <cmath>
#include <vector>

class RedBlackTree
{
    public:
        RedBlackTree();

        void insert(int key, std::string value);

        void remove(int key);

        bool findKey(int key);

        std::string getValue(int key);

        std::vector<std::string> getAllValues(int key);

        bool isEmpty() const;

        int getSize() const;

        void printTree();

    private:
        RBNode *_root;

        RBNode *nil;

        const int OUTPUT_DIVIDER = 150;

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

        void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel,
                        const std::deque<RBNode *> &nodesQueue, std::ostream &out);

        int maxHeight(RBNode *p);

        void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel,
                           const std::deque<RBNode *> &nodesQueue, std::ostream &out);

        void printPretty(RBNode *root, int level, int indentSpace, std::ostream &out);

        void printLeaves(int indentSpace, int level, int nodesInThisLevel,
                         const std::deque<RBNode *> &nodesQueue, std::ostream &out);

        std::string intToString(int val);

        void outputDivider() const;
};

#endif //RED_BLACK_TREE_DICTIONARY_REDBLACKTREE_H
