//
// Created by Erik Karlsson on 4/1/16.
//

#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    this->_root = nullptr;
    this->size  = 0;
}

void RedBlackTree::rotateLeft(RBNode *x)
{
    RBNode *y;


    // Set y to be the right child of x
    y = x->getRight();

    // Then set the right child of x to now be the left child of y
    x->setRight(y->getLeft());

    // If the left child of y is not nil
    if (y->getLeft() != nullptr)
    {
        // Set the parent of the left child to now be x
        y->getLeft()->setParent(x);
    }

    // Set the parent of y to now have same parent as x
    y->setParent(x->getParent());

    // If the parent of x is null (Meaning it has not parent and thus is the root)
    if (x->getParent() == nullptr)
    {
        // Set y to be the new root of the tree
        this->_root = y;
    }
    else if (x == x->getParent()->getLeft()) // Check if x is on the left side of the tree
    {
        // If see then set x's parent's left child to be y
        x->getParent()->setLeft(y);
    }
    else
    {
        // Else set x's parent's right child to by y
        x->getParent()->setRight(y);
    }

    // Set y's left child to be x
    y->setLeft(x);

    // Set y to be the new parent of x
    x->setParent(y);
}

/**
 * rotateRight
 * ----
 *  This is a helper method to rotate a subtree around the axis of y in the rightward direction.
 * The sub trees will not be affected except for the right child of y
 */
void RedBlackTree::rotateRight(RBNode *y)
{
    RBNode *x;

    // Set x to be the left child of y
    x = y->getLeft();

    // Set the left child of y to now be the right child of x
    y->setLeft(x->getRight());

    // if the right child of x is not nullptr
    if (x->getRight() != nullptr)
    {
        // Set the parent of the right child of x to be y
        x->getRight()->setParent(y);
    }

    // Set the parent of x to now be the same parent as y
    x->setParent(y->getParent());

    // Check if the parent of y is nullptr (Meaning y is the root node)
    if (y->getParent() == nullptr)
    {
        // Set x to be the new root
        this->_root = x;
    }
    else if (y == y->getParent()->getRight()) // Else check if y is on the right side of the tree
    {
        // If y is on the right side of the tree then set y's parent's right child to be x
        y->getParent()->setRight(x);
    }
    else
    {
        // Else y is on the left side of the tree and set y's parent's left child to be x
        y->getParent()->setLeft(x);
    }

    // Set x's right child to be y
    x->setRight(y);

    // Set y's parent to be x
    y->setParent(x);

}

/**
 * insertNode
 * -----
 *
 *
 */
void RedBlackTree::insertNode(RBNode *insertNode)
{
    RBNode *y;
    RBNode *x;

    y = nullptr;
    x = this->_root;

    while (x != nullptr)
    {
        y = x;
        if (insertNode->getKey() < x->getKey())
        {
            x = x->getLeft();
        }
        else
        {
            x = x->getRight();
        }
    }
    insertNode->setParent(y);

    if (y == nullptr)
    {
        this->_root = insertNode;
    }
    else if (insertNode->getKey() < y->getKey())
    {
        y->setLeft(insertNode);
    }
    else
    {
        y->setRight(insertNode);
    }

    insert_fixup(insertNode);
}

/**
 * insert_fixup
 * ------
 *
 *  This method will fix any situations within the red-black tree that break any of the 5 properties needed
 * to be held by the Red-Black Tree.
 *
 * @param RBNode
 * @return none
 */
