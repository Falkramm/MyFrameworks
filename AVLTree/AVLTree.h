//
// Created by user on 20/11/2022.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>

class AVLTree {
private:
    struct Node {
        int key;
        int height;
        Node *left;
        Node *right;

        Node(int key = 0) {
            this->key = key;
            this->left = this->right = nullptr;
            height = 1;
        }

        ~Node() {
            left = nullptr;
            right = nullptr;
        }
    };

    static int height(Node *node) {
        return node ? node->height : 0;
    }

    static int balanceFactor(Node *node) {
        return height(node->right) - height(node->left);
    }

    static void fixHeight(Node *node) {
        node->height = (height(node->left) > height(node->right) ? height(node->left) : height(node->right)) + 1;
    }

    static Node *leftRotation(Node *node) {
        Node *node1 = node->right;
        node->right = node1->left;
        node1->left = node;
        fixHeight(node);
        fixHeight(node1);
        return node1;
    }

    static Node *rightRotation(Node *node) {
        Node *node1 = node->left;
        node->left = node1->right;
        node1->right = node;
        fixHeight(node);
        fixHeight(node1);
        return node1;
    }

    static Node *balance(Node *node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0)
                node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0)
                node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        return node;
    }

    static Node *findMin(Node *node) {
        return node->left ? findMin(node->left) : node;
    }

    static Node *findMax(Node *node) {
        return node->right ? findMin(node->right) : node;
    }

    static Node *removeMin(Node *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }

    static Node *removeMax(Node *node) {
        if (!node->right)
            return node->left;
        node->right = removeMin(node->right);
        return balance(node);
    }

public:
    AVLTree() {
        this->head = nullptr;
    }

private:
    static Node *insert(Node *node, int key) {
        if (!node) {
            node = new Node(key);
            return node;
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else { node->right = insert(node->right, key); }
        return balance(node);
    }

    static Node *remove(Node *node, int key) {
        if (!node)
            return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            Node *l = node->left;
            Node *r = node->right;
            delete node;
            if (!r) return l;
            Node *min = findMin(r);
            min->right = removeMin(r);
            min->left = l;
            return balance(min);
        }
        return balance(node);
    }

    static void LPRprint(Node *node) {
        if (!node) return;
        std::cout << "[<";
        LPRprint(node->left);
        std::cout << ">{" << node->key << "}<";
        LPRprint(node->right);
        std::cout << ">]";
    }

public:
    Node *insert(int key) {
        head = insert(head, key);
        return head;
    }

    Node *remove(int key) {
        head= remove(head,key);
        return head;
    }

    void LPRprint() {
        LPRprint(head);
    }

private:
    Node *head;

};


#endif //AVLTREE_AVLTREE_H
