#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ROW_LENGTH = 9;
const int COLUMN_LENGTH = 9;
const int PUZZLE_LENGTH = ROW_LENGTH*COLUMN_LENGTH;
const int NUMBER_OF_BOXES = 9;
const int BOX_LENGTH;

void read_clues(int* clue_info, int num_clues) {
    for (int i=0; i<num_clues; i++) {
        if (scanf("%d %d %d", &clue_info[3*i], &clue_info[3*i+1], &clue_info[3*i+2]) != 3) {
            printf("error reading the clue info\n");
            exit(1);
        }
    }
}

bool check_board_is_valid(int* guesses) {
    printf("checking validity of rows\n");
    //check all rows are valid
    for (int row=0; row<ROW_LENGTH; row++) {
        printf("checking row %d\n", row);
        int counts[ROW_LENGTH] = { 0 };
        for (int col=0; col<COLUMN_LENGTH; col++) {
            int guess = guesses[row*ROW_LENGTH + col];
            if (guess != 0) {
                counts[guess-1]++;
            }
            if (counts[guess-1] > 1) {
                return false;
            }
        }
    }
    printf("all rows are valid\n");

    printf("checking validity of columns\n");
    //check all columns are valid
    for (int col=0; col<COLUMN_LENGTH; col++) {
        printf("checking column %d\n", col);
        int counts[COLUMN_LENGTH] = { 0 };
        for (int row=0; row<ROW_LENGTH; row++) {
            int guess = guesses[row*ROW_LENGTH + col];
            if (guess != -1) {
                counts[guess-1]++;
            }
            if (counts[guess-1] > 1) {
                return false;
            }
        }
    }
    printf("all columns are valid\n");

    printf("checking validity of boxs\n");
    //check all 3x3 box's are valid
    for (int box=0; box<NUMBER_OF_BOXES; box++) {
        printf("checking box %d\n", box);
        for (int row=0; row<BOX_LENGTH; row++) {
            int counts[NUMBER_OF_BOXES] = { 0 };
            for (int col=0; col<BOX_LENGTH; col++) {
                int guess = guesses[row*ROW_LENGTH + col];
                if (guess != -1) {
                    counts[guess-1]++;
                }
                if (counts[guess-1] > 1) {
                    return false;
                }
            }
        }
    }
    printf("all boxs are valid\n");

    return true;
}

int main() {
    int num_clues;
    if (scanf("%d", &num_clues) != 1) {
        printf("error reading the number of clues\n");
        return 1;
    } else {
        printf("succesfully scanned number of clues\n");
    }
    int clue_info[3*num_clues];
    printf("attempting to read all clue information\n");
    read_clues(clue_info, num_clues);
    printf("succesfully read in all clue information\n");

    //test check board
    printf("filling out board\n");
    int guesses[PUZZLE_LENGTH] = {0};
    for (int i=0; i<num_clues; i++) {
        int guess = clue_info[3*i];
        int row = clue_info[3*i+1];
        int col = clue_info[3*i+2];
        if (guess != 0) {
            guesses[row*ROW_LENGTH+col] = guess;
        }
    }
    printf("succesfully filled out board\n");

    printf("printing board...\n");
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            printf("%d ", guesses[row*ROW_LENGTH+col]);
        }
        printf("\n");
    }
    printf("succesfully print out board\n");

    printf("checking board validity\n");
    if (check_board_is_valid(guesses)) {
        printf("board is valid\n");
    }
    printf("board is invalid\n");

    return 0;
}