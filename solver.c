#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ROW_LENGTH = 9;
const int COLUMN_LENGTH = 9;
const int PUZZLE_LENGTH = ROW_LENGTH*COLUMN_LENGTH;
const int NUMBER_OF_BOXES = 9;
const int BOX_LENGTH;

void read_clues(int* puzzle, int* clue_indices, int* num_clues) {

    *num_clues = 0;
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            if (scanf("%d", &puzzle[row*ROW_LENGTH+col]) != 1) {
                printf("error reading clue at position (row, col) = %d, %d", row, col);
                exit(1);
            }
            if (puzzle[row*ROW_LENGTH+col] != 0) {
                clue_indices[*num_clues] =  row*ROW_LENGTH+col;
                (*num_clues)++;
            }
        }
    }

}

bool check_guesses_are_valid(int* puzzle) {

    //check all rows are valid
    for (int row=0; row<ROW_LENGTH; row++) {
        int counts[ROW_LENGTH] = { 0 };
        for (int col=0; col<COLUMN_LENGTH; col++) {
            int guess = puzzle[row*ROW_LENGTH + col];
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
            int guess = puzzle[row*ROW_LENGTH + col];
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
                int guess = puzzle[row*ROW_LENGTH + col];
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

void print_board(int* puzzle) {
    for (int row=0; row<ROW_LENGTH; row++) {
        for (int col=0; col<COLUMN_LENGTH; col++) {
            printf("%d ", puzzle[row*ROW_LENGTH+col]);
        }
        printf("\n");
    }
}

bool check_index_is_clue(int index, int* clue_indices, int num_clues) {
    for (int i=0; i<num_clues; i++) {
        if (clue_indices[i] > index) {
            return false;
        } else if (clue_indices[i] == index) {
            return true;
        }
    }
    return false;
}

void set_guess_indices(int* guess_indices, int num_guesses, int* clue_indices, int num_clues) {
    int index = 0;
    for (int i=0; i<num_guesses; i++) {
        if (!check_index_is_clue(i, clue_indices, num_clues)) {
            guess_indices[index] = i;
            index++;
        }
    }
}

bool solve_puzzle(int* guess_indices, int num_guesses, int* puzzle, int num_clues, int* clue_indices) {

    int curr = 0;
    bool moved_back = false;
    int max_iter = 1000000;
    while (max_iter >= 0) {

        int* guess = puzzle+guess_indices[curr];
        *guess = (*guess==0) ? 1 : *guess;

        printf("curr=%d, guess=%d\n",curr,*guess);

        if (*guess == 9) {
            if (moved_back) {
                if (curr == 0) {
                    return false;
                } else {
                    *guess = 0;
                    curr--;
                }
            } else if (!check_guesses_are_valid(puzzle)) {
                if (curr == 0) {
                    return false;
                } else {
                    *guess = 0;
                    curr--;
                    moved_back = true;
                }
            } else {
                curr++;
            }
        } else {
            if (moved_back) {
                (*guess)++;
                moved_back = false;
            }
            printf("test\n");
            if (!check_guesses_are_valid(puzzle)) {
            printf("test2\n");
                (*guess)++;
            } else {
                if (curr >= num_guesses) {
                    return true;
                } else {
                    curr++;
                }
            }
        }

        max_iter--;
    }

    printf("max iterations reached\n");
    return false;

}

int main() {
    int puzzle[PUZZLE_LENGTH];
    int num_clues;
    int clue_indices[PUZZLE_LENGTH];
    read_clues(puzzle, clue_indices, &num_clues);

    print_board(puzzle);

    int num_guesses = PUZZLE_LENGTH-num_clues;
    int guess_indices[num_guesses];
    set_guess_indices(guess_indices, num_guesses, clue_indices, num_clues);

    if (solve_puzzle(guess_indices, num_guesses, puzzle, num_clues, clue_indices)) {
        print_board(puzzle);
    } else {
        printf("Puzzle is invalid (Can't be solved)\n");
    }

    return 0;
}