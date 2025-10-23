#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Create a board with given dimensions
Board *create_board(uint32_t rows, uint32_t cols)
{
    // TODO Create the board
    Cell **cells = malloc(sizeof(Cell *) * rows);
    if (cells == NULL)
        exit(1);
    for (uint32_t i = 0; i < rows; i++)
    {
        cells[i] = malloc(sizeof(Cell) * cols);
        for (uint32_t j = 0; j < cols; j++)
        {
            cells[i][j].alive = false;
            cells[i][j].x = i;
            cells[i][j].y = j;
        }
    }
    Board *b = malloc(sizeof(Board));
    b->rows = rows;
    b->cols = cols;
    b->cells = cells;

    return b;
}

// Free all memory associated with a board
void free_board(Board *board)
{
    // TODO See the notes on freeing memory
    free(board->cells);
    free(board);
}

// Print the board to the console
void print_board(Board *board)
{

    for(uint32_t i=0;i<board->rows;i++){
        for(uint32_t j=0;j<board->cols;j++){
            if(board->cells[i][j].alive){
                printf("👾");
            }else{
                printf("💀");
            }
        }
        printf("\n");
    }
    // TODO
}

// Update the board to the next generation (placeholder)
void update_board(Board *board)
{
    // TODO: Implement the Game of Life rules here
}

// Load a board from a file (placeholder)
Board *load_board_from_file(const char *filename)
{
    // TODO: Read rows/cols and cell states from file
    // format: uint32 (rows), uint32 (cols), cell, cell, cell, cell
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        exit(1);

    uint32_t rows;
    uint32_t cols;

    if (fread(&rows, sizeof(rows), 1, f) == 0)
    {
        fclose(f);
        exit(1);
    }
    if (fread(&cols, sizeof(cols), 1, f) == 0)
    {
        fclose(f);
        exit(1);
    }

    Cell **cells = malloc(sizeof(Cell *) * rows);
    if (cells == NULL)
        exit(1);

    for (uint32_t i = 0; i < rows; i++)
    {
        cells[i] = malloc(sizeof(Cell) * cols);
        for (uint32_t j = 0; j < cols; j++)
        {
            if (fread(&cells[i][j], sizeof(Cell), 1, f) == 0)
            {
                fclose(f);
                exit(1);
            }
        }
    }

    Board *b = malloc(sizeof(Board));
    b->rows = rows;
    b->cols = cols;
    b->cells = cells;

    fclose(f);
    return NULL;
}

// Save a board to a file (placeholder)
void save_board_to_file(Board *board, const char *filename)
{
    // TODO: Write board dimensions and cell states to file
    FILE *f = fopen(filename, "w");
    if (f == NULL)
        exit(1);

    uint32_t rows = board->rows;
    uint32_t cols = board->cols;

    if (fwrite(&rows, sizeof(uint32_t), 1, f) == 0)
        exit(1);
    if (fwrite(&cols, sizeof(uint32_t), 1, f) == 0)
        exit(1);
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            Cell c = board->cells[i][j];
            if (fwrite(&c, sizeof(Cell), 1, f) == 0)
            {
                fclose(f);
                exit(1);
            }
        }
    }
}
