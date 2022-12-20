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
        std::vector<unsigned int> indexVec;
        
        Node();
        ~Node();
        virtual void insertIndex(int idx) = 0; 
        virtual void deleteIndex(int idx) = 0;
        virtual void printNode() = 0;
        
        void insertIndexHelper(int idx);
};

class LeafNode : public Node, public std::enable_shared_from_this<LeafNode> {
    public:
        //static members  
        std::shared_ptr<Node> parentNode;

        //methods 
        LeafNode();
        LeafNode(int nodeCount); 
        std::shared_ptr<LeafNode> getPtr() { //get shared_ptr to this
            return shared_from_this();
        }

        void copyUp(int idx);
        void insertIndex(int idx) override; 
        void deleteIndex(int idx) override; 
        void printNode() override;
};

typedef struct index_with_pointer {
    int index;
    std::shared_ptr<Node> child; //node with indexes >= index
} IndexPointerNode;


class InternalNode : public Node {
    public:
        //static members
        std::shared_ptr<Node> parentNode;
        std::vector<std::shared_ptr<Node>> nodeVec; //size of n + 1
        std::vector<IndexPointerNode> internalVec;

        //methods
        InternalNode();
        InternalNode(int nodeCount);

        void insertNodePtr(std::shared_ptr<Node> node, int nodeVal); 
        void pushUp(int idx);
        void insertIndex(int idx) override; 
        void deleteIndex(int idx) override;
        void printNode() override;
};


/*
*/