#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

class Node {
    public: 
        bool isLeaf = false;
        bool isInternal = false;
        unsigned int curCapacity;
        unsigned int maxCapacity;
        int nodeNumber;
        std::shared_ptr<Node> parentNode;
        
        Node();
        ~Node();
        virtual void insertIndex(int idx) = 0; 
        virtual void deleteIndex(int idx) = 0;
        virtual void printNode() = 0;
        
};

class LeafNode : public Node, public std::enable_shared_from_this<LeafNode> {
    public:
        //static members  
        std::vector<unsigned int> indexVec;

        //methods 
        LeafNode();
        LeafNode(int nodeCount); 
        std::shared_ptr<LeafNode> getPtr() { //get shared_ptr to this
            return shared_from_this();
        }

        void insertIndexHelper(int idx);
        void copyUp(int idx);
        void insertIndex(int idx) override; 
        void deleteIndex(int idx) override; 
        void printNode() override;
};

typedef struct index_with_pointer {
    int index;
    std::shared_ptr<Node> child; //node with indexes >= index
} IndexPointerNode;


class InternalNode : public Node, public std::enable_shared_from_this<InternalNode> {
    public:
        //static members
        std::vector<std::shared_ptr<Node>> nodeVec; //size of n + 1
        std::vector<std::shared_ptr<IndexPointerNode>> internalVec;

        //methods
        InternalNode();
        InternalNode(int nodeCount);
        std::shared_ptr<InternalNode> getPtr() { //get shared_ptr to this
            return shared_from_this();
        }

        void insertIndexPointerNode(std::shared_ptr<IndexPointerNode> indexPtrNode);
        void pushUp(std::shared_ptr<IndexPointerNode> indexPtrNode);
        void insertIndex(int idx) {}
        void deleteIndex(int idx) override;
        void printNode() override;
};


/*
*/