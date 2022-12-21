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
        if (leafNode->parentNode != nullptr) {
            //make root the parent
            root = leafNode->parentNode;
        }
    } else { 
        // find the leaf node we should insert idx into  
        auto internalNode = std::dynamic_pointer_cast<InternalNode>(root);
        std::shared_ptr<Node> curNode = internalNode;
        
        while (curNode->isInternal) {
            int i = 0; 
            for (auto it = internalNode->internalVec.begin(); it <= internalNode->internalVec.end(); it++) {
                if (idx < (*it)->index) {
                    // follow ptr to the left
                    curNode = internalNode->internalVec[i-1]->child;
                    // curNode = (*it)->child; //previous iterator
                    if (curNode->isLeaf) break;
                } 
                // rightmost pointer at sizeof(indexVec) + 1
                else if (it == internalNode->internalVec.end()) {
                    curNode = (*it)->child;
                } 
                i++;
            }
        }
        // leaf node to insert into is found
        auto leafNode = std::dynamic_pointer_cast<LeafNode>(curNode);
        leafNode->insertIndex(idx);

        //assign root
        std::shared_ptr<Node> highestNode = leafNode;
        while (highestNode->parentNode != nullptr) {
            highestNode = highestNode->parentNode;
        }
        root = highestNode;
    }
    return;
}

void BTree::printTree(std::shared_ptr<Node> node) {

    if (node->isLeaf) {
        auto leaf = std::dynamic_pointer_cast<LeafNode>(root);
        leaf->printNode();
        return;
    } else {
        
        // auto curNode = std::dynamic_pointer_cast<InternalNode>(node);

        auto internal = std::dynamic_pointer_cast<InternalNode>(root); 
        // std::cout << "\n"; 
        internal->printNode();
        // std::cout << "\n"; 
        for (auto child : internal->internalVec) {
            printf("\n"); 
            if (child->child->isLeaf) {
                auto leafNode = std::dynamic_pointer_cast<LeafNode>(child->child);
                leafNode->printNode();
            }
            // printTree(child->child);
        }
    }
}
