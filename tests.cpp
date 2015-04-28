#include <iostream>
#include <regex>

#include <sstream>


#include "solver.hpp"
#include "altproj.hpp"
#include "game.hpp"
#include "tests.hpp"

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;


void unitTest(int size, int nobs, int ntimes, bool verbose){

    int total = 0;

    for (int i = 0; i < ntimes; ++i)
    {
        Board board = generatePuzzle(size,nobs);


        auto t = measure<std::chrono::nanoseconds>::execution(solve, board, 0, 0);
        auto t2 = measure<std::chrono::nanoseconds>::execution(DR, board);


        if (verbose)
            cout << "Backtrace solved in " << t << " ns." << " Random projections solved in " << t2 << " ns." << endl;
        total += t;
    }

    cout << "Average time: " << total/ntimes << endl;

}