void RedBlackTree::insert_fixup(RBNode *z)
{
    RBNode *y;

    if (z != this->_root)
    {

        while (z->getParent()->getNodeColor() == RED)
        {
            // Check to see if the violation is occurring on the left side of the tree
            if (z->getParent() == z->getParent()->getParent()->getLeft())
            {
                y = z->getParent()->getParent()->getRight();

                // Case 1: If the color of z's grandparent's right child is red
                if (y->getNodeColor() == RED)
                {
                    z->getParent()->setNodeColor(BLACK);
                    y->setNodeColor(BLACK);
                    z->getParent()->getParent()->setNodeColor(RED);
                    z = z->getParent()->getParent();
                }
                else
                {
                    // Case 2:
                    if (z == z->getParent()->getRight())
                    {
                        z = z->getParent();
                        rotateLeft(z);
                    }

                    // Case 3: Case 2 falls through into case 3 because these two cases are not mutually exclusive
                    z->getParent()->setNodeColor(BLACK);
                    z->getParent()->getParent()->setNodeColor(RED);
                    rotateRight(z->getParent()->getParent());
                }
            }
            else
            {
                // Checking the violation on the right side of the tree.
                y = z->getParent()->getParent()->getLeft();

                // Case 1: If the color of z's grandparent's right child is red
                if (y->getNodeColor() == RED)
                {
                    z->getParent()->setNodeColor(BLACK);
                    y->setNodeColor(BLACK);
                    z->getParent()->getParent()->setNodeColor(RED);
                    z = z->getParent()->getParent();
                }
                else
                {
                    // Case 2:
                    if (z == z->getParent()->getLeft())
                    {
                        z = z->getParent();
                        // DEBUG: IF there are issues where to tree is not behaving the way it should then I may need to switch
                        //      the rotateRight and rotateLeft methods
                        rotateRight(z);
                    }

                    // Case 3: Case 2 falls through into case 3 because these two cases are not mutually exclusive
                    z->getParent()->setNodeColor(BLACK);
                    z->getParent()->getParent()->setNodeColor(RED);
                    // DEBUG: May need to switch this to rotateRight
                    rotateLeft(z->getParent()->getParent());
                }
            }
        }
    }

    // Set the root of the tree to be black
    this->_root->setNodeColor(BLACK);
}

/**
 * transplant
 * -----
 *
 * @param1 RBNode
 * @param2 RBNode
 * @return none
 */

void RedBlackTree::transplant(RBNode *u, RBNode *v)
{
    if (u->getParent() == nullptr)
    {
        this->_root = v;
    }
    else if (u == u->getParent()->getLeft())
    {
        u->getParent()->setLeft(v);
    }
    else
    {
        u->getParent()->setRight(v);
    }

    v->setParent(u->getParent());
}

/**
 * deleteNode
 * -----
 *
 * @param1 RBNode
 * @return none
 */
void RedBlackTree::deleteNode(RBNode *deleteNode)
{
    RBNode *y;
    RBNode *x;

    color y_original_color;

    y = deleteNode;

    y_original_color = y->getNodeColor();

    if (deleteNode->getLeft() == nullptr)
    {
        x = deleteNode->getRight();
        transplant(deleteNode, deleteNode->getRight());
    }
    else if (deleteNode->getRight() == nullptr)
    {
        x = deleteNode->getLeft();
        transplant(deleteNode, deleteNode->getLeft());
    }
    else
    {
        y                = minimum(deleteNode->getRight());
        y_original_color = y->getNodeColor();

        x = y->getRight();

        if (y->getParent() == deleteNode)
        {
            x->setParent(y);
        }
        else
        {
            transplant(y, y->getRight());
            y->setRight(deleteNode->getRight());
            y->getRight()->setParent(y);
        }

        transplant(deleteNode, y);
        y->setLeft(deleteNode->getLeft());
        y->getLeft()->setParent(y);
        y->setNodeColor(deleteNode->getNodeColor());
    }

    if (y_original_color == BLACK)
    {
        delete_fixup(x);
    }

}

