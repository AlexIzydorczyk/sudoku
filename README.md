# sudoku
C++ sudoku game

## Program Use ##

Game can be started by compiling (with makefile) and running sudoku

1. Default action is to start interactive, 9x9 game
2. To fill in cell, enter the column number, row number, and value you want to enter (1 based). Separate with spaces, commas, or any other delimiter (besides an integer of course)
3. At any time, enter "Solve" to have the backtracer solve the game for you based on your current position.
4. If you've walked yoursel into an impossible configuration you will be prompted to first clear the board
5. Once solved, you will be asked if you want to play again

6. Run speed test / alternate game configurations using command flags below

Command line flags can be used to configure the game

-s --seed Set the random seed to replicate results
-u --Unittest Runs unit (speed) test with both solvers. Specify number of times to run
-g --gamesize Integer value to specify game size
				ie 9 for 9x9 game, 16 for 16x16 etc.
-n --nobs Specify number of pre-filled values to include (ie. immutable Sudoku cells)
-v --verbose Add flag with no argument for verbose output after every unit test. No effect if game played in interactive mode


Notes:

- Puzzles are always generating using a sort of reverse backtrace (ie. filling in diagonal using random permutation, solving puzzle, and then removing cells). This means that sometimes generating the puzzle takes longer than solving it (especially for big puzzles). The unit test times only the solver function
- During the class demo, in the speed test, our first puzzle took an order of magnitude longer to solve for the backtracer than the other 9 puzzles. Upon investigation, it turns out that this was likely because of the constant random seed (there is significant variability in time to solve puzzles for backtracer, the Alternating Projections approach seems to be less variable for given puzzle configuration)


Items to grade:

1. Game Logic/ Gameplay of the interactive game + command line tools/speed tests
2. Back-tracking solver (the "solve" function in solve.cpp)
3. Alternating projection solver (the "DR" function in altproj.cpp)

## Project Contributions ##

1. Matt:
    * implemented two Sudoku solvers: backtracking and alternating projections
    * implemented function to generate a Sudoku puzzle

2. Alex:
    * implements actual game-play and game-play logic (taking user input, printing/formatting to screen etc.)
    * implemented comamnd line flags and associated functions(ie. unit testing / timing functions)

## Notes on Building Project ##

Build reqiures the `armadillo` library.  You can download it from the website
http://arma.sourceforge.net/.

## References ##

1. Pseudo-code for backtracking algorithm
    - http://moritz.faui2k3.org/en/yasss

2. Idea to use Douglas-Rachford splitting to solve Sudoku
    - "Recent Results on Douglas–Rachford Methods for Combinatorial Optimization Problems"

3. Function timing code
	- http://stackoverflow.com/questions/29719999/testing-function-for-speed-performance-in-cpp

