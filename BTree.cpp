#include "BTree.h"

BTree::BTree() {}
BTree::~BTree() {}

void BTree::insertIndex(int idx) {
    if (root == NULL) {
        auto leafNode = std::make_shared<LeafNode>(LeafNode());
        root = leafNode;
        root->insertIndex(idx); 
    } 
    else if (root->isLeaf) {
        // check if the node is already full
        auto leafNode = std::dynamic_pointer_cast<LeafNode>(root);
        leafNode->insertIndex(idx);
        std::cout << leafNode->parentNode << std::endl;
        if (leafNode->parentNode != nullptr) {
            //make root the parent
            root = leafNode->parentNode;
        }
    } else { 
        //search for index location
        auto internalNode = std::dynamic_pointer_cast<InternalNode>(root);
        std::shared_ptr<Node> curNode = internalNode;
        
        while (curNode->isInternal) {
            int i = 0;
            for (auto it = internalNode->indexVec.begin(); it < internalNode->indexVec.end(); it++) {
                if (idx < *it) {
                    // follow ptr to the left
                    curNode = internalNode->nodeVec[i];
                    if (curNode->isLeaf) break;
                } 
                // rightmost pointer at sizeof(indexVec) + 1
                else if (i >= *it && i == internalNode->indexVec.size()-1 ) {
                    curNode = internalNode->nodeVec[i + 1];
                } 
                i++; 
            }
        }
         
        // leaf node to insert into is found
        auto leafNode = std::dynamic_pointer_cast<LeafNode>(curNode);
        leafNode->insertIndex(idx);
    }
    return;
}

void BTree::printTree(std::shared_ptr<Node> node) {

    if (node->isLeaf) {
        auto leaf = std::dynamic_pointer_cast<LeafNode>(root);
        leaf->printNode();
        return;
    } else {
        auto internal = std::dynamic_pointer_cast<InternalNode>(root); 
        std::cout << "\n"; 
        internal->printNode();
        std::cout << "\n"; 
        for (auto child : internal->nodeVec) {
            if (child->isLeaf) {
                auto leafNode = std::dynamic_pointer_cast<LeafNode>(child);
                leafNode->printNode();
            }         
        }
    }
}
