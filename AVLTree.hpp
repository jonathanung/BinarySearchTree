#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "BinarySearchTree.hpp"
#include "AVLTreeNode.hpp"
#include <algorithm>
#include <vector>

template<class T>
/**
 * @brief AVL Tree class
 * 
 * @author Jonathan Ung
 */
class AVLTree : public BinarySearchTree<T> {
    public:
        AVLTree() : BinarySearchTree<T>() {}
        AVLTree(std::vector<T>);
        ~AVLTree() {} //Base destructor destroys the nodes
        bool insert(const T &);
        bool remove(const T &);
        void printStructure(AVLTreeNode<T> * = nullptr, bool = false, int = 0) const;

    protected:
        AVLTreeNode<T> *createNewNode(const T& d) { return new AVLTreeNode<T>(d); }

    private:
        void balancePath(const T &);
        int balanceFactor(AVLTreeNode<T>*);
        void updateHeight(AVLTreeNode<T> *);
        void rotateLL(AVLTreeNode<T>*, TreeNode<T>*);
        void rotateLR(AVLTreeNode<T>*, TreeNode<T>*);
        void rotateRR(AVLTreeNode<T>*, TreeNode<T>*);
        void rotateRL(AVLTreeNode<T>*, TreeNode<T>*);
};

template<class T>
AVLTree<T>::AVLTree(std::vector<T> vec) : BinarySearchTree<T>() {
    for (T val : vec) {
        insert(val);
    }
}

template<class T>
bool AVLTree<T>::insert(const T& val) {
    bool complete = BinarySearchTree<T>::insert(val);
    if (!complete) return false;
    balancePath(val);
    return true;
}

template<class T>
bool AVLTree<T>::remove(const T& val) {
    AVLTreeNode<T> *parent = static_cast<AVLTreeNode<T>*>(this->searchParent(val));
    AVLTreeNode<T> *curr = static_cast<AVLTreeNode<T>*>(this->searchNode(val));
    bool left = true;
    if (curr == nullptr) return false;
    this->size--;
    if (parent && parent->right == curr) {
        left = false;
    }
    if (curr->left != nullptr && curr->right != nullptr){
        AVLTreeNode<T> *next = static_cast<AVLTreeNode<T>*>(curr->right);
        while (next->left != nullptr) {
            next = static_cast<AVLTreeNode<T>*>(next->left);
        }
        if (!parent) this->root = curr->right;
        else if (left) parent->left = curr->right;
        else parent->right = curr->right;
        next->left = curr->left;
        balancePath(next->data);
    }
    if(curr->left == nullptr) {
        if (!parent) this->root = curr->right;
        else if (left) parent->left = curr->right; 
        else parent->right = curr->right;
        if(parent) balancePath(parent->data);
    }
    if(curr->right == nullptr) {
        if (!parent) this->root = curr->left;
        else if (left) parent->left = curr->left;
        else parent->right = curr->left;
        if(parent) balancePath(parent->data);
    }
    delete curr;
    curr = nullptr;
    return true;
}

template <class T>
void AVLTree<T>::balancePath(const T& val) {
    std::vector<TreeNode<T> *> p = this->path(val);
    for (int i = p.size() - 1; i >= 0; i--) {
        AVLTreeNode<T> *curr = static_cast<AVLTreeNode<T>*>(p[i]);
        updateHeight(curr);
        AVLTreeNode<T> *parent = (i > 0) ? static_cast<AVLTreeNode<T>*>(p[i - 1]) : nullptr;
        switch(balanceFactor(curr)) {
            case -2:
                if (balanceFactor(static_cast<AVLTreeNode<T>*>(curr->left)) <= 0) rotateLL(curr,parent);
                else rotateLR(curr,parent);
                break;
            case +2:
                if (balanceFactor(static_cast<AVLTreeNode<T>*>(curr->right)) <= 0) rotateRR(curr,parent);
                else rotateRL(curr,parent);
        }
    }
}

