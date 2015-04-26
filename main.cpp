#include <iostream>
#include <regex>

#include <sstream>


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


void unitTest(int size, int nobs, int ntimes, bool verbose){

    int total = 0;

    for (int i = 0; i < ntimes; ++i)
    {
        Board board = generatePuzzle(size,nobs);
        auto t = measure<std::chrono::milliseconds>::execution(solve, board, 0, 0);
        if (verbose)
            cout << "Solved puzzle in " << t << " ns." << endl;
        total += t;
    }

    cout << "Average time: " << total/ntimes << endl;

}

void unitTest2(){

    int total = 0;

    for (int i = 0; i < 30; ++i)
    {
        Board board = generatePuzzle(16,150);
        auto t = measure<std::chrono::nanoseconds>::execution(DR, board);
        auto t2 = measure<std::chrono::nanoseconds>::execution(solve, board, 0, 0);

        cout << "Solved puzzle in " << t << " ns. other solved in " << t2 << endl;
        total += t;
    }

    cout << "Average time: " << total/30 << endl;

}

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

    Board board = generatePuzzle(size,nobs);

    regex rgx("[0-9]{1,}");
    smatch match;

    int input_int[3];
    do {
        board.printPuzzle();
        getline(cin, user_entry);

        if (user_entry == "Solve"){
            bool isSolved = solve(board,0,0);
            board.printPuzzle();
            break;
        }

        if (user_entry == "Clear"){
            board.clearPuzzle();
            continue;
        }

        int count = 0;
        for(sregex_iterator i = sregex_iterator(user_entry.begin(), user_entry.end(), rgx);
                                i != sregex_iterator();
                                ++i )
        {
            smatch m = *i;

            input_int[count] = stoi(m.str());
            ++count;
        }

        if (!board.inBounds(input_int[2])){
            cout << "Values entered must be between 1 and " << board.getSize() << endl;
            continue;
        }

        if (board.feasibleUser((input_int[1]-1),(input_int[0]-1),input_int[2])==true){
        // if (feasible(board, (input_int[1]-1),(input_int[0]-1),input_int[2]) == true){

            if (board.checkImmutable((input_int[1]-1),(input_int[0]-1)) == false){
                board.assignValue((input_int[1]-1),(input_int[0]-1),input_int[2]);
            } else {
                cout << "You can't change that value!" << endl;
            }

        } else {
            cout << "Not feasible!" << endl;
        }

    } while (!board.checkPuzzle());


    string user_response;

    if (board.checkPuzzle()){

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

int main(int argc, char* argv[]){

    int seed;
    int gamesize = 9;
    int nobs = 10;
    int sim = 0;
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--seed") || (std::string(argv[i]) == "-s")) {
            // cout << "got seed argument" << endl;
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!

                istringstream ss(argv[++i]);

                if (!(ss >> seed))
                    cerr << "Invalid number " << argv[i++] << endl;

                cout << seed << endl;
            } else { // Uh-oh, there was no argument to the destination option.
                  std::cerr << "--seed option requires one argument." << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--gamesize") || (std::string(argv[i]) == "-g")) {

            if (i + 1 < argc) {

                istringstream ss(argv[++i]);

                if (!(ss >> gamesize))
                    cerr << "Invalid number " << argv[i++] << endl;

                cout << seed << endl;
            } else {
                  std::cerr << "--gamesize option requires one argument." << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--nobs") || (std::string(argv[i]) == "-n")) {

            if (i + 1 < argc) {

                istringstream ss(argv[++i]);

                if (!(ss >> nobs))
                    cerr << "Invalid number " << argv[i++] << endl;

            } else {
                  std::cerr << "--nobs option requires one argument." << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Unittest") || (std::string(argv[i]) == "-u")) {

            if (i + 1 < argc) {

                istringstream ss(argv[++i]);

                if (!(ss >> sim))
                    cerr << "Invalid number " << argv[i++] << endl;

                cout << sim << endl;
            } else {
                  std::cerr << "--Unittest option requires one argument." << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Verbose") || (std::string(argv[i]) == "-v")) {
            verbose = true;
        }

    }

    srand(seed);


    cout << "===========================================" << endl;
    cout << "============ Welcome to Sudoku! ===========" << endl;
    cout << "===========================================" << endl;

    if (sim == 0){
        playGame(gamesize, nobs);
    } else {
        unitTest(gamesize, nobs, sim, verbose);
    }

    return 0;
}

