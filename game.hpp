/*
Matt Olson
Alex Izydorczyk

Game-play function declarations
*/
#pragma once
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "altproj.hpp"

//main function to run the user interactive game
void playGame(int size, int nobs);
// helper function to prompt user to play again
void playAgainPrompt(int size, int nobs);

