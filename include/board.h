#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>


typedef struct {
    bool alive;
    // uint32_t x;
    // uint32_t y;
} Cell;

typedef struct {
    uint32_t rows;
    uint32_t cols;
    Cell **cells; // 2D dynamic array of Cells
} Board;

// Create a board with given dimensions
Board *create_board(uint32_t rows, uint32_t cols);

// Free all memory associated with a board
void free_board(Board *board);

// Print the board to the console
void print_board(Board *board);

// Update the board to the next generation
void update_board(Board *board, Board *boardCopy);

// Load a board from a file
Board *load_board_from_file(const char *filename);

// Save a board to a file
void save_board_to_file(Board *board, const char *filename);

#endif
