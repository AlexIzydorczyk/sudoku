#include <iostream>
#include <regex>
#include "solver.hpp"
#include "altproj.hpp"

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




void unitTest(){

    int total = 0;

    for (int i = 0; i < 30; ++i)
    {
        Board board = generatePuzzle(9,10);
        auto t = measure<std::chrono::nanoseconds>::execution(solve, board, 0, 0);
        cout << "Solved puzzle in " << t << " ns." << endl;
        total += t;
    }

    cout << "Average time: " << total/30 << endl;

}


int main(){
    //srand(time(NULL));
    srand(345);


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


    unitTest();

    string user_entry;

    Board board = generatePuzzle(4,2);
    // cout << "Welcome to Sudoku" << endl << endl;

    regex rgx("[0-9]{1,}");
    smatch match;

    int input_int[3];
    cout << "===========================================" << endl;
    cout << "============ Welcome to Sudoku! ===========" << endl;
    cout << "===========================================" << endl;
    do {
        board.printPuzzle();
        getline(cin, user_entry);

        if (user_entry == "Solve"){
            bool isSolved = solve(board,0,0);
            break;
        }

        int count = 0;
        for(sregex_iterator i = sregex_iterator(user_entry.begin(), user_entry.end(), rgx);
                                i != sregex_iterator();
                                ++i )
        {
            smatch m = *i;
            // cout << m.str() << " at position " << m.position() << '\n';

            input_int[count] = stoi(m.str());
            ++count;
        }

        if (feasible(board, input_int[0],input_int[1],input_int[2]) == true){
            if (board.checkImmutable(input_int[0],input_int[1]) == false){
                board.assignValue(input_int[0],input_int[1],input_int[2]);
            } else {
                cout << "You can't change that value!" << endl;
            }
        } else {
            cout << "Not feasible!" << endl;
        }

    } while (!board.checkPuzzle());

    // cout << checkPuzzle(board) << endl;
    // cout << "here is the puzzle" << endl;
    // cout << "===========================================" << endl << endl;

    board.printPuzzle();
    if (board.checkPuzzle()){
        cout << "The puzzle is solved!" << endl;
    } else {
        cout << "Could not solve puzzle" << endl;
    }
    // cout << "===========================================" << endl << endl;

    // cout << "===========================================" << endl << endl;
    // printPuzzle(board);
    // cout << "===========================================" << endl << endl;
    // bool isSolved = solve(board,0,0);

    // printPuzzle(board);



    return 0;
}

