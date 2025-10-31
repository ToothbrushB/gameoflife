#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <time.h>
#include <unistd.h>

int main(void) {
    int generations;
    
    Board *board;
    Board *boardCopy;

    // prompt for the new board filename
    char filename[256];
    printf("Enter initial board filename (or press enter to create a new board): ");
    fgets(filename, sizeof(filename), stdin);
    if (filename[0] != '\n') {
        // Remove newline character
        for (int i = 0; filename[i]; i++) {
            if (filename[i] == '\n') filename[i] = '\0';
        }
        board = load_board_from_file(filename); // load board from file
        if (!board) {
            printf("Error loading board from file.\n");
            return 1;
        }
        boardCopy = create_board(board->rows, board->cols); // make the temporary board copy
    }   
    else // if no file given, generate a new board
    {
        int number;
        printf("Enter a number: ");  
        scanf("%i", &number);
        if (number >= 1) {
            board = create_board(number,number);  // create a board with given dimensions
            boardCopy = create_board(number,number);
        }
        else{ // create a board with default dimensions
            board = create_board(100,100); 
            boardCopy = create_board(100,100); 
        }
      
        srand(time(NULL)); 

        // fill with random
        for (int i = 0; i<number; i++)
        {
            for (int j = 0; j<number; j++)
            {
                board->cells[i][j].alive = rand() & 1;
            }
        }
        // make a glider

        // board->cells[0][1].alive = true;
        // board->cells[1][2].alive = true;
        // board->cells[2][0].alive = true;
        // board->cells[2][1].alive = true;
        // board->cells[2][2].alive = true;
    }

    printf("Enter number of generations to simulate: ");
    scanf("%d", &generations);


    // simulate specified number of generations
    for (int i = 0; i < generations; i++) {
        printf("Generation %d:\n", i);
        print_board(board);
        update_board(board, boardCopy); // boardCopy is the new board
        // // swap board and boardCopy
        Board *temp = boardCopy;
        boardCopy = board;
        board = temp;
        printf("\n");
    }

    // save the baord
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
    // free memory
    free_board(board);
    free_board(boardCopy);
    return 0;
}
