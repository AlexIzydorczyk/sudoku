#include "solver.hpp"
#include <iostream>
#include <cassert>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;


// void assignValue(Board &board){
//     board(1,1) = 1;
// }



void Board::printPuzzle() {

    int blockSize = (int)sqrt(N);
    cout << blockSize << endl;

    for(int i = 0; i < N; i++){
        cout << "+---";
    }

    cout << "+" << endl;

    for(int i = 0; i < N; i++){
        cout << "| ";
        for(int j = 0; j < N; j++){

            if ((*this)(i,j) == 0){
                cout << ".";
            } else {
                cout << (*this)(i,j);
            }

            if ((j+1) % blockSize == 0){
                cout << " | ";
            } else {
                cout << "   ";
            }
        }

        cout << endl;
        if ((i+1) % blockSize == 0){
            for(int j = 0; j < N; j++)
                cout << "+---";
            cout << "+" << endl;
        }

    }

}

bool Board::checkPuzzle(){
    int val = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            val = (*this)(i,j);
            (*this)(i,j) = 0;
            if(!feasible(*this, i, j, val)){
                (*this)(i,j) = val;
                return false;
            }
            (*this)(i,j) = val;
        }
    return true;
}

// check to see if solved puzzle is correct...dumb implementation,
// just for debugging
// bool checkPuzzle(Board &b){
//     int val = 0;
//     int N = b.getSize();
//     for(int i = 0; i < N; i++)
//         for(int j = 0; j < N; j++){
//             val = b(i,j);
//             b(i,j) = 0;
//             if(!feasible(b, i, j, val)){
//                 b(i,j) = val;
//                 return false;
//             }
//             b(i,j) = val;
//         }
//     return true;
// }

/*
                                    My Versions
https://codemyroad.wordpress.com/2014/05/01/solving-sudoku-by-backtracking/
 */

// Helper function for solve: checks to see if candidate is feasible or not
bool feasible(Board &board, int row, int col, int val){
    int N = board.getSize();
    assert(row < N);
    assert(col < N);
    int blockSize = (int)sqrt(N);

    // See if used yet in row
    for(int j = 0; j < N; j++)
        if(board(row,j) == val) return false;

    // See if used yet in col
    for(int i = 0; i < N; i++)
        if(board(i,col) == val) return false;

    // coordinates of upper-left hand corner of block that (row,col) occupies
    int blockRow = blockSize*(row/blockSize);
    int blockCol = blockSize*(col/blockSize);

    // See if used yet in block
    for(int i = 0; i < blockSize; i++)
        for(int j = 0; j < blockSize; j++)
            if(board(blockRow + i,blockCol + j) == val)
                return false;

     return true;
}

// Solve partially filled board
bool solve(Board &board, int row, int col){
    // N: size of the board; note N must be a perfect square!
    int N = board.getSize();
    assert(N == pow(sqrt(N),2));

    // Check to see if we are at end of board
    if(row == N)
        return true;

    // Skip over values that have been filled in
    if(board(row,col) != 0){
        if(col == (N-1)){
            if(solve(board, row+1, 0)) return true;
        } else {
            if(solve(board, row, col+1)) return true;
        }
        return false;
    }

    // Try different values
    for(int val = 1; val <= N; val++){
        if(feasible(board, row, col, val)){
            board(row,col) = val;
            if(col == (N-1)){
                if(solve(board, row+1, 0)) return true;
            } else {
                if(solve(board, row, col+1)) return true;
            }
        }
    }

    // We failed to find a value that works
    board(row,col) = 0;
    return false;
}

// Generate board to solve (only generates N! possible boards, could easily
// be extended to get more, but this is simple enough for now)
Board generatePuzzle(int N, int nobs){
    // generate permutation of 1...n
    // fill diagonal of board with this permutation
    // solve board
    // randomly remove enough entries to only leave nobs observed
    assert(nobs <= N*N);
    Board board(N);

    int* perm = genPerm(N); // permuted 1...N

    // fill diag of board with perm
    for(int i = 0; i<N;i++)
        board(i,i) = perm[i];
    delete [] perm;

    // solve board
    bool isSolved = solve(board,0,0);
    assert(isSolved); // by filling diagonal, this should never be violated

    // remove N*N - nobs entries
    perm = genPerm(N*N);
    int x, y;
    for(int i = 0; i < (N*N - nobs); i++){
        x = (perm[i]-1)/N;
        y = (perm[i]-1)%N;
        board(x,y) = 0;
        board.assignImmutable(x,y, false);
    }

    delete [] perm;
    return board;

}

// http://www.cs.berkeley.edu/~jfc/cs174/lecs/lec2/lec2.pdf
// function to return a random permutation of integers 0,..,(N-1)
int* genPerm(int N){

    // initialize array [1,...,N]
    int *x = new int[N];
    for(int i = 0; i < N; i++)
        x[i] = i+1;

    // generate random permutation of [1,...,N]
    int rindex;
    int temp;
    for(int i = (N-1); i > 0; i--){
        rindex = rand()%(i+1);
        temp = x[i];
        x[i] = x[rindex];
        x[rindex] = temp;
    }

    return x;

}