void RedBlackTree::delete_fixup(RBNode *x)
{
    RBNode *w;

    while (x != this->_root && x->getNodeColor() == BLACK)
    {
        if (x == x->getParent()->getLeft())
        {

            w = x->getParent()->getRight();

            // Case 1:
            if (w->getNodeColor() == RED)
            {
                w->setNodeColor(BLACK);
                x->getParent()->setNodeColor(RED);
                rotateLeft(x->getParent());
                w = x->getParent()->getRight();
            }

            // Case 2:
            if (w->getLeft()->getNodeColor() == BLACK && w->getRight()->getNodeColor() == BLACK)
            {
                w->setNodeColor(RED);

                // Move X up one level
                x = x->getParent();
            }
            else
            {
                if (w->getRight()->getNodeColor() == BLACK)
                {
                    w->getLeft()->setNodeColor(BLACK);
                    w->setNodeColor(RED);
                    rotateRight(w);
                    w = x->getParent()->getRight();
                }
                w->setNodeColor(x->getParent()->getNodeColor());
                x->getParent()->setNodeColor(BLACK);
                w->getRight()->setNodeColor(BLACK);
                rotateLeft(x->getParent());
                x = this->_root;
            }
        }
        else
        {

            w = x->getParent()->getLeft();

            // Case 1:
            if (w->getNodeColor() == RED)
            {
                w->setNodeColor(BLACK);
                x->getParent()->setNodeColor(RED);
                rotateRight(x->getParent());
                w = x->getParent()->getLeft();
            }

            // Case 2:
            if (w->getRight()->getNodeColor() == BLACK && w->getLeft()->getNodeColor() == BLACK)
            {
                w->setNodeColor(RED);

                // Move X up one level
                x = x->getParent();
            }
            else
            {
                if (w->getLeft()->getNodeColor() == BLACK)
                {
                    w->getRight()->setNodeColor(BLACK);
                    w->setNodeColor(RED);
                    rotateLeft(w);
                    w = x->getParent()->getLeft();
                }
                w->setNodeColor(x->getParent()->getNodeColor());
                x->getParent()->setNodeColor(BLACK);
                w->getLeft()->setNodeColor(BLACK);
                rotateRight(x->getParent());
                x = this->_root;
            }
        }
    }
    x->setNodeColor(BLACK);
}

/**
 * Minimum
 * -----
 *
 *  This method will find the node with the minimum key value by searching the farthest left of the tree.
 * Since the tree is following the binary-search tree property, the node with the minimum key value will
 * always be guaranteed to be the most left of the tree.
 *
 * @param RBNode
 * @return RBNode
 */
RBNode *RedBlackTree::minimum(RBNode *x)
{
    if (x->getLeft() != nullptr)
    {
        minimum(x->getLeft());
    }
    return x;
}

/**
 * Maximum
 * -----
 *
 *  This method will find the node with the minimum key value by searching the farthest left of the tree.
 * Since the tree is following the binary-search tree property, the node with the minimum key value will
 * always be guaranteed to be the most left of the tree.
 *
 * @param RBNode
 * @return RBNode
 */
RBNode *RedBlackTree::maximum(RBNode *x)
{
    if (x->getRight() != nullptr)
    {
        maximum(x->getRight());
    }
    return x;
}

RBNode *RedBlackTree::findNode(RBNode *x, int key)
{
    RBNode *searchPtr;
    searchPtr = x;
    while (searchPtr != nullptr && key != searchPtr->getKey())
    {
        if (key < searchPtr->getKey())
        {
            searchPtr = searchPtr->getLeft();
        }
        else
        {
            searchPtr = searchPtr->getRight();
        }
    }

    return searchPtr;
}

void RedBlackTree::insert(int key, std::string value)
{
    RBNode *newNode;
    newNode = new RBNode();

    if (newNode != nullptr)
    {
        newNode->setKey(key);
        newNode->setValue(value);
        this->insertNode(newNode);
        this->size++;
    }
}

void RedBlackTree::remove(int key)
{
    RBNode *nodeToRemove;
    nodeToRemove = findNode(this->_root, key);
    if (nodeToRemove != nullptr)
    {
        this->deleteNode(nodeToRemove);
        this->size--;
    }
    else
    {
        std::cout << "Node not found!\n";
    }
}

