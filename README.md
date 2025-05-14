# Sudoku Solver


## Installation

**Build from source:**
1. Clone the chess repository:
```sh
❯ git clone https://github.com/SachitoGH/sudoku_solver
```
2. Navigate to the project directory:
```sh
❯ cd sudoku_solver
```
3. Compile the code using GCC:
```sh
❯ gcc sudoku_solver.c -o sudoku_solver
```

## Usage

```sh
❯ ./sudoku_solver <sudoku_grid>
```
you can send the sudoku grid using different notation, an empty cell can be set using "0" or "." all other char than these and digit are ignored. The program fill the grid with given value, if given value lenght size < grid size the program assume the rest is empty.
Here is multiple way to send the same grid to the program:
```sh
./sudoku_solver  "0,0,7   ,0,0,0    ,4,0,6,
                 8,0,0   ,4,0,0    ,1,7,0,
                 0,0,0   ,3,0,0    ,9,0,5,
                 
                 0,0,0   ,7,0,5    ,0,0,8,
                 0,0,0   ,0,0,0    ,0,0,0,
                 4,0,0   ,2,0,8    ,0,0,0,
                 
                 7,0,4   ,0,0,3    ,0,0,0,
                 0,5,2   ,0,0,1    ,0,0,9,
                 1,0,8   ,0,0,0    ,6,0,0"
./sudoku_solver 007000406800400170000300905000705008000000000400208000704003000052001009108000600
./sudoku_solver ..7...4.68..4..17....3..9.5...7.5..8........4..2.8...7.4..3....52..1..91.8...6..
```

## Features

- Possible to change the grid size in the code.

