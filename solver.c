#include <stdio.h>
#include <stdlib.h>

void read_clues(int* clue_info, int num_clues) {
    for (int i=0; i<num_clues; i++) {
        if (scanf("%d %d %d", &clue_info[i], &clue_info[i+1], &clue_info[i+2]) != 3) {
            printf("error reading the file\n");
            exit(1);
        }
    }
}

int main() {
    int num_clues;
    if (scanf("%d", &num_clues) != 1) {
        printf("error reading the file\n");
        return 1;
    }
    int clue_info[3*num_clues];
    read_clues(clue_info, num_clues);

    //Hello World - print input
    for (int i=0; i<num_clues; i++) {
        printf("%d %d %d\n", clue_info[i], clue_info[i+1], clue_info[i+2]);
    }

    return 0;
}