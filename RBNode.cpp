//
// Created by Erik Karlsson on 4/1/16.
//

#include "RBNode.h"

RBNode::RBNode()
{

    this->key   = -1;
    this->value = "";
    this->left  = nullptr;
    this->right  = nullptr;
    this->parent = nullptr;
    this->nodeColor = RED;
}

int RBNode::getKey() const
{
    return this->key;
}

void RBNode::setKey(int key)
{
    this->key = key;
}

std::string RBNode::getValue() const
{
    return this->value;
}

void RBNode::setValue(const std::string &value)
{
    this->value = value;
}

RBNode *RBNode::getLeft() const
{
    return this->left;
}

void RBNode::setLeft(RBNode *left)
{
    this->left = left;
}

RBNode *RBNode::getRight() const
{
    return this->right;
}

void RBNode::setRight(RBNode *right)
{
    this->right = right;
}

RBNode *RBNode::getParent() const
{
    return this->parent;
}

void RBNode::setParent(RBNode *parent)
{
    this->parent = parent;
}

color RBNode::getNodeColor() const
{
    return this->nodeColor;
}

void RBNode::setNodeColor(color nodeColor)
{
    this->nodeColor = nodeColor;
}
