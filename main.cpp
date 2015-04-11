#include <iostream>
using namespace std;

#include "solver.hpp"


int main(){
    //srand(time(NULL));
    srand(123);

    /*
    int puzzle[][9] = { {0, 0, 0,   7, 4, 0,    0, 0, 0},
                        {0, 0, 4,   3, 0, 0,    0, 0, 0},
                        {0, 0, 0,   0, 6, 0,    0, 0, 0},
        
                        {8, 0, 9,   1, 0, 0,    7, 3, 6},
                        {0, 4, 7,   6, 9, 0,    2, 1, 0},
                        {1, 0, 0,   8, 0, 0,    9, 0, 4},
        
                        {0, 1, 0,   0, 0, 0,    0, 0, 7},
                        {9, 0, 6,   0, 8, 0,    0, 0, 3},
                        {2, 0, 0,   4, 0, 3,    0, 0, 0}};
     */
    /*
    int puzzle[][9] = { {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0},

                        {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0},
        
                        {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0},
                        {0,0,0,    0,0,0,     0,0,0}};
     */
    
    int puzzle[4][4] = {{1,0,0,0},
                        {0,2,0,0},
                        {0,0,3,0},
                        {0,0,0,4}};
    //Board board(4);
    //board.setFromArray(puzzle);
    //bool isSolved = solve(board,0,0);
    //printPuzzle(board);
    
    Board board = generatePuzzle(9,10);
    printPuzzle(board);
    cout << "===========================================" << endl << endl;
    bool isSolved = solve(board,0,0);
    printPuzzle(board);
    
    
    return 0;
}

