#include "BinarySearchTree.hpp"
#include <iostream>

int main() {
    std::vector<int> vals = {10, 5, 15, 2, 7, 12, 17, 19, 1, 3, 9};
    BinarySearchTree<int> bST = BinarySearchTree<int>();
    BinarySearchTree<int> bST2 = BinarySearchTree<int>();
    BinarySearchTree<int> bST3 = BinarySearchTree<int>();
    for(int val : vals) {
        bST.insert(val);
        bST2.insert(val);
        bST3.insert(val);
    }
    // bST.printInOrder();
    // std::cout << std::endl;
    // bST.printPreOrder();
    // std::cout << std::endl;
    // bST.printPostOrder();
    // std::cout << std::endl;
    bST.printStructure();
    std::cout << "Find 11:" << bST.search(11) << std::endl;
    std::cout << "Find 12:" << bST.search(12) << std::endl;
    bST.remove(10);
    bST.printStructure();
    // bST2.remove(7);
    // bST2.printStructure();
    // bST3.remove(9);
    // bST3.printStructure();
    return 0;
}