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

bool check_guesses_are_valid(int* guesses) {

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

void print_board(int* guesses) {
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            printf("%d ", guesses[row*ROW_LENGTH+col]);
        }
        printf("\n");
    }
}

bool check_index_is_clue(int index, int* clue_indices, int num_clues) {
    for (int i=0; i<num_clues; i++) {
        return true;
    }
    return false;
}

bool solve_puzle(int* guesses, int num_clues, int* clue_indices) {

    int curr_index = 0;
    int max_iter = 100000;
    while (max_iter-- >= 0) {

        if (check_index_is_clue(curr_index, num_clues, clue_indices)) {
            curr_index++
        }

        // Check if the sudoku is invalid (Can't be solved)
        // If curr_index is -1, it has traversed every state and did not find a solution.
        if (curr_index == -1) {
            return false;
        }

        // Check if the sudoku is solved.
        // First check if the curr_index is at the last position on the board.
        // Then check if the last position has a guess (not zero)
        // Then finally, checks if the puzzle is valid. (If so a solution has been found)
        if ((curr_index == PUZZLE_LENGTH) & (guesses[curr_index] != 0)) {
            if (check_guesses_are_valid(guesses)) {
                return true;
            }
        }

        if (check_guesses_are_valid(guesses)) {
            curr_index++;
        }
    }

}

int main() {
    int guesses[PUZZLE_LENGTH];
    int num_clues;
    int clue_indices[PUZZLE_LENGTH];
    read_clues(guesses, clue_indices, num_clues);

    if (solve_puzzle(guesses, num_clues, clue_indices)) {
        print_board(guesses);
    } else {
        printf("Puzzle is invalid (Can't be solved)\n");
    }

    return 0;
}