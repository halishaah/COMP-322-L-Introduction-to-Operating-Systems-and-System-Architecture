#include <stdio.h>
#include <stdlib.h>

// declare global variables, including dynamic array of integers to store sequence of tracks
int *sequence = NULL;
int num_tracks;
int sequence_size;


/*******************************************/
void OPTION_1() {
    // prompt for number of concentric tracks and size of sequence
    printf("Enter number of concentric tracks: ");
    scanf("%d", &num_tracks);
    printf("Enter size of sequence: ");
    scanf("%d", &sequence_size);
    
    // allocate memory for sequence dynamic array
    sequence = (int*) malloc (sequence_size * sizeof(int));
    
    return;
}


/*******************************************/
void PROCEDURE_FIFO() {
    // declare local variables
    int num_traversed;

    // for-loop: prompt for each track in sequence
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequence_size; i++){
        scanf("%d", &sequence[i]);
        
        // if track is out of range (<0 or > number of tracks, printe message and return
        if( sequence[i] < 0 || sequence[i] > num_tracks){
            printf("it is out of range");
            return;
        }
    }
    
    // initilize number of traversed tracks to first track in sequence
    printf("\nTraversed sequence: %d", sequence[0]);
    num_traversed = sequence[0];
    // for loop:
    for (int i = 1; i < sequence_size; i++){
        // update nummber of trversed tracks based on absolute value of difference between adjacent indices in sequence
        num_traversed += abs(sequence[i] - sequence[i-1]);
        // print traversed sequence indexed value
        printf(" %d", sequence[i]);
    }
    printf("\n");
    
    // print number of traversed tracks
    printf("The number of tracks traversed is: %d\n\n", num_traversed);
    return;
}
    
    
/*******************************************/
void PROCEDURE_SSTF() {
    // declare local variables
    int *sorted = NULL;
    int i,j, temp;
    int num_moves;
    int total_delay = 0;
    int longest_delay = 0;
    int longest_track = 0;
    int num_traversed;
    int average_delay;
    int num_tracks_moved=0;

    // for-loop: prompt for each track in sequence
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequence_size; i++){
        scanf("%d", &sequence[i]);
        
        // if track is out of range (<0 or > number of tracks, printe message and return
        if( sequence[i] < 0 || sequence[i] > num_tracks){
            printf("it is out of range");
            return;
        }
    }
    
    // allocate memory for sorted sequence dynamic array & initialize to original sequence
    sorted = (int*) malloc (sequence_size * sizeof(int));
    for (int i = 0; i < sequence_size; i++){
        sorted [i] = sequence [i];
    }
    
    // sort elements in increasing order using a sorting algorithm (Selection sort, etc.)
    
    for (i=0; i<sequence_size-1; i++){
        for (j=i+1; j<sequence_size; j++){
            if(sorted[i] > sorted[j]){
                temp = sorted[i];
                sorted[i]= sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    // for-loop:
    for (i=0; i<sequence_size-1; i++){
        num_moves = 0;
        j = i+1;
        while((sequence[i] != sorted[j]) && (j < sequence_size)){
            j++;
        }
        // calculate delays based on difference between track position in sorted array and original array
        if (j < sequence_size){
            num_moves = j - i;
            total_delay += num_moves;
            num_tracks_moved += 1;
            // update value of longest delay & associated track if number of moved positions is greater than current longest delay
            if (num_moves > longest_delay){
                longest_delay = num_moves;
                longest_track = sequence [i];
                
            }
        }
    }
    
    // initilize number of traversed tracks to first track in sequence
    printf("\nTraversed sequence: %d", sorted[0]);
    num_traversed = sorted [0];
    // for loop:
    for (int i = 1; i < sequence_size; i++){
        // update nummber of trversed tracks based on difference between adjacent indices in sorted array
        num_traversed += sorted[i] - sorted[i-1];
        // print traversed sequence
        printf(" %d", sorted[i]);
    }
    printf(" \n");
    
    // print number of traversed tracks
    printf("The number of tracks traversed is: %d\n", num_traversed);
    
    // calculate and print average_delay
    average_delay = total_delay / num_tracks_moved;
    printf("The average delay of all tracks processed later is: %d \n", average_delay);
    
    // print longest delay and associated track
    printf("The longest delay experienced by a track is: %d by track %d\n\n", longest_delay, longest_track);
    free(sorted);

    return;
}

/***************************************************************/
void GARBAGE_COLLECTION() {
    // if sequence is not NULL, free sequence
    if (sequence != NULL){
           free(sequence);
       }
       printf("Quitting program...\n\n");
    return;
}


/***************************************************************/
int main() {
    /* Declare local variables */
        int choice = 0;
        /* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
        while (choice!=4) {
            printf("Disk scheduling\n");
            printf("----------------\n");
            printf("1) Enter parameters\n");
            printf("2) Schedule disk tracks with FIFO\n");
            printf("3) Schedule disk tracks with SSTF\n");
            printf("4) Quit program and free memory\n\n");
            printf("Enter selection: ");
            
            
            scanf("%d", &choice);
            // we can use if statement instead of switch

            switch(choice){
                case 1: OPTION_1();
                    break;
                case 2: PROCEDURE_FIFO();
                    break;
                case 3:PROCEDURE_SSTF();
                    break;
                case 4: GARBAGE_COLLECTION() ;
                    break;
                default: printf("Invali Input!\n");
                    
             }
        }
    return 1;
}
