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
    //check all rows are valid
    for (int row=0; row<ROW_LENGTH; row++) {
        int counts[ROW_LENGTH] = { 0 };
        for (int col=0; col<COLUMN_LENGTH; col++) {
            int guess = guesses[row*ROW_LENGTH + col];
            if (guess != 0) {
                counts[guess]++;
            }
            if (counts[guess] > 1) {
                return false;
            }
        }
    }

    //check all columns are valid
    for (int col=0; col<COLUMN_LENGTH; col++) {
        int counts[COLUMN_LENGTH] = { 0 };
        for (int row=0; row<ROW_LENGTH; row++) {
            int guess = guesses[row*ROW_LENGTH + col];
            if (guess != -1) {
                counts[guess]++;
            }
            if (counts[guess] > 1) {
                return false;
            }
        }
    }

    //check all 3x3 box's are valid
    for (int box=0; box<NUMBER_OF_BOXES; box++) {
        for (int row=0; row<BOX_LENGTH; row++) {
            int counts[NUMBER_OF_BOXES] = { 0 };
            for (int col=0; col<BOX_LENGTH; col++) {
                int guess = guesses[row*ROW_LENGTH + col];
                if (guess != -1) {
                    counts[guess]++;
                }
                if (counts[guess] > 1) {
                    return false;
                }
            }
        }
    }

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
    int guesses[PUZZLE_LENGTH];
    for (int i=0; i<num_clues; i++) {
        int guess = clue_info[3*i];
        int row = clue_info[3*i+1];
        int col = clue_info[3*i+2];
        if (guess != 0) {
            guesses[row*ROW_LENGTH+col] = guess;
        } else {
            guesses[row*ROW_LENGTH+col] = 0;
        }
    }
    printf("succesfully print out board\n");

    printf("checking board validity\n");
    if (check_board_is_valid(guesses)) {
        printf("board is valid\n");
    }
    printf("board is invalid\n");

    return 0;
}