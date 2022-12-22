#pragma once
#include "Node.h" 

class BTree {
    public:
        int height = 0;
        int nodeCount = 0;
        std::shared_ptr<Node> root;
        std::shared_ptr<Node> leafTemp;
        BTree();
        ~BTree();

        void searchIndex(int idx, std::shared_ptr<Node> node = nullptr);
        // std::shared_ptr<Node> findLeafNode(int idx, std::shared_ptr<Node> node = nullptr); //searchIndex && insertIndex helper
        void findLeafNode(int idx, std::shared_ptr<Node> node = nullptr); //searchIndex && insertIndex helper
        
        void insertIndex(int idx);
        void printTree(std::shared_ptr<Node> node);
        void internalPrint(std::shared_ptr<InternalNode> node);
};