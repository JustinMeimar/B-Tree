#include "BTree.h"

int main() {

    std::shared_ptr<BTree> tree = std::make_shared<BTree>(BTree());
    tree->root = NULL;   
    tree->nodeCount++;

   
    tree->insertIndex(20);  
    // tree->printTree(tree->root);

    tree->insertIndex(40); 
    // tree->printTree(tree->root);
    
    tree->insertIndex(5);
    // tree->printTree(tree->root);
 
    tree->insertIndex(25);
    // tree->printTree(tree->root);
    /*
     
    tree->insertIndex(17); 
    // tree->printTree(tree->root);
    
    tree->insertIndex(10);
    // tree->printTree(tree->root);
    
    tree->insertIndex(12);
    // tree->printTree(tree->root);
    
    tree->insertIndex(19);
    // tree->printTree(tree->root);
    
    tree->insertIndex(15);
    tree->printTree(tree->root);
    
    */ 
    /*
    
    tree->insertIndex(19);
    tree->printTree(tree->root);
    */ 
 
    /*
    
    std::cout << "-----------" << std::endl;
    tree->insertIndex(6);
    std::cout << "\n-----------" << std::endl;
    */


    return 0;
}