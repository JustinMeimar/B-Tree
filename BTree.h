#pragma once
#include "Node.h" 
#include <cmath>

class BTree {
    public:
        int height = 0;
        int nodeCount = 0;
        std::shared_ptr<Node> root;
        BTree();
        ~BTree();

        void insertIndex(int idx);
        void printTree();
};