#include "BTree.h"

int main() {

    std::shared_ptr<BTree> tree = std::make_shared<BTree>(BTree());
    tree->root = NULL;   
    tree->nodeCount++;

	srand((unsigned) time(NULL));

	// Get a random number
    
    for (int i = 0; i < 8; i++) {\
        int random = (rand() % 36);
        printf("\n--------- INSERT %d -----------\n", random);
        tree->insertIndex(random); 
        tree->printTree(tree->root); 
        printf("\n\n"); 
        // std::cout << random<< std::endl;
    }

	// Print the random number

    /* //working testcase
    tree->insertIndex(20);  
    tree->insertIndex(40); 
    tree->insertIndex(5);
    tree->insertIndex(25);
    tree->insertIndex(6); 
    tree->insertIndex(10);
    tree->insertIndex(12);
    tree->insertIndex(19);
    tree->insertIndex(15);
    tree->insertIndex(7);
    tree->insertIndex(8);
    tree->insertIndex(9);
    
    tree->printTree(tree->root);
    tree->searchIndex(19, tree->root); 
    // tree->searchIndex(99, tree->root); 
    */ 

    return 0;
}