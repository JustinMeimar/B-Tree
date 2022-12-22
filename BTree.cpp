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
        findLeafNode(idx, internalNode);

        // leaf node to insert into is found
        auto leafNode = std::dynamic_pointer_cast<LeafNode>(this->leafTemp);
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

void BTree::internalPrint(std::shared_ptr<InternalNode> node) {
    return;
}

void BTree::findLeafNode(int idx, std::shared_ptr<Node> node) {
    if (node->isLeaf) {
        this->leafTemp = node;
        return;
    } else {
        auto internalNode = std::dynamic_pointer_cast<InternalNode>(node); 
        int vecSize = internalNode->internalVec.size(); 
        //recursively search the internal nodes        
        if (idx < internalNode->internalVec[0]->index)  {
            //index less than all index in internal
            findLeafNode(idx, internalNode->leftPointer);
 
        } else if(idx > internalNode->internalVec[vecSize-1]->index) {
            //index greater than all indexes in internal
            findLeafNode(idx, internalNode->internalVec[vecSize-1]->child);
       
        } else {
            //index somewhere in the middle of the B+ Tree 
            for (int i = 1; i < vecSize; i++) {
                if (idx < internalNode->internalVec[i]->index) {
                    //search the child of the previous index entry
                   findLeafNode(idx, internalNode->internalVec[i-1]->child);
                }
            }
        }
    }
}

void BTree::searchIndex(int idx, std::shared_ptr<Node> node) {
    if (node == nullptr) { node == root; } // override default arg

    findLeafNode(idx, node);
    auto leafNode = std::dynamic_pointer_cast<LeafNode>(this->leafTemp);
    // auto leafNode = std::dynamic_pointer_cast<LeafNode>(node);

    for (auto leafIndex : leafNode->indexVec) {
        if (leafIndex == idx) {
            printf("\n --- Found index %d in leaf node: ", idx);
            leafNode->printNode(); 
            return;
        }
    }
    printf("\n --- Index: %d is not in the B+ Tree", idx);
    
    return;
}

void BTree::printTree(std::shared_ptr<Node> node) {

    auto leafNode = std::dynamic_pointer_cast<LeafNode>(node);
    if (leafNode != nullptr) {
        leafNode->printNode();
        return;
    }
    auto curNode = std::dynamic_pointer_cast<InternalNode>(node);
     
    curNode->printNode();
    printf("\n");
    printTree(curNode->leftPointer); 
    for (auto childNode : curNode->internalVec) {
        printTree(childNode->child);
    } 
}
