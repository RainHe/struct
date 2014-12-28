#ifndef RB_TREE_H
#define RB_TREE_H
#include <iostream>
using namespace std;
template<class Key> class RBTree {
public:
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
    Node *insert_search_node(Key *key);
    Node *remove_search_node(Node *node, Key *key);
    void insert(Key *key);
    void insert_fixup(Node *node);
    int remove(Key *key);
    void remove_fixup(Node *node);
    void getAll(Node *node);
    
    ~RBTree();
};

template<class Key> RBTree<Key>::Node::Node() {
    parent = NULL;
    left = NULL;
    right = NULL;
    key = NULL;
    color = RED;
    
}

template<class Key> RBTree<Key>::Node::~Node() {
    if (key != NULL) {
        delete key;
    }
}
template<class Key> typename RBTree<Key>::Node * RBTree<Key>::Node::getBrother() {
    if (this == parent->right) {
        return parent->left;
    } else {
        return parent->right;
    }
    
}

template<class Key> typename RBTree<Key>::Node * RBTree<Key>::Node::getUcle() {
    //如果parent是根节点或者是nil节点
    if (parent == NULL || parent->parent == NULL) {
        return NULL;
    }
    Node *gradParent = parent->parent;
    if (parent == gradParent->left) {
        return gradParent->right;
    } else {
        return gradParent->left;
    }
}

template<class Key> RBTree<Key>::RBTree() {
    nil = new Node();
    nil->parent = NULL;
    nil->left = NULL;
    nil->right = NULL;
    nil->color = BLACK;
    head = NULL;
}

template<class Key> RBTree<Key>::~RBTree() {
    if (head != NULL) {
        delete head;
    }
}

template<class Key> void RBTree<Key>::rotate_left(Node *node) {
    if (node != head && node != nil) {
        Node *p = node->parent;
        Node *gp = p->parent;
        p->right = node->left;
        node->left = p;
        p->parent = node;
        if (p == head) {
            node->parent = nil;
            head = node;
        } else if (p == gp->right) {
            node->parent = gp;
            gp->right = node;
        } else {
            node->parent = gp;
            gp->left = node;
        }
    }
    
}

template<class Key> void RBTree<Key>::rotate_right(Node *node) {
    if (node != head && node != nil) {
        Node *p = node->parent;
        Node *gp = p->parent;
        p->left = node->right;
        node->right = p;
        p->parent = node;
        if (p == head) {
            node->parent = nil;
            head = node;
        } else if (p == gp->right) {
            node->parent = gp;
            gp->right = node;
        } else {
            node->parent = gp;
            gp->left = node;
        }
    }
    
}

