#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>

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

       //matrix to track which values are causing infeasibility
        infeasible = new bool*[N];
        for(int i = 0; i < N; i++){
            infeasible[i] = new bool[N];
        }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                infeasible[i][j] = false;

    }

  //    Board(int n, int nobs);

    ~Board(){
        for(int i = 0; i < N; i++){
            delete [] grid[i];
        }
        delete [] grid;
    }

    void printPuzzle(); // print the puzzle to the screen
    bool checkPuzzle(); // Check if puzzle is complete
    void clearPuzzle(); //Clear mutables from puzzle
    bool inBounds(int val); //Check if value can exist in puzzle
    bool feasibleUser(int row, int col, int val);

    int& operator() (int x, int y){
        assert(x < N && y < N);
        return grid[x][y];
    }

    void assignValue(int x, int y, int val){
        (*this)(x,y) = val;
    }

    void assignImmutable(int x, int y, bool val){
        immutable[x][y] = val;
    }

    bool checkImmutable(int x, int y){
        return immutable[x][y];
    }

    bool isProblem(int x, int y){
        return infeasible[x][y];
    }

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

// void printPuzzle(Board &b);
bool feasible(Board &b, int row, int col, int val);
bool solve(Board &b, int row, int col);
// bool checkPuzzle(Board &b);
int* genPerm(int N);
Board generatePuzzle(int n, int nobs);

// void assignValue(Board &b);

