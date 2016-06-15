#ifndef RBTREE_HPP
#define RBTREE_HPP

#ifndef RB_COLOR_BLACK
#define RB_COLOR_BLACK 1
#endif

#ifndef RB_COLOR_RED
#define RB_COLOR_RED 0
#endif

template <typename T>
class rbtree/*<T>*/;

template <typename T>
class rbTreeNode
{
public:
    friend class rbtree<T>;
    T getKey(){
        return key;
    }
private:
    rbTreeNode *left;
    rbTreeNode *right;
    rbTreeNode *parent;
    T key;
    int color;
};

template <typename T>
class rbtree
{
public:
    rbtree():nil(new rbTreeNode<T>()),root(nil){
        nil->color = RB_COLOR_BLACK;
        nil->left = NULL;
        nil->right = NULL;
        nil->parent = NULL;
    }
    void insert(T k);
    rbTreeNode<T> *search(T k);
    void erase(T k);
private:
    void leftRotate(rbTreeNode<T>*x);
    void rightRotate(rbTreeNode<T>*x);
    void rbDelete(rbTreeNode<T>*x);
    void rbDeleteFixup(rbTreeNode<T>*x);
    void rbInsertFixup(rbTreeNode<T>*x);
    rbTreeNode<T> *rbSuccessor(rbTreeNode<T>*x);
private:
    rbTreeNode<T>*nil;
    rbTreeNode<T>*root;

};

#endif // RBTREE_HPP


template <typename T>
void rbtree<T>::insert(T k)
{
    rbTreeNode<T> *x = root;
    rbTreeNode<T> *y = x;
    rbTreeNode<T> *z = new rbTreeNode<T>();
    z->color = RB_COLOR_RED;
    z->left = nil;
    z->right = nil;
    z->key = k;

    while(x != nil)
    {
        y = x;
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent  = y;
    if(y == nil)
    {
        root = z;
        return;
    }
    else
    {
        if(k < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
    }
    rbInsertFixup(z);
}

template <typename T>
rbTreeNode<T> *rbtree<T>::search(T k)
{
    rbTreeNode<T> *x = root;
    while(x != nil)
    {
        if(x->key == k)
            break;
        else if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

template <typename T>
void rbtree<T>::erase(T k)
{
    rbTreeNode<T> *x = search(k);
    if(x != nil)
    {
        rbDelete(x);
    }
}

template <typename T>
void rbtree<T>::leftRotate(rbTreeNode<T> *x)
{
    rbTreeNode<T> *y = x->left;
    rbTreeNode<T> *p = x->parent;
    rbTreeNode<T> *yl = y->left;
    x->right = yl;
    if(yl != nil)
        yl->parent = x;
    y->parent = p;
    if(p != nil)
    {
        p->left == x ? p->left = y : p->right = y;
    }
    else
    {
        root = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename T>
void rbtree<T>::rightRotate(rbTreeNode<T> *x)
{
    rbTreeNode<T> *y = x->left;
    rbTreeNode<T> *p = x->parent;
    rbTreeNode<T> *yr = y->right;
    x->left = yr;
    if(yr != nil)
        yr->parent = x;
    y->parent = p;
    if(p != nil)
    {
        p->left == x ? p->left = y : p->right = y;
    }
    else
    {
        root = y;
    }
    y->right = x;
    x->parent = y;

}

template <typename T>
void rbtree<T>::rbDelete(rbTreeNode<T> *z)
{
    rbTreeNode<T> *x,*y;
    if(z->left == nil || z->right == nil)
        y = z;
    else
        y = rbSuccessor(z);

    if(y != z)
        z->key = y->key;

    if(y->left != nil)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if(y->parent != nil)
        y->parent->left == y ? y->parent->left = x : y->parent->right = x;
    else
        root = x;

    if(y->color == RB_COLOR_BLACK)
        rbDeleteFixup(x);
    delete y;
}

template <typename T>
void rbtree<T>::rbDeleteFixup(rbTreeNode<T> *x)
{
    rbTreeNode<T> *p,*sibling = nil,*gp = nil;
    p = x->parent;
    if(p != nil)
    {
        gp = p->parent;
        x == p->left ? sibling = p->right : sibling = p->left;
    }

    while(x->color == RB_COLOR_BLACK)
    {

    }
    x->color = RB_COLOR_BLACK;

}

template <typename T>
void rbtree<T>::rbInsertFixup(rbTreeNode<T> *x)
{
    rbTreeNode<T> *u;
    rbTreeNode<T> *p;
    rbTreeNode<T> *gp;
    while(/*x != root && */x->parent->color == RB_COLOR_RED)    //if parent's color is red,there is a grandparent exist(not nil)
    {
        p = x->parent;
        gp = p->parent;
        p == gp->left ? u = gp->right : u = gp->left;
        if(u->color == RB_COLOR_RED)    //u->color is red
        {
            p->color = RB_COLOR_BLACK;
            u->color = RB_COLOR_BLACK;
            gp->color = RB_COLOR_RED;
            x = gp;
            continue;
        }                               //u->color is black
        else
        {
            if(p == gp->left)
            {
                if(x == p->right)
                    leftRotate(p);

                rightRotate(x);
                x->color = RB_COLOR_BLACK;
                x->right->color = RB_COLOR_RED;
            }
            else
            {
                if(x == p->left)
                    rightRotate(x);

                leftRotate(x);
                x->color = RB_COLOR_BLACK;
                x->left->color = RB_COLOR_RED;
            }
            return;     //
        }
    }
    x->color = RB_COLOR_BLACK;
}

template <typename T>
rbTreeNode<T> *rbtree<T>::rbSuccessor(rbTreeNode<T> *x)
{
    rbTreeNode<T>*y;
    if(x->right != nil)
    {
        x = x->right;
        while(x->left != nil)
        {
            x = x->left;
        }
        return x;
    }

    y = x->parent;
    while(y != nil && y->right == x)
    {
        x = y;
        y = x->parent;
    }
    return y;
}

