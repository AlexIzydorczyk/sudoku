/*
Matt Olson
Alex Izydorczyk

Main driver of Sudoku game
*/
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "altproj.hpp"
#include "game.hpp"
#include "tests.hpp"

using namespace std;

int main(int argc, char* argv[]){

    int seed; //random seed
    int gamesize = 9; // default size of game
    int nobs = 10; // default number of prefilled spaces
    int sim = 0; // number of simulation runs (if running speed tests)
    bool verbose = false; // print each simulation result for speed tests
    string method = "backtrace"; //choose solving method

    // Handle command line args
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--seed") || 
            (std::string(argv[i]) == "-s")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> seed))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                  std::cerr << "--seed option requires one argument." 
                            << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--gamesize") || 
            (std::string(argv[i]) == "-g")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> gamesize))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                  std::cerr << "--gamesize option requires one argument." 
                            << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--nobs") || 
            (std::string(argv[i]) == "-n")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> nobs))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                  std::cerr << "--nobs option requires one argument." 
                            << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Unittest") || 
            (std::string(argv[i]) == "-u")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> sim))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                  std::cerr << "--Unittest option requires one argument." 
                            << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Verbose") || 
            (std::string(argv[i]) == "-v")) {
            verbose = true;
        }

        if ((std::string(argv[i]) == "--RP") || 
            (std::string(argv[i]) == "-rp")) {
            method = "RP";
        }

    }

    srand(seed); // set random seed

    // Welcome message
    cout << "===========================================" << endl;
    cout << "============ Welcome to Sudoku! ===========" << endl;
    cout << "===========================================" << endl;

    // Play game or run simulations
    if (sim == 0){
        playGame(gamesize, nobs);
    } else {
        unitTest(gamesize, nobs, sim, verbose);
    }

    return 0;
}

