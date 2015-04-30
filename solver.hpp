/*
Matt Olson
Alex Izydorczyk

Implement Board class to hold state of sudoku game
*/
#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>

// board class to hold state of sudoku game (parts of board implementation
// borrowed from lecture code)
class Board{
    int N;
    int **grid;
    bool **immutable;
    bool **infeasible;

public:

    // To be implemented as matrix with single array
    Board(int _N) : N(_N){

        //matrix to keep track of values
        grid = new int*[N];
        for(int i = 0; i < N; i++){
            grid[i] = new int[N];
        }
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                grid[i][j] = 0;

        //matrix to track immutables
        immutable = new bool*[N];
        for(int i = 0; i < N; i++){
            immutable[i] = new bool[N];
        }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                immutable[i][j] = true;

        // matrix to track which values are causing infeasibilitsy
        // these are problem cells that will be
        // highlighted in red during gameplay
        infeasible = new bool*[N];
        for(int i = 0; i < N; i++){
            infeasible[i] = new bool[N];
        }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                infeasible[i][j] = false;

    }

    //destructor for board
    ~Board(){
        for(int i = 0; i < N; i++){
            delete [] grid[i];
        }
        delete [] grid;

        for(int i = 0; i < N; i++){
            delete [] immutable[i];
        }
        delete [] immutable;

        for(int i = 0; i < N; i++){
            delete [] infeasible[i];
        }
        delete [] infeasible;
    }

    void printPuzzle(); // print the puzzle to the screen
    bool checkPuzzle(); // Check if puzzle is complete
    void clearPuzzle(); //Clear mutables from puzzle
    bool inBounds(int val); //Check if value can exist in puzzle
    bool feasibleUser(int row, int col, int val);

    //Operator overload to assign value to cell
    int& operator() (int x, int y){
        assert(x < N && y < N);
        return grid[x][y];
    }

    //Operator overload to assign value to cell
    void assignValue(int x, int y, int val){
        (*this)(x,y) = val;
    }

    // toggle cell mutability
    void assignImmutable(int x, int y, bool val){
        immutable[x][y] = val;
    }

    //Checks if cell is ummutable (not changeable by solve/user)
    bool checkImmutable(int x, int y){
        return immutable[x][y];
    }

    //Keep track of "problem cells"
    //i.e. cells that cause infeasibility
    bool isProblem(int x, int y){
        return infeasible[x][y];
    }

    //Get size of game
    //ie. 9 for 9x9 game
    int getSize(){
        return N;
    }

    // function for debugging (kind of dumb, but need to change its
    // signature each time you change the puzzle size...but I suppose
    // in practice we will never need this)
    void setFromArray(int a[4][4]){
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                grid[i][j] = a[i][j];
    }

};

bool feasible(Board &b, int row, int col, int val);
bool solve(Board &b, int row, int col);
int* genPerm(int N);
Board generatePuzzle(int n, int nobs);


