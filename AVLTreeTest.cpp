#include "AVLTree.hpp"
#include <iostream>

int main() {
    std::vector<int> vals = {10, 5, 15, 2, 7, 12, 17, 19, 1, 3, 9};
    AVLTree<int> aT = AVLTree<int>();
    AVLTree<int> aT2 = AVLTree<int>();
    AVLTree<int> aT3 = AVLTree<int>();
    for(int val : vals) {
        aT.insert(val);
        aT2.insert(val);
        aT3.insert(val);
    }
    // aT.printInOrder();
    // std::cout << std::endl;
    // aT.printPreOrder();
    // std::cout << std::endl;
    // aT.printPostOrder();
    // std::cout << std::endl;
    aT.printStructure();
    std::cout << "Find 11:" << aT.search(11) << std::endl;
    std::cout << "Find 12:" << aT.search(12) << std::endl;
    aT.remove(10);
    aT.printStructure();
    // aT2.remove(7);
    // aT2.printStructure();
    // aT3.remove(9);
    // aT3.printStructure();
    return 0;
}