#include <stdio.h>
#include <stdlib.h>

/* Declare dynamic arrays/vectors and global variables*/
int *resource = NULL;
int *available = NULL;
int *max_claims = NULL;
int *allocation = NULL;
int *need = NULL;

int num_processes;
int num_resources;
 


/***********************************************************/
void PRINT_RESOURCE() {
    /* declare local variables */
    int i;
    printf("Resources:\n");
    /* for loop: print each resource index */
    for (i=0; i< num_resources; i++){
        printf("\tr%d", i);
    }
    printf("\n");
    /* for loop: print number of total units of each resource index */
    for (i=0; i< num_resources; i++){
        printf("\t%d", resource[i]);
    }
    printf("\n");
    return;
}


/***********************************************************/
void PRINT_AVAILABLE() {
    /* declare local variables */
    int i;
    printf("Available:\n");
    /* for loop: print each resource index */
    for (i=0; i< num_resources; i++){
        printf("\tr%d", i);
    }
    printf("\n");
    /* for loop: print number of available units of each resource index */
    for (i=0; i< num_resources; i++){
        printf("\t%d", available[i]);
    }
    printf("\n");
    return;
}


/***************************************************************/
void PRINT_MAX_CLAIM() {
    /* declare local variables */
    int i, j;
    printf("Max claim: \n");
    /* for loop: print each resource index */
    for (i=0; i< num_resources; i++){
        printf(" \tr%d", i);
    }
    printf("\n");
    /* for each process: */
    for (i=0; i< num_processes; i++){
        printf("p%d", i);
        /* for each resource: */
        for (j=0; j< num_resources; j++){
            /* print maximum number of units each process may request from each resource */
            printf("\t%d", max_claims[i * num_resources + j]);
          
        }
        printf("\n");
    }
    
    return;
}


/***************************************************************/
void print_allocated() {
    /* declare local variables */
    int i, j;
    printf("Allocated: \n");
    /* for loop: print each resource index */
    for (i=0; i< num_resources; i++){
        printf(" \tr%d", i);
    }
    printf("\n");
    /* for each process: */
    for (i=0; i< num_processes; i++){
        printf("p%d", i);
        /* for each resource: */
        for (j=0; j< num_resources; j++){
            /* print maximum number of units each process is allocated from each resource */
            printf("\t%d", allocation[i * num_resources + j]);
         
        }
        printf("\n");
    }
    return;
}

/***************************************************************/
void print_need() {
    /* declare local variables */
    int i, j;
    printf("Need: \n");
    /* for loop: print each resource index */
    for (i=0; i< num_resources; i++){
        printf(" \tr%d", i);
    }
    printf("\n");
    /* for each process: */
    for (i=0; i< num_processes; i++){
        printf("p%d", i);
        /* for each resource: */
        for (j=0; j< num_resources; j++){
            /* print number of units needed by each process from each resource */
            printf("\t%d", need[i * num_resources + j]);

        }
        printf("\n");
    }
    return;
}


