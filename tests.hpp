/*
Matt Olson
Alex Izydorczyk

Function declarations for unit-testing
*/
#pragma once
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "altproj.hpp"
#include "game.hpp"
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

// Unit testing code
// Based on http://stackoverflow.com/questions/29719999/
// testing-function-for-speed-performance-in-cpp

template<typename TimeT> //template as measurement size (seconds, milliseconds)
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...); //forward arguments to function
        auto duration = std::chrono::duration_cast< TimeT>
                (std::chrono::high_resolution_clock::now() - start);
        return duration.count();
    }
};

//Unit test
void unitTest(int size, int nobs, int ntimes, bool verbose);