bool RedBlackTree::findKey(int key)
{
    return findNode(this->_root, key) != nullptr;
}

std::string RedBlackTree::getValue(int key)
{
    RBNode *returnNode;

    returnNode = findNode(this->_root, key);

    if (returnNode != nullptr)
    {
        return returnNode->getValue();
    }
    return "Key not found and thus no value exists.\n";
}

bool RedBlackTree::isEmpty() const
{ return this->_root == nullptr; }

// Print the branches and node (eg, ___10___ )
void RedBlackTree::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel,
                              const std::deque<RBNode *> &nodesQueue, std::ostream &out)
{
    typename std::deque<RBNode *>::const_iterator iter = nodesQueue.begin();

    for (int i = 0; i < nodesInThisLevel; i++, iter++)
    {
        out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << ""
        << ((*iter && (*iter)->getLeft()) ? std::setfill('_') : std::setfill(' '));

        out << std::setw(branchLen + 2) << ((*iter) ? intToString((*iter)->getKey()) : "");
        out << ((*iter && (*iter)->getRight()) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << ""
        << std::setfill(' ');
    }
    out << std::endl;
}

// Print the leaves only (just for the bottom row)
void RedBlackTree::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<RBNode *> &nodesQueue,
                               std::ostream &out)
{
    typename std::deque<RBNode *>::const_iterator iter = nodesQueue.begin();
    for (int                                      i    = 0; i < nodesInThisLevel; i++, iter++)
    {
        out << ((i == 0) ? std::setw(indentSpace + 2) : std::setw(2 * level + 2))
        << ((*iter) ? intToString((*iter)->getKey()) : "");
    }
    out << std::endl;
}

/**
 * Pretty formatting of a binary tree to the output stream
 * @ param level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
* indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
 */
void RedBlackTree::printPretty(RBNode *root, int level, int indentSpace, std::ostream &out)
{
    int h                = maxHeight(root);
    int nodesInThisLevel = 1;

    int branchLen    = 2 * ((int) pow(2.0, h) - 1)
                       - (3 - level) * (int) pow(2.0, h - 1);  // eq of the length of branch for each node of each level
    int nodeSpaceLen = 2 + (level + 1) * (int) pow(2.0,
                                                   h);  // distance between left neighbor node's right arm and right neighbor node's left arm
    int startLen     = branchLen + (3 - level)
                       + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

    typename std::deque<RBNode *> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++)
    {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
        branchLen    = branchLen / 2 - 1;
        nodeSpaceLen = nodeSpaceLen / 2 + 1;
        startLen     = branchLen + (3 - level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

        for (int i = 0; i < nodesInThisLevel; i++)
        {
            RBNode *currNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currNode)
            {
                nodesQueue.push_back(currNode->getLeft());
                nodesQueue.push_back(currNode->getRight());
            }
            else
            {
                nodesQueue.push_back(nullptr);
                nodesQueue.push_back(nullptr);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

void RedBlackTree::printTree()
{
    printPretty(_root, 2, 0, std::cout);
}

int RedBlackTree::getSize() const
{ return this->size; }

// Convert an integer value to string
std::string RedBlackTree::intToString(int val)
{
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
void RedBlackTree::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel,
                                 const std::deque<RBNode *> &nodesQueue, std::ostream &out)
{

    typename std::deque<RBNode *>::const_iterator iter = nodesQueue.begin();

    for (int i = 0; i < nodesInThisLevel / 2; i++)
    {
        out << ((i == 0) ? std::setw(startLen - 1) : std::setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
        out << std::setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << std::endl;
}

// Find the maximum height of the binary tree
int RedBlackTree::maxHeight(RBNode *p)
{
    if (!p)
    { return 0; }
    int leftHeight  = maxHeight(p->getLeft());
    int rightHeight = maxHeight(p->getRight());
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}
