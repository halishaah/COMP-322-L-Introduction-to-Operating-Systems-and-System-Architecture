#include <stdio.h>
#include <stdlib.h>

/* Define structures (complex data type) and global variables*/
struct node {
    int parent ;
    int first_child;
    int older_sibling;
    int younger_sibling;
}
*pcb = NULL; // pcb variable to point to the strcture
int num_processes;
typedef struct node pcb_type;


/***************************************************************/
void option() {

    /* Declare local variables */
    int i;
    
    /* Prompt for maximum number of processes */
    printf("Enter The Maximum Number Of Processes: ");
    scanf("%d", &num_processes);
    
    /* check id dynamic array already exists--if so deallocate it before creating new one*/
    if (pcb != NULL){
        free(pcb);
    }

    /* Allocate memmory for dynamic array of PCB's */
    pcb = (pcb_type * )malloc(num_processes *  sizeof(pcb_type));

    /* Initialize PCB[0] */
    pcb[0].parent = 0;
    pcb[0].first_child = -1;
    pcb[0].older_sibling = -1;
    pcb[0].younger_sibling = -1;
  
    /* Intitialize all other PCBs' parent, first_child, younger_sibiling, older_sibling */
    for (i=1; i<num_processes; i++){
        pcb[i].parent = -1;
        pcb[i].first_child = -1;
        pcb[i].older_sibling = -1;
        pcb[i].younger_sibling = -1;
        
    }/* for-Loop */

  return;
}


/***************************************************************/
void printTable() {

    /* Declare local variables */
    int i;
    
    /* For each existing PCB, print valid fields */
    printf("\ni\tParent\tFirst\tOlder\tYounger\n");
      printf("-----------------------------------------\n");
    for (i=0; i< num_processes; i++){
        if (pcb[i].parent != -1){
            printf("%d", i);
            printf("\t%d", pcb[i].parent);
        }
        else
            printf("\t");
        if (pcb[i].first_child != -1)
            printf("\t%d", pcb[i].first_child);
        else
            printf("\t");
        if (pcb[i].older_sibling != -1)
            printf("\t%d", pcb[i].older_sibling);
        else
            printf("\t");
        if (pcb[i].younger_sibling != -1)
            printf("\t%d", pcb[i].younger_sibling);
        else
            printf("\t");
        printf("\n");
    } /* for-Loop */
    
  return;
}


/***************************************************************/
void create() {
  
    /* Declare local variables */
    int p;
    int q=1;
    int next_child = 0;
    int num_children=0;
    /* Prompt for the parent PCB index */
    printf( "Enter the parent process index: ");
    scanf("%d", &p);
    
    /* Search for the next unused PCB index q */
    while (pcb[q].parent != -1 ){
        q++;
    } /* while-Loop */
  
    /* Record the parent PCB index p in PCB[q] */
    pcb[q].parent = p;
    /* Initialize the first_child & younger_sibling of PCB[q] to -1, everything already is -1, so there is need to do anything  */

    /* Check if parent PCB p has no first child--is so, set fields appropriately */
    if (pcb[p].first_child == -1){
        pcb[p].first_child = q;
        num_children = 1;
    } /* if */
    /* Else, search for appropriate available spot for next child, set fields appropriately */
    else {
        num_children = 2;
        next_child = pcb[p].first_child;
        while(pcb[next_child].younger_sibling != -1){
            next_child = pcb[next_child].younger_sibling;
            num_children++;
        } /* while-Loop */
        pcb[q].older_sibling = next_child;
        pcb[next_child].younger_sibling = q;
        
    } /* else */
        
    
    
    /* Print message indicating the creation of the ith child of process p at q */
    printf("cr[%d]: \tcreates the %dth child of process PCB[%d] at PCB[%d]\n",p, num_children, p,q );
    /* NOTE: do not use the letters i,p,q directly in the print statement, but the values of each variable */
   
    /* Print PCB table */
    printTable();
  return;
}


/***************************************************************/
void destroyh(int q) {

    /* If the formal parameter is -1, return */
    if (q == -1)
        return;
    // Else:
    else {
     
        //Call this procedure (itself) on the current PCB's younger sibling
        destroyh(pcb[q].younger_sibling);
        //Call this procedure on the current PCB's first child
        destroyh(pcb[q].first_child);
       // Set all fields to invalid
        printf( "PCB[%d]\t",q);
        pcb[q].parent = -1;
        pcb[q].first_child = -1;
        pcb[q].older_sibling = -1;
        pcb[q].younger_sibling = -1;
       // Print current PCB to be destroyed
    } /* else  */
    
  return;
}


/***************************************************************/
void destroy() {
  
    /* Declare local variables */
    int p;
    
    /* Prompt for the parent PCB index p*/
    printf( "Enter the process whose descendants are to be destroyed: ");
    scanf("%d", &p);
    /* Print message indicating the destruction of the descendants of PCB[p] */
    printf("de[%d]: \tdestroys all descendants of PCB[%d] which includes: \n", p, p);
    /* Call recursive procedure on PCB[p]'s first child */
    destroyh(pcb[p].first_child );
    
    /* recursive ended  */
    /* Set PCB[p]'s first child to invalid */
    pcb[p].first_child = -1;
   
    
    /* Print PCB table */
    printTable();
  return;
}


/***************************************************************/
void quit() {

    /* If the dynamic array "PCB" is not NULL, free the memory */
    if (pcb != NULL){
        free(pcb);
    }
    printf("Quitting program\n");

  return;
}


/***************************************************************/
int main() {

    /* Declare local variables */
    int choice = 0;
    /* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
    while (choice!=4) {
        printf("Process creation and destruction\n");
        printf("--------------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of a process\n");
        printf("4) Quit program and free memory\n\n");
        printf("Enter selection: ");
        
        
    scanf("%d", &choice);
    // we can use if statement instead of switch

        switch(choice){
            case 1: option();
                break;
            case 2: create();
                break;
            case 3:destroy();
                break;
            case 4: quit();
                break;
            default: printf("Invali Input!\n");
                
         }
    }

  return 1;
}

