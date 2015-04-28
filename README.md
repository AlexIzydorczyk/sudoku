# sudoku
C++ sudoku game

## Program Use ##

(Alex, fill in this part: how to run the game, etc.)

Items to grade:

1. gameplay of simple game
2. back-tracking solver (the "solve" function in solve.cpp)
3. alternating projection solver (the "DR" function in altproj.cpp)

## Project Contributions ##

(Alex, fill in anything I missed)

1. Matt:
    * implemented two Sudoku solvers: backtracking and alternating projections
    * implemented function to generate a Sudoku puzzle
    
2. Alex:
    * wrote code that implements actual game-play (taking user input, printing to screen, etc.)
    * wrote code to profile solvers

## Notes on Building Project ##

Build reqiures the `armadillo` library.  You can download it from the website
http://arma.sourceforge.net/.  

## References ##

1. Pseudo-code for backtracking algorithm
    - http://moritz.faui2k3.org/en/yasss

2. Idea to use Douglas-Rachford splitting to solve Sudoku
    - "Recent Results on Douglas–Rachford Methods for Combinatorial Optimization Problems"

