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

template<typename TimeT>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT>
                (std::chrono::high_resolution_clock::now() - start);
        return duration.count();
    }
};


void unitTest(int size, int nobs, int ntimes, bool verbose);