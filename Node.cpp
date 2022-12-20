#include "Node.h"

Node::Node() {}
Node::~Node() {}

void Node::insertIndexHelper(int idx) {
    curCapacity++;
    int i = 0; 
    for(auto it=indexVec.begin() ; it < indexVec.end(); it++) {
        if (*it > idx) {
            indexVec.insert(it, idx);
            return;
        }
    }
    indexVec.push_back(idx);
}

LeafNode::LeafNode() {
    curCapacity = 0;
    maxCapacity = 3;
    isLeaf = true;
}

void LeafNode::copyUp(int idx) {
    // copy up index from leafnode into parent internal node
    std::shared_ptr<LeafNode> thisLeafNode = getPtr();
    std::shared_ptr<LeafNode> nextLeafNode = std::make_shared<LeafNode>(LeafNode());
    std::shared_ptr<InternalNode> internalNode = std::dynamic_pointer_cast<InternalNode>(thisLeafNode->parentNode); 

    int copyIdx = floor(maxCapacity / 2);
    int copyVal = thisLeafNode->indexVec[copyIdx];   

    if (internalNode == nullptr) { 
        //make new internal node
        internalNode = std::make_shared<InternalNode>(InternalNode()); 

        // IndexPointerNode initNode = {
        //     0, // 
        //     thisLeafNode
        // };

        // internalNode->internalVec.insert(
        //     internalNode->internalVec.begin(), 
        //     initNode
        // );

        internalNode->insertIndex(copyVal); //index we copy up
        internalNode->insertNodePtr(thisLeafNode, thisLeafNode->indexVec[0]);       
    } else {
        //internal already exists
        internalNode->insertIndex(copyVal); //index we copy up
    } 
    internalNode->insertNodePtr(nextLeafNode, copyVal);

    //remove leaf node values from [copyIdx:end]
    int curIdx = thisLeafNode->indexVec.size() - 1; //end of the vector
    while(curIdx >= copyIdx) {
        int carryIdx = thisLeafNode->indexVec[curIdx]; 
        // remove index from current leaf node and insert into new leaf node. 
        thisLeafNode->deleteIndex(carryIdx);
        nextLeafNode->insertIndex(carryIdx); 
        // decrement counters
        thisLeafNode->curCapacity--;
        curIdx--;
    }
    nextLeafNode->insertIndex(idx);
    
    //link to existing tree
    nextLeafNode->parentNode = internalNode;
    parentNode = internalNode;

    return;
}

void LeafNode::insertIndex(int idx) { 
    if (curCapacity == maxCapacity) {
        copyUp(idx);
    } else {
        insertIndexHelper(idx);
    }
    return; 
}


void LeafNode::deleteIndex(int idx) {
    for (auto it = indexVec.begin(); it < indexVec.end(); it++) {
        if (*it == idx) {
            indexVec.erase(it);
        }
    }
    return;
}

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
    std::cout << curCapacity;
}

InternalNode::InternalNode() {
    curCapacity = 0;
    maxCapacity = 3;
    isInternal = true;
}

void InternalNode::insertNodePtr(std::shared_ptr<Node> node, int nodeVal) {
    int i = 1;
    if (nodeVal < indexVec[0]) {
        nodeVec.insert(nodeVec.begin(), node); 
        return;
    } else {
        for (auto it = indexVec.begin(); it < indexVec.end(); it++) {
            if (nodeVal >= *it) { 
                // std::cout << "iterator over index vec in internal node: " << *it << std::endl;
                break;
            }
            i++;
        }
        nodeVec.insert(nodeVec.begin() + i, node);
    }
}

void InternalNode::pushUp(int idx) {
    return;
}

void InternalNode::insertIndex(int idx) {
    if (curCapacity == maxCapacity) {
        pushUp(idx);
    } else {
        insertIndexHelper(idx);
    }
    return; 
} 

void InternalNode::deleteIndex(int idx) {}

void InternalNode::printNode() {
    int i = 0;
    std::cout << "[ "; 
    for (auto index : indexVec) {
        auto node = nodeVec[i+1]; 
        std::cout << index << "";
        if (i != indexVec.size() - 1) {
            std::cout << ", ";
        } 
        i++;
    }
    std::cout << " ]";  
}
/*
*/