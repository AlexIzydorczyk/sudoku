#include <iostream>
#include <cstdlib>
#include<ctime>
#include "solver.hpp"
#include "altproj.hpp"
using namespace std;
using namespace arma;

int main(int argc, char **argv){
  
  srand(time(NULL));
  int n = 9;
  Board board = generatePuzzle(n,9);
  board.printPuzzle();
  cout << "\n==================================\n";

  Board matt = DR(board);
  if(!matt.checkPuzzle())
    cout << "DR Failed to Solve" << endl;
  else
    matt.printPuzzle();
  
  cout << "\n==================================\n";

  solve(board,0,0);
  board.printPuzzle();
  
}
