/*
Matt Olson
Alex Izydorczyk

File to implement game play
*/

#include <iostream>
#include <regex>
#include <sstream>
#include "game.hpp"
#include "solver.hpp"
#include "altproj.hpp"
using namespace std;

void playGame(int size, int nobs);

void playAgainPrompt(int size, int nobs){
    string user_response;

    do{
        cout << "Would you like to play again? y/n" << endl;
        getline(cin, user_response);
    } while ((user_response != "y") && (user_response != "n"));

    if (user_response == "y"){
        playGame(size, nobs);
    } else {
        return;
    }
}

void playGame(int size, int nobs){

    string user_entry;
    bool solverSucces = false;
    Board board = generatePuzzle(size,nobs);
    regex rgx("[0-9]{1,}"); // For parsing user input
    smatch match;

    int input_int[3]; // Array for user input

    do {
        board.printPuzzle();
        getline(cin, user_entry);

        if (user_entry == "Solve"){
            solverSucces = solve(board,0,0);
            board.printPuzzle();
            break;
        }

        if (user_entry == "Clear"){
            board.clearPuzzle();
            continue;
        }

        int count = 0;
        for(sregex_iterator i = sregex_iterator(user_entry.begin(), 
                                                user_entry.end(), rgx);
                                i != sregex_iterator();
                                ++i )
        {
            smatch m = *i;
            input_int[count] = stoi(m.str());
            ++count;
        }

        if (!board.inBounds(input_int[2])){
            cout << "Values entered must be between 1 and " 
                 << board.getSize() << endl;
            continue;
        }

        if (board.feasibleUser((input_int[1]-1),(input_int[0]-1),
                               input_int[2])==true){

            if (board.checkImmutable((input_int[1]-1),
                                     (input_int[0]-1)) == false){
                board.assignValue((input_int[1]-1),(input_int[0]-1),
                                  input_int[2]);
            } else {
                cout << "You can't change that value!" << endl;
            }

        } else {
            cout << "Not feasible!" << endl;
        }

    } while (!board.checkPuzzle());

    string user_response;

    if (solverSucces){

        cout << "The puzzle is solved!" << endl;
        playAgainPrompt(size, nobs);

    } else {

        cout << "Could not solve puzzle based on pre-filled values" << endl;

        do {

            cout << "Would you like to clear and try to solve? y/n" << endl;
            getline(cin, user_response);

        } while ((user_response != "y") && (user_response != "n"));

        if (user_response == "y"){
            board.clearPuzzle();
            solve(board,0,0);
            board.printPuzzle();
            playAgainPrompt(size, nobs);
        }

    }


}
