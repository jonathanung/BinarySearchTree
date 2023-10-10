#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "TreeNode.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

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
        BinarySearchTree() { size = 0, root = nullptr; }
        BinarySearchTree(std::vector<T>);
        ~BinarySearchTree() { destroy(root); }
        TreeNode<T> *createNewNode(const T) { return new TreeNode<T>(d); }
        void destroy(TreeNode<T> *);
        void insert(const T);
        void remove(const T);
        bool search(const T v) const { return searchNode(v) != nullptr; }
        TreeNode<T>* searchNode(const T) const;
        TreeNode<T>* searchParent(const T) const;
        size_t getSize() const { return size; }
        void clear() { destroy(root); }
        std::vector<TreeNode<T> *> path(const T) const;

        void printInOrder() const { inOrder(root); }
        void inOrder(TreeNode<T> *) const;
        void printPreOrder() const { preOrder(root); }
        void preOrder(TreeNode<T> *) const;
        void printPostOrder() const { postOrder(root); }
        void postOrder(TreeNode<T> *) const;
        void printStructure(TreeNode<T> * = nullptr, bool = false, int = 0) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree(std::vector<T> vec) : BinarySearchTree<T>() {
    for (T val : vec) {
        insert(val);
    }
}

template <class T>
void BinarySearchTree<T>::destroy(TreeNode<T> * node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }
}

template <class T>
void BinarySearchTree<T>::insert(const T val) {
    if(search(val)) return;
    TreeNode<T> *temp = createNewNode(val);
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
void BinarySearchTree<T>::remove(const T val) {
    TreeNode<T> *parent = searchParent(val);
    TreeNode<T> *curr = searchNode(val);
    bool left = true;
    if (curr == nullptr)
        return;
    size--;
    if (parent && parent->right == curr) {
        left = false;
    }
    if (curr->left != nullptr && curr->right != nullptr){
        TreeNode<T> *nextParent = curr;
        TreeNode<T> *next = curr->right;
        while (next->left != nullptr) {
            nextParent = next;
            next = next->left;
        }
        if (!parent) root = curr->right;
        else if (left) parent->left = curr->right;
        else parent->right = curr->right;
        next->left = curr->left;
        delete curr;
        curr = nullptr;
        return;
    }
    if(curr->left == nullptr) {
        if (!parent) root = curr->right;
        else if (left) parent->left = curr->right; 
        else parent->right = curr->right;
        delete curr;
        curr = nullptr;
        return;
    }
    if(curr->right == nullptr) {
        if (!parent) root = curr->left;
        else if (left) parent->left = curr->left;
        else parent->right = curr->left;
        delete curr;
        curr = nullptr;
        return;
    }
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::searchNode(const T val) const {
    TreeNode<T> *curr = root;
    while (curr != nullptr) {
        if (val == curr->data) break;
        curr = curr->data < val ? curr->right : curr->left;
    }
    return curr;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::searchParent(const T val) const {
    TreeNode<T> *curr = root;
    if(root != nullptr && root->data == val) {
        return nullptr;
    }
    while (curr != nullptr) {
        TreeNode<T> *next = curr->data < val ? curr->right : curr->left;
        if (val == next->data) break;
        curr = next;
    }
    return curr;
}

template <class T>
std::vector<TreeNode<T>*> BinarySearchTree<T>::path(const T val) const {
    std::vector<TreeNode<T> *> vecPath = std::vector<TreeNode<T> *>();
    TreeNode<T> *curr = root;
    while (curr != nullptr) {
        vecPath.pushBack(curr);
        if (val == curr->data) break;
        curr = curr->data < val ? curr->right : curr->left;
    }
    return vecPath;
}

template <class T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* curr) const {
    if (curr == nullptr) return;
    inOrder(curr->left);
    std::cout << curr->data << " ";
    inOrder(curr->right);
}

template <class T>
void BinarySearchTree<T>::preOrder(TreeNode<T>* curr) const {
    if (curr == nullptr) return;
    std::cout << curr->data << " ";
    preOrder(curr->left);
    preOrder(curr->right);
}

template <class T>
void BinarySearchTree<T>::postOrder(TreeNode<T>* curr) const {
    if (curr == nullptr) return;
    postOrder(curr->left);
    postOrder(curr->right);
    std::cout << curr->data << " ";
}

template <class T>
void BinarySearchTree<T>::printStructure(TreeNode<T>* curr, bool right, int level) const {
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