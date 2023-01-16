#include <stdio.h>
#include <stdlib.h>

/* Declare global variables & struct to hold process scheduling information */
struct node {
    int id;
    int arrival;
    int total_cpu;
    int done;
    int start;
    int end;
    int turnaround;
    int sort_field;
}
*sched_table = NULL;
typedef struct node table_type;
int num_processes;


/***************************************************************/
void print_table(table_type *table) {
    //choose which table to print:
    //table_type *print_table(table_type *table)
    // void print_table (table_type *table)

    /* Declare local variables */
    int i;
    
    // print top row of the table containing field name
    printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
    printf("--------------------------------------------\n");

    /* Print valid contents of each row in a for-loop */
    for (i=0; i< num_processes ;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\n", sched_table[i].id, sched_table[i].arrival, sched_table[i].total_cpu, sched_table[i].start, sched_table[i].end, sched_table[i].turnaround);
    }
    

    return;
}


/***************************************************************/
void option1() {

    /* Declare local variables */
    int i;
    
    
    /* Prompt for total number of processes */
    printf("Enter total number of processes: ");
    scanf("%d", &num_processes);
    
    /* Allocate memory for schedule table */
    sched_table = (table_type*) calloc (num_processes, sizeof (table_type));
    /* For each process */
    for (i=0; i< num_processes ; i++){
    
        // ****with the calloc we can omit y=this initialization*****
       /*
        sched_table[i].done = 0;
        sched_table[i].start = 0;
        sched_table[i].end = 0;
        sched_table[i].turnaround = 0;
        */
      

        /*  Prompt for process id, arrival time, and total CPU time */
        printf("Enter process id: ");
        scanf ("%d", &sched_table[i].id);
        
        printf("Enter arrival time for process P[%d]: ", sched_table[i].id);
        scanf ("%d", &sched_table[i].arrival);
        
        printf("Enter total CPU time for process P[%d]: ",sched_table[i].id );
        scanf ("%d", &sched_table[i].total_cpu);
        
    }
    
        
    /* Print table contents */
    print_table(sched_table);
    
    return;
}


/***************************************************************/
table_type * sort_table(table_type *table) {
    
    /* Declare local variables */
    int i,j;
    table_type temp;
    
    /* Sort rows of table in increasing order based on formal parameter using some sorting algorithm */
    for (i=0; i<num_processes-1; i++){
        for (j=i+1; j<num_processes; j++){
            if(table[i].sort_field > table[j].sort_field){
                temp = table[i];
                table[i]= table[j];
                table[j] = temp;
            }
        }
    }

    return table;
}


/***************************************************************/
void FIFO() {

    /* Declare local variables */
    int i;
    table_type *sorted_table;
    
    /* Allocate memory for copy of table for sorting */
    sorted_table = calloc (num_processes ,sizeof(table_type));
    
    /* For each row in table, set sorting field to arrival field  */
    for (i=0; i<num_processes; i++){
        sched_table[i].sort_field = sched_table[i].arrival;
    }

    /* Call "sort" function on original table and assign to table copy */
    sorted_table  = sort_table(sched_table);
    
    /* Set field values for index 0 of sorted table based on user input values */
    sorted_table[0].start =  sorted_table[0].arrival;
    sorted_table[0].end =  sorted_table[0].total_cpu + sorted_table[0].start;
    sorted_table[0].turnaround = sorted_table[0].total_cpu ;
    // sorted_table[0].turnaround = sorted_table[0].total_cpu + sorted_table[0].start - sorted_table[0].arrival ;
    

    /* For each additional row of sorted table, set fields appropriately */
    for (i=1; i<num_processes; i++){
        if (sorted_table[i].arrival > sorted_table[i-1].end){
            sorted_table[i].start = sorted_table[i].arrival;
        } else{
            sorted_table[i].start = sorted_table[i-1].end;
        }
        sorted_table[i].end =  sorted_table[i].total_cpu + sorted_table[i].start;
        sorted_table[i].turnaround = sorted_table[i].total_cpu + sorted_table[i].start - sorted_table[i].arrival ;
        
    }
    /* Print sorted table */
    print_table (sorted_table);
    //free(sorted_table);
    
    return;
}


/***************************************************************/
void SJF() {
    
    /* Declare local variables */
    int i;
    table_type *sorted_table;
    int num_processed = 0;
    int current_cycle = 0;
    int atleast_one;
    
    /* Allocate memory for copy of table for sorting */
    sorted_table = (table_type*) malloc (num_processes * sizeof(table_type));
    
    /* For each row in table, set sorting field to total CPU field, initialize other fields appropriately */
    for (i=0; i<num_processes; i++){
        sched_table[i].sort_field = sched_table[i].total_cpu;
    }
        
    /* Call "sort" function on original table and assign to table copy */
    sorted_table = sort_table(sched_table);

    /* Loop until all processes have been scheduled */
    while (num_processed < num_processes){
        atleast_one = 0;

        /* For each process */
        for (i=0; i<num_processes; i++){

            /* If not already scheduled and arrival time is <= current cycle */
            if (!sorted_table[i].done && (sorted_table[i].arrival <= current_cycle)){
                atleast_one = 1;
                sorted_table[i].done = 1;
                /* Set sorted table fields appropiately */
                sorted_table[i].start = current_cycle; //based on the current cycle
                sorted_table[i].end =  sorted_table[i].total_cpu + sorted_table[i].start;
                sorted_table[i].turnaround = sorted_table[i].total_cpu + sorted_table[i].start - sorted_table[i].arrival ;
        
                /* Update current cycle and increment number of processes completed */
                current_cycle = sorted_table[i].end;
                num_processed++;
            }
        }
        if (atleast_one == 0)
            current_cycle++;
    }
    /* Print and free sorted table */
    print_table (sorted_table);
    //free(sorted_table);
    return;
}


/***************************************************************/
void quit() {

    /* If the table is not NULL, free the memory */
    if (sched_table != NULL){
        free(sched_table);
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
        printf("Batch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Quit program and free memory\n\n");
        printf("Enter selection: ");
        
        
        scanf("%d", &choice);
        // we can use if statement instead of switch

        switch(choice){
            case 1: option1();
                break;
            case 2: FIFO();
                break;
            case 3:SJF();
                break;
            case 4: quit();
                break;
            default: printf("Invali Input!\n");
                
         }
    }
  return 1;
}

   
