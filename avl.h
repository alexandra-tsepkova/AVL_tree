//
// Created by sasha on 19.11.2020.
//

#ifndef TREE_AVL_H
#define TREE_AVL_H

#include <algorithm>

class avl_node {
public:
    avl_node(avl_node *parent, int key) : parent(parent), key(key), balance(0), left(nullptr), right(nullptr) {}

    // Attach to the correct side and set correct parent
    avl_node* attach(avl_node* node) {
        if (!node) {
            throw std::exception();
        }

        if (node->key < key) {
            left = node;
        } else {
            right = node;
        }

        node->parent = this;
        return node;
    }

    avl_node* attach_left(avl_node* node) {
        left = node;
        if (node) {
            node->parent = this;
        }
        return node;
    }

    avl_node* attach_right(avl_node* node) {
        right = node;
        if (node) {
            node->parent = this;
        }
        return node;
    }

    avl_node* attach(int key) {
        return attach(new avl_node(this, key));
    }

    avl_node* forward(int key) {
        return key < this->key ? left : right;
    }

    int balance; //left - right subtrees depth
    int key;
    avl_node *left;
    avl_node *right;
    avl_node *parent;
};

class avl_tree {
public:
    avl_node *root = nullptr;

    avl_node *balance_left (avl_node *cur) {
        if((cur->right->balance == -1) || (cur->right->balance == 0)) {
            cur = small_left_rotation(cur);
            return cur;
        }
        else if(cur->right->balance == 1) {
            cur = big_left_rotation(cur);
            return cur;
        }
    }

    avl_node *balance_right (avl_node *cur) {
        if((cur->left->balance == 1) || (cur->left->balance == 0)) {
            cur = small_right_rotation(cur);
            return cur;
        }
        else if(cur->left->balance == -1) {
            cur = big_right_rotation(cur);
            return cur;
        }
    }

    avl_node *balance (avl_node *cur) {
        if (cur->balance == -2) {
            return balance_left(cur);
        }
        if (cur->balance == 2) {
            return balance_right(cur);
        }
    }

    void insert(int key){
        if (root == nullptr) {
            root = new avl_node(nullptr, key);
        }

        else {
            avl_node *cur = root;

            int i = 0;

            while (cur->forward(key)) {
                i++;
                if (i > 10000) {
                    int fhlahg = 0;
                    fhlahg++;
                }
                cur = cur->forward(key);
            }

            cur = cur->attach(key);

            while(cur->parent) {
                i++;
                if (i > 10000) {
                    int fhlahg = 0;
                    fhlahg++;
                }
                if (cur == cur->parent->left) {
                    cur = cur->parent;
                    cur->balance++;
                }
                else if (cur == cur->parent->right) {
                    cur = cur->parent;
                    cur->balance--;
                }
                else {
                    throw std::exception();
                }

                if (cur->balance == 2 || cur->balance == -2) {
                    avl_node* parent = cur->parent;
                    cur = balance(cur);
                    if (parent) {
                        parent->attach(cur);
                    }
                    else {
                        root = cur;
                        cur->parent = nullptr;
                    };
                }
                if (cur->balance == 0){
                    break;
                }
            }
        }
    }

    avl_node *rough_search(avl_node *node, int key) const{
        if (node->key == key) {
            return node;
        }
        if (key < node->key) {
            return node->left ? rough_search(node->left, key) : node;
        }
        else {
            return node->right ? rough_search(node->right, key) : node;
        }

    }

    avl_node *next (avl_node *cur) const{
        avl_node *tmp;
        if (cur->right) {
            cur = cur->right;
            tmp = cur->right;
            while (cur) {
                tmp = cur;
                cur = cur->left;
            }
            return tmp;
        }
        else {
            tmp = cur->parent;
            while ((tmp) && (tmp->key < cur->key)) {
                tmp = tmp -> parent;
                cur = cur -> parent;
            }
            if ((tmp) && (tmp->key > cur->key)) return tmp;
            else return nullptr;
        }
    }

    unsigned int range_query(int start, int end) {
        int count = 0;
        avl_node *first = rough_search(root, start);
        if(first->key < start) first = next(first);
        while ((first) && (first->key <= end)) {
            first = next(first);
            count++;
        }
        return count;
    }

    void remove(int key) = delete;

private:
    avl_node* small_left_rotation(avl_node *a) {
        avl_node *b = a->right;
//        avl_node *c = a->parent;
        a->attach_right(b->left);
        b->attach_left(a);
        b->parent = nullptr;

        int diff_A = a->balance, diff_B = b->balance;
        int C = -1 + (diff_A < 0 ? diff_A : 0);
        int B = -1 - (diff_A > 0 ? diff_A : 0);
        int D = B - 1 + (diff_B < 0 ? diff_B : 0);
        int E = B - 1 - (diff_B > 0 ? diff_B : 0);

        a->balance = C - D;
        b->balance = std::max(C, D) + 1 - E;

//        if(b->balance == -1) {
//            b->balance = 0;
//            a->balance = 0;
//        }
//        else if(b->balance == 0) {
//            b->balance = 1;
//            a->balance = -1;
//        }

        if ((a->left == a->right && a->balance != 0)) {
            int fuck = 1;
        }

//        b->parent = c;/
//        a->parent = b;

        return b;
    }

    avl_node* small_right_rotation (avl_node *a) {
        avl_node *b = a->left;
//        avl_node *c = a->parent;

        a->attach_left(b->right);
        b->attach_right(a);

        int diff_A = a->balance, diff_B = b->balance;
        int C = -1 - (diff_A > 0 ? diff_A : 0);
        int B = -1 + (diff_A < 0 ? diff_A : 0);
        int D = B - 1 + (diff_B < 0 ? diff_B : 0);
        int E = B - 1 - (diff_B > 0 ? diff_B : 0);

        a->balance = E - C;
        b->balance = D - (std::max(E, C) + 1);

//        if(b->balance == 1) {
//            b->balance = 0;
//            a->balance = 0;
//        }
//        else if(b->balance == 0) {
//            b->balance = 1;
//            a->balance = -1;
//        }

        if ((a->left == a->right && a->balance != 0)) {
            int me_daddy = 1;
        }


//        b->parent = c;
//        a->parent = b;

//        a->depth = std::max(a->left->depth, a->right->depth) + 1;
//        b->depth = std::max(b->left->depth, b->right->depth) + 1;
        return b;
    }

    avl_node* big_left_rotation(avl_node *a) {
        a->attach(small_right_rotation(a->right));
        return small_left_rotation(a);
    }

    avl_node* big_right_rotation(avl_node *a) {
        a->attach(small_left_rotation(a->left));
        return small_right_rotation(a);
    }

};



#endif //TREE2_AVL_H
