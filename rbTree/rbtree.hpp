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
    rbTreeNode<T> *w = nil;

    while(x != root && x->color == RB_COLOR_BLACK)
    {
        if(x->parent->left == x)        //left
        {
            w = x->parent->right;
            if(w->color == RB_COLOR_RED) //x->parent->right->color == RB_COLOR_RED
            {
                leftRotate(x->parent);  //then x->parent->right->color == RB_COLOR_BLACK
                x->parent->color = RB_COLOR_RED;
                x->parent->parent->color = RB_COLOR_BLACK;
                w = x->parent->right;
            }

//          w->color == RB_COLOR_BLACK
            if(w->right->color == RB_COLOR_BLACK)    //at this point, x->parent->color must equal red
            {
                if(w->left->color == RB_COLOR_BLACK)
                {
                    x = x->parent;
                    w->color = RB_COLOR_RED;
                    continue;
                }
                //w->left->color == RB_COLOR_RED
                w->left->color = RB_COLOR_BLACK;
                w->color = RB_COLOR_RED;
                rightRotate(w);
                w = x->parent->right;
            }
//            w->right->color == RB_COLOR_RED
            w->color = RB_COLOR_RED;
            w->right->color = RB_COLOR_BLACK;
            x->parent->color = RB_COLOR_BLACK;
            leftRotate(x->parent);
            x = root;

        }
        else        //right
        {
            w = x->parent->left;
            if(w->color == RB_COLOR_RED)
            {
                w->color = RB_COLOR_BLACK;
                w->parent->color = RB_COLOR_RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->left->color == RB_COLOR_BLACK)
            {
                if(w->right->color == RB_COLOR_BLACK)
                {
                    w->color = RB_COLOR_RED;
                    x = x->parent;
                    continue;
                }
//                w->right->color == RB_COLOR_RED
                w->right->color = RB_COLOR_BLACK;
                w->color = RB_COLOR_RED;
                leftRotate(w);
                w = x->parent->left;
            }
//            w->left->color == RB_COLOR_RED
            w->left->color = RB_COLOR_BLACK;
            w->color = RB_COLOR_RED;
            w->parent->color = RB_COLOR_BLACK;
            x = root;
        }
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
//            continue;
        }                               //u->color is black
        else
        {
            if(p == gp->left)
            {
                if(x == p->right)
                {
                    leftRotate(p);
                    x = p->left;
                    p = x->parent;
                }
                rightRotate(gp);
                gp->color = RB_COLOR_BLACK;
                gp->right->color = RB_COLOR_RED;
            }
            else
            {
                if(x == p->left)
                {
                    rightRotate(p);
                    x = x->right;
                    p = x->parent;
                }

                leftRotate(gp);
                gp->color = RB_COLOR_BLACK;
                gp->left->color = RB_COLOR_RED;
            }
//            return;     //
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

