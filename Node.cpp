#include "Node.h"

Node::Node() {}
Node::~Node() {}

/*
Leaf Node Implementation
        */
void LeafNode::insertIndexHelper(int idx) {
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
        internalNode->leftPointer = thisLeafNode; 
    }    

    //Add IndexPointer node to new leaf node into internal node  
    std::shared_ptr<IndexPointerNode> copyUpNode = std::make_shared<IndexPointerNode>();
    copyUpNode->index = copyVal;
    copyUpNode->child = nextLeafNode;
    internalNode->insertIndexPointerNode(copyUpNode);   

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

    if (internalNode->shouldPushUp) { 
        //trigger push up on internal parent node
        int pushIdx = floor(internalNode->curCapacity / 2) -1; 
        auto pushVal = internalNode->internalVec[pushIdx];
        internalNode->pushUp(pushVal);
        
        internalNode->shouldPushUp = false;
    }

    //link to existing tree
    nextLeafNode->parentNode = internalNode;
    thisLeafNode->nextNode = nextLeafNode;
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
        std::cout << index << "*";
        if (i != indexVec.size() - 1) {
            std::cout << ", ";
        } 
        i++;
    }
    std::cout << " ]";
    std::cout << curCapacity;
}

/*
Internal Node Implementation
    */

InternalNode::InternalNode() {
    curCapacity = 0;
    maxCapacity = 3;
    isInternal = true;
}

void InternalNode::insertIndexPointerNode(std::shared_ptr<IndexPointerNode> indexPtrNode) {
    // push up if one more than max capacity (accounted for implicit first ptr)
    bool inserted = false;
    for (auto it = internalVec.begin(); it < internalVec.end(); it++) {
        if (indexPtrNode->index < (*it)->index ) {
            internalVec.insert(it, indexPtrNode);
            curCapacity++;
            inserted = true;
            break;
        }
    }
    if (!inserted) {
        internalVec.push_back(indexPtrNode);
        curCapacity++;
    }
    
    if (curCapacity == (maxCapacity + 1)) {
        this->shouldPushUp = true; 
    }
    return;
}

std::shared_ptr<IndexPointerNode> InternalNode::initIndexPointerNodeFromCopy(std::shared_ptr<IndexPointerNode> indexPtrNode) {

    auto newIndexPointerNode = std::make_shared<IndexPointerNode>();
    newIndexPointerNode->index = indexPtrNode->index;
    newIndexPointerNode->child = indexPtrNode->child;

    return newIndexPointerNode;
}

void InternalNode::pushUp(std::shared_ptr<IndexPointerNode> indexPtrNode) {

    auto thisNode = getPtr();
    auto splitNode = std::make_shared<InternalNode>(InternalNode());
    auto parentInternal = std::make_shared<InternalNode>(InternalNode());

    // copy split indexes into split node 
    bool split = false;
    for (int i = 0; i < thisNode->internalVec.size(); i++) {
        auto currentIndex = thisNode->internalVec[i];
        if (split) {            
            auto copyNode = initIndexPointerNodeFromCopy(currentIndex);
            splitNode->insertIndexPointerNode(copyNode);
        }
        if (thisNode->internalVec[i]->index == indexPtrNode->index) {
            split = true;
            continue;
        }
    } 
    //assign left pointer to the pushed up node's child 
    splitNode->leftPointer = indexPtrNode->child;    

    // remove split indexes from this node
    for (auto node : splitNode->internalVec) {
        thisNode->deleteIndexPtrNode(node->index);
    }
    thisNode->deleteIndexPtrNode(indexPtrNode->index);

    // associate parent to this node and split node
    parentInternal->leftPointer = thisNode;
    indexPtrNode->child = splitNode;
    parentInternal->insertIndexPointerNode(indexPtrNode);

    thisNode->parentNode = parentInternal;
    splitNode->parentNode = parentInternal;

    /*
        parentInternal->printNode();
        auto child1 = std::dynamic_pointer_cast<InternalNode>(parentInternal->leftPointer);
        auto child2 = std::dynamic_pointer_cast<InternalNode>(parentInternal->internalVec[0]->child);
        
        child1->printNode();
        child2->printNode();

        child1->leftPointer->printNode();
        child1->internalVec[0]->child->printNode();

        child2->leftPointer->printNode();
        child2->internalVec[0]->child->printNode();
        child2->internalVec[1]->child->printNode();
    */ 


    // thisNode->printNode();
    // splitNode->internalVec[0]->child->printNode();
    // splitNode->internalVec[0]->child->printNode();
    return;
}

void InternalNode::deleteIndexPtrNode(int idx) {
    auto thisNode = getPtr();
    for (int i = 0; i < thisNode->internalVec.size(); i++)  {
        auto curIdxPtr = thisNode->internalVec[i];
        if (curIdxPtr->index == idx) {
            thisNode->internalVec.erase(
                thisNode->internalVec.begin() + i
            );
            thisNode->curCapacity--;
        }
    }
    return;
} 

void InternalNode::printNode() {
    if (internalVec.size() == 0) {
        std::cout << "[ ]" << 0;

    } else if (internalVec[0]->index == 0) {
        int i = 0;
        std::cout << "[ "; 
        for (auto child : internalVec) {
            if (child->index == 0) {
                continue;
            }
            std::cout << child->index;
            if (i != internalVec.size() -2) {
                std::cout << ", ";
            } 
            i++;
        }
        std::cout << " ]"; 
        std::cout << curCapacity;
    } else {
        std::cout << "[ ";
        int i = 0;
        for (auto child : internalVec) { 
            std::cout << child->index;
            if (i != internalVec.size() -1) {
                std::cout << ", ";
            } 
            i++;
        } 
        std::cout << " ]" << " " << internalVec.size();
        std::cout << "\n";
    }
     
}
/*
*/