#include "redblacktree.h"

RedBlackTree::RedBlackTree()
{
    root = NULL;
}

RedBlackTree::~RedBlackTree()
{
    if(root)
        deleteTree(root);
}

void RedBlackTree::leftRotate(TreeNode *x)
{
    TreeNode *y = x->rightNode;
    TreeNode *p = x->parentNode;
    x->rightNode = y->leftNode;
    if(y->leftNode != NULL)
        y->leftNode->parentNode = x;
    y->parentNode = p;
    if(p != NULL)
        x==p->leftNode ? p->leftNode = y : p->rightNode = y;
    else
        root = y;
    y->leftNode = x;
    x->parentNode = y;
}

void RedBlackTree::rightRotate(TreeNode *x)
{
    TreeNode *y = x->leftNode;
    TreeNode *p = x->parentNode;
    x->leftNode = y->rightNode;
    if(y->rightNode != NULL)
            y->rightNode->parentNode = x;
    y->parentNode = p;
    if(p == NULL)
            root = y;
    else
        p->leftNode == x ? p->leftNode = y : p->rightNode = y;
    y->rightNode = x;
    x->parentNode = y;
}

void RedBlackTree::inorder(TreeNode *node)
{
    assert(node);
    if(node->leftNode)
        inorder(node->leftNode);
    cout<<node->key<<" ";
    if(node->rightNode)
        inorder(node->rightNode);
}

TreeNode *RedBlackTree::findNode(int key)
{
    TreeNode *x = root;
    while(x)
    {
        if(x->key == key)
            break;
        else if(key < x->key)
            x = x->leftNode;
        else
            x = x->rightNode;
    }
    return x;
}

TreeNode *RedBlackTree::getSmallestNode(TreeNode *node)
{
    if(node == NULL)
        return NULL;

    TreeNode *x = node;
    while(x->leftNode)
    {
        x = x->leftNode;
    }
    return x;
}

TreeNode *RedBlackTree::getLargestNode(TreeNode *node)
{
    if(node == NULL)
        return NULL;
    TreeNode *x = node;
    while(x->rightNode)
    {
        x = x->rightNode;
    }
    return x;
}

void RedBlackTree::insert(TreeNode *z)
{
    TreeNode *y = NULL;
    TreeNode *x = root;
    while(x)
    {
        y = x;
        if(z->key < x->key)
            x = x->leftNode;
        else
            x = x->rightNode;
    }
    z->parentNode = y;
    if(y == NULL)
        root = z;
    else if(z->key < y->key)
        y->leftNode = z;
    else
        y->rightNode = z;
}

void RedBlackTree::deleteTree(TreeNode *node)
{
    if(node->leftNode)
        deleteTree(node->leftNode);
    if(node->rightNode)
        deleteTree(node->rightNode);
    delete node;
}
