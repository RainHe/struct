#ifndef RB_TREE_H
#define RB_TREE_H
template<class Key> class RBTree {
    enum Color {
        RED,BLACK
    };
    struct Node {
        Node();
        Node *parent;
        Node *left;
        Node *right;
        Key *key;
        Color color;
        Node *getUcle();
        Node *getBrother();
        ~Node();
    };
public:
    Node *nil;
    Node *head;
    RBTree();
    void rotate_left(Node *node);
    void rotate_right(Node *node);
    void transplant(Node *des, Node*src);
    Node *successor(Node *node);
    Node *search_node(Key *key);
    void insert(Key *key);
    void insert_fixup(Node *node);
    void remove(Key *key);
    void remove_fixup(Node *node);
    ~RBTree();
};
#endif