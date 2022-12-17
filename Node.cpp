#include "Node.h"

Node::Node() {}
Node::~Node() {}

LeafNode::LeafNode() {}
LeafNode::LeafNode(int nodeCount) {
    curCapacity = 0;
    maxCapacity = 3;
    nodeNumber = nodeCount;
}

void LeafNode::insertIndex() {}
void LeafNode::deleteIndex() {}
void LeafNode::printNode() {
    std::cout << "[ "; 
    int i = 0;
    for (auto index : indexVec) {
        std::cout << index;
        if (i != indexVec.size() - 1) {
            std::cout << ", ";
        } 
        i++;
    }
    std::cout << " ]";
}

InternalNode::InternalNode() {}
InternalNode::InternalNode(int nodeCount) {
    curCapacity = 0;
    maxCapacity = 4;
    nodeNumber = nodeCount;
}
void InternalNode::insertIndex() {} 
void InternalNode::deleteIndex() {}
void InternalNode::printNode() {
    int i = 0;
    std::cout << "[ "; 
    std::cout << "#" << nodeVec[0]->nodeNumber << " | ";
    for (auto index : indexVec) {
        auto node = nodeVec[i+1]; 
        std::cout << index << " | ";
        std::cout << "#" << node->nodeNumber << " | ";
        if (i != indexVec.size() - 1) {
            std::cout << ", ";
        } 
        i++;
    }
    std::cout << " ]";  
}
/*
*/