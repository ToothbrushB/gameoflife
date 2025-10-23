#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <time.h>

int main(void) {
    int generations;
    
    Board *board;
    char filename[256];
    printf("Enter initial board filename: ");
    fgets(filename, sizeof(filename), stdin);
    if (filename[0] != '\n') {
        // Remove newline character
        for (int i = 0; filename[i]; i++) {
            if (filename[i] == '\n') filename[i] = '\0';
        }
        Board *board = load_board_from_file(filename);
        if (!board) {
            printf("Error loading board from file.\n");
            return 1;
        }
    }
    board = create_board(10,10);
    srand(time(NULL));
    // fill the board with random data for now
    for (int i = 0; i<10; i++)
    {
        for (int j = 0; j<10; j++) 
        {
            board->cells[i][j].alive = rand() & 1;
        }
    }

    printf("Enter number of generations to simulate: ");
    scanf("%d", &generations);

    for (int i = 0; i < generations; i++) {
        printf("Generation %d:\n", i);
        print_board(board);
        update_board(board);
        printf("\n");
    }

    char save_file[256];
    printf("Enter filename to save final board (or press enter to skip): ");
    getchar(); // consume leftover newline
    fgets(save_file, sizeof(save_file), stdin);
    if (save_file[0] != '\n') {
        // Remove newline character
        for (int i = 0; save_file[i]; i++) {
            if (save_file[i] == '\n') save_file[i] = '\0';
        }
        save_board_to_file(board, save_file);
    }
    free_board(board);
    return 0;
}
