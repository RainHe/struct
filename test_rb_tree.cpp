#include "RBTree.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    RBTree<int> rbtree;
    int *a = new int;
    int *b = new int;
    int *c = new int;
    int *d = new int;
    int *e = new int;
    int *f = new int;
    int *g = new int;
    *a = 10;
    *b = 11;
    *c = 12;
    *d = 13;
    *e = 14;
    *f = 15;
    *g = 16;
    rbtree.insert(a);
    rbtree.insert(b);
    rbtree.insert(c);
    rbtree.insert(d);
    rbtree.insert(e);
    rbtree.insert(f);
    rbtree.insert(g);
    rbtree.getAll(rbtree.head);
    return 0;
}