/****************************************************************/
    void OPTION_1() {
        
      /* declare local variables */
      int i, j, units;
    
    
    /* prompt for number of processes and number of resources */
        printf("Enter number of processes: ");
        scanf("%d", &num_processes);
        printf("Enter number of resources: ");
        scanf("%d", &num_resources);
    /* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
    resource = (int *) malloc (num_resources * sizeof(int));
    available = (int *) malloc (num_resources * sizeof(int));
                                
    max_claims = (int *) malloc (num_processes * num_resources * sizeof(int));
    allocation = (int *) malloc (num_processes * num_resources * sizeof(int));
    need = (int *) malloc (num_processes * num_resources * sizeof(int));
    /* for each resource, prompt for number of units, set resource and available vectors indices*/
    /* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */
    printf("Enter number of units for resources (r0 to r%d): ",  num_resources-1);
    for (i=0; i< num_resources; i++){
        scanf("%d", &units);
        resource [i] = units;
        available [i] = units;
    }
    for (i=0; i< num_processes; i++){
        printf("Enter maximum number of units process p%d will request from each resource (r0 to r%d): ", i, num_resources-1);
        for (j=0; j< num_resources; j++){
                scanf("%d", &units);
                max_claims [i*num_resources+j] = units;
                need [i*num_resources+j] = units;
        }
    }
                        
    /* for each process, for each resource, prompt for number of resource units allocated to process */
                           
    for (i=0; i< num_processes; i++){
        printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: ", num_resources-1, i);
        for (j=0; j< num_resources; j++){
                scanf("%d", &units);
                allocation [i * num_resources + j] = units;
            available[j] -= units;
            need [i * num_resources + j] -= units;
        }
    }
    printf("\n");
    /* print resource vector, available vector, max_claim array, allocated array, need array */
    PRINT_RESOURCE();
        printf("\n");
    PRINT_AVAILABLE();
        printf("\n");
    PRINT_MAX_CLAIM();
        printf("\n");
    print_allocated();
        printf("\n");
    print_need();
        printf("\n");
    return;
}


/********************************************************************/
void OPTION_2() {

    /* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
        int i,j;
        int less_than;
        int num_sequenced = 0;
        int *safe = (int *) calloc (num_processes, sizeof(int));
       // int ....
        
        
    /* while not all processed are sequenced */
        while (num_sequenced < num_processes){
        /* for each process */
            for (i=0 ; i < num_processes ; i++) {
                
                
                less_than = 1;
            /* if process has not been safely sequenced yet */
                if (safe[i] == 0) {
                    printf("\n");
                    printf("Checking: < ");
                    for (j=0; j< num_resources; j++){
                        /* print number of units needed by each process from each resource */
                        printf("%d ",need[i * num_resources + j]);
                    }
                    printf("> <= < ");
                    for (j=0; j< num_resources; j++){
                        printf("%d ", available[j]);
                    }
                    printf("> ");
                /* for each resource */
                    for (j=0; j < num_resources; j++) {
                    /* check for safe sequencing by comparing process' need vector to available vector */
                        less_than = less_than & (need[i*num_resources+j] <= available [j]);
                    } /* For-Loop */
                    /* if each resource is available */
                    if (less_than ==1){
                        /* print message that process had been safely sequenced */
                        printf(":p%d safely sequenced", i);
                        for (j=0; j< num_resources; j++){
                            /* update number of available units of resource */
                            available[j] += allocation [i*num_resources+j];
                        /* for each resource free all resources allocated to process */
                        allocation [i*num_resources+j] = 0;
                        } /* For-Loop */
                        /* increment number of sequenced processes */
                        num_sequenced++;
                        safe[i] = 1;
                    } /* if-statement*/
                } /* if- statement*/
                // printf("\n");
            } /* For-Loop */
        } /* While-Loop */
return;
}


/********************************************************************/

void garbage_collection() {
    /* check if vectors/array are not NULL--if so, free each vector/array */
        if (resource != NULL){
            free(resource);
            free(available);
            free(max_claims);
            free(allocation);
            free(need);
        }
    return;
}


/***************************************************************/
int main() {

    /* Declare local variables */
    int choice = 0;
    /* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
        while (choice!=3) {
            printf("\n");
            printf("Banker's Algorithm\n");
            printf("------------------\n");
            printf("1) Enter parameters\n");
            printf("2) Determine safe sequence\n");
            printf("3) Quit program\n\n");
            printf("Enter selection: ");
            
            
        
            scanf("%d", &choice);
            // we can use if statement instead of switch

            switch(choice){
                case 1: OPTION_1();
                    break;
                case 2: OPTION_2();
                    break;
                case 3: garbage_collection();
                    break;
                default: printf("Invali Input!\n");
                    
             }
        }
  return 1;
}
