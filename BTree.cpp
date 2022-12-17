#include "BTree.h"

BTree::BTree() {}
BTree::~BTree() {}

void BTree::insertIndex(int idx) {
    auto leafNode = std::dynamic_pointer_cast<LeafNode>(root);
    if (leafNode != nullptr) {
        // check if the node is already full
        if (leafNode->curCapacity < leafNode->maxCapacity) { 
            leafNode->indexVec.push_back(idx);
            leafNode->curCapacity++;
        } else {
            //copy up
            int copyIdx = floor(leafNode->maxCapacity / 2);
            int copyVal = leafNode->indexVec[copyIdx];

            if (leafNode->parentNode == nullptr ) { // No internal node parent (must be onyl node in tree)
                //make new internal node and configure 
                std::shared_ptr<LeafNode> nextLeafNode = std::make_shared<LeafNode>(LeafNode(nodeCount));
                std::shared_ptr<InternalNode> internalNode = std::make_shared<InternalNode>(InternalNode(nodeCount + 1));

                internalNode->indexVec.push_back(copyVal); //index we copy up
                internalNode->nodeVec.push_back(leafNode); //pointer to the leafNode
                
                //remove leaf node values from [copyIdx:end]
                std::vector<unsigned int> nextIndexVec;
                int curIdx = leafNode->indexVec.size() - 1; //end of the vector
                while(curIdx >= copyIdx) {
                    int carryIdx = leafNode->indexVec[curIdx]; 
                    leafNode->indexVec.pop_back(); 
                    nextIndexVec.push_back(carryIdx);
                    curIdx--;
                }
                nextIndexVec.push_back(idx);
                nextLeafNode->indexVec = nextIndexVec;
                nextLeafNode->parentNode = internalNode; 
                internalNode->nodeVec.push_back(nextLeafNode);
                root = internalNode;
                nodeCount+=2;

                //show we made the right copy up 
                internalNode->printNode();
                leafNode->printNode();
                nextLeafNode->printNode();
            }
        }
        return;
    } else {
        std::cout << "\nroot node is internal node" << std::endl;
    }

    //search for index location
    auto internalNode = std::dynamic_pointer_cast<InternalNode>(root);
    int prevIdx = -1; 
    for (auto eIdx : internalNode->indexVec) {
        if (idx > prevIdx && idx < eIdx ) { 
            break;
        }
        prevIdx = eIdx;
    }
    std::cout << prevIdx << std::endl;
}

void BTree::printTree() {
    auto leafNode = std::dynamic_pointer_cast<LeafNode>(root);
    leafNode->printNode();
}