/*
Implement alternating projections (Douglas-Rachford splitting with non-convex
projections) to solve sudoku puzzle.  Note that this algorithm is NOT gauranteed to solve a puzzle, but seems to have a good empirical track record.
 */

#pragma once

#include <armadillo>
#include "solver.hpp"
using namespace arma;

//Board cube2mat(const cube& Q);

// RC1 - RC5 implement "reflection" operators that make up the iterations
// in the DR splitting procedure
cube RC1(const cube& Q);
cube RC2(const cube& Q);
cube RC3(const cube& Q);
cube RC4(const cube& Q);
//cube RC5(const cube&Q, const Board& board);

// The main solver
Board DR(const Board& board);