template<class Key> typename RBTree<Key>::Node *RBTree<Key>::successor(Node *key) {
    if (key->right != NULL) {
        Node *start = key->right;
        while(start->left != nil) {
            start = start->left;
        }
        return start;
    } else {
        Node *parent = key->parent;
        Node *cur = key;
        while(cur != nil && cur == parent->right) {
            cur = parent;
            parent = parent->parent;
        }
        return parent;
    }
}
template<class Key> typename RBTree<Key>::Node *RBTree<Key>::search_node(Key *key) {
    if (key != NULL) {
        if (head == NULL) {
            return nil;
        }
        Node *node = head;
        while(node != nil) {
            if (node->key != NULL) {
                Key *compared_key = node->key;
                if (*compared_key > *key) {
                    if (node->left->key != NULL) {
                        node = node->left;
                    } else {
                        break;
                    }
                } else if (*compared_key < *key) {
                    if (node->right->key != NULL) {
                        node = node->right;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;  
            }
        }
        return node;
    }
    return NULL;
}
template<class Key> typename RBTree<Key>::Node *RBTree<Key>::insert_search_node(Key *key) {
    if (key != NULL) {
        if (head == NULL) {
            return nil;
        }
        Node *node = head;
        while(node != nil) {
            if (node->key != NULL) {
                Key *compared_key = node->key;
                if (*compared_key > *key) {
                    if (node->left->key != NULL) {
                        node = node->left;
                    } else {
                        break;
                    }
                } else if (*compared_key < *key) {
                    if (node->right->key != NULL) {
                        node = node->right;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;  
            }
        }
        return node;
    }
    return NULL;
}

template<class Key> typename RBTree<Key>::Node *RBTree<Key>::remove_search_node(Node *start, Key *key) {
    Node *tmp = nil;
    if (start == NULL && start == nil) {
        return nil;
    }
    if (start->key == NULL || key == NULL) {
        return nil;
    }
    if (*start->key == *key) {
        tmp = start;
    } else if (*start->key > *key) {
        tmp = remove_search_node(start->left, key);
    } else {
        tmp = remove_search_node(start->right, key);
    }
    return tmp;
    
}

template<class Key> void RBTree<Key>::insert(Key *key) {
    if (key != NULL) {
        Node *node = new Node();
        node->right = nil;
        node->left = nil;
        node->key = key;
        Node *search_node = this->insert_search_node(key);
        if (search_node == nil) {
            node->color = BLACK;
            node->parent = nil;
            head = node;
        } else {
            if(*search_node->key != *key) {
                node->color = RED;
                if (*search_node->key > *key) {
                    search_node->left = node;
                } else {
                    search_node->right = node;
                }
                node->parent = search_node;
            }
        }
        if (search_node->color == RED) {
            insert_fixup(node);
        }
    }
}

template<class Key> void RBTree<Key>::insert_fixup(Node *node) {
    while(node != nil && node != head && node->parent->color == RED) {
        Node *ucle = node->getUcle();
        if (ucle != NULL && ucle->color == RED) {
            ucle->color = BLACK;
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
            if (node->parent = head) {
                break;
            }
            continue;
        }
        if (node->parent == node->parent->parent->right) {
            if (node == node->parent->left) {
                rotate_right(node);
            } else {
                node->parent->color = node->parent->parent->color;
                node->parent->parent->color = RED;
                rotate_left(node->parent);
                break;
            }
        } else {
            if (node == node->parent->right) {
                rotate_left(node);
            } else {
                node->parent->color = node->parent->parent->color;
                node->parent->parent->color = RED;
                rotate_right(node->parent);
                break;
            }
            
        }
    }
    if (node == head) {
        node->color = BLACK;
    }
    
}

template<class Key> void RBTree<Key>::transplant(Node *des, Node *src) {
    if (src == nil) {
        head == NULL;
    } else {
        des->key = src->key;
    }
}

template<class Key> int RBTree<Key>::remove(Key *key) {
    if (key != NULL) {
        Node *element = remove_search_node(head,key);
        if (element == nil) {
            return -1;
        }
        if (element == head && element->left == nil && element->right == nil) {
            head = nil;
            return 0;
        }
        Node *deleted = nil;
        if (element->left == nil && element->right != nil) {
            deleted = element->right;
        } else if (element->left != nil && element->right == nil) {
            deleted = element->left;
        } else if (element->left == nil && element->right ==nil) {
            deleted = element;
        } else {
            deleted = successor(element);
            cout << "successor key is : " << *deleted->key << endl;
        }
        Node *child = nil;
        if (deleted->right != nil) {
            child = deleted->right;
            Node *deleted_parent = deleted->parent;
            if (deleted == deleted_parent->right) {
                deleted_parent->right = child;
            } else {
                deleted_parent->left = child;
            }
            child->parent = deleted_parent;
        } else {
            child = deleted;
        }
        element->key = child->key;
        if (deleted->color == BLACK) {
            remove_fixup(child);
        }
        if (child == deleted) {
            Node *child_parent = child->parent;
            if (child == child_parent->right) {
                child_parent->right = nil;
            } else {
                child_parent->left = nil;
            }
        }
        return 0;
    }
    return -1;
}

template<class Key> void RBTree<Key>::remove_fixup(Node *node) {
    while (node != head && node->color == BLACK) {
        Node *brother = node->getBrother();
        cout << "brother key is : " << *brother->key << endl;
        if (node == node->parent->left) {
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rotate_left(brother);
            } else {
                if (brother->left->color == BLACK && brother->right->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                } else if (brother->right->color == BLACK) {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rotate_right(brother->left);
                } else {
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->right->color = BLACK;
                    rotate_left(brother);
                    break;
                }
            }
        } else {
            if (brother->color == RED) {
                brother->color = BLACK;
                rotate_right(brother);
            } else {
                if (brother->left->color == BLACK && brother->right->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                } else if (brother->left->color == BLACK) {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    rotate_left(brother->right);
                } else {
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->left->color = BLACK;
                    rotate_right(brother);
                    break;
                }
            }
        }
    }
    node->color = BLACK;
}

template<class Key> void RBTree<Key>::getAll(Node *node) {
    if (node != nil) {
        getAll(node->left);
        std::cout << "key : " << *node->key << " color : " << node->color << std::endl;
        getAll(node->right);
    }
}






#endif