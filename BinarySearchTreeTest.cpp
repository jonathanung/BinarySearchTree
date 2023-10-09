#include "BinarySearchTree.hpp"
#include <iostream>

int main() {
    std::vector<int> vals = {10, 5, 15, 2, 7, 12, 17, 19, 1, 3, 9};
    BinarySearchTree<int> bST = BinarySearchTree<int>();
    for(int val : vals) {
        bST.insert(val);
    }
    // bST.printInOrder();
    // std::cout << std::endl;
    // bST.printPreOrder();
    // std::cout << std::endl;
    // bST.printPostOrder();
    // std::cout << std::endl;
    bST.printStructure();
    return 0;
}