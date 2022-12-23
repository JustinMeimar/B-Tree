#include "BTree.h"

#define GEN_RAND false
#define NUM_INSERTS 10

int main(int argc, char** argv) {

    std::shared_ptr<BTree> tree = std::make_shared<BTree>(BTree());
    tree->root = NULL;   
    tree->nodeCount++;
    
	
    srand((unsigned) time(NULL));
    int* inserts = (int*)malloc(sizeof(int) * NUM_INSERTS);
    
    #if GEN_RAND
    printf("Gen random inserts");  
    for (int i = 0; i < NUM_INSERTS; i++) {
        //gen random index 
        int random = (rand() % 99) + 1;
        
        //scan for duplicate 
        bool duplicate = false; 
        for (int j = 0; j < NUM_INSERTS; j++) {
            if (*(inserts + j) == random) {
                duplicate = true;
            }
        }
        if (duplicate) {
            i--;
            continue;
        }
        *(inserts + i) = random;
    }
    
    #endif 

    #if !GEN_RAND 
    int explicit_inserts[NUM_INSERTS] = {
        1,2,3,4,5,6,7,8,9,10
    };
    int explicit_inserts2[NUM_INSERTS] = {
        32, 84, 74, 44, 46, 25, 66, 11, 51, 82
    };
    for (int i = 0; i < NUM_INSERTS; i++) {
        inserts[i] = explicit_inserts[i];
    }
    #endif

    for (int i = 0; i < NUM_INSERTS; i++) {
        printf("\n\n---- INSERTING %d -----\n", inserts[i]);
        tree->insertIndex(inserts[i]);
        // tree->searchIndex(inserts[i], tree->root);
        if (i < 10) {
            tree->printTree(tree->root);
        }
    }

    free(inserts);



    /*
        printf("\n--------- INSERT %d -----------\n", random);
        tree->insertIndex(random); 
        // tree->searchIndex(random);
        tree->printTree(tree->root); 
        printf("\n\n"); 
    */
 
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