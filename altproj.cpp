/*
Matt Olson
Alex Izydorczyk

Code to implement Douglas Rachford splitting to to solve sudoku puzzle
The idea to use DR to solve sudoku comes from the paper:
"Recent Results on Douglas–Rachford Methods for Combinatorial Optimization 
Problems"
*/

#include "altproj.hpp"
#include <iostream>
using namespace std;
using namespace arma;

// "Project" onto cubes that obey row constrains
cube RC1(const cube& Q){

  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int k = 0; k < n; k++){
      ix = k*n*n + n*seq + i;
      order = sort_index(Q.elem(ix), "descend");
      P(i,order(0),k) = 1;
    }
  return 2*P - Q;
}

// "Project" onto cubes that obey column constrains
cube RC2(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int j = 0; j < n; j++)
    for(int k = 0; k < n; k++){
      ix = k*n*n + j*n + seq;
      order = sort_index(Q.elem(ix), "descend");
      P(order(0),j,k) = 1;
    }
  return 2*P - Q;
}

// "Project" onto cubes that obey block constaints
cube RC3(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  // a handy tool for indexing later on
  int blockSize = sqrt(n);
  uvec mask(blockSize*blockSize);
  uvec ix(blockSize*blockSize), order;
  for(int i = 0; i < blockSize; i++)
    for(int j = 0; j < blockSize; j++)
      mask(i+blockSize*j) = i + n*j;

  // now do the projection
  for(int k = 0; k < n; k++)
    for(int i = 0; i < blockSize; i++)
      for(int j = 0; j < blockSize; j++){
        ix = mask + (i*blockSize + j*n*blockSize);
        order = sort_index(Q.elem(ix+k*n*n), "descend");
        P(ix(order(0)) + k*n*n) = 1;
      }
  return 2*P - Q;
}

// "Project" onto cubes that obey uniqueness constraints
cube RC4(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      ix = seq*n*n + j*n + i;
      order = sort_index(Q.elem(ix), "descend");
      P(i,j,order(0)) = 1;
    }
  return 2*P - Q;
}

// "Project" onto cubes that agree with the given sudoku configuration
cube RC5(const cube&Q, Board& board){
  int n = Q.n_rows;
  cube P = Q;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(board(i,j) != 0)
        P(i,j,board(i,j)-1) = 1;
  return 2*P - Q;

}

// converts a cube to a board by filling board(i,j) with the index
// of the largest index of Q(i,j,:)
Board cube2Board(const cube& Q){
  int n = Q.n_rows;
  Board solvedBoard(n);
  uword ix;
  vec A;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      A = Q.tube(i,j);
      A.max(ix);
      solvedBoard(i,j) = (int)ix + 1;
    }
  return solvedBoard;
}

// perform DR iterations to solve sudoku board
Board DR(Board& board){
  int n = board.getSize();
  double err;
   cube X1(n,n,n,fill::zeros),
     X2(n,n,n,fill::zeros),
     X3(n,n,n,fill::zeros),
     X4(n,n,n,fill::zeros),
     X5(n,n,n,fill::zeros),
     Z(n,n,n,fill::zeros);

   // do the DR iterations
   for(int i =0; i < MAXITS; i++){

     Z = (X1+X2+X3+X4+X5)/5;

     // check every 50 iterations if we have a solution
     if( i%50 == 0 ){
       err = accu(abs(Z - RC1(Z))) + accu(abs(Z - RC2(Z))) +
         accu(abs(Z - RC3(Z))) + accu(abs(Z - RC4(Z))) +
         accu(abs(Z - RC5(Z, board)));
       if(err < TOL){
         //cout << i << endl;
         return cube2Board(Z);
       }
     }

     // compute reflection operators
     X1 = X1/2 + RC1(2*Z-X1)/2;
     X2 = X2/2 + RC2(2*Z-X2)/2;
     X3 = X3/2 + RC3(2*Z-X3)/2;
     X4 = X4/2 + RC4(2*Z-X4)/2;
     X5 = X5/2 + RC5(2*Z-X5,board)/2;

   }

   return cube2Board(Z);

}
