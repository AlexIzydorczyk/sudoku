#include <iostream>
#include <cstdlib>
#include "solver.hpp"
#include "altproj.hpp"
using namespace std;
using namespace arma;

int main(int argc, char **argv){
  
  srand(123);
  Board board = generatePuzzle(16,5);

  //  board.printPuzzle();

  //  cout << "\n==================================\n";
  Board matt = DR(board);
  //  matt.printPuzzle();

//  cout << "\n==================================\n";

  /*
  if(solve(board, 0, 0))
    board.printPuzzle();
  else
    cout << "FAIL" << endl;
  */
  
}
