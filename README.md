# Game of Life Simulation

This project implements the Game of Life simulation, a cellular automaton devised by mathematician John Conway. The simulation consists of a grid of cells that can be either alive or dead, and the state of each cell changes based on a set of rules.

## Project Structure

```
gameoflife
├── src
│   ├── main.c       # Contains the main function and user interaction
│   ├── board.c      # Implements board manipulation functions
│   └── cell.c       # Implements functions related to the Cell structure
├── include
│   ├── board.h      # Header file for board-related structures and functions
│   └── cell.h       # Header file for Cell structure declarations
├── Makefile         # Build script for compiling the project
└── README.md        # Documentation for the project
```

## Compilation

To compile the project, navigate to the project directory and run:

```
make
```

This will generate an executable named `gameoflife`.

## Running the Simulation

After compiling, you can run the simulation with:

```
./gameoflife
```

You will be prompted to enter the filename of the initial board configuration and the number of generations to simulate. You can also choose to save the final board state to a file.

## Cleaning Up

To remove the compiled object files and the executable, run:

```
make clean
```

## License

This project is licensed under the MIT License.