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
};

template<class T>
AVLTree<T>::AVLTree(std::vector<T> vec) : BinarySearchTree<T>() {
    for (T val : vec) {
        insert(val);
    }
}

template<class T>

#endif