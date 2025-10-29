#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Create a board with given dimensions
Board *create_board(uint32_t rows, uint32_t cols)
{
    // make array of row pointers
    // this malloc each of the cells
    Cell **cells = calloc(rows, sizeof(Cell *));
    if (cells == NULL)
        exit(1);
    for (uint32_t i = 0; i < rows; i++)
    {
        // make each row of cells
        cells[i] = NULL;
        cells[i] = calloc(cols, sizeof(Cell));
        if (cells[i] == NULL)
            exit(1);
        for (uint32_t j = 0; j < cols; j++)
        {
            // initialize each cell
            cells[i][j].alive = false;
            // cells[i][j].x = i;
            // cells[i][j].y = j;
        }
    }
    // create the board
    Board *b = malloc(sizeof(Board));
    b->rows = rows;
    b->cols = cols;
    b->cells = cells;

    return b;
}

// Free all memory associated with a board
void free_board(Board *board)
{
    // TODO need to free the memory!!!
    for (uint32_t i = 0; i < board->rows; i++)
    {
        // make each row of cells
        free(board->cells[i]);
    }
    free(board);
}

// Print the board to the console
void print_board(Board *board)
{

    for(uint32_t i=0;i<board->rows;i++){
        for(uint32_t j=0;j<board->cols;j++){
            if(board->cells[i][j].alive){
                printf("\x1b[33m█");
            }else{
                printf("\x1b[0m█");
            }
        }
        printf("\x1b[0m\n");
    }
}

// Update the board to the next generation (placeholder)
void update_board(Board *board, Board *boardCopy){ // board copy is the new board
    // TODO: Implement the Game of Life rules here

     for(uint32_t i=0;i<board->rows;i++){
        for(uint32_t j=0;j<board->cols;j++){
            int numAround = 0;
            // printf("%i %i %i %i\n", i, j, board->rows, board->cols);
            if(board->cells[i==0 ? (board->rows)-1 : i-1][j==0 ? (board->cols)-1 : j-1].alive){
                numAround++;
            }
            if(board->cells[i==0 ? board->rows-1 : i-1][j].alive){
               numAround++;
            }
            if(board->cells[i][j==0 ? board->cols-1 : j-1].alive){
               numAround++;
            }
            if(board->cells[(i+1) % board->rows][(j+1) % board->cols].alive){
               numAround++;
            }
            if(board->cells[(i+1) % board->rows][j].alive){
               numAround++;
            }
             if(board->cells[i][(j+1) % board->cols].alive){
               numAround++;
            }
             if(board->cells[(i+1) % board->rows][j==0 ? board->cols-1 : j-1].alive){
               numAround++;
            }
             if(board->cells[i==0 ? board->rows-1 : i-1][(j+1) % board->cols].alive){
               numAround++;
            }
            /**
            Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */
            if (board->cells[i][j].alive && numAround<2){
                boardCopy->cells[i][j].alive = false;
            }
            else if(!board->cells[i][j].alive && numAround==3 || board->cells[i][j].alive && (numAround==2 || numAround==3)){
                boardCopy->cells[i][j].alive = true;
            }else if (board->cells[i][j].alive && numAround >3) {
                boardCopy->cells[i][j].alive = false;
            } else {
                boardCopy->cells[i][j].alive = board->cells[i][j].alive;
            }

        }
    }
}

// Load a board from a file (placeholder)
Board *load_board_from_file(const char *filename)
{
    // format: uint32 (rows), uint32 (cols), cell, cell, cell, cell
    FILE *f = fopen(filename, "rb"); // open the file
    if (f == NULL)
        exit(1);

    uint32_t rows;
    uint32_t cols;

    if (fread(&rows, sizeof(rows), 1, f) == 0) // read number of rows
    {
        fclose(f);
        exit(1);
    }
    if (fread(&cols, sizeof(cols), 1, f) == 0) // read number of columns
    {
        fclose(f);
        exit(1);
    }

    Cell **cells = calloc(rows, sizeof(Cell *)); // allocate array of row pointers
    if (cells == NULL)
        exit(1);

    for (uint32_t i = 0; i < rows; i++) // populate each row
    {
        cells[i] = calloc(cols, sizeof(Cell));
        if (cells[i] == NULL)
            exit(1);
        for (uint32_t j = 0; j < cols; j++)
        {
            if (fread(&cells[i][j], sizeof(Cell), 1, f) == 0)
            {
                fclose(f);
                exit(1);
            }
        }
    }
    fclose(f);

    Board *b = malloc(sizeof(Board));
    b->rows = rows;
    b->cols = cols;
    b->cells = cells;

    // print_board(b);
    
    return b;
}

// Save a board to a file (placeholder)
void save_board_to_file(Board *board, const char *filename)
{
    // TODO: Write board dimensions and cell states to file
    
    FILE *f = fopen(filename, "wb"); // open file
    if (f == NULL)
        exit(1);

    uint32_t rows = board->rows; // get rows
    uint32_t cols = board->cols; // get cols

    if (fwrite(&rows, sizeof(uint32_t), 1, f) == 0) // write rows
        exit(1);
    if (fwrite(&cols, sizeof(uint32_t), 1, f) == 0) // write cols
        exit(1);
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            Cell c = board->cells[i][j]; // write each cell in order
            printf("%i,%i,%i\n",i,j,board->cells[i][j].alive);
            if (fwrite(&c, sizeof(Cell), 1, f) == 0)
            {
                fclose(f);
                exit(1);
            }
        }
    }
}
