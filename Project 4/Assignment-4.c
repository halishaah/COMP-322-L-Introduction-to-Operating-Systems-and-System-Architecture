#include <stdio.h>
#include <stdlib.h>

// declare structure to store block information (id, starting address, ending address, link to next block)
// declare linked list to connect allocation blocks
struct node {
    int id;
    int start;
    int end;
    struct node *link;
} *block_list = NULL;
typedef struct node block_type;
// declare global variables
int pm_size;
int hole_algo;
int remaining;

/********************************************************************/
void OPTION_1() {
    
    // declare local variables (if any)
    // prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory
    printf("Enter size of physical memory: ");
    scanf("%d", &pm_size);
    printf("Enter hole-fitting algorithm (0=first fit, 1=best_fit): ");
    scanf("%d", &hole_algo);
    remaining = pm_size;
    // initilize linked list with "dummy" block of size 0, id=-1
    block_list = (block_type*)malloc (sizeof(block_type));
    block_list -> id = -1;
    block_list -> start = 0;
    block_list -> end = 0;
    block_list -> link = NULL;
    
    return;
}


/********************************************************************/
void PRINT_ALLOCATION_TABLE() {
    
    // declare local variables
    block_type *next_block = block_list -> link;
    //print header row with field names
    
    printf("ID    Start   End \n");
    printf("-------------------\n");
    while (next_block != NULL){
        // print table containing block id, starting address, ending address
        printf("%d",next_block->id);
        printf("    %d    ",next_block->start);
        printf("%d   \n",next_block->end);
        next_block = next_block -> link;
    }
    
    return;
}


/********************************************************************/
void OPTION_2() {
    
    // declare local variables
    int block_id;
    int block_size;
    block_type *new_block, *next_block, *best_block;
    int hole_start, hole_end, best_start, best_end;
 
    // initialize best hole so far to size of physical memory
    int best_hole = pm_size;
    // prompt for block id & block size
    printf("Enter block id: ");
    scanf("%d", &block_id);
    printf("Enter block size: ");
    scanf("%d", &block_size);
    // check if size of block is larger than remaining unallocated space, if so, return
    if (block_size > remaining){
        printf("******* IT IS OUT OF MEMORY, THE BLOCK IS TOO BIG ********");
        return;
    }
    // allocate space for new block and set id
    new_block = (block_type*)malloc (sizeof(block_type));
    new_block -> id = block_id;
    // if only "dummy" block exists, insert block at end of linked list, set fields, return
    if (block_list -> link == NULL){
        new_block -> start = block_list->end ;
        new_block->end = new_block -> start + block_size;
        new_block->link = NULL;
        block_list->link = new_block;
        PRINT_ALLOCATION_TABLE();
        return;
    }
        
    // else traverse list until either appropriate hole is found or the end of the list is reached
    else {
        next_block = block_list->link;
        while (next_block != NULL){
            // if id already exists, reject request and return
            if (next_block->id == new_block->id){
                printf("******* IT IS DUPLICARED ID ********");
                return;

            } //if
            next_block = next_block->link;
        }//while loop
        next_block = block_list->link;
        while (next_block != NULL){
            // set values for start and end of currently found hole
            hole_start = next_block->end;
            if(next_block->link ==NULL){
                hole_end = pm_size;
            }else{
                hole_end = next_block->link->start;
            }
            // if hole is large enough for block
            if (block_size <= (hole_end - hole_start)){
                // if first-fit algorithm
                if (hole_algo==0){
                    // set start & end fields of new block & add block into linked list
                    new_block->start = hole_start;
                    new_block->end = new_block->start+ block_size;
                    new_block->link = next_block->link;
                    next_block->link = new_block;
                    // reduce remaining available memory and return
                    remaining -= block_size;
                    PRINT_ALLOCATION_TABLE();
                    return;
                } //first_fit
                // else--best-fit algorithm
                else{
                    // if hole is smaller than best so far
                    if((hole_end - hole_start) < best_hole){
                        // set values of best start & best end & best hole size so far
                        // update best block & advance next block
                        best_hole = hole_end - hole_start;
                        best_start = hole_start;
                        best_end = hole_end;
                        best_block = next_block;
                    }//if best so far
                    
                } // best_fit
                
            }// if the block fit
            next_block = next_block->link;
        } // while-Loop
        // set start & end fields of new block & add block into linked list
        new_block->start = best_start;
        new_block->end = new_block->start+ block_size;
        new_block->link = best_block->link;
        best_block->link = new_block;
        // reduce remaining available memory and return
        remaining -= block_size;
    }// first else
    PRINT_ALLOCATION_TABLE();
    return;
}
    

/********************************************************************/
void OPTION_3() {
    
    // declare local variables
    int block_id;
    block_type *next_block = block_list->link;
    block_type *prev_block;
    
    // prompt for block id
    printf("Enter block id: ");
    scanf("%d", &block_id);
    
    // until end of linked list is reached or block id is found
    while((next_block != NULL) && (next_block->id != block_id)){
        // traverse list
        prev_block = next_block;
        next_block = next_block->link;
    }
    
    // if end of linked list reached, print block id not found
    if ( next_block == NULL ){
        printf("****** THE BLOCK IS NOT FOUND *********");
    }
    // else remove block and deallocate memory
    else {
        prev_block->link = next_block->link;
        remaining += (next_block->end - next_block->start);
        free(next_block);
    }
    PRINT_ALLOCATION_TABLE();
    return;
}


/********************************************************************/
void OPTION_4() {
    // declare local variables
    block_type *next_block;
    next_block = block_list->link;
    int next_size;
    int prev_end = 0;

    // until end of list is reached
    while (next_block != NULL ) {
        // calculate current hole size
        // adjust start & end fields of current block to eliminate hole
        next_size = next_block->end - next_block->start;
        next_block->start = prev_end;
        next_block->end = next_block->start + next_size;
        prev_end = next_block->end ;
        next_block = next_block->link;
    }
    PRINT_ALLOCATION_TABLE();
    return;
}


/********************************************************************/
void garbage_collectio(block_type *node) {
    
    // if node is NULL, return
    if(node == NULL)
        return;
    // else
    else
        //recursively call procedure on node->link
        garbage_collectio(node->link);
        // deallocate memory from node
    free(node);
    return;
}


/***************************************************************/
int main() {

    /* Declare local variables */
    int choice = 0;
    /* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
        while (choice!=5) {
            printf("\n");
            printf("Memory allocation\n");
            printf("-----------------\n");
            printf("1) Enter parameters\n");
            printf("2) Allocate memory for block\n");
            printf("3) Deallocate memory for block\n");
            printf("4) Defragment memory\n");
            printf("5) Quit program\n\n");
            printf("Enter selection: ");
            
            
        
            scanf("%d", &choice);
            // we can use if statement instead of switch

            switch(choice){
                case 1: OPTION_1();
                    break;
                case 2: OPTION_2();
                    break;
                case 3: OPTION_3();
                    break;
                case 4: OPTION_4();
                    break;
                case 5: return 0;
                    break;
             
                default: printf("Invali Input!\n");
                    
             }
        }
  return 1;
}
