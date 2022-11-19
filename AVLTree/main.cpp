#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree tree;
    int qNum;
    std::cin >> qNum;
    for (; qNum; --qNum) {
        int qType;
        std::cin >> qType;
        int key;
        std::cin >> key;
        if (qType == 1)
            tree.insert(key)->key;
        else
            tree.remove(key)->key;
        tree.LPRprint();
        std::cout << '\n';
    }
}
