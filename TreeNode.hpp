#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

template <class T>
/**
 * @brief TreeNode class
 * 
 * @author Jonathan Ung
 */
class TreeNode{
    public:
        int data;
        TreeNode<T> *left, *right;
        TreeNode(int);
        ~TreeNode() {};
};

template <class T>
TreeNode<T>::TreeNode(int d) {
    data = d;
    left = nullptr, right = nullptr;
}

#endif