template <class T>
int AVLTree<T>::balanceFactor(AVLTreeNode<T>* node) {
    if (node->left == nullptr) return +(node->height);
    if (node->right == nullptr) return -(node->height);
    return (static_cast<AVLTreeNode<T>*>(node->right)->height) - (static_cast<AVLTreeNode<T>*>(node->left)->height);
}

template <class T>
void AVLTree<T>::updateHeight(AVLTreeNode<T> * node) {
    if (node->left == nullptr && node->right == nullptr) node->height = 0;
    else if (node->left == nullptr) node->height = static_cast<AVLTreeNode<T>*>(node->right)->height + 1;
    else if (node->right == nullptr) node->height = static_cast<AVLTreeNode<T>*>(node->left)->height + 1;
    else node->height = ((static_cast<AVLTreeNode<T>*>(node->left)->height > static_cast<AVLTreeNode<T>*>(node->right)->height) ? static_cast<AVLTreeNode<T>*>(node->left)->height : static_cast<AVLTreeNode<T>*>(node->right)->height) + 1;
}

template <class T>
void AVLTree<T>::rotateLL(AVLTreeNode<T>* curr, TreeNode<T>* parent) {
    AVLTreeNode<T> *currLChild = static_cast<AVLTreeNode<T>*>(curr->left);
    if (parent == nullptr) this->root = currLChild;
    else if (parent->left == curr) parent->left = currLChild;
    else parent->right = currLChild;
    curr->left = currLChild->right;
    currLChild->right = curr;
    updateHeight(curr);
    updateHeight(currLChild);
}

template <class T>
void AVLTree<T>::rotateLR(AVLTreeNode<T>* curr, TreeNode<T>* parent) {
    AVLTreeNode<T> *currLChild = static_cast<AVLTreeNode<T>*>(curr->left);
    AVLTreeNode<T> *lChildR = static_cast<AVLTreeNode<T>*>(currLChild->right);
    if (parent == nullptr) this->root = lChildR;
    else if (parent->left == curr) parent->left = lChildR;
    else parent->right = lChildR;
    curr->left = lChildR->right;
    currLChild->right = lChildR->left;
    lChildR->left = currLChild;
    lChildR->right = curr;
    updateHeight(curr);
    updateHeight(currLChild);
    updateHeight(lChildR);
}

template <class T>
void AVLTree<T>::rotateRR(AVLTreeNode<T>* curr, TreeNode<T>* parent) {
    AVLTreeNode<T> *currRChild = static_cast<AVLTreeNode<T>*>(curr->right);
    if (parent == nullptr) this->root = currRChild;
    else if (parent->left == curr) parent->left = currRChild;
    else parent->right = currRChild;
    curr->right = currRChild->left;
    currRChild->left = curr;
    updateHeight(curr);
    updateHeight(currRChild);
}

template <class T>
void AVLTree<T>::rotateRL(AVLTreeNode<T>* curr, TreeNode<T>* parent) {
    AVLTreeNode<T> *currRChild = static_cast<AVLTreeNode<T>*>(curr->right);
    AVLTreeNode<T> *rChildL = static_cast<AVLTreeNode<T>*>(currRChild->left);
    if (parent == nullptr) this->root = rChildL;
    else if (parent->left == curr) parent->left = rChildL;
    else parent->right = rChildL;
    curr->right = rChildL->left;
    currRChild->left = rChildL->right;
    rChildL->right = currRChild;
    rChildL->left = curr;
    updateHeight(curr);
    updateHeight(currRChild);
    updateHeight(rChildL);
}

template <class T>
void AVLTree<T>::printStructure(AVLTreeNode<T>* curr, bool right, int level) const {
    if ((curr == nullptr) && (this->root != nullptr) && (level == 0)) {
        std::cout << "BST Size: " << this->size << std::endl;
        curr = static_cast<AVLTreeNode<T>*>(this->root);
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
    std::cout << curr->data << " : " << curr->height << std::endl;
    printStructure(static_cast<AVLTreeNode<T>*>(curr->left), false, level + 1);
    printStructure(static_cast<AVLTreeNode<T>*>(curr->right), true, level + 1);
}
#endif