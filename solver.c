#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ROW_LENGTH = 9;
const int COLUMN_LENGTH = 9;
const int PUZZLE_LENGTH = ROW_LENGTH*COLUMN_LENGTH;
const int NUMBER_OF_BOXES = 9;
const int BOX_LENGTH;

void read_clues(int* guesses, int* clue_indices, int* num_clues) {

    *num_clues = 0;
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            if (scanf("%d", &guesses[row*ROW_LENGTH+col]) != 1) {
                printf("error reading clue at position (row, col) = %d, %d", row, col);
                exit(1);
            }
            if (guesses[row*ROW_LENGTH+col] != 0) {
                clue_indices[*num_clues] =  row*ROW_LENGTH+col;
                *num_clues++;
            }
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
                counts[guess-1]++;
                if (counts[guess-1] > 1) {
                    return false;
                }
            }
        }
    }

    //check all columns are valid
    for (int col=0; col<COLUMN_LENGTH; col++) {
        int counts[COLUMN_LENGTH] = { 0 };
        for (int row=0; row<ROW_LENGTH; row++) {
            int guess = guesses[row*ROW_LENGTH + col];
            if (guess != 0) {
                counts[guess-1]++;
                if (counts[guess-1] > 1) {
                    return false;
                }
            }
        }
    }

    //check all 3x3 boxes are valid
    for (int box=0; box<NUMBER_OF_BOXES; box++) {
        for (int row=0; row<BOX_LENGTH; row++) {
            int counts[NUMBER_OF_BOXES] = { 0 };
            for (int col=0; col<BOX_LENGTH; col++) {
                int guess = guesses[row*ROW_LENGTH + col];
                if (guess != 0) {
                    counts[guess-1]++;
                    if (counts[guess-1] > 1) {
                        return false;
                    }
                }
            }
        }
    }

    return true;

}

bool check_row_is_valid(int* row) {

    int counts[NUMBER_OF_BOXES] = { 0 };
    for (int i=0; i<ROW_LENGTH; i++) {
        int guess = row[i];
        if (guess != 0) {
            counts[guess-1]++;
            if (counts[guess-1] > 1) {
                return false;
            }
        }
    }

}

void print_board(int* guesses) {
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            printf("%d ", guesses[row*ROW_LENGTH+col]);
        }
        printf("\n");
    }
}

int main() {
    int guesses[PUZZLE_LENGTH];
    int num_clues;
    int clue_indices[PUZZLE_LENGTH];
    read_clues(guesses, clue_indices, num_clues);

    return 0;
}