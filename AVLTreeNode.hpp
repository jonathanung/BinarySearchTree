#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include "TreeNode.hpp"

template <class T>
/**
 * @brief AVLTreeNode class
 * 
 * @author Jonathan Ung
 */
class AVLTreeNode : public TreeNode<T> {
    public:
        size_t height;
        AVLTreeNode(const T&);
};

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& d) : TreeNode<T>(d){
    height = 0;
}

#endif