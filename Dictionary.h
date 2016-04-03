//
// Created by Erik Karlsson on 4/3/16.
//

#ifndef RED_BLACK_TREE_DICTIONARY_DICTIONARY_H
#define RED_BLACK_TREE_DICTIONARY_DICTIONARY_H

#include <vector>
#include "RedBlackTree.h"

class Dictionary
{
    public:
        RBNode *find(int key);

        std::vector findAll(int key);

        bool erase(int key);

        bool erase(RBNode *node);

        RBNode *begin();

        RBNode *end();

        int  size();

        bool empty();

    private:

};

#endif //RED_BLACK_TREE_DICTIONARY_DICTIONARY_H
