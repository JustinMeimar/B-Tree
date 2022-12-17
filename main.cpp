#include "BTree.h"

int main() {

    std::shared_ptr<BTree> tree = std::make_shared<BTree>(BTree());
    std::shared_ptr<LeafNode> root = std::make_shared<LeafNode>(LeafNode(0));
    root->parentNode = nullptr;
    tree->root = root;   
    tree->nodeCount++;

    tree->insertIndex(3);
    tree->insertIndex(17);
    tree->insertIndex(7);
    tree->insertIndex(5);


    tree->insertIndex(14);

    return 0;
}