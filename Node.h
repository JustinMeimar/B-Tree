#include <iostream>
#include <memory>
#include <vector>

class Node {
    public: 
        bool isLeaf, isInternal;
        unsigned int curCapacity;
        unsigned int maxCapacity;
        int nodeNumber; 
        Node();
        ~Node();
        virtual void insertIndex() = 0; 
        virtual void deleteIndex() = 0;
        virtual void printNode() = 0;
};

class LeafNode : public Node {
    public:
        //static members 
        bool isLeaf = true;
        bool isInternal = false;
        std::vector<unsigned int> indexVec;
        std::shared_ptr<Node> parentNode;

        //methods 
        LeafNode();
        LeafNode(int nodeCount);
        void insertIndex() override; 
        void deleteIndex() override; 
        void printNode() override;
};

class InternalNode : public Node {
    public:
        //static members
        bool isInternal = true;
        bool isLeaf = false;
        std::vector<std::shared_ptr<Node>> nodeVec; //size of n + 1
        std::vector<unsigned int> indexVec;         //size of n

        //methods
        InternalNode();
        InternalNode(int nodeCount);
        void insertIndex() override; 
        void deleteIndex() override;
        void printNode() override;
};
/*
*/