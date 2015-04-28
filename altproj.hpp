/*
Matt Olson
Alex Izydorczyk

Function declarations for Douglas Rachford splitting to to solve sudoku puzzle
*/

#pragma once
#include "solver.hpp"
#include <armadillo>

#define TOL 1e-7
#define MAXITS 1e4

// RC1 - RC5 implement "reflection" operators that make up the iterations
// in the DR splitting procedure
arma::cube RC1(const arma::cube& Q);
arma::cube RC2(const arma::cube& Q);
arma::cube RC3(const arma::cube& Q);
arma::cube RC4(const arma::cube& Q);
arma::cube RC5(const arma::cube&Q,  Board& board);
Board cube2Board(const arma::cube& Q);
// Douglash Rachford splitting operator (i.e. solves puzzle)
Board DR(Board& board);
