#include <iostream>
#include "redblacktree.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    RedBlackTree rb;
    int key ;
    while(cin>>key)
    {
        TreeNode * z = new TreeNode();
        z->key = key;
        rb.insert(z);
    }

    TreeNode *x = rb.findNode(5);
    x != NULL ? cout<<"find node : 5 "<<endl : cout<<"can't find node : 5"<<endl;
    rb.inorder(rb.getRoot());

    return 0;
}

