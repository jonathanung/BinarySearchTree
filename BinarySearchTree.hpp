#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "TreeNode.hpp"
#include <iostream>

template <class T>
/**
 * @brief Binary Search Tree Class
 * 
 * @author Jonathan Ung
 */
class BinarySearchTree {
    private:
        TreeNode<T> *root;
        size_t size;

    public:
        BinarySearchTree() { root = nullptr; }
        void insert(T);
        void remove(T);
        bool search(T v) { return searchNode(v) != nullptr; }
        TreeNode<T>* searchNode(T);
        void printInOrder() { inOrder(root); }
        void inOrder(TreeNode<T> *);
        void printPreOrder() { preOrder(root); }
        void preOrder(TreeNode<T> *);
        void printPostOrder() { postOrder(root); }
        void postOrder(TreeNode<T> *);
        void printStructure(TreeNode<T> * = nullptr, bool = false, int = 0);
};

template <class T>
void BinarySearchTree<T>::insert(T val) {
    TreeNode<T> *temp = new TreeNode<T>(val);
    size++;
    if (root == nullptr)
    {
        root = temp;
        return;
    }
    TreeNode<T> *curr = root;
    while (temp != nullptr) {
        if (temp->data > curr->data){
            if (curr->right == nullptr) {
                curr->right = temp;
                temp = nullptr;
            } else {
                curr = curr->right;
            }
        } else {
            if (curr->left == nullptr) {
                curr->left = temp;
                temp = nullptr;
            } else {
                curr = curr->left;
            }
        }
    }
}

template <class T>
void BinarySearchTree<T>::remove(T val) {
    TreeNode<T> *prev = nullptr;
    TreeNode<T> *curr = root;
    while (curr != nullptr) {
        if (val > curr->data) {
            prev = curr;
            curr = curr->right;
        }
        else if (val < curr->data){
            prev = curr
            curr = curr->left;
        }
        else{
            break;
        }
    }
    if (curr != nullptr) {
        //complete this method
    }
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::searchNode(T val) {
    TreeNode<T> *curr = root;
    while (curr != nullptr) {
        if (val > curr->data) {
            curr = curr->right;
        }
        else if (val < curr->data){
            curr = curr->left;
        }
        else{
            break;
        }
    }
    return curr;
}


template <class T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* curr) {
    if (curr == nullptr) return;
    inOrder(curr->left);
    std::cout << curr->data << " ";
    inOrder(curr->right);
}

template <class T>
void BinarySearchTree<T>::preOrder(TreeNode<T>* curr) {
    if (curr == nullptr) return;
    std::cout << curr->data << " ";
    preOrder(curr->left);
    preOrder(curr->right);
}

template <class T>
void BinarySearchTree<T>::postOrder(TreeNode<T>* curr) {
    if (curr == nullptr) return;
    postOrder(curr->left);
    postOrder(curr->right);
    std::cout << curr->data << " ";
}

template <class T>
void BinarySearchTree<T>::printStructure(TreeNode<T>* curr, bool right, int level) {
    if ((curr == nullptr) && (root != nullptr) && (level == 0)) {
        std::cout << "BST Size: " << size << std::endl;
        curr = root;
    }
    if (curr == nullptr) {
        return;
    }
    for (int i = 0; i < level; i++) {
        std::cout << "|";
        if (i < level - 1) {
            std::cout << "   ";
        }
    }
    if(right && level > 0) {
        std::cout << "-R ";
    }
    else if (!right && level > 0){
        std::cout << "-L ";
    }
    std::cout << curr->data << std::endl;
    printStructure(curr->left, false, level + 1);
    printStructure(curr->right, true, level + 1);
}
#endif