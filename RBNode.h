//
// Created by Erik Karlsson on 4/1/16.
//

#ifndef RED_BLACK_TREE_DICTIONARY_RBNODE_H
#define RED_BLACK_TREE_DICTIONARY_RBNODE_H

#include <string>
#include <iostream>

enum color
{
    BLACK,
    RED
};

class RBNode
{
    public:
        RBNode();

        void        setKey(int key);

        void        setValue(const std::string &value);

        void        setLeft(RBNode *left);

        void        setRight(RBNode *right);

        void        setParent(RBNode *parent);

        void        setNodeColor(color nodeColor);

        std::string getValue() const;

        RBNode      *getLeft() const;

        int         getKey() const;

        RBNode      *getRight() const;

        RBNode      *getParent() const;

        color       getNodeColor() const;

        std::string getColorString() const;

        std::string getKeyColorValue() const;

    private:
        int         key;
        std::string value;
        RBNode      *left;
        RBNode      *right;
        RBNode      *parent;
        color       nodeColor;

};

#endif //RED_BLACK_TREE_DICTIONARY_RBNODE_H
