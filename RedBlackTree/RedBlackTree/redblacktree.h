#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#ifndef COLOR_BLACK
#define COLOR_BLACK 1
#endif

#ifndef COLOR_RED
#define COLOR_RED   0
#endif


class TreeNode
{
public:
    TreeNode():leftNode(NULL),rightNode(NULL),parentNode(NULL),key(-1),color(COLOR_RED){}

    TreeNode *grandParent(){
        return parentNode == NULL ? NULL : parentNode->parentNode;
    }
    TreeNode *uncle(){
        TreeNode *gp = grandParent();
        if(gp == NULL)
        {
            return NULL;
        }
        if(gp->leftNode == parentNode)
        {
            return gp->rightNode;
        }
        else
        {
            return gp->leftNode;
        }
    }
    TreeNode *sibling(){
        if(parentNode == NULL)
            return NULL;
        if(this == parentNode->leftNode)
            return parentNode->rightNode;
        else
            return parentNode->leftNode;
    }


    int color;
    int key;
    TreeNode *leftNode,*rightNode,*parentNode;
};

class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();
    void leftRotate(TreeNode *x);
    void rightRotate(TreeNode *x);
    void inorder(TreeNode *node);
    void insert(TreeNode *z);
    void insertFixup(TreeNode *z);
    void transplant(TreeNode *u,TreeNode *v);
    void deleteNode(TreeNode *z);
    void deleteFixup(TreeNode *x);
    void deleteTree(TreeNode *node);
    TreeNode *findNode(int key);
    TreeNode *getSmallestNode(TreeNode *node);
    TreeNode *getLargestNode(TreeNode *node);
    string color(TreeNode *node){ return node->color ? "BLACK" : "RED"; }

    TreeNode *getRoot(){return root;}
private:
    TreeNode *root;
};



#endif // REDBLACKTREE_H
