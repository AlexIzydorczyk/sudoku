#include <iostream>
#include <cstdlib>
#include<ctime>
#include "solver.hpp"
#include "altproj.hpp"
using namespace std;
using namespace arma;

int main(int argc, char **argv){
  
  srand(time(NULL));
  int n = 16;
  Board board = generatePuzzle(n,20);
  cout << "now!\n";
  //  board.printPuzzle();
  //cout << "\n==================================\n";

  Board matt = DR(board);

  bool solve = matt.checkPuzzle();
  if(!solve)
    cout << "DR Failed to Solve" << endl;
  else
    matt.printPuzzle();
  
  //cout << "\n==================================\n";

  //solve(board,0,0);
  //board.printPuzzle();
  
}
