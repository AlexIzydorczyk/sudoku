/*
Implement alternating projections (Douglas-Rachford splitting with non-convex
projections) to solve sudoku puzzle.  Note that this algorithm is NOT gauranteed to solve a puzzle, but seems to have a good empirical track record.
 */

#pragma once
#include "solver.hpp"
#include <armadillo>

// RC1 - RC5 implement "reflection" operators that make up the iterations
// in the DR splitting procedure
arma::cube RC1(const arma::cube& Q);
arma::cube RC2(const arma::cube& Q);
arma::cube RC3(const arma::cube& Q);
arma::cube RC4(const arma::cube& Q);
arma::cube RC5(const arma::cube&Q,  Board& board);

// The main solver
Board DR(Board& board);


