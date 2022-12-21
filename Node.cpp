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
        //init first IndexPointerNode (Left Most Pointer) 
        std::shared_ptr<IndexPointerNode> initNode = std::make_shared<IndexPointerNode>();
        initNode->index = 0; 
        initNode->child = thisLeafNode;
        //make new internal node
        internalNode = std::make_shared<InternalNode>(InternalNode()); 
        internalNode->internalVec.insert(internalNode->internalVec.begin(), initNode);
        internalNode->curCapacity++;
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

/*
Internal Node Implementation
    */

InternalNode::InternalNode() {
    curCapacity = 0;
    maxCapacity = 3;
    isInternal = true;
}

void InternalNode::insertIndexPointerNode(std::shared_ptr<IndexPointerNode> indexPtrNode) {
    
    if (curCapacity > maxCapacity) {
        int copyIdx = floor(curCapacity / 2); 
        int copyVal = internalVec[copyIdx]->index;
        pushUp(indexPtrNode);

    } 

    for (auto it = internalVec.begin(); it < internalVec.end(); it++) {
        if (indexPtrNode->index < (*it)->index ) {
            internalVec.insert(it, indexPtrNode);
            curCapacity++;
            return;
        }
    }
    internalVec.push_back(indexPtrNode);
    curCapacity++;
}

void InternalNode::pushUp(std::shared_ptr<IndexPointerNode> indexPtrNode) {

    auto thisNode = getPtr();
    auto splitNode = std::make_shared<InternalNode>();
    std::shared_ptr<InternalNode> parentInternalNode = std::dynamic_pointer_cast<InternalNode>(thisNode->parentNode);

    if (parentInternalNode == nullptr) {
        // make new parent internal node 
        auto parentInternalNode = std::make_shared<InternalNode>();
        auto initIndexPointerNode = std::make_shared<IndexPointerNode>();
        initIndexPointerNode->index = 0;
        initIndexPointerNode->child = thisNode;
        parentInternalNode->insertIndexPointerNode(initIndexPointerNode);
    }
    
    thisNode->parentNode = parentInternalNode;
    splitNode->parentNode = parentInternalNode;

    //copy values into split node
    bool copy = false;
    for (auto it = thisNode->internalVec.begin(); it < thisNode->internalVec.end(); it++) { 
        if (copy) {
            splitNode->internalVec.push_back(*it);
            thisNode->internalVec.erase(it);
            splitNode->curCapacity++;
            continue;
        }
        if ((*it)->index == indexPtrNode->index) {
            copy = true;  
        }
    }

    /*
    //consider the pushed up index should be accessible through LHS pointer of split node
    auto pushedIndexPtrNode = std::make_shared<IndexPointerNode>();
    pushedIndexPtrNode->index = indexPtrNode->index;
    pushedIndexPtrNode->child = indexPtrNode->child;
    splitNode->internalVec.insert(internalVec.begin(), pushedIndexPtrNode);
    splitNode->curCapacity++;

    //create the new indexPointerNode that will be pushed into parent
    auto parentIndexPtrNode = std::make_shared<IndexPointerNode>();
    parentIndexPtrNode->index = indexPtrNode->index;
    parentIndexPtrNode->child = splitNode;
    parentInternalNode->insertIndexPointerNode(parentIndexPtrNode); 
    parentInternalNode->curCapacity++;
    */ 

    return;
}

void InternalNode::deleteIndex(int idx) {}

void InternalNode::printNode() {
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
}
/*
*/