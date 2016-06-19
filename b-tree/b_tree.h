#ifndef btree_H
#define btree_H

template <typename T>
class btree;

template <typename T>
class btree_node{
public:

    btree_node(int t):n(0),leaf(true){
        key = new T[2*t-1];
        c   = new btree_node *[2*t];
    }
    ~btree_node()
    {
        delete key;
        delete c;
    }

private:
    friend class btree<T>;
    //    int t;
    int     n;
    bool    leaf;
    T       *key;
    btree_node **c;
};

template <typename T>
struct bvalue{
    bvalue(btree_node<T>*n,int i):node(n),index(i){}

    btree_node<T> *node;
    int index;
};

template <typename T>
class btree
{
public:
    btree(int d=2):degree(d){ root = new btree_node<T>(d); }

    struct bvalue<T> btree_search(btree_node<T>*node,T key);

private:
    int degree;
    btree_node<T> *root;
};

template <typename T>
bvalue<T> btree<T>::btree_search(btree_node<T> *node, T key)
{
    int i=0;
    while(i < node->n && key > node->key[i])
        i++;
    if(i < node->n && key == node->key[i])
        return bvalue<T>(node,i);
    else if(node->leaf)
        return bvalue<T>(0,-1);
    else
        return btree_search(node->c[i],key);
}

#endif // btree_